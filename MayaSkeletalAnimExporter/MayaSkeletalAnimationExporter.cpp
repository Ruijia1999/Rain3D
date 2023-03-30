#include "MayaSkeletalAnimationExporter.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <limits>
#include <stdlib.h>
#include <windows.h>
#include <map>
#include <maya/MItDag.h>
#include <maya/MDagPath.h>
#include <maya/MFloatVector.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFnMesh.h>
#include <maya/MFnIkJoint.h>
#include <maya/MFnSkinCluster.h>
#include <maya/MFnAnimCurve.h>
#include <maya/MFnAttribute.h>
#include <maya/MAnimUtil.h>
#include <maya/MGlobal.h>
#include <maya/MIntArray.h>
#include <maya/MItDag.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MItSelectionList.h>
#include <maya/MPlug.h>
#include <maya/MMatrix.h>
#include <maya/MDagPathArray.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MPointArray.h>
#include <maya/MSelectionList.h>
#include <maya/MQuaternion.h>
#include <maya/MItGeometry.h>
#include <maya/MGeometry.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <map>

// Joint Definition
//==================
struct Triangle {
	int vertexIndex[3];
};
struct Position {
	float position[3];
};
struct JointInfluence {
	int jointIndex;
	double weight;
	JointInfluence() {
		jointIndex = -1;
		weight = 0;
	}
};
struct Skincluster {
	JointInfluence influenceData[4];
	int influenceCount;

	Skincluster() {
		influenceCount = 0;
	}
};
struct Joint {
	MFnIkJoint* jointNode;
	std::string name;
	unsigned int layer;
	std::vector<int> children;
	MTransformationMatrix transformationMatrix;

	double S[3];
	MQuaternion RO;
	MQuaternion R;
	MQuaternion JO;
	double IS[3];
	MVector T;

	Joint() { 
		jointNode = nullptr;
		layer = 0;
	}
	Joint(MObject i_joint, int i_layer){
	
		jointNode = new MFnIkJoint(i_joint);
		MFnDependencyNode dpNode(jointNode->object());
		name = dpNode.name().asChar();
		layer = i_layer;

		jointNode->getScale(S);
		MTransformationMatrix S_MTMatrix;
		S_MTMatrix.setScale(S, MSpace::kTransform);
		MMatrix S_Matrix = S_MTMatrix.asMatrix();


		jointNode->getScaleOrientation(RO);
		MTransformationMatrix RO_MTMatrix;
		RO_MTMatrix.rotateBy(RO, MSpace::kTransform);
		MMatrix RO_Matrix = RO_MTMatrix.asMatrix();


		jointNode->getRotation(R);
		MTransformationMatrix R_MTMatrix;
		R_MTMatrix.rotateBy(R, MSpace::kTransform);
		MMatrix R_Matrix = R_MTMatrix.asMatrix();


		jointNode->getOrientation(JO);
		MTransformationMatrix JO_MTMatrix;
		JO_MTMatrix.rotateBy(JO, MSpace::kTransform);
		MMatrix JO_Matrix = JO_MTMatrix.asMatrix();

		
		MObject parent = jointNode->parent(0);
		if (strcmp( parent.apiTypeStr(),"kWorld")!=0) {
			MFnTransform(parent).getScale(IS);
		}
		else {
			IS[0] = 1; IS[1] = 1; IS[2] = 1;
		}
		MTransformationMatrix IS_MTMatrix;
		IS_MTMatrix.setScale(IS, MSpace::kTransform);
		MMatrix IS_Matrix = IS_MTMatrix.asMatrixInverse();


		T = jointNode->getTranslation(MSpace::kTransform);
		MTransformationMatrix T_MTMatrix;
		T_MTMatrix.setTranslation(T, MSpace::kTransform);
		MMatrix T_Matrix = T_MTMatrix.asMatrix();

		
		transformationMatrix = jointNode->transformation();// S_Matrix* RO_Matrix* R_Matrix* JO_Matrix* IS_Matrix* T_Matrix;
		
		return;
	}

	Joint& operator=(const Joint& i_joint) {
		if (&i_joint != this) {
			jointNode = i_joint.jointNode;
			layer = i_joint.layer;
			name = i_joint.name;
			children = i_joint.children;
			transformationMatrix = i_joint.transformationMatrix;
			for (int i = 0; i < 3; i++) {
				S[i] = i_joint.S[i];
			}
			RO = i_joint.RO;
			R = i_joint.R;
			JO = i_joint.JO;
			for (int i = 0; i < 3; i++) {
				IS[i] = i_joint.IS[i];
			}
			T = i_joint.T;
		}

		return *this;

	}
};




