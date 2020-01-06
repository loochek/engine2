#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

void importMaterials(const aiScene* scene)
{
    for (int i = 0; i < scene->mNumMaterials; i++)
    {
        aiMaterial* mat = scene->mMaterials[i];

        aiString name;
        if (mat->Get(AI_MATKEY_NAME, name) != AI_SUCCESS)
        {
            std::cout << "Unable to import noname material" << std::endl;
            continue;
        }
        std::ofstream matFile("materials/" + std::string(name.C_Str()) + ".e2mtl");
        matFile << "Shader shader\n";
        if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString texturePath;
            mat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
            matFile << "DiffuseMap " << texturePath.C_Str() << '\n';
        }
        if (mat->GetTextureCount(aiTextureType_SPECULAR) > 0)
        {
            aiString texturePath;
            mat->GetTexture(aiTextureType_SPECULAR, 0, &texturePath);
            matFile << "SpecularMap " << texturePath.C_Str() << '\n';
        }
        matFile.close();
    }
}

#pragma pack (push)
#pragma pack (1)
struct E2mdlHeader
{
    char signature[6] = "E2MDL";
    uint8_t version = 1;
    uint32_t meshCount;
};
#pragma pack (pop)

#pragma pack (push)
#pragma pack (1)
struct E2mdlMeshEntry
{
    char signature[5] = "HAAX";
    uint32_t verticesCount;
    uint32_t indicesCount;
    uint8_t flags; // UV present - 1st bit
    char material[16]; // used material
};
#pragma pack (pop)

/*
header

mesh entry - vertices count, indices count
mesh data
{
    vertices - sizeof(glm::vec3) * verticesCount
    normals - sizeof(glm::vec3) * verticesCount
    Indices - sizeof(GLfloat) * indicesCount
    uv coords - sizeof(glm::vec2) * verticesCount if flag set
}
mesh data {}
...
*/

void processNode(aiNode* node, const aiScene* scene, std::ofstream &modelFile)
{
    // process meshes from current node
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* impMesh = scene->mMeshes[node->mMeshes[i]]; // assimp mesh

        std::vector<glm::vec3> vertices(impMesh->mNumVertices);
        for (int i = 0; i < impMesh->mNumVertices; i++)
            vertices[i] = glm::vec3(impMesh->mVertices[i].x, impMesh->mVertices[i].y, impMesh->mVertices[i].z);

        std::vector<glm::vec3> normals(impMesh->mNumVertices);
        for (int i = 0; i < impMesh->mNumVertices; i++)
            normals[i] = glm::vec3(impMesh->mNormals[i].x, impMesh->mNormals[i].y, impMesh->mNormals[i].z);

        std::vector<GLuint> indicies;
        for (int i = 0; i < impMesh->mNumFaces; i++)
        {
            aiFace face = impMesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
                indicies.push_back(face.mIndices[j]);
        }

        std::vector<glm::vec2> texCoords;
        if (impMesh->mTextureCoords[0])
        {
            texCoords.resize(impMesh->mNumVertices);
            for (int i = 0; i < impMesh->mNumVertices; i++)
                texCoords[i] = glm::vec2(impMesh->mTextureCoords[0][i].x, impMesh->mTextureCoords[0][i].y);
        }

        E2mdlMeshEntry meshEntry;
        meshEntry.verticesCount = impMesh->mNumVertices;
        meshEntry.indicesCount = indicies.size();
        if (impMesh->mTextureCoords[0])
            meshEntry.flags = 1;

        if (impMesh->mMaterialIndex >= 0)
        {
            aiString name;
            if (scene->mMaterials[impMesh->mMaterialIndex]->Get(AI_MATKEY_NAME, name) == AI_SUCCESS)
                strcpy(meshEntry.material, name.C_Str());
            else
                strcpy(meshEntry.material, "Default");
        }
        else
            strcpy(meshEntry.material, "Default");

        modelFile.write((char*)&meshEntry, sizeof(meshEntry));
        modelFile.write((char*)vertices.data(), sizeof(glm::vec3) * impMesh->mNumVertices);
        modelFile.write((char*)normals.data(), sizeof(glm::vec3) * impMesh->mNumVertices);
        modelFile.write((char*)indicies.data(), sizeof(GLfloat) * indicies.size());
        if (impMesh->mTextureCoords[0])
            modelFile.write((char*)texCoords.data(), sizeof(glm::vec2) * impMesh->mNumVertices);
    }

    // recursively process child nodes
    for (int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, modelFile);
}

int main(int argc, char* argv[])
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(argv[1], aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    importMaterials(scene);
    std::ofstream modelFile(std::string(argv[1]) + ".e2mdl", std::ios::binary);
    E2mdlHeader header;
    header.meshCount = scene->mNumMeshes;
    modelFile.write((char*)&header, sizeof(E2mdlHeader));
    processNode(scene->mRootNode, scene, modelFile);
    modelFile.close();
	return 0;
}