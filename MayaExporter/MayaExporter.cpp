#include "MayaExporter.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <limits>
#include <map>
#include <maya/MDagPath.h>
#include <maya/MFloatVector.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFnMesh.h>
#include <maya/MFnIkJoint.h>
#include <maya/MFnAnimCurve.h>
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

namespace
{
	// This is the vertex struct that will hold the Maya data.
	// Note that this is independent of the Rain::Graphics::VertexFormats::sMesh struct
	// that is used by the engine to store geometry data!
	// This struct is used to store Maya-specific vertex information
	// and then output it to the human-readable source mesh file.
	struct sVertex_maya
	{
		// Position
		const float x, y, z;
		// Normal
		const float nx, ny, nz;
		// Tangent
		const float tx, ty, tz;
		// Bitangent
		const float btx, bty, btz;
		// Texture coordinates
		const float u, v;
		// Color
		const float r, g, b, a;

		sVertex_maya(const MPoint& i_position, const MFloatVector& i_normal,
			const MFloatVector& i_tangent, const MFloatVector& i_bitangent,
			const float i_texcoordU, const float i_texcoordV,
			const MColor& i_vertexColor)
			:
			x(static_cast<float>(i_position.x)), y(static_cast<float>(i_position.y)), z(static_cast<float>(i_position.z)),
			nx(i_normal.x), ny(i_normal.y), nz(i_normal.z),
			tx(i_tangent.x), ty(i_tangent.y), tz(i_tangent.z),
			btx(i_bitangent.x), bty(i_bitangent.y), btz(i_bitangent.z),
			u(i_texcoordU), v(i_texcoordV),
			r(i_vertexColor.r), g(i_vertexColor.g), b(i_vertexColor.b), a(i_vertexColor.a)
		{

		}
		bool operator==(const sVertex_maya& i_vertex) {
			if (x != i_vertex.x || y != i_vertex.y || z != i_vertex.z) {
				return false;
			}
			if (nx != i_vertex.nx || ny != i_vertex.ny || nz != i_vertex.nz) {
				return false;
			}
			if (tx != i_vertex.tx || ty != i_vertex.ty || tz != i_vertex.tz) {
				return false;
			}
			return true;
		}
		bool operator<(const sVertex_maya& i_vertex) const {
			if (x >= i_vertex.x ) {
				return false;
			}
			return true;
		}
	};

	// This stores any information associated with a vertex that is necessary to export the mesh.
	// Most of the information is in the sVertex_maya itself,
	// but there are a few other things needed during processing that shouldn't be exported.
	struct sVertexInfo
	{
		const sVertex_maya vertex;

		// This unique key is calculated in order to decide whether a new vertex should be created or not,
		// and that calculated key is assigned to the vertex so that it can be sorted uniquely
		const std::string uniqueKey;

		sVertexInfo(const MPoint& i_position, const MFloatVector& i_normal,
			const MFloatVector& i_tangent, const MFloatVector& i_bitangent,
			const float i_texcoordU, const float i_texcoordV,
			const MColor& i_vertexColor,
			const std::string& i_uniqueKey)
			:
			vertex(i_position, i_normal, i_tangent, i_bitangent, i_texcoordU, i_texcoordV, i_vertexColor),
			uniqueKey(i_uniqueKey)
		{

		}
	};

}

// Static Data
//============

namespace
{
	constexpr size_t s_vertexCountPerTriangle = 3;

	struct sTriangle
	{
		std::string vertexKeys[s_vertexCountPerTriangle];

		static bool CompareTriangles(const sTriangle& i_lhs, const sTriangle& i_rhs)
		{
			for (size_t i = 0; i < s_vertexCountPerTriangle; ++i)
			{
				if (i_lhs.vertexKeys[i] != i_rhs.vertexKeys[i])
				{
					return i_lhs.vertexKeys[i] < i_rhs.vertexKeys[i];
				}
			}
	
			return false;
		}
	};

	
}

// Helper Declarations
//====================

