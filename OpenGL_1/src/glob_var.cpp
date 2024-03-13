#include "glob_var.hpp"

int CurrentWidth = 800;
int CurrentHeight = 600;
int WindowHandle = 0;
unsigned int FrameCount = 0;

GLuint VertexShaderId{};
GLuint FragmentShaderId{};
GLuint ProgramId{};
GLuint VaoId{};
GLuint VboId{};
GLuint ColorBufferId{};
const GLchar *VertexShader =
    {
        "#version 400\n"

        "layout(location=0) in vec4 in_Position;\n"
        "layout(location=1) in vec4 in_Color;\n"
        "out vec4 ex_Color;\n"

        "void main(void)\n"
        "{\n"
        "  gl_Position = in_Position;\n"
        "  ex_Color = in_Color;\n"
        "}\n"
    };
const GLchar *FragmentShader =
    {
        "#version 400\n"

        "in vec4 ex_Color;\n"
        "out vec4 out_Color;\n"

        "void main(void)\n"
        "{\n"
        "  out_Color = ex_Color;\n"
        "}\n"
    };