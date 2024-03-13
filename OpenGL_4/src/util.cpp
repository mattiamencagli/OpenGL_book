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

    if (ActiveIndexBuffer == 0) {
        //glDrawElements(GL_POINTS, 48, GL_UNSIGNED_BYTE, NULL);
        glDrawElements(GL_LINE_LOOP, 48, GL_UNSIGNED_BYTE, NULL);
        //glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, NULL);
    } else {
        //glDrawElements(GL_POINTS, 36, GL_UNSIGNED_BYTE, NULL);
        glDrawElements(GL_LINE_LOOP, 36, GL_UNSIGNED_BYTE, NULL);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
    }
    glPointSize(5);

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

void KeyboardFunction(unsigned char Key, int X, int Y){
	switch (Key)
	{
	case 'T':
	case 't':
		{
			ActiveIndexBuffer = (ActiveIndexBuffer ? 0 : 1);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[ActiveIndexBuffer]);
			break;
		}
	default:
		break;
	}
}