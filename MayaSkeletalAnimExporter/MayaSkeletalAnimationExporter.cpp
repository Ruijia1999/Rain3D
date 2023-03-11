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

// Joint Definition
//==================

struct Joint {
	MFnIkJoint* jointNode;
	std::string name;
	unsigned int layer;
	std::vector<Joint> children;
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

struct Skincluster {

};



namespace {
	MStatus ProcessJoints(MSelectionList& list, Joint& rootJoint);
	MStatus ProcessSingleJoint(Joint& joint);
	MStatus ProcessSkincluster( std::ofstream& fileOut);
	MStatus ProcessSingleSkincluster(std::ofstream& fileOut);
	MStatus WriteJoints(const Joint& rootJoint, std::ofstream& fileOut);
	MStatus WriteSingleJoint(const Joint& rootJoint, std::ofstream& fileOut);
}


// Inherited Interface
//====================

MStatus Rain::MayaSkeletalAnimExporter::writer(const MFileObject& i_file, const MString& i_options, FileAccessMode i_mode)
{
	MStatus status;
	const auto filePath = i_file.resolvedFullName();
	std::ofstream fout(filePath.asChar());

	//Skeleton
	Joint rootJoint;
	MSelectionList list;
	if (i_mode == MPxFileTranslator::kExportActiveAccessMode)
	{
		if (!(status = ProcessJoints(list, rootJoint)))
		{
			return status;
		}
		if (!(status = ProcessSkincluster( fout)))
		{
			return status;
		}
	}
	else
	{
		MGlobal::displayError("Unexpected file access mode");
		return MStatus::kFailure;
	}

	WriteJoints(rootJoint, fout);


	//Skincluster

	fout.close();
	return MStatus::kSuccess;
}

//Helper
//-------------------------
namespace {
	
	MStatus ProcessJoints(MSelectionList& list, Joint& rootJoint)
	{
		MStatus status;

		// Iterate through each selected object
		MGlobal::getActiveSelectionList(list);
		for (MItSelectionList i(list, MFn::kJoint); !i.isDone(); i.next())
		{

			MObject object;
			i.getDependNode(object);
			rootJoint = Joint(object,0);
			ProcessSingleJoint(rootJoint);
		
		}

		
		return status;
	}
	MStatus ProcessSingleJoint(Joint& joint) {
		
	

		int childCount = joint.jointNode->childCount();
	
		for (int i = 0; i < childCount; i++) {
			MObject nextJointObject = joint.jointNode->child(i);
			Joint nextJoint(nextJointObject,joint.layer+1);
			
			ProcessSingleJoint(nextJoint);
			joint.children.push_back(nextJoint);
		}
		return MStatus::kSuccess;
	}
	MStatus ProcessSkincluster(std::ofstream& fileOut) {
	
		MItDependencyNodes iter(MFn::kInvalid);
		for (; !iter.isDone(); iter.next()){
	
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
					fileOut << skinPath.partialPathName().asChar() << " "<<gIter.count()<<" " << nInfs << "\n";

					// print out the influence objects
					//
					for (unsigned int kk = 0; kk < nInfs; ++kk) {
						fileOut << infs[kk].partialPathName().asChar() << " ";
					}
					fileOut << "\n";

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
						fileOut << gIter.index() << " ";
						
						for (unsigned int jj = 0; jj < infCount; ++jj) {
							fileOut << wts[jj] << " ";
						}
						fileOut << "\n";
					}
				}
			}
		}
		return MStatus::kSuccess;
	}
	MStatus WriteJoints(const Joint& rootJoint, std::ofstream& fileOut) {
		WriteSingleJoint(rootJoint, fileOut);
		return MStatus::kSuccess;
	}
	MStatus WriteSingleJoint(const Joint& joint, std::ofstream& fileOut) {
		//name
		for (int i = 0; i < joint.layer * 4; i++) {
			fileOut << " ";
		}
		fileOut << joint.name << "    ";
		//transformation
		for (int i = 0; i < 4; i++) {
			fileOut << "{";
			for (int j = 0; j < 4; j++) {
				fileOut << joint.transformationMatrix.asMatrix()[i][j];
				fileOut << ",";
			}
			fileOut << "},";
		}
		fileOut << "\n";

		for (auto child : joint.children) {
			WriteSingleJoint(child, fileOut);
		}
		return MStatus::kSuccess;
	}
}

