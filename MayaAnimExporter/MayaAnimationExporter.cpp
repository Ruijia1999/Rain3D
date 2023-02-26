#include "MayaAnimationExporter.h"
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
#include <maya/MFnAnimCurve.h>
#include <maya/MFnAttribute.h>
#include <maya/MAnimUtil.h>
#include <maya/MGlobal.h>
#include <maya/MIntArray.h>
#include <maya/MItDag.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MItSelectionList.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MSelectionList.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Vertex Definition
//==================
namespace {
	MStatus ProcessAllAnimationObjects(MSelectionList& list, std::ofstream& fileOut);
	MStatus ProcessSelectedAnimationObjects(MSelectionList& list, std::ofstream& fileOut);
	MStatus ProcessAnimation(const MPlugArray& i_Object, std::ofstream& fileOut);
	MStatus WriteAnimation(const MSelectionList& list, std::ofstream& fineName);
	MStatus write(std::ofstream& animFile, const MDagPath& path);
	MStatus writeAnimatedPlugs(std::ofstream& animFile, const MPlugArray& animatedPlugs, const MString& nodeName, unsigned int depth, unsigned int childCount);
	MStatus writeAnimCurve(std::ofstream& animFile, const MObject* animCurvObj);
}


// Inherited Interface
//====================

MStatus Rain::MayaAnimExporter::writer(const MFileObject& i_file, const MString& i_options, FileAccessMode i_mode)
{
	MStatus status;
	const auto filePath = i_file.resolvedFullName();
	std::ofstream fout(filePath.asChar());
	MSelectionList list;
	// The user decides whether to export the entire scene or just a selection
	if (i_mode == MPxFileTranslator::kExportAccessMode)
	{
		if (!(status = ProcessAllAnimationObjects(list,fout)))
		{
			return status;
		}
	}
	else if (i_mode == MPxFileTranslator::kExportActiveAccessMode)
	{
		if (!(status = ProcessSelectedAnimationObjects(list, fout)))
		{
			return status;
		}
	}
	else
	{
		MGlobal::displayError("Unexpected file access mode");
		return MStatus::kFailure;
	}


	WriteAnimation(list, fout);
	fout.close();
	return MStatus::kSuccess;
}