namespace
{
	std::string CreateUniqueVertexKey(const int i_positionIndex, const int i_normalIndex, const int i_tangentIndex,
		const int i_texcoordIndex, const int i_vertexColorIndex, const char* i_transformName);
	MStatus FillVertexAndIndexArrays(const std::map<std::string, sVertexInfo>& i_uniqueVertices,
		std::vector<sTriangle>& io_triangles,
		std::vector<sVertexInfo>& o_vertexArray, std::vector<size_t>& o_indexArray);
	MStatus ProcessAllObjects(std::map<std::string, sVertexInfo>& o_uniqueVertices, std::vector<sTriangle>& o_triangles);
	MStatus ProcessSelectedObjects(std::map<std::string, sVertexInfo>& o_uniqueVertices, std::vector<sTriangle>& o_triangles);
	MStatus ProcessSingleDagNode(const MDagPath& i_dagPath,std::map<std::string, sVertexInfo>& io_uniqueVertices, std::vector<sTriangle>& io_triangles);
	MStatus WriteMeshToFile(const MString& i_fileName, const std::vector<sVertexInfo>& i_vertexArray, const std::vector<size_t>& i_indexArray);
}

// Inherited Interface
//====================

MStatus Rain::MayaExporter::writer(const MFileObject& i_file, const MString& i_options, FileAccessMode i_mode)
{
	MStatus status;

	// Calculate the vertex and index data
	std::vector<sVertexInfo> vertexArray;
	std::vector<size_t> indexArray;
	
	{
		// Gather the vertex and triangle information
		std::map<std::string, sVertexInfo> uniqueVertices;
		std::vector<sTriangle> triangles;
		{
			// The user decides whether to export the entire scene or just a selection
			if (i_mode == MPxFileTranslator::kExportAccessMode)
			{
				if (!(status = ProcessAllObjects(uniqueVertices, triangles)))
				{
					return status;
				}
			}
			else if (i_mode == MPxFileTranslator::kExportActiveAccessMode)
			{
				if (!(status = ProcessSelectedObjects(uniqueVertices, triangles)))
				{
					return status;
				}
			}
			else
			{
				MGlobal::displayError("Unexpected file access mode");
				return MStatus::kFailure;
			}
		}
		// Convert the mesh information to vertex and index arrays
		if (!(status = FillVertexAndIndexArrays(uniqueVertices, triangles, vertexArray, indexArray)))
		{
			return status;
		}
	}

	// Write the mesh data to the requested file
	{
		const auto filePath = i_file.resolvedFullName();
		return WriteMeshToFile(filePath, vertexArray, indexArray);
	}
}

// Helper Definitions
//===================

namespace
{
	std::string CreateUniqueVertexKey(const int i_positionIndex, const int i_normalIndex, const int i_tangentIndex,
		const int i_texcoordIndex, const int i_vertexColorIndex, const char* i_transformName)
	{
		std::ostringstream vertexKey;
		vertexKey << i_positionIndex << "_" << i_normalIndex 
			<< "_" << i_texcoordIndex << "_" << i_vertexColorIndex;
		if (i_transformName)
		{
			vertexKey << "_" << i_transformName;
		}
		return vertexKey.str();
	}

