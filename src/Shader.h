#pragma once
#include <string>
#include <GL/gl.h>

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void Use() const;
    void SetUniformMat4(const std::string &name, const float* mat) const;
    void SetUniformVec3(const std::string &name, float x, float y, float z) const;
};