//Helper
//-------------------------
namespace {
	MStatus ProcessAllAnimationObjects(MSelectionList& list, std::ofstream& fileOut)
	{
		MStatus status;

		for (MItDag i(MItDag::kDepthFirst, MFn::kMesh); !i.isDone(); i.next())
		{
			MDagPath dagPath;
			i.getPath(dagPath);
			list.add(dagPath);
			
		}
		MPlugArray animatedPlugs;
		MAnimUtil::findAnimatedPlugs(list, animatedPlugs);
		ProcessAnimation(animatedPlugs, fileOut);
		return status;
	}
	MStatus ProcessSelectedAnimationObjects(MSelectionList& list, std::ofstream& fileOut)
	{
		MStatus status;

		// Iterate through each selected object
		MGlobal::getActiveSelectionList(list);
		MPlugArray animatedPlugs;
		MAnimUtil::findAnimatedPlugs(list, animatedPlugs);
		ProcessAnimation(animatedPlugs, fileOut);
		return status;
	}
	MStatus ProcessAnimation(const MPlugArray& i_animatedPlugs, std::ofstream& fileOut)
	{

		unsigned int numPlugs = i_animatedPlugs.length();
		bool hasTime = false;
		double startTime = 0.0;
		double endTime = 0.0;
		bool hasUnitless = false;
		double startUnitless = 0.0;
		double endUnitless = 0.0;

		for (int i = 0; i < numPlugs; i++) {
			MPlug plug = i_animatedPlugs[i];
			MObjectArray animation;
			// Find the animation curve(s) that animate this plug
			//
			if (!MAnimUtil::findAnimation(plug, animation)) {
				continue;
			}
			unsigned int numCurves = animation.length();
			for (unsigned int j = 0; j < numCurves; j++) {
				MObject animCurveNode = animation[j];
				if (!animCurveNode.hasFn(MFn::kAnimCurve)) {
					continue;
				}
				MFnAnimCurve animCurve(animCurveNode);
				unsigned int numKeys = animCurve.numKeys();
				if (numKeys == 0) {
					continue;
				}
				if (animCurve.isUnitlessInput()) {
					if (!hasUnitless) {
						startUnitless = animCurve.unitlessInput(0);
						endUnitless = animCurve.unitlessInput(numKeys - 1);
						hasUnitless = true;
					}
					else {
						startUnitless = min(startUnitless, animCurve.unitlessInput(0));
						endUnitless = max(endUnitless, animCurve.unitlessInput(numKeys - 1));
					}
				}
				else {
					if (!hasTime) {
						startTime = animCurve.time(0).value();
						endTime = animCurve.time(numKeys - 1).value();
						hasTime = true;
					}
					else {
						startTime = min(startTime, animCurve.time(0).value());
						endTime = max(endTime, animCurve.time(numKeys - 1).value());
					}
				}
			}
		}
		fileOut << "startTime = "<<startTime << "\nendTime = " << endTime << "\n";
		return MStatus::kSuccess;
	}
	MStatus WriteAnimation(const MSelectionList& list, std::ofstream& fileOut) {
		unsigned int numObjects = list.length();
		for (int i = 0; i < numObjects; i++) {
			MDagPath path;
			MObject node;
			if (list.getDagPath(i, path) == MS::kSuccess) {
				write(fileOut, path);
			}
			else if (list.getDependNode(i, node) == MS::kSuccess) {
		
				
			}
		}
		return MStatus::kSuccess;
	}
	MStatus write(std::ofstream& animFile, const MDagPath& path)
	{
		animFile << "pipeline = {\n";
		// Walk through the dag breadth first
		MItDag dagIt(MItDag::kDepthFirst);
		dagIt.reset(path, MItDag::kDepthFirst);
		for (; !dagIt.isDone(); dagIt.next()) {
			MDagPath thisPath;
			if (dagIt.getPath(thisPath) != MS::kSuccess) {
				continue;
			}
			// Find the animated plugs for this object
			//
			MPlugArray animatedPlugs;
			MObject node = thisPath.node();
			MFnDependencyNode fnNode(node);
			MAnimUtil::findAnimatedPlugs(thisPath, animatedPlugs);
			unsigned int numPlugs = animatedPlugs.length();
			if (numPlugs == 0) {
				// If the object is not animated, then write out place holder
				// information
				//
				
			}
			else {
				// Otherwise write out each animation curve
				//
				

				writeAnimatedPlugs(animFile, animatedPlugs, fnNode.name(), dagIt.depth(), thisPath.childCount());
				
				
			}
			
		}
		animFile << "}";
		return MStatus::kSuccess;
	}
	MStatus writeAnimatedPlugs(std::ofstream& animFile, const MPlugArray& animatedPlugs, const MString& nodeName,unsigned int depth,unsigned int childCount){
		// Walk through each animated plug and write out the animation curve(s)
		unsigned int numPlugs = animatedPlugs.length();
		for (unsigned int i = 0; i < numPlugs; i++) {
			MPlug plug = animatedPlugs[i];
			MObjectArray animation;
			if (!MAnimUtil::findAnimation(plug, animation)) {
				continue;
			}
			// Write out the plugs' anim statement
			//
			// build up the full attribute name
			//
			MPlug attrPlug(plug);
			MObject attrObj = attrPlug.attribute();
			MFnAttribute fnAttr(attrObj);
			MString fullAttrName(fnAttr.name());
			attrPlug = attrPlug.parent();
			while (!attrPlug.isNull()) {
				attrObj = attrPlug.attribute();
				MFnAttribute fnAttr2(attrObj);
				fullAttrName = fnAttr2.name() + "." + fullAttrName;
				attrPlug = attrPlug.parent();
			}
			attrObj = plug.attribute();
			MFnAttribute fnLeafAttr(attrObj);
			animFile << "    {\n";
			animFile << "        name = \"" << fnLeafAttr.name().asChar() << "\",\n";
			unsigned int numCurves = animation.length();


			// Write out each animation curve that animates the plug
			//
			
			for (unsigned int j = 0; j < numCurves; j++) {
				MObject animCurveNode = animation[j];
				if (!animCurveNode.hasFn(MFn::kAnimCurve)) {
					continue;
				}
			
				writeAnimCurve(animFile, &animCurveNode);
				
			}
			
			animFile << "    },\n";
		}
		return MStatus::kSuccess;
	}

