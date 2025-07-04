#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include <iostream>

// callback de redimensionamiento
void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    glViewport(0,0,w,h);
}

int main() {
    // 1) Inicializar GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2) Crear ventana
    GLFWwindow* window = glfwCreateWindow(800, 600, "Phong con GLFW", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error creando ventana\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 3) Cargar punteros OpenGL con GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // 4) Preparar shaders y geometría (cubo)
    Shader shader("shaders/phong.vs", "shaders/phong.fs");
    float verts[] = {
        // posición         // normal
       -0.5f,-0.5f,-0.5f,   0,0,-1,
        0.5f,-0.5f,-0.5f,   0,0,-1,
        0.5f, 0.5f,-0.5f,   0,0,-1,
        0.5f, 0.5f,-0.5f,   0,0,-1,
       -0.5f, 0.5f,-0.5f,   0,0,-1,
       -0.5f,-0.5f,-0.5f,   0,0,-1,
       // … repite para 6 caras (36 vértices) …
    };
    unsigned int VAO, VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // 5) Bucle principal
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        // matrices
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(0,0,5), glm::vec3(0,0,0), glm::vec3(0,1,0));
        glm::mat4 model = glm::rotate(glm::mat4(1.0f),
                           (float)glfwGetTime(), glm::vec3(0.5f,1.0f,0));
        shader.SetUniformMat4("projection", &proj[0][0]);
        shader.SetUniformMat4("view",       &view[0][0]);
        shader.SetUniformMat4("model",      &model[0][0]);

        // luz y cámara
        shader.SetUniformVec3("lightPos", 1.2f,1.0f,2.0f);
        shader.SetUniformVec3("viewPos",  0.0f,0.0f,5.0f);
        shader.SetUniformVec3("lightColor",1.0f,1.0f,1.0f);
        shader.SetUniformVec3("objectColor",1.0f,0.5f,0.31f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 6) Limpieza
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
