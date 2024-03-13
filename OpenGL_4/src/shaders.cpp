
#include "shaders.hpp"

void Cleanup()
{
    DestroyShaders();
    DestroyVBO();
}

void CreateVBO()
{
    Vertex Vertices[] =
        {
            {{0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
            // Top [left bottom, right bottom, center bottom, center top]
            {{-0.2f, 0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{0.2f, 0.8f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
            {{0.0f, 0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
            {{0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
            // Bottom
            {{-0.2f, -0.8f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
            {{0.2f, -0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{0.0f, -0.8f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
            {{0.0f, -1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
            // Left
            {{-0.8f, -0.2f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{-0.8f, 0.2f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
            {{-0.8f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
            {{-1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
            // Right
            {{0.8f, -0.2f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
            {{0.8f, 0.2f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{0.8f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
            {{1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}};

    GLubyte Indices[] = {
        // Top
        0, 1, 3,
        0, 3, 2,
        3, 1, 4,
        3, 4, 2,
        // Bottom
        0, 5, 7,
        0, 7, 6,
        7, 5, 8,
        7, 8, 6,
        // Left
        0, 9, 11,
        0, 11, 10,
        11, 9, 12,
        11, 12, 10,
        // Right
        0, 13, 15,
        0, 15, 14,
        15, 13, 16,
        15, 16, 14};

    GLubyte AlternateIndices[] = {
        // Outer square border:
        3, 4, 16,
        3, 15, 16,
        15, 16, 8,
        15, 7, 8,
        7, 8, 12,
        7, 11, 12,
        11, 12, 4,
        11, 3, 4,

        // Inner square
        0, 11, 3,
        0, 3, 15,
        0, 15, 7,
        0, 7, 11};

    GLenum ErrorCheckValue = glGetError();

    const size_t BufferSize = sizeof(Vertices);
    const size_t VertexSize = sizeof(Vertices[0]);
    const size_t RgbOffset = sizeof(Vertices[0].XYZW);

    glGenVertexArrays(1, &VaoId); // number of Vertex Arrays to generate, stored in the arrays parameter (&VaoId)
    glBindVertexArray(VaoId);

    glGenBuffers(1, &VboId); // number of Vertex Buffer to generate, stored in the arrays parameter (&VboId)
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW); // copy to GPU

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0); // first 0 is the layout location
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid *)RgbOffset);

    glEnableVertexAttribArray(0); // 0 is the layout location
    glEnableVertexAttribArray(1);

    glGenBuffers(2, IndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(AlternateIndices), AlternateIndices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

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
    glDeleteBuffers(1, &VboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, IndexBufferId);

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

    // link all the shaders together
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