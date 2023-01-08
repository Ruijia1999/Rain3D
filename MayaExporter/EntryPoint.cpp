#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MSimple.h>

#include "MayaExporter.h"
namespace
{
	// This will be displayed in Maya's dropdown list of available export formats
	constexpr auto* const s_pluginName = "Ruijia Huang's Mesh Format"
#ifdef _DEBUG
		" -- DEBUG"
#endif
		;
}

__declspec(dllexport) MStatus initializePlugin(MObject io_object) {
	// Create a plugin function set
	MFnPlugin plugin(io_object);

	// Register the exporter
	MStatus status;
	{
		constexpr auto* const noIcon = "none";
		if (!(status = plugin.registerFileTranslator(s_pluginName, noIcon,
			// This function is what Maya should call to create a new instance of the mesh exporter
			Rain::MayaExporter::Create)))
		{
			MGlobal::displayError(MString("Failed to register mesh exporter: ") + status.errorString());
		}
	}
	return MS::kSuccess;
}

__declspec(dllexport) MStatus uninitializePlugin(MObject io_object){
	
	// Create a plugin function set
	MFnPlugin plugin(io_object);

	// Unregister the exporter
	MStatus status;
	{
		if (!(status = plugin.deregisterFileTranslator(s_pluginName)))
		{
			MGlobal::displayError(MString("Failed to deregister mesh exporter: ") + status.errorString());
		}
	}
	return MS::kSuccess;
}