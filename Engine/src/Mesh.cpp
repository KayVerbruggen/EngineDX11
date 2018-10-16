#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

std::vector<Vertex> ProcessVertices(aiMesh* mesh)
{
	std::vector<Vertex> vertices(mesh->mNumVertices);

	// Process vertices.
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		// Get the vertices.
		vertices[i].x = mesh->mVertices[i].y;
		vertices[i].y = mesh->mVertices[i].z;
		vertices[i].z = mesh->mVertices[i].x;

		// Get the normals.
		if (mesh->HasNormals())
		{
			vertices[i].nx = mesh->mNormals[i].y;
			vertices[i].ny = mesh->mNormals[i].z;
			vertices[i].nz = mesh->mNormals[i].x;
		}
		else
		{
			// TODO: Add the file name to the error message.
			MessageBox(0, "No normals were found for this mesh.", "Assimp Error", MB_OK);
		}

		// Get the UV coordinates.
		if (mesh->mTextureCoords[0])
		{
			vertices[i].u = mesh->mTextureCoords[0][i].x;
			vertices[i].v = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertices[i].u = 0;
			vertices[i].v = 0;
		}
	}

	return vertices;
}

std::vector<unsigned int> ProcessIndices(aiMesh* mesh)
{
	std::vector<unsigned int> indices;

	// Process indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return indices;
}

Mesh::Mesh(std::string meshFile)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(meshFile, aiProcess_CalcTangentSpace		|
													   aiProcess_Triangulate			|
													   aiProcess_FlipUVs				|
													   aiProcess_JoinIdenticalVertices	|
													   aiProcess_SortByPType);

	meshCount = scene->mNumMeshes;

	// Loop through each mesh in the scene.
	for (unsigned int i = 0; i < meshCount; i++)
	{
		aiMesh* currMesh = scene->mMeshes[i];

		auto vertices = ProcessVertices(currMesh);
		auto indices = ProcessIndices(currMesh);

		m_vertexBuffers.push_back(VertexBuffer(vertices));
		m_indexBuffers.push_back(IndexBuffer(indices));
		m_indexSize.push_back((unsigned int)indices.size());
	}
}

Mesh::~Mesh()
{
}