namespace {
	MStatus ProcessJoints(MSelectionList& list, Joint& rootJoint, Joint* jointDataArray, const std::map<std::string, int> jointIndexArray);
	MStatus ProcessSingleJoint(Joint& joint, Joint* jointDataArray, const std::map<std::string, int> jointIndexArray);
	MStatus ProcessJointIndex(std::ofstream& fileOut, int& dataCount, std::map<std::string, int>& jointIndexArray);
	MStatus ProcessSkincluster( std::ofstream& fileOut, Skincluster* skinClusterDataArray);
	MStatus ProcessSingleDagNode(const MDagPath& i_dagPath, std::ofstream& fileOut);
	MStatus WriteJoints(const int jointCount, const Joint* jointDataArray, std::ofstream& fileOut);
	MStatus WriteSingleJoint(const Joint& rootJoint, std::ofstream& fileOut);
	MStatus WriteSkinCluster(const int positionCount, const Skincluster* skinClusterDataArray, std::ofstream& fileOut);

}


// Inherited Interface
//====================

MStatus Rain::MayaSkeletalAnimExporter::writer(const MFileObject& i_file, const MString& i_options, FileAccessMode i_mode)
{
	MStatus status;
	const auto filePath = i_file.resolvedFullName();
	std::ofstream fout(filePath.asChar());

	
	Joint rootJoint;
	MSelectionList list;
	std::map<std::string, int> jointIndexArray;
	Skincluster* skinclusterDataArray = nullptr;
	Joint* jointDataArray = nullptr;
	int skinClusterDataCount = 0;
	if (i_mode == MPxFileTranslator::kExportActiveAccessMode)
	{
		//MeshData
		MGlobal::getActiveSelectionList(list);
		for (MItSelectionList i(list, MFn::kMesh); !i.isDone(); i.next())
		{

			MDagPath dagPath;
			i.getDagPath(dagPath);

			if (!(status = ProcessSingleDagNode(dagPath, fout)))
			{
				return status;
			}
		}
		for (MItSelectionList i(list, MFn::kCharacter); !i.isDone(); i.next())
		{

			MDagPath dagPath;
			i.getDagPath(dagPath);

			if (!(status = ProcessSingleDagNode(dagPath, fout)))
			{
				return status;
			}
		}
		

		//Joint
		if (!(status = ProcessJointIndex(fout, skinClusterDataCount, jointIndexArray)))
		{
			return status;
		}
		int j = jointIndexArray.size();
		jointDataArray = new Joint[jointIndexArray.size()];
		skinclusterDataArray = new Skincluster[skinClusterDataCount];
		if (!(status = ProcessJoints(list, rootJoint, jointDataArray, jointIndexArray)))
		{
			return status;
		}

		//SkinCluster
		if (!(status = ProcessSkincluster(fout, skinclusterDataArray)))
		{
			return status;
		}

		
		
		WriteSkinCluster(skinClusterDataCount, skinclusterDataArray, fout);
		WriteJoints(j, jointDataArray, fout);
		
	}
	else
	{
		MGlobal::displayError("Unexpected file access mode");
		return MStatus::kFailure;
	}



	fout.close();
	return MStatus::kSuccess;
}

//Helper
//-------------------------
namespace {
#pragma region Joint
	MStatus ProcessJoints(MSelectionList& list, Joint& rootJoint, Joint* jointDataArray, std::map<std::string, int> jointIndexArray)
	{
		MStatus status;

		// Iterate through each selected object
		MGlobal::getActiveSelectionList(list);
		for (MItSelectionList i(list, MFn::kJoint); !i.isDone(); i.next())
		{

			MObject object;
			i.getDependNode(object);
			rootJoint = Joint(object, 0);
			ProcessSingleJoint(rootJoint, jointDataArray, jointIndexArray);

		}


		return status;
	}
	MStatus ProcessSingleJoint(Joint& joint, Joint* jointDataArray, std::map<std::string, int> jointIndexArray) {



		int childCount = joint.jointNode->childCount();

		for (int i = 0; i < childCount; i++) {
			MObject nextJointObject = joint.jointNode->child(i);
			Joint nextJoint(nextJointObject, joint.layer + 1);

			ProcessSingleJoint(nextJoint, jointDataArray, jointIndexArray);
			if (jointIndexArray.find(nextJoint.name) != jointIndexArray.end()) {
				int index = jointIndexArray.find(nextJoint.name)->second;
				joint.children.push_back(index);
			}
			
		}
		
		if (jointIndexArray.find(joint.name) != jointIndexArray.end()) {
			int index = -1;
			index = jointIndexArray.find(joint.name)->second;
			jointDataArray[index] = joint;
		}
		else {
			return MStatus::kFailure;
		}
		
		return MStatus::kSuccess;
	}

