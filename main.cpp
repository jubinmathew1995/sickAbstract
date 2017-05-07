#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <ctype.h>
#include <math.h>
#include "primitives.hpp"

// window TITLE, WIDTH and HEIGHT
#define WINDOW_TITLE_PREFIX "Sick Abstract"
extern int windowWidth,windowHeight;

// coodinates of the center for the primitives objects.
extern int yPrimCoo,temp,xPrimCoo[6];

extern int flag,winStatus;

extern void *currentfont;

extern int windowStatus;

// function prototype
static void ResizeFunction(int, int);
static void displayFunction(void);
static void idleFunction(void);
static void keyFunction(unsigned char, int, int);
static void processSpecialKeys(int, int, int);
// static void mouseMove(int, int);
static void mouseButton(int, int, int, int);

extern movement mov[6];
extern level play;
extern PrimiviteShapes topBar;
extern PrimiviteMovShapes item;

int main(int argc, char *argv[])
{
    // init GLUT and create Window
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

    // sets the glut to listen to the mouse actions.
    glutMouseFunc(mouseButton);
    // glutMotionFunc(mouseMove);

    // sets the background color RED:GREEN:BLUE:ALPHA
    glClearColor((23.0/255),(32.0/255),(42.0/255),0);

    gluOrtho2D(0,windowWidth,0,windowHeight);

    // Enabling transparency for the color buffer.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // enter GLUT event processing cycle/
    glutMainLoop();

    return 1;
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

    //window3();

    window1();
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
    //keyboardWindow3(key,x,y);
    keyboardWindow1(key,x,y);
    glutPostRedisplay();
}

static void processSpecialKeys(int key, int x, int y)
{
	// specialKeyboardWindow3(key,x,y);
    specialKeyboardWindow1(key,x,y);
    glutPostRedisplay();
}
// static void mouseMove(int x, int y) {
//     printf("Mouse-Coodinates:(%d,%d)\n",x,y );
// }

static void mouseButton(int button, int state, int x, int y)
{
    mouseWindow3(button,state,x,y);
}