	MStatus writeAnimCurve(std::ofstream& animFile, const MObject* animCurveObj) {
		MStatus status = MS::kSuccess;
		if (NULL == animCurveObj || animCurveObj->isNull() || !animFile) {
			return status;
		}
		MFnAnimCurve animCurve(*animCurveObj, &status);
		if (MS::kSuccess != status) {
			std::cerr << "Error: Could not read the anim curve for export." << std::endl;
			return status;
		}

		double conversion = 1.0;
		MString unitName;
		MFnAnimCurve::AnimCurveType type = animCurve.animCurveType();
		switch (type) {
		case MFnAnimCurve::kAnimCurveTA:
		case MFnAnimCurve::kAnimCurveUA:
			/*animUnitNames::setToShortName(angularUnit, unitName);
			if (verboseUnits) animFile << unitName;
			{
				MAngle angle(1.0);
				conversion = angle.as(angularUnit);
			}*/
			break;
		case MFnAnimCurve::kAnimCurveTL:
		case MFnAnimCurve::kAnimCurveUL:
		/*	animUnitNames::setToShortName(linearUnit, unitName);
			if (verboseUnits) animFile << unitName;
			{
				MDistance distance(1.0);
				conversion = distance.as(linearUnit);
			}*/
			break;
		case MFnAnimCurve::kAnimCurveTT:
		case MFnAnimCurve::kAnimCurveUT:
			/*animUnitNames::setToShortName(timeUnit, unitName);
			if (verboseUnits) animFile << unitName;*/
			break;
		default:
			//if (verboseUnits) animFile << kUnitlessString;
			break;
		}
		//if (verboseUnits) animFile << kSemiColonChar << std::endl;
		//if (verboseUnits) {
		//	MString angleUnitName;
		//	animUnitNames::setToShortName(angularUnit, angleUnitName);
		//	animFile << kTwoSpace << kTanAngleUnitString <<
		//		kSpaceChar << angleUnitName << kSemiColonChar << std::endl;
		//}
		//animFile << kTwoSpace << kPreInfinityString << kSpaceChar <<
		//	infinityTypeAsWord(animCurve.preInfinityType()) <<
		//	kSemiColonChar << std::endl;
		//animFile << kTwoSpace << kPostInfinityString << kSpaceChar <<
		//	infinityTypeAsWord(animCurve.postInfinityType()) <<
		//	kSemiColonChar << std::endl;
		//animFile << kTwoSpace << kKeysString << kSpaceChar << kBraceLeftChar << std::endl;
		// And then write out each keyframe
		//
	
		unsigned numKeys = animCurve.numKeyframes();
		animFile << "        frameCount = " << numKeys << ",\n";
		animFile << "        frames = {\n           ";
		for (unsigned i = 0; i < numKeys; i++) {
			animFile << "{";
			if (animCurve.isUnitlessInput()) {
				animFile << animCurve.unitlessInput(i);
			}
			else {
				animFile << animCurve.time(i).value();
			}
			animFile << "," << (conversion * animCurve.value(i));

			double slope;
			double intercept;
			//in tangent
			//animCurve.getTangent(i, slope, intercept, true);
			//animFile << " " << slope;
			//animFile << " " << intercept;
			//out tangent
			//animCurve.getTangent(i, slope, intercept, false);
			//animFile << " " << slope;
			//animFile << " " << intercept;
			//animCurve.getTangent(i, angle, weight, false);
			//animFile << " " << angle.as(MAngle::uiUnit());
			//animFile << " " << weight;
			
			animFile << "},";
		}
		animFile << "\n        },\n";
		//animFile << kTwoSpace << kBraceRightChar << std::endl;
		//animFile << kBraceRightChar << std::endl;
		return MStatus::kSuccess;
	}
}

