#include "../Config.h"

#if SUPPORT_OPENGL

#if defined(_WIN32)
#define _GLAD_WIN32
#endif
#if defined(__linux__)
#define _GLAD_X11
#endif

#include <glad/src/glad.c>

#endif