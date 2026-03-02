#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Shader
{
public:
    // program ID
    unsigned int ID;
    // constructor reads and builds shader
    Shader(const char *vertexPath, const char *fragmentPath);
    // use/activatre the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMatrix4(const std::string &name, glm::mat4 mat) const;
};

#endif