	MStatus FillVertexAndIndexArrays(const std::map<std::string, sVertexInfo>& i_uniqueVertices,
		std::vector<sTriangle>& io_triangles,
		std::vector<sVertexInfo>& o_vertexArray, std::vector<size_t>& o_indexArray)
	{
		MStatus status;


		// Fill the vertex buffer with the vertices
		// and create a map from the unique key to the assigned index in the vertex buffer
		std::map<std::string, size_t> vertexKeyToIndexMap;
		{
			// Create a reverse map with a custom sorting order for the vertices
			struct CompareVertices
			{
				bool operator()(const sVertexInfo& i_lhs, const sVertexInfo& i_rhs) const
				{
					
						// If two vertices use the same shading group the order doesn't matter
					return i_lhs.uniqueKey < i_rhs.uniqueKey;
					
				}
			};
			std::map<sVertexInfo, std::string, CompareVertices> sortedVertices;
			for (auto i = std::as_const(i_uniqueVertices).begin(); i != i_uniqueVertices.end(); ++i)
			{
				sortedVertices.insert(std::make_pair(i->second, i->first));
			}
			// Assign the sorted vertices to the buffer
			size_t vertexIndex = 0;
			for (auto i = sortedVertices.begin(); i != sortedVertices.end(); ++i, ++vertexIndex)
			{
				const auto& vertex = i->first;
				o_vertexArray.push_back(vertex);
				vertexKeyToIndexMap.insert(std::make_pair(i->second, vertexIndex));
			}
		}

		// Fill the index buffer with the indices
		{
			// Sort the triangles by shading group
			std::sort(io_triangles.begin(), io_triangles.end(), sTriangle::CompareTriangles);
			// Assign the triangle indices to the index buffer
			const auto triangleCount = io_triangles.size();
			const auto indexCount = triangleCount * s_vertexCountPerTriangle;
			o_indexArray.resize(indexCount);
			for (size_t i = 0; i < triangleCount; ++i)
			{
				const auto& triangle = io_triangles[i];
				for (size_t j = 0; j < s_vertexCountPerTriangle; ++j)
				{
					const auto& vertexKey = triangle.vertexKeys[j];
					const auto triangleIndex = vertexKeyToIndexMap.find(vertexKey)->second;
					const auto indexBufferIndex = (i * s_vertexCountPerTriangle) + j;
					o_indexArray[indexBufferIndex] = triangleIndex;
					
				}
			}
		}

		return MStatus::kSuccess;
	}

	MStatus ProcessAllObjects(std::map<std::string, sVertexInfo>& o_uniqueVertices, std::vector<sTriangle>& o_triangles)
	{
		MStatus status;


		for (MItDag i(MItDag::kDepthFirst, MFn::kMesh); !i.isDone(); i.next())
		{
			MDagPath dagPath;
			i.getPath(dagPath);
			if (!(status = ProcessSingleDagNode(dagPath, o_uniqueVertices, o_triangles)))
			{
				return status;
			}
		}

		return status;
	}

	MStatus ProcessSelectedObjects(std::map<std::string, sVertexInfo>& o_uniqueVertices, std::vector<sTriangle>& o_triangles)
	{
		MStatus status;

		// Iterate through each selected object
		MSelectionList selectionList;
		if (status = MGlobal::getActiveSelectionList(selectionList))
		{

			for (MItSelectionList i(selectionList, MFn::kMesh); !i.isDone(); i.next())
			{

				MDagPath dagPath;
				i.getDagPath(dagPath);

				if (!(status = ProcessSingleDagNode(dagPath, o_uniqueVertices, o_triangles)))
				{
					return status;
				}
			}	
			for (MItSelectionList i(selectionList, MFn::kCharacter); !i.isDone(); i.next())
			{

				MDagPath dagPath;
				i.getDagPath(dagPath);

				if (!(status = ProcessSingleDagNode(dagPath, o_uniqueVertices, o_triangles)))
				{
					return status;
				}
			}
		}
		else
		{
			MGlobal::displayError(MString("Failed to get active selection list: ") + status.errorString());
			return status;
		}

		return status;
	}

	MStatus ProcessSingleDagNode(const MDagPath& i_dagPath,
		std::map<std::string, sVertexInfo>& io_uniqueVertices, std::vector<sTriangle>& io_triangles)
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

		// Get a list of the positions
		MPointArray positions;
		{
			const auto status = mesh.getPoints(positions, MSpace::kWorld);
			if (!status)
			{
				MGlobal::displayError(status.errorString());
				return status;
			}
		}
	
		// Get a list of the normals
		MFloatVectorArray normals;
		{
			const auto status = mesh.getNormals(normals, MSpace::kWorld);
			if (!status)
			{
				MGlobal::displayError(status.errorString());
				return status;
			}
		}

