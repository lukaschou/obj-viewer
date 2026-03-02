#include "Model.h"
#include <iostream>

Model::Model(
        std::vector<float> vertices,
        std::vector<float> normals,
        std::vector<float> texCoords,
        std::vector<FaceElement> elements
) : vertices(vertices) {
    for (int f { 0 } ; f < elements.size() / 3; f++) {
        
    }
    // Later, this will zip all attributes together
    for (const auto& element : elements) {
        indices.push_back(element.vertexIndex); 
        std::cout << "Vertex: " << element.vertexIndex << std::endl;
        std::cout << "Texture: " << element.vertexIndex << std::endl;
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBOs);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(
        GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
        vertices.data(), GL_STATIC_DRAW
    );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture data
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(
        GL_ARRAY_BUFFER, texCoords.size() * sizeof(float),
        texCoords.data(), GL_STATIC_DRAW
    );
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
        indices.data(), GL_STATIC_DRAW
    );

}

void Model::draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

