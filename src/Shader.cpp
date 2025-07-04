#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/gl.h>

static std::string loadFile(const char* path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

Shader::Shader(const char* vertPath, const char* fragPath) {
    std::string vCode = loadFile(vertPath);
    std::string fCode = loadFile(fragPath);
    const char* vSrc = vCode.c_str();
    const char* fSrc = fCode.c_str();

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vSrc, nullptr);
    glCompileShader(vShader);
    // (aquí podrías chequeos de error)

    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fSrc, nullptr);
    glCompileShader(fShader);

    ID = glCreateProgram();
    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);
    glLinkProgram(ID);
    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::Use() const {
    glUseProgram(ID);
}

void Shader::SetUniformMat4(const std::string &name, const float* mat) const {
    int loc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
}

void Shader::SetUniformVec3(const std::string &name, float x, float y, float z) const {
    int loc = glGetUniformLocation(ID, name.c_str());
    glUniform3f(loc, x, y, z);
}
