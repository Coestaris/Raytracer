//
// Created by maxim on 6/24/19.
//

#include "graphics.h"

uint16_t winW;
uint16_t winH;

void initGraphics(int argc, const char** argv, uint16_t win_w, uint16_t win_h, const char* winTitle)
{
#ifdef OVERRIDE_GL_VERSION
    puts("Overriding default OpenGL version...");

    glutInitContextVersion(MAJOR_GL_VERSION, MINOR_GL_VERSION);
    glutInitContextProfile(GLUT_CORE_PROFILE);
#endif

    winW = win_w;
    winH = win_h;

    glutInit(&argc, (char**)argv);

#ifdef USE_DOUBLE_BUFFERING
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
#else
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
#endif
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

#ifdef USE_FBO
    surfInit();
#endif
}

void graphicsFlush(void)
{
#ifdef USE_DOUBLE_BUFFERING
    glutSwapBuffers();
#else
    glFlush();
#endif
}

#ifdef USE_FBO
GLuint surfTexID;
GLuint surfFBO;

void surfInit()
{
    glGenTextures(1, &surfTexID);
    glBindTexture(GL_TEXTURE_2D, surfTexID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    uint8_t* data = malloc(winW * winH * 4);
    memset(data, 0, winW * winH * 4);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, winW, winH, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    free(data);

    glGenFramebuffers(1, &surfFBO);
    glBindFramebuffer( GL_FRAMEBUFFER, surfFBO );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, surfTexID, 0 );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void surfBind()
{
    glColor4f(1, 1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, surfTexID);
}

int surfFree()
{
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    glDeleteFramebuffers( 1, &surfFBO );
    glDeleteTextures(1, &surfTexID);
}

int surfClear()
{
    uint8_t* data = malloc(winW * winH * 4);
    memset(data, 0, winW * winH * 4);
    glBindTexture(GL_TEXTURE_2D, surfTexID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, winW, winH, GL_RGBA, GL_UNSIGNED_BYTE, data);
    free(data);
}

void surfDraw()
{
    surfBind();
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(0.0, 0.0);
        glTexCoord2i(1, 0); glVertex2f(winW, 0.0);
        glTexCoord2i(1, 1); glVertex2f(winW, winH);
        glTexCoord2i(0, 1); glVertex2f(0.0, winH);
    glEnd();
}

void surfDrawPixels(pixelBuffer_t* buffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, surfFBO);
    glViewport(0, 0, winW, winH);

    glBegin(GL_POINTS);
    {
        for(size_t i = 0; i < buffer->count; i++)
        {
            glColor3f(buffer->colors[i].r, buffer->colors[i].g, buffer->colors[i].b);
            glVertex2f(buffer->pixels[i].x, buffer->pixels[i].y);
        }
    }
    glEnd();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    surfDraw();
}

#else
void surfDrawPixels(pixelBuffer_t* buffer)
{
    glBegin(GL_POINTS);
    {
        for(size_t i = 0; i < buffer->count; i++)
        {
            glColor3f(buffer->colors[i].r, buffer->colors[i].g, buffer->colors[i].b);
            glVertex2f(buffer->pixels[i].x, buffer->pixels[i].y);
        }
    }
    glEnd();
}
#endif
void displayFunc()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    graphicsFlush();
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