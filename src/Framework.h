#pragma once

#include "Config.h"

//=============================================================================
// Header
//=============================================================================

#include <exception>
#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <string_view>

#if SUPPORT_OPENGL
#   include <glad/glad.h>
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#if defined(__linux__) || (defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__)  || defined(__DragonFly__))
#	define GLFW_EXPOSE_NATIVE_X11
#	define GLFW_EXPOSE_NATIVE_GLX
#endif
#if defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#	define GLFW_EXPOSE_NATIVE_COCOA
#	define GLFW_EXPOSE_NATIVE_NSGL
#endif
#if defined(_WIN32) || defined(_WIN64)
#	define GLFW_EXPOSE_NATIVE_WIN32
#	define GLFW_EXPOSE_NATIVE_WGL
#endif
#include <glfw/glfw3native.h>

//=============================================================================
// Window
//=============================================================================

static void ErrorGLFWfunc(int error, const char *description)
{
	throw std::exception(("GLFW error " + std::to_string(error) + ": " + std::string(description)).c_str());
}

class Window
{
public:
	Window(int width, int height, const char *title, bool vsync, bool enableOpenGL = false);
	~Window();

	bool IsEnd();
	void Swap();

	void GetWindowSize(int &width, int &height)
	{
		glfwGetFramebufferSize(m_window, &width, &height);
	}

	Window* Get()
	{
		if ( !thisWnd ) throw std::exception("Window no create!!!");
		return thisWnd;
	}

	GLFWwindow* GetGLFWWindow() 
	{ 
		return m_window; 
	}

	void* GetNativeWindowHandle()
	{
#if defined(__linux__) || (defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__)  || defined(__DragonFly__))
		return (void*)(uintptr_t)glfwGetX11Window(m_window);
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
		return glfwGetCocoaWindow(m_window);
#elif defined(_WIN32) || defined(_WIN64)
		return glfwGetWin32Window(m_window);
#endif
	}

private:
	inline static Window *thisWnd = nullptr;

	GLFWwindow *m_window = nullptr;
};

//=============================================================================
// Inline Method
//=============================================================================

//-----------------------------------------------------------------------------
inline Window::Window(int width, int height, const char *title, bool vsync, bool enableOpenGL)
{
	thisWnd = this;

	glfwSetErrorCallback(ErrorGLFWfunc);

    if ( !glfwInit() )
        throw std::exception("Failed to init GLFW");

#if SUPPORT_OPENGL
	if ( enableOpenGL )
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	else
#endif
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if ( !m_window  )
		throw std::exception("Failed to create GLFW window");	

#if SUPPORT_OPENGL
	if ( enableOpenGL )
	{
		glfwMakeContextCurrent(m_window);

		if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
			throw std::exception("Failed to init GLAD");

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

		glfwSwapInterval(vsync == true ? 1 : 0);
	}
#endif	
}
//-----------------------------------------------------------------------------
inline Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
	thisWnd = nullptr;
}
//-----------------------------------------------------------------------------
inline bool Window::IsEnd()
{
	return glfwWindowShouldClose(m_window);
}
//-----------------------------------------------------------------------------
inline void Window::Swap()
{
#if SUPPORT_OPENGL
	if ( enableOpenGL )
		glfwSwapBuffers(m_window);
#endif
	glfwPollEvents();
}
//-----------------------------------------------------------------------------