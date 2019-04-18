#include "Window.h"
#include <iostream>

int Window::s_Width = 0;
int Window::s_Height = 0;
std::string Window::s_Title = "";
bool Window::s_Resized = false;
bool Window::s_ShouldClose = false;
bool Window::s_MouseMooved = false;
float Window::s_CurrentX = 0;
float Window::s_CurrentY = 0;

#pragma region Public API

Window::Window(int width, int height, const char* title)
	: m_Window{nullptr}
{
    Window::s_Width = width;
    Window::s_Height = height;
    Window::s_Title = title;
	Window::s_Resized = false;
	Window::s_ShouldClose = false;
	Window::s_MouseMooved = false;
	Window::s_CurrentX = ((float)width) / 2;
	Window::s_CurrentY = ((float)height) / 2;
}

Window::~Window()
{
}

void Window::Init()
{
    if(glfwInit() == GLFW_FALSE)
    {
        std::cout << "Couldn't init GLFW." << std::endl;
		std::cin.get();
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(Window::s_Width, Window::s_Height, Window::s_Title.c_str(), NULL, NULL);
    if(m_Window == NULL)
    {
        std::cout << "Couldn't create the window." << std::endl;
        glfwTerminate();
		std::cin.get();
        exit(-1);
    }

    glfwSetKeyCallback(m_Window, [](GLFWwindow* Window, int key, int scancode, int action, int mods)
    {
        if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
            glfwSetWindowShouldClose(Window, true);
    });

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* Window, double xpos = 0, double ypos = 0)
	{
		Window::s_MouseMooved = true;
		Window::s_CurrentX = (float)xpos;
		Window::s_CurrentY = (float)ypos;
	});

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* Window, int width, int height)
    {
        Window::s_Width = width;
        Window::s_Height = height;
        Window::s_Resized = true;
    });

    const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(
        m_Window,
        (vidmode->width - Window::s_Width)/2,
        (vidmode->height - Window::s_Height)/2
    );

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(m_Window, Window::s_CurrentX, Window::s_CurrentY);

    glfwMakeContextCurrent(m_Window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Couldn't init OpenGL." << std::endl;
		glfwTerminate();
		std::cin.get();
		exit(-1);
	}

	std::cout << glGetString(GL_VENDOR) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

    glfwSwapInterval(1);

	glClearColor(0.001f, 0.0111f, 0.0105f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	// LEQUAL for the skybox
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_FRAMEBUFFER_SRGB);
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

#pragma endregion