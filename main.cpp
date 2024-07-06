#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

const char* vertex_shader = 
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 460\n" 
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";

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

int main(void)
{
    GLFWwindow* window = nullptr;
    init(&window);

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    glClearColor(1, 1, 0, 1);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);

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

        glUseProgram(shader_program);
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

