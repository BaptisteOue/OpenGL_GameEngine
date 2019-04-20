#pragma once

#include <GL/glew.h> // Include before gl.h before glfw3.h
#include <GLFW/glfw3.h>
#include <string>

class Window
{
private:
	GLFWwindow* m_Window;

public:
    static int s_Width;
    static int s_Height;
    static std::string s_Title;
    static bool s_Resized;
    static bool s_ShouldClose;
	static bool s_MouseMooved;
	static float s_CurrentX;
	static float s_CurrentY;
	static float s_Gamma;

public:
    Window(int width, int height, const char* title);
    ~Window();

    void Init();
    void Update();
    void CleanUp();

    bool IsKeyPressed(int key);
    bool ShouldClose();
};