	MStatus WriteJoints(const int jointCount, const Joint* jointDataArray, std::ofstream& fileOut) {
		
		fileOut << "\nSkeletonData = {\n";
		for (int i = 0; i < jointCount; i++) {
			WriteSingleJoint(jointDataArray[i], fileOut);
		}
		fileOut << "}\n";
		return MStatus::kSuccess;
	}
	MStatus WriteSingleJoint(const Joint& joint, std::ofstream& fileOut) {

		fileOut << "    {\n";
		//name
		fileOut << "        name = "<< joint.name << ",\n";

		//Index

		fileOut << "        index = " << 1 << ",\n";
		//transformation


		fileOut << "        transformation = {";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				fileOut << joint.transformationMatrix.asMatrix()[i][j];
				fileOut << ",";
			}
			
		}

		fileOut << "},\n";

		//Children

		fileOut << "        children = {";
		for (auto child : joint.children) {
			fileOut << child << ",";
		}
		fileOut << "},\n";

		fileOut << "    },\n";
		return MStatus::kSuccess;
	}
#pragma endregion

#pragma region Skincluster
	MStatus ProcessSkincluster(std::ofstream& fileOut, Skincluster* skinClusterDataArray) {

		MItDependencyNodes iter(MFn::kInvalid);
		for (; !iter.isDone(); iter.next()) {

			MObject object = iter.thisNode();
			if (object.apiType() == MFn::kSkinClusterFilter) {

				MFnSkinCluster skinCluster(object);
				MDagPathArray infs;
				MStatus stat;
				unsigned int nInfs = skinCluster.influenceObjects(infs, &stat);


				if (0 == nInfs) {
					stat = MS::kFailure;
					MGlobal::displayError("Error: No influence objects found.");
				}

				// loop through the geometries affected by this cluster
				//
				unsigned int nGeoms = skinCluster.numOutputConnections();
				for (unsigned int ii = 0; ii < nGeoms; ++ii) {
					unsigned int index = skinCluster.indexForOutputConnection(ii, &stat);
					// get the dag path of the ii'th geometry
					//
					MDagPath skinPath;
					stat = skinCluster.getPathAtIndex(index, skinPath);
					// iterate through the components of this geometry
					//
					MItGeometry gIter(skinPath);
					
	

					for ( /* nothing */; !gIter.isDone(); gIter.next()) {
						MObject comp = gIter.currentItem(&stat);

						// Get the weights for this vertex (one per influence object)
						//
						MDoubleArray wts;
						unsigned int infCount;
						stat = skinCluster.getWeights(skinPath, comp, wts, infCount);

						if (0 == infCount) {
							stat = MS::kFailure;
							MGlobal::displayError("Error: 0 influence objects.");
						}
						// Output the weight data for this vertex
						//
						
						for (unsigned int jj = 0; jj < infCount; ++jj) {
							
							if (wts[jj] > 1e-6) {
							
								if (skinClusterDataArray[gIter.index()].influenceCount < 4) {
									skinClusterDataArray[gIter.index()].influenceData[skinClusterDataArray[gIter.index()].influenceCount].jointIndex = jj;
									skinClusterDataArray[gIter.index()].influenceData[skinClusterDataArray[gIter.index()].influenceCount].weight = wts[jj];
									skinClusterDataArray[gIter.index()].influenceCount++;
								}
								else {
									for (int i = 0; i < 4; i++) {
										if (skinClusterDataArray[gIter.index()].influenceData[i].weight < wts[jj]) {
											skinClusterDataArray[gIter.index()].influenceData[i].jointIndex = jj;
											skinClusterDataArray[gIter.index()].influenceData[i].weight = wts[jj];
										}
									}
								}
								
								
							}
						}
					}
				}
			}
		}
		return MStatus::kSuccess;
	}
	MStatus ProcessJointIndex(std::ofstream& fileOut, int& dataCount, std::map<std::string, int>& jointIndexArray) {

		MItDependencyNodes iter(MFn::kInvalid);
		for (; !iter.isDone(); iter.next()) {

			MObject object = iter.thisNode();
			if (object.apiType() == MFn::kSkinClusterFilter) {

				MFnSkinCluster skinCluster(object);
				MDagPathArray infs;
				MStatus stat;
				unsigned int nInfs = skinCluster.influenceObjects(infs, &stat);


				if (0 == nInfs) {
					stat = MS::kFailure;
					MGlobal::displayError("Error: No influence objects found.");
				}

				// loop through the geometries affected by this cluster
				//
				unsigned int nGeoms = skinCluster.numOutputConnections();
				for (unsigned int ii = 0; ii < nGeoms; ++ii) {
					unsigned int index = skinCluster.indexForOutputConnection(ii, &stat);
					// get the dag path of the ii'th geometry
					//
					MDagPath skinPath;
					stat = skinCluster.getPathAtIndex(index, skinPath);
					// iterate through the components of this geometry
					//
					MItGeometry gIter(skinPath);
					// print out the path name of the skin, vertexCount & influenceCount
					//
			
					
					dataCount = gIter.count();
					// print out the influence objects
					//
					for (unsigned int kk = 0; kk < nInfs; ++kk) {
						
						jointIndexArray.insert(std::pair<std::string, int>(infs[kk].partialPathName().asChar(), kk));
					}
					

				}
			}
		}
		return MStatus::kSuccess;
	}

	MStatus WriteSkinCluster(const int positionCount, const Skincluster* skinClusterDataArray, std::ofstream& fileOut) {

		struct WriteData {
			int index;
			float weight;
		};
		WriteData* dataArray = new WriteData[positionCount*4];
		if (skinClusterDataArray == nullptr) {
			return MStatus::kFailure;
		}
		for (int i = 0; i < positionCount; i++) {
		
			for (int j = 0; j < 4; j++) {
				dataArray[i * 4 + j].index = skinClusterDataArray[i].influenceData[j].jointIndex;
				dataArray[i * 4 + j].weight = skinClusterDataArray[i].influenceData[j].weight;
			}
		}


		fileOut.write((char*)&positionCount, sizeof(positionCount));
		fileOut.write((char*)dataArray, sizeof(WriteData) * positionCount*4);
		return MStatus::kSuccess;
	}
