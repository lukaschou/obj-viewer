#ifndef MODEL_H
#define MODEL_H

#include "loader.h" 

#include <glad/glad.h>
#include <vector>

class Model
{
public:
    Model(
        std::vector<float> vertices,
        std::vector<float> normals,
        std::vector<float> texCoords,
        std::vector<FaceElement> elements
    );

    void draw() const;

private:
    GLuint VAO{};
    GLuint VBOs[2];
    GLuint EBO{};

    std::vector<float> vertices;
    std::vector<int> indices;
};

#endif
