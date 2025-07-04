cmake_minimum_required(VERSION 3.10)
project(PhongExample)

set(CMAKE_CXX_STANDARD 11)

# Encuentra GLFW y GLM
find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)

# Añade GLAD (asumamos lo tienes en extern/glad)
add_subdirectory(extern/glad)

# Shader helper
add_library(Shader src/Shader.cpp)
target_include_directories(Shader PUBLIC src)

# Ejecutable principal
add_executable(PhongApp
    src/main.cpp
)

# Incluye directorios
target_include_directories(PhongApp PRIVATE
    extern/glad/include
    ${GLM_INCLUDE_DIRS}
    src
)

# Linkea librerías
target_link_libraries(PhongApp PRIVATE
    glad
    glfw
    Shader
)
