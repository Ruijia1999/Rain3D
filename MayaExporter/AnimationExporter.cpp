#include "AnimationExporter.h"
#include <maya/MItDag.h>
#include <maya/MFnDagNode.h>
#include <maya/MTypes.h>
#include <maya/MFnMesh.h>
#include <maya/MFloatPointArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFloatArray.h>
#include <maya/MPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MFloatMatrix.h>
#include <maya/MMatrix.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>

void Rain::AnimationExporter::readSkinCluster() {
	MItDependencyNodes jointIT(MFn::kJointCluster);
	// go over all joint clusters
	while (!jointIT.isDone())
	{
		int j = 1;
	}
}