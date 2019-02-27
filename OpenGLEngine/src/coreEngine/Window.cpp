#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Window.h"

int Window::s_Width = 0;
int Window::s_Height = 0;
std::string Window::s_Title = "";
bool Window::s_Resized = false;
bool Window::s_ShouldClose = false;

Window::Window(int width, int height, const char* title)
{
    Window::s_Width = width;
    Window::s_Height = height;
    Window::s_Title = title;
	Window::s_Resized = false;
    Window::s_ShouldClose = false;
}

Window::~Window()
{
}

void Window::Init()
{
    if(glfwInit() == GLFW_FALSE)
    {
        std::cout << "Couldn't init GLFW." << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    m_Window = glfwCreateWindow(Window::s_Width, Window::s_Height, Window::s_Title.c_str(), NULL, NULL);
    if(m_Window == NULL)
    {
        std::cout << "Couldn't create the window." << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwSetKeyCallback(m_Window, [](GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
    {
        if(Key == GLFW_KEY_ESCAPE && Action == GLFW_RELEASE)
            glfwSetWindowShouldClose(Window, true);
    });

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height)
    {
        Window::s_Width = Width;
        Window::s_Height = Height;
        Window::s_Resized = true;
    });

    const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(
        m_Window,
        (vidmode->width - Window::s_Width)/2,
        (vidmode->height - Window::s_Height)/2
    );

    glfwMakeContextCurrent(m_Window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Couldn't init OpenGL." << std::endl;
		glfwTerminate();
		exit(-1);
	}

    glfwSwapInterval(1);
    glfwShowWindow(m_Window);
}

void Window::Update()
{
    if(Window::s_Resized)
    {
        glViewport(0, 0, Window::s_Width, Window::s_Height);
        Window::s_Resized = false;
    }

    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void Window::CleanUp()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}


bool Window::IsKeyPressed(int key)
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Window::ShouldClose()
{
    return s_ShouldClose || glfwWindowShouldClose(m_Window);
}