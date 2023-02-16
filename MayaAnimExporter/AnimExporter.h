#ifndef _animExportUtil
#define _animExportUtil
// *****************************************************************************
// INCLUDED HEADER FILES
#include <maya/MPxFileTranslator.h>
#include <maya/MFStream.h>
// *****************************************************************************
// DECLARATIONS
class MDagPath;
class MObject;
// *****************************************************************************
// CLASS DECLARATION (AnimExporter)
// The AnimExporter command object
//
class AnimExporter : public MPxFileTranslator {
public:
    AnimExporter();
    virtual ~AnimExporter();
    virtual MStatus     writer(
        const MFileObject& file,
        const MString& optionsString,
        FileAccessMode mode
    );
protected:
    void                write(ofstream& animFile, const MDagPath& path);
    void                write(ofstream& animFile, const MObject& node);
    void                writeAnimatedPlugs(
        ofstream& animFile,
        const MPlugArray& animatedPlugs,
        const MString& nodeName,
        unsigned int depth,
        unsigned int childCount
    );
public:
    virtual bool        haveWriteMethod() const;
    virtual MString     defaultExtension() const;
    virtual MFileKind   identifyFile(
        const MFileObject&,
        const char* buffer,
        short size
    ) const;
    static void* creator();
};
#endif