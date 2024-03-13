
#include "shaders.hpp"

void Cleanup()
{
    DestroyShaders();
    DestroyVBO();
}

void CreateVBO()
{
    // TRIANGLE EXAMPLE
    /*GLfloat Vertices[] = {
        -0.8f, -0.8f, 0.0f, 1.0f,
        0.0f, 0.8f, 0.0f, 1.0f,
        0.8f, -0.8f, 0.0f, 1.0f};
    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f}; */

    // RECTANGLE EXAMPLE (using 2 separate triangles)
    /*GLfloat Vertices[] = {
        -0.8f, 0.8f, 0.0f, 1.0f,
        0.8f, 0.8f, 0.0f, 1.0f,
        -0.8f, -0.8f, 0.0f, 1.0f,

        -0.8f, -0.8f, 0.0f, 1.0f,
        0.8f, 0.8f, 0.0f, 1.0f,
        0.8f, -0.8f, 0.0f, 1.0f};
    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f};*/

    // RECTANGLE EXAMPLE (using 2 triangles with 2 common vertex)
    GLfloat Vertices[] = {
        -0.8f, 0.8f, 0.0f, 1.0f,
        0.8f, 0.8f, 0.0f, 1.0f,
        -0.8f, -0.8f, 0.0f, 1.0f,
        0.8f, -0.8f, 0.0f, 1.0f};
    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f};

    GLenum ErrorCheckValue = glGetError();

    glGenVertexArrays(1, &VaoId); // number of Vertex Arrays to generate, stored in the arrays parameter (&VaoId)
    glBindVertexArray(VaoId);

    glGenBuffers(1, &VboId); // number of Vertex Buffer to generate, stored in the arrays parameter (&VboId)
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); // copy to GPU
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);                     // first 0 is the layout location
    glEnableVertexAttribArray(0);                                              // 0 is the layout location

    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(stderr, "ERROR: Could not create a VBO: %s \n", gluErrorString(ErrorCheckValue));
        exit(-1);
    }
}

void DestroyVBO()
{
    GLenum ErrorCheckValue = glGetError();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &VboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(stderr, "ERROR: Could not destroy the VBO: %s \n", gluErrorString(ErrorCheckValue));
        exit(-1);
    }
}

void CreateShaders()
{
    GLenum ErrorCheckValue = glGetError();

    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL); // copy GLSL source code to OpenGL for compilation. 1 long string.
    glCompileShader(VertexShaderId);                        // compile the shaders

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);

    // link alll the shaders together
    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);
    glUseProgram(ProgramId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(stderr, "ERROR: Could not create the shaders: %s \n", gluErrorString(ErrorCheckValue));
        exit(-1);
    }
}

void DestroyShaders()
{
    GLenum ErrorCheckValue = glGetError();

    glUseProgram(0);

    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);

    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
            stderr,
            "ERROR: Could not destroy the shaders: %s \n",
            gluErrorString(ErrorCheckValue));

        exit(-1);
    }
}