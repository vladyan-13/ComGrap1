#define GLFW_DLL
#define GLEW_DLL

#include <iostream>
#include <cmath>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

float vertex[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main()
{
    std::cout << "Hello World!\n";

    if (!glfwInit()) {
        fprintf(stderr, "ERROR GLFW:\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* Okno = glfwCreateWindow(512, 512, "okno", NULL, NULL);
    if (!Okno) {
        glfwTerminate();
        return 1;
    }

    glewExperimental = GL_TRUE;
    glfwMakeContextCurrent(Okno);

    GLenum ret = glewInit();
    if (GLEW_OK != ret) {
        fprintf(stderr, "ERROR: %s \n", glewGetErrorString(ret));
        return 1;
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader ourShader("triangle.vert", "triangle.frag");

    while (!glfwWindowShouldClose(Okno)) {
        glfwPollEvents();

        float timeValue = glfwGetTime();
        float red = (sin(timeValue) * 0.5f) + 0.5f;
        float green = (cos(timeValue) * 0.5f) + 0.5f;
        float blue = (sin(timeValue * 2.0f) * 0.5f) + 0.5f;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        ourShader.use();
        ourShader.setVec4("ourColor", red, green, blue, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(Okno);

        if (glfwGetKey(Okno, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(Okno, true);
    }

    glfwTerminate();
    return 0;
}