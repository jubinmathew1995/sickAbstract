#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <ctype.h>
#include <math.h>
#include "primitives.hpp"
#include "windows.hpp"

// window TITLE, WIDTH and HEIGHT
#define WINDOW_TITLE_PREFIX "Sick Abstract"
#define SUCCESS 0
extern int windowWidth,windowHeight;

// coodinates of the center for the primitives objects.
extern int yPrimCoo,temp,xPrimCoo[6];

extern int flag,winStatus;

extern void *currentfont;

extern int windowStatus;

extern int gameFinish;

// Menu handling function declaration
void menu(int);

// function prototype
static void ResizeFunction(int, int);
static void displayFunction(void);
static void idleFunction(void);
static void keyFunction(unsigned char, int, int);
static void processSpecialKeys(int, int, int);

extern movement mov[6];
extern level play;
extern PrimiviteShapes topBar;
extern PrimiviteMovShapes item;

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    windowWidth = glutGet(GLUT_SCREEN_WIDTH);
    windowHeight = glutGet(GLUT_SCREEN_HEIGHT);

    calCenters();
    play.selectLevel(1);

    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(0,0);
    glutCreateWindow(WINDOW_TITLE_PREFIX);


    // setting correct perspective when window size is changed.
    glutReshapeFunc(ResizeFunction);

    // register callbacks
    glutDisplayFunc(displayFunction);

    // keyFunction is called whenever an keyboard event is encountered.
    glutKeyboardFunc(keyFunction);

    // added special keyboard keys like up,down,left and right arroe keys.
    glutSpecialFunc(processSpecialKeys);

    // this IDLE tells the glut to keep calling render function
    // to allow animations.
    glutIdleFunc(idleFunction);

    // sets the background color RED:GREEN:BLUE:ALPHA
    glClearColor((23.0/255),(32.0/255),(42.0/255),0);
    // glClearColor(1.0,1.0,1.0,1);

    glutFullScreen();
    gluOrtho2D(0,windowWidth,0,windowHeight);

    // Enabling transparency for the color buffer.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enter GLUT event processing cycle/
    glutMainLoop();

    return SUCCESS;
}


static void ResizeFunction(int width, int height)
{
    //////////////////////////////////////////////////////
    ////// NEVER DELETE THIS SECTION - SINCE OBJECT //////
    ////// SELECTION DOESN'T WORK !!!!!!!!!!!!!!!!! //////
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /////////////////////////////////////////////////////
    //glutReshapeWindow(windowWidth,windowHeight);
}

static void displayFunction(void)
{
    // clear previous colors.
    glClear(GL_COLOR_BUFFER_BIT);

    if(windowStatus==1)
        window1();
    else if(windowStatus==2)
        window2();
    else if(windowStatus==3)
        window3();
    else if(windowStatus == 4)
        window4();
    else if(windowStatus == 5)
        window5();

    // swaps the front and back buffers.
    glutSwapBuffers();
}

static void idleFunction(void)
{
    // tells GULT to continously redisplay/call the
    // display function continously, so that animations
    // can be possible.
    glutPostRedisplay();
}

static void keyFunction(unsigned char key, int x, int y)
{
    if(windowStatus==1)
        keyboardWindow1(key,x,y);
    else if(windowStatus==2)
        keyboardWindow2(key,x,y);
    else if(windowStatus==3)
        keyboardWindow3(key,x,y);
    else if(windowStatus==4)
        keyboardWindow4(key,x,y);
    else if(windowStatus==5)
        keyboardWindow5(key,x,y);

    glutPostRedisplay();
}

static void processSpecialKeys(int key, int x, int y)
{
    if(windowStatus==1)
        specialKeyboardWindow1(key,x,y);
    else if(windowStatus==2)
        specialKeyboardWindow2(key,x,y);
    else if(windowStatus==3)
        specialKeyboardWindow3(key,x,y);
    else if(windowStatus==4)
        specialKeyboardWindow4(key,x,y);
    else if(windowStatus==5)
        specialKeyboardWindow5(key,x,y);
    glutPostRedisplay();
}
