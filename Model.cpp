#include "Model.h"
#include <iostream>
#include <tuple>
#include <unordered_map>

inline void hash_combine(std::size_t& seed, int v) {
        seed ^= std::hash<int>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

Model::Model(
        std::vector<float> vertices,
        std::vector<float> normals,
        std::vector<float> texCoords,
        std::vector<FaceElement> elements
) : vertices(vertices) {
    typedef std::tuple<int, int, int> vertex_t;
    struct vertex_hash {
        std::size_t operator()(const vertex_t& v) const {
        std::size_t seed = 0;
            hash_combine(seed, std::get<0>(v));
            hash_combine(seed, std::get<1>(v));
            hash_combine(seed, std::get<2>(v));
            return seed;
        }
    };
    typedef std::unordered_map<const vertex_t,int,vertex_hash> vertex_map_t;
    vertex_map_t seen {};
    std::vector<float> verts {};
    std::vector<int> indices {};

    for (int i {}; i < elements.size() / 3; i++) {
        FaceElement f1 = elements[i * 3];
        FaceElement f2 = elements[i * 3 + 1];
        FaceElement f3 = elements[i * 3 + 2];

        for (const auto& element : {f1, f2, f3}) {
            int vertexIndex = element.vertexIndex;
            int textureIndex = element.vertexIndex;
            int normalIndex = element.normalIndex;

            vertex_t vertex = std::make_tuple(vertexIndex, textureIndex, normalIndex);
            if (seen.find(vertex) != seen.end()) {
                // append index
            } else {
                // insert into VBO + append index
            }
        }
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

