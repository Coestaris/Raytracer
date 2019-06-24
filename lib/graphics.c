//
// Created by maxim on 6/24/19.
//

#include "graphics.h"

void initGraphics(int argc, const char** argv, uint16_t winW, uint16_t winH, const char* winTitle)
{
#ifdef OVERRIDE_GL_VERSION
    puts("Overriding default OpenGL version...");

    glutInitContextVersion(MAJOR_GL_VERSION, MINOR_GL_VERSION);
    glutInitContextProfile(GLUT_CORE_PROFILE);
#endif
    //srand(time(NULL));

    glutInit(&argc, (char**)argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
    glutInitWindowSize(winW, winH);

    glutCreateWindow(winTitle);

    glViewport(0, 0, winW, winH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, winW, winH, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    printf("[GL Spec]: Vendor: %s\n", (char*) glGetString(GL_VENDOR));
    printf("[GL Spec]: Using OpenGL Version: %s\n", (char*) glGetString(GL_VERSION));
    printf("[GL Spec]: Using OpenGL Rendered: %s\n", (char*) glGetString(GL_RENDERER));
    printf("[GL Spec]: GLSH Version: %s\n=========\n", (char*) glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutSwapBuffers();
}

void freezeGraphics()
{
    glutDisplayFunc(displayFunc);
    glutIdleFunc(displayFunc);
    glutMainLoop();
}



void closeGraphics()
{
    //Hmm..
}