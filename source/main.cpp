#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
    if (!glfwInit()) return -1;

    //Telling OpenGL what version to expect
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //The window acts as an object stored in a pointer
    GLFWwindow *window = glfwCreateWindow(1280, 720, "GameDevelopmentProject", nullptr, nullptr);

    if (window == nullptr) {
        std::cout<<"Error creating window"<<'\n';
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); //Telling OpenGL what window to target

    if (glewInit() != GLEW_OK) {
        std::cout<<"Error initializing GLEW"<<'\n';
        glfwTerminate();
        return -1;
    }

#pragma region vertex shader
    //R means raw string
    std::string vertexShaderSource = R"(
          #version 330 core
          layout (location = 0) in vec3 position;

            void main(){
                gl_Position = vec4(position.x, position.y, position.z, 1);
            }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr<<"ERROR: VERTEX_SHADER_COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
#pragma endregion

#pragma region fragment shader
    std::string fragmentShaderSource = R"(
          #version 330 core
          out vec4 FragColor;

            void main(){
                FragColor = vec4(1, 0, 0, 1);
            }
    )";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderCStr, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr<<"ERROR: FRAGMENT_SHADER_COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
#pragma endregion

#pragma region shader program linking
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr<<"ERROR: SHADER_PROGRAM_LINKING_FAILED\n"<<infoLog<<std::endl;
    }
#pragma endregion

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::vector<float> vertices = {
        0, 0.5, 0,
        -0.5, -0.5, 0,
        0.5, -0.5, 0,
    };

#pragma region configuring buffers
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#pragma endregion

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1, 1, 0, 1); //each number is for the color channels
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window); //swapping the back buffer to the front buffer

        glfwPollEvents(); //Events like the close button
    }

    glfwTerminate();

    return 0;
}