#pragma endregion

#pragma region MeshData
	MStatus ProcessSingleDagNode(const MDagPath& i_dagPath, std::ofstream& fileOut)
	{
		// Get the mesh from the DAG path
		MFnMesh mesh(i_dagPath);
		MIntArray count;
		MIntArray ver;
		mesh.getVertices(count, ver);

		int j = count.length();
		int k = ver.length();
		MStatus status = MS::kSuccess;
		if (mesh.isIntermediateObject())
		{
			return MStatus::kSuccess;
		}

		// An instance ID identifies the specific node that should be processed by this function.
		unsigned int instanceId = 0;
		if (i_dagPath.isInstanced())
		{
			MStatus status;
			instanceId = i_dagPath.instanceNumber(&status);
			if (!status)
			{
				MGlobal::displayError(MString("Failed to get the DAG path's instance number: ") + status.errorString());
				return MStatus::kFailure;
			}
		}

		// Gather vertex and triangle information
		{

			const auto* const transformName = MFnDependencyNode(mesh.parent(instanceId)).name().asChar();

			MPointArray trianglePositions;
			MIntArray positionIndices;
			size_t polygonIndex = 0;
			std::vector< Triangle> indexArray;
			for (MItMeshPolygon i(mesh.object()); !i.isDone(); i.next(), ++polygonIndex)
			{
				if (i.hasValidTriangulation())
				{
					// Store information for each individual triangle in the polygon
					{
						const auto triangleCount = [&i]
						{
							int triangleCount = 0;
							i.numTriangles(triangleCount);
							return triangleCount;
						}();
						for (std::remove_const<decltype(triangleCount)>::type j = 0; j < triangleCount; ++j)
						{
							i.getTriangle(j, trianglePositions, positionIndices);
							if (static_cast<size_t>(positionIndices.length()) == 3)
							{
								Triangle triangle;
								for (unsigned int k = 0; k < 3; ++k)
								{
									triangle.vertexIndex[k] = positionIndices[k];
								}
								indexArray.push_back(triangle);
							}
							else
							{
								return MStatus::kFailure;
							}
						}
					}
				}
				else
				{
					MGlobal::displayError("This mesh has an invalid triangulation");
					return MStatus::kFailure;
				}

				
			}
			int length = indexArray.size();
			fileOut.write((char*)&length, sizeof(length));
			fileOut.write((char*)&indexArray[0], sizeof(Triangle)*length);
		}

		return MStatus::kSuccess;
	}
#pragma endregion



}

