#ifndef RAIN_MAYAANIMEXPORTER_H
#define RAIN_MAYAANIMEXPORTER_H

#include <maya/MPxFileTranslator.h>

// Class Definition
//=================

namespace Rain
{
	class MayaSkeletalAnimExporter final : public MPxFileTranslator
	{
		// Inherited Interface
		//====================

	public:

		// The writer method is what exports the file
		bool haveWriteMethod() const final { return true; }
		MStatus writer(const MFileObject& i_file, const MString& i_options, FileAccessMode i_mode) final;


		// You can choose what the default file extension of an exported mesh is
		MString defaultExtension() const final {
			return "hrjSkelAnim";
		}	


	public:

		// This function is used by Maya to create an instance of the exporter (see registerFileTranslator() in EntryPoint.cpp)
		static void* Create()
		{
			return new MayaSkeletalAnimExporter;
		}
	};
}

#endif	
