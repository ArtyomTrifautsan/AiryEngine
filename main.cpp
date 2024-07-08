#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "src/ShaderProgram.h"
#include "src/ResourceManager.h"

using std::cout, std::endl;

int SCREEN_SIZE[] = {1440, 810};

GLfloat points[] = {
    0.0f, 0.8f, 0.0f,
    0.7f, -0.5f, 0.0f,
    -0.7f, -0.5f, 0.0f,
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

int init(GLFWwindow* *window)
{
    // Initialize the glfw library
    if (!glfwInit()) 
    {
        cout << "can't load glfw library" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);      // Установить использование конкретной версии opengl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);      // Установить использование конкретной версии opengl
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      // Выключить функции обратной совместимости с предыдущими версиями

    // Create a windowed mode window and its OpenGL context 
    *window = glfwCreateWindow(
        SCREEN_SIZE[0], 
        SCREEN_SIZE[1], 
        "3D game", 
        nullptr,
        nullptr
    );
    if (nullptr == *window)
    {
        cout << "can't create a window" << endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current 
    glfwMakeContextCurrent(*window);

    // Initialize the glad library
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "can't load glad library" << endl;
        return -1;
    }

    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    //cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << endl;

    return 0;
}

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    SCREEN_SIZE[0] = width;
    SCREEN_SIZE[1] = height;
    glViewport(0, 0, SCREEN_SIZE[0], SCREEN_SIZE[1]);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int node)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

}

int main(int argc, char** argv)
{
    ResourceManager resource_manager(argv[0]);
    auto p_default_shader_program = resource_manager.load_shaders("Default", "shaders/vertex_shader.txt", "shaders/fragment_shader_txt");
    if (!p_default_shader_program)
    {
        std::cerr << "Can't create shader program: " << "Default shader" << std::endl;
        return -1;
    }

    GLFWwindow* window = nullptr;
    init(&window);

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    glClearColor(1, 1, 0, 1);

    GLuint poitns_vbo = 0;
    glGenBuffers(1,&poitns_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, poitns_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1,&colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, poitns_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Loop until the user closes the window 
    while (!glfwWindowShouldClose(window))
    {
        // Render here 
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shader_program);
        p_default_shader_program->use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers 
        glfwSwapBuffers(window);

        // Poll for and process events 
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

