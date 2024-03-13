#ifndef GLOB_VAR_H
#define GLOB_VAR_H

#include "opengl_headers.hpp"

#define WINDOW_TITLE_PREFIX "OpenGL project 0"

extern int CurrentWidth;
extern int CurrentHeight;
extern int WindowHandle;
extern unsigned int FrameCount;

extern GLuint VertexShaderId;
extern GLuint FragmentShaderId;
extern GLuint ProgramId;
extern GLuint VaoId; //Vertex Array Object
extern GLuint VboId; //Vertex Buffer Object
extern GLuint IndexBufferId;
extern const GLchar* VertexShader;
extern const GLchar* FragmentShader;

typedef struct{
    float XYZW[4];
    float RGBA[4];
} Vertex;

#endif