		// Get a list of tangents and bitangents
		MFloatVectorArray tangents, bitangents;
		{
			constexpr MString* const useDefaultUvSet = nullptr;	// If more than one UV set exists this code will use the "default" one (as chosen by Maya)
			{
				const auto status = mesh.getTangents(tangents, MSpace::kWorld, useDefaultUvSet);
				if (!status
					// Tangents may not exist if there are no UVs
					&& (status != MS::kInvalidParameter))
				{
					MGlobal::displayError(status.errorString());
					return status;
				}
			}
			{
				const auto status = mesh.getBinormals(bitangents, MSpace::kWorld, useDefaultUvSet);
				if (!status
					// Bitngents may not exist if there are no UVs
					&& (status != MS::kInvalidParameter))
				{
					MGlobal::displayError(status.errorString());
					return status;
				}
			}
		}

		// Get a list of the texture coordinates
		MFloatArray texcoordUs, texcoordVs;
		{
			MStatus status;
			const auto uvSetCount = mesh.numUVSets(&status);
			if (status)
			{
				if (uvSetCount > 0)
				{
					constexpr MString* const useDefaultUvSet = nullptr;	// If more than one UV set exists this code will use the "default" one (as chosen by Maya)
					status = mesh.getUVs(texcoordUs, texcoordVs, useDefaultUvSet);
					if (!status)
					{
						MGlobal::displayError(status.errorString());
						return status;
					}
				}
			}
			else
			{
				MGlobal::displayError(status.errorString());
				return status;
			}
		}

