#include "mesh.hpp"
#include <iostream>

Mesh::Mesh(vector<Vertex> vertices, vector<u_int> indices, vector<Texture> textures) :
    vertices(vertices), indices(indices), textures(textures)
{
    setup();
}

void Mesh::setup(Shader* shader)
{

    glGenVertexArrays(1, &VAO); //Create VAO, VBO, EBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind VAO and VBO

    //move date from vertices vector to VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), 
        &vertices[0], GL_STATIC_DRAW); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Bind EBO
    //Move indices to EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int), 
        &indices[0], GL_STATIC_DRAW);

    //defines array of VAO for vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    //defines array of VAO for normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    //defines array of VAO for texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::draw(Shader* shader)
{
    shader->use();
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].getType();
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader->setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].getID());
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

