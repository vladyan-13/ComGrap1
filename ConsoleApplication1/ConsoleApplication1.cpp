#define GLEW_DLL
#define GLFW_DILL

#include <iostream>
#include "GL\glew.h"
#include "GLFW/glfw3.h"

int main()
{
    glfwInit();

    if (!glfwInit()) {
        fprintf(stderr, "ERROR GLFW INIT: \n");
        return -1;
    }

    if (!glfwInit()) {
        glfwTerminate();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1.0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0.0);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)


    GLFWwindow* Okno;
    Okno = glfwCreateWindow(512, 512, "Okno", NULL, NULL);
    glfwMakeContextCurrent(Okno);

    if (!Okno) {
        glfwTerminate();
    }

    glewInit();
    GLenum ret = glewInit();
    if (GLEW_OK != ret) {
        fprintf(stderr, "ERROR GLEW INIT: \n", glewGetErrorString(ret));
        return -2;
    }


    while (!glfwWindowShouldClose(Okno)) {
        glClear(GL_COLOR_BUFFER_BIT);
        //10 ВАРИАНТ
        glClearColor(0.2, 1.0, 1.0, 1.0);

        glBegin(GL_QUADS);
        //10 ВАРИАНТ
        glColor3f(1.0, 0.8, 0.5); glVertex2f(-0.5, -0.5);
        glColor3f(1.0, 0.8, 0.5); glVertex2f(0.5, -0.5);
        glColor3f(1.0, 0.8, 0.5); glVertex2f(0.5, 0.5); 
        glColor3f(1.0, 0.8, 0.5); glVertex2f(-0.5, 0.5);

        glEnd();

        glfwSwapBuffers(Okno);
        glfwPollEvents();
    }

    glfwTerminate();

}