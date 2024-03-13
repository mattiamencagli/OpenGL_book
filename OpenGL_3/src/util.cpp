#include "util.hpp"

void ResizeFunction(int Width, int Height){
    CurrentWidth = Width;
    CurrentHeight = Height;
    //std::cout << " new Width and Height : " << Width << " x " << Height << std::endl;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(){
    ++FrameCount;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, (GLvoid*)0);

    // just the right portion, using the offset 36
    //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, (GLvoid*)(sizeof(GLubyte) * 36));
    // just the left portion, using the offset 24
    //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, (GLvoid*)(sizeof(GLubyte) * 24));
    // just the bottom portion, using the offset 12
    //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, (GLvoid*)(sizeof(GLubyte) * 12));

    glutSwapBuffers();
    glutPostRedisplay();
}

void TimerFunction(int Value){
    if (Value) {
    char* TempString = (char*)
        malloc(512 + strlen(WINDOW_TITLE_PREFIX));

    sprintf(TempString, "%s: %d Frames Per Second @ %d x %d", WINDOW_TITLE_PREFIX, FrameCount, CurrentWidth, CurrentHeight);

    glutSetWindowTitle(TempString);
    free(TempString);
    }

    FrameCount = 0;
    glutTimerFunc(1000, TimerFunction, 1);
    // every 1000 ms call TimerFunction with argument "1"
}

void IdleFunction(){
    glutPostRedisplay();
}