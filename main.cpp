#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>

// window TITLE, WIDTH and HEIGHT
#define WINDOW_TITLE_PREFIX "Object Puzzle"
int windowWidth = 800,
    windowHeight = 600;

// coodinates of the center for the primitives objects.
int yPrimCoo = windowHeight-(0.15*windowHeight),i=0;
int temp = windowWidth/7;
int xPrimCoo[6] = {temp, 2*temp, 3*temp, 4*temp, 5*temp, 6*temp};

// function prototype
static void ResizeFunction(int, int);
static void displayFunction(void);
static void idleFunction(void);
static void keyFunction(unsigned char, int, int);
static void mouseMove(int, int);
static void mouseButton(int, int, int, int);

int main(int argc, char *argv[])
{
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(WINDOW_TITLE_PREFIX);

    // setting correct perspective when window size is changed.
    glutReshapeFunc(ResizeFunction);

    // register callbacks
    glutDisplayFunc(displayFunction);

    // keyFunction is called whenever an keyboard event is encountered.
    glutKeyboardFunc(keyFunction);

    // this IDLE tells the glut to keep calling render function
    // to allow animations.
    glutIdleFunc(idleFunction);

    // sets the glut to listen to the mouse actions.
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // sets the background color RED:GREEN:BLUE:ALPHA
    glClearColor(0,0,0,0);

    gluOrtho2D(0,windowWidth,0,windowHeight);

    // enter GLUT event processing cycle/
    glutMainLoop();

    return 1;
}

static void ResizeFunction(int width, int height)
{
    windowHeight=height;
    windowWidth=width;
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}
void drawCenterPointsForPrimitives ()
{
    glPointSize(3.0);	// sers the width of the point
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
        glVertex3f(xPrimCoo[0],yPrimCoo,0.0);
        glVertex3f(xPrimCoo[1],yPrimCoo,0.0);
        glVertex3f(xPrimCoo[2],yPrimCoo,0.0);
        glVertex3f(xPrimCoo[3],yPrimCoo,0.0);
        glVertex3f(xPrimCoo[4],yPrimCoo,0.0);
        glVertex3f(xPrimCoo[5],yPrimCoo,0.0);
    glEnd();
}
void drawSquare(int x,int y)
{
    glColor3f(1.0,1.0,1.0);
    int num=30;
    glBegin(GL_POLYGON);
        glVertex3f(x-num,y+num,0.0);
        glVertex3f(x+num,y+num,0.0);
        glVertex3f(x+num,y-num,0.0);
        glVertex3f(x-num,y-num,0.0);
    glEnd();
}
void drawRectangle(int x,int y)
{
    glColor3f(1.0,1.0,1.0);
    int bre=30, len=50;

    glBegin(GL_POLYGON);
        glVertex3f(x-len,y+bre,0.0);
        glVertex3f(x+len,y+bre,0.0);
        glVertex3f(x+len,y-bre,0.0);
        glVertex3f(x-len,y-bre,0.0);
    glEnd();
}
void drawCircle(float cx, float cy, float r, int num_segments) {
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex3f(x + cx, y + cy,0.0);//output vertex
    }
    glEnd();
}
void drawTriangle(int cx,int cy)
{
    glBegin(GL_TRIANGLES);
        glVertex3f(cx,cy+30,0.0);
        glVertex3f(cx-(30*0.8660), cy-(50.0*0.5), 0.0);
        glVertex3f(cx+(30*0.8660), cy-(50.0*0.5), 0.0);
    glEnd();
}
void drawHexagon(int x, int y)
{
    glBegin(GL_POLYGON);
        glVertex3f(x-30,y,0.0);
        glVertex3f(x-(30*0.5),y+(30*0.8660),0.0);
        glVertex3f(x+(30*0.5),y+(30*0.8660),0.0);
        glVertex3f(x+30,y,0.0);
        glVertex3f(x+(30*0.5),y-(30*0.8660),0.0);
        glVertex3f(x-(30*0.5),y-(30*0.8660),0.0);
    glEnd();
}
void drawKite(int x,int y)
{
    glBegin(GL_POLYGON);
        glVertex3f(x,y+30,0.0);
        glVertex3f(x-30,y,0.0);
        glVertex3f(x,y-50,0.0);
        glVertex3f(x+30,y,0.0);
    glEnd();
}
static void displayFunction(void)
{
    // clear previous colors.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawCenterPointsForPrimitives();
    drawSquare(xPrimCoo[0],yPrimCoo);
    drawRectangle(xPrimCoo[1],yPrimCoo);
    drawCircle(xPrimCoo[2],yPrimCoo,30,100);
    drawTriangle(xPrimCoo[3], yPrimCoo);
    drawHexagon(xPrimCoo[4],yPrimCoo);
    drawKite(xPrimCoo[5],yPrimCoo);

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
    printf("keyboard--%d->%c\n",key,char(key));
    switch (key)
    {
        case 27 :
        case 'q':
            printf("quit\n");
            exit(0);
            break;
    }
    glutPostRedisplay();
}

static void mouseMove(int x, int y) {
    printf("Mouse-Coodinates:(%d,%d)\n",x,y );
}

static void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			printf("Mouse--LEFT--onKeyUp--(%d,%d)\n",x,y );
		}
		else  {// state = GLUT_DOWN
            printf("Mouse--LEFT--onKeyDown--(%d,%d)\n",x,y );
		}
	}
    else if (button == GLUT_RIGHT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            printf("Mouse--RIGHT--onKeyUp--(%d,%d)\n",x,y );
        }
        else  {// state = GLUT_DOWN
            printf("Mouse--RIGHT--onKeyDown--(%d,%d)\n",x,y );
        }
    }
    else {

        // when the button is released
        if (state == GLUT_UP) {
            printf("Mouse--MIDDLE--onKeyUp--(%d,%d)\n",x,y );
        }
        else  {// state = GLUT_DOWN
            printf("Mouse--MIDDLE--onKeyDown--(%d,%d)\n",x,y );
        }
    }
}