		// Get a list of the vertex colors
		MColorArray vertexColors;
		{
			MStatus status;
			const auto colorSetCount = mesh.numColorSets(&status);
			if (status)
			{
				if (colorSetCount > 0)
				{
					constexpr MString* const useDefaultColorSet = nullptr;	// If more than one color set exists this code will use the "default" one (as chosen by Maya)
					MColor defaultColor(1.0f, 1.0f, 1.0f, 1.0f);
					status = mesh.getColors(vertexColors, useDefaultColorSet, &defaultColor);
					if (!status)
					{
						MGlobal::displayError(status.errorString());
						return status;
					}
				}
			}
			else
			{
				MGlobal::displayError(status.errorString());
				return status;
			}
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
			for (MItMeshPolygon i(mesh.object()); !i.isDone(); i.next(), ++polygonIndex)
			{
				if (i.hasValidTriangulation())
				{
					// Store information for each vertex in the polygon
					std::map<int, const std::string> indexToKeyMap;
					{
						MIntArray vertices;
						const auto status = i.getVertices(vertices);
						if (status)
						{
							const auto vertexCount = vertices.length();
							for (std::remove_const<decltype(vertexCount)>::type j = 0; j < vertexCount; ++j)
							{
								const auto positionIndex = vertices[j];
								const auto normalIndex = i.normalIndex(j);
								int texcoordIndex = -1;
								struct { float u, v; } texcoord = { 0.0f, 0.0f };
								{
									int potentialTexcoordIndex;
									constexpr MString* const useDefaultUvSet = nullptr;
									const auto status = i.getUVIndex(j, potentialTexcoordIndex, useDefaultUvSet);
									if (status && (potentialTexcoordIndex >= 0)
										&& (static_cast<unsigned int>(potentialTexcoordIndex) < texcoordUs.length())
										&& (static_cast<unsigned int>(potentialTexcoordIndex) < texcoordVs.length()))
									{
										texcoordIndex = potentialTexcoordIndex;
										texcoord.u = texcoordUs[texcoordIndex];
										texcoord.v = texcoordVs[texcoordIndex];
									}
								}
								int tangentIndex = -1;
								MFloatVector tangent(0.0f, 0.0f, 0.0f);
								MFloatVector bitangent(0.0f, 0.0f, 0.0f);
								{
									MStatus status;
									const auto potentialTangentIndex = i.tangentIndex(j, &status);
									if (status && (potentialTangentIndex >= 0)
										&& (static_cast<unsigned int>(potentialTangentIndex) < tangents.length())
										&& (static_cast<unsigned int>(potentialTangentIndex) < bitangents.length()))
									{
										tangentIndex = potentialTangentIndex;
										tangent = tangents[tangentIndex];
										bitangent = bitangents[tangentIndex];
									}
								}
								int vertexColorIndex = -1;
								MColor vertexColor(1.0f, 1.0f, 1.0f, 1.0f);
								{
									int potentialColorIndex;
									constexpr MString* const useDefaultColorSet = nullptr;
									const auto status = i.getColorIndex(j, potentialColorIndex, useDefaultColorSet);
									if (status && (potentialColorIndex >= 0)
										&& (static_cast<unsigned int>(potentialColorIndex) < vertexColors.length()))
									{
										vertexColorIndex = potentialColorIndex;
										vertexColor = vertexColors[vertexColorIndex];
									}
								}
								const auto vertexKey = CreateUniqueVertexKey(positionIndex, normalIndex, tangentIndex,
									texcoordIndex, vertexColorIndex, transformName);
								indexToKeyMap.insert(std::make_pair(positionIndex, vertexKey));
								if (io_uniqueVertices.find(vertexKey) != io_uniqueVertices.end()) {
									int j = 0;
								}
								io_uniqueVertices.insert(std::make_pair(vertexKey,
									sVertexInfo(positions[positionIndex], normals[normalIndex],
										tangent, bitangent,
										texcoord.u, texcoord.v,
										vertexColor,vertexKey)
								));
							}
						}
						else
						{
							MGlobal::displayError(status.errorString());
							return status;
						}
					}
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
							if (static_cast<size_t>(positionIndices.length()) == s_vertexCountPerTriangle)
							{
								sTriangle triangle;
								for (unsigned int k = 0; k < static_cast<unsigned int>(s_vertexCountPerTriangle); ++k)
								{
									const auto positionIndex = positionIndices[k];
									const auto mapLookUp = indexToKeyMap.find(positionIndex);
									if (mapLookUp != indexToKeyMap.end())
									{
										triangle.vertexKeys[k] = mapLookUp->second;
									}
									else
									{
										MGlobal::displayError("A triangle gave a different vertex index than the polygon gave");
										return MStatus::kFailure;
									}
								}
								io_triangles.push_back(triangle);
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
		}

		return MStatus::kSuccess;
	}

	MStatus WriteMeshToFile(const MString& i_fileName, const std::vector<sVertexInfo>& i_vertexArray, const std::vector<size_t>& i_indexArray)
	{

		std::ofstream fout(i_fileName.asChar());
		if (fout.is_open())
		{
			// Lua should be able to parse scientific notation,
			// but if you run into problems you can uncomment the line below to always used fixed notation
//			fout << std::fixed;
			int vertexCount = (int)i_vertexArray.size();
			int indexCount = (int)i_indexArray.size() / 3;
			// Open table
			// (If you want to use JSON instead of Lua you will have to change this slightly)
			{
				fout << "vertexCount = " << vertexCount << "\n";
				fout << "vertexData = {""\n";
				{
					for (int i = 0; i < vertexCount; i++) {
						fout << "	{" << i_vertexArray[i].vertex.x << "," << i_vertexArray[i].vertex.y << "," << -1*i_vertexArray[i].vertex.z <<","
							 << i_vertexArray[i].vertex.nx << "," << i_vertexArray[i].vertex.ny << "," << i_vertexArray[i].vertex.nz <<","
							 << i_vertexArray[i].vertex.u << "," << i_vertexArray[i].vertex.v<< "," << i_vertexArray[i].vertex.tx<<","<<i_vertexArray[i].vertex.ty<<"," << i_vertexArray[i].vertex.tz<< "},""\n";
					}
				}
				fout << "}""\n";

				fout << "indexCount = " << indexCount << "\n";
				fout << "indexData = {""\n";
				{
					for (int i = 0; i < indexCount; i++) {
						fout << "	{" << i_indexArray[3 * i] << "," << i_indexArray[3 * i + 1] << "," << i_indexArray[3 * i + 2] << "},""\n";
					}
				}
				fout << "}""\n";
			}

			fout.close();

			return MStatus::kSuccess;
		}
		else
		{
			MGlobal::displayError(MString("Couldn't open ") + i_fileName + " for writing");
			return MStatus::kFailure;
		}
	}
}
