#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
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

// function prototype
static void ResizeFunction(int, int);
static void displayFunction(void);
static void idleFunction(void);
static void keyFunction(unsigned char, int, int);
static void processSpecialKeys(int, int, int);
static void mouseMove(int, int);
static void mouseButton(int, int, int, int);

extern movement mov[6];
extern level play;
extern PrimiviteShapes topBar;
extern PrimiviteMovShapes item;

int main(int argc, char *argv[])
{
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    windowWidth = glutGet(GLUT_SCREEN_WIDTH);
    windowHeight = glutGet(GLUT_SCREEN_HEIGHT);

    calCenters();

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
    // glutMouseFunc(mouseButton);
    // glutMotionFunc(mouseMove);

    // sets the background color RED:GREEN:BLUE:ALPHA
    glClearColor((23.0/255),(32.0/255),(42.0/255),0);

    gluOrtho2D(0,windowWidth,0,windowHeight);

    // Enabling transparency for the color buffer.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enter GLUT event processing cycle/
    glutMainLoop();

    return 1;
}

void drawAxes()
{
    glColor4ub(255,87,51,255);

    glLineWidth(3.0);
    glBegin(GL_LINES);
        glVertex3f(windowWidth/2,windowHeight*0.70,0.0);
        glVertex3f(windowWidth/2,0.0,0.0);
    glEnd();
}

void drawGrid()
{
    int num = windowWidth/(5.0*4);
    glColor4ub(255,87,51,255);

    glPointSize(3.0);
    glBegin(GL_POINTS);
        for(int i=-200;i<=200;i+=20)
        {
             glVertex3f((windowWidth*0.25)+i,(windowHeight*0.35),0.0);
             glVertex3f((windowWidth*0.25),(windowHeight*0.35)+i,0.0);
        }
    glEnd();
}

void chooseColor(int stat)
{
    if(stat==1)
        glColor4ub(255,87,51,255);
    else
        glColor4ub(255,87,51,77);

}

static void ResizeFunction(int width, int height)
{
    // windowHeight=height;
    // windowWidth=width;
    glutReshapeWindow(windowWidth,windowHeight);
}

static void displayFunction(void)
{
    // clear previous colors.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the top bar shapes with the specific color with which they are needed.
    for(int i=0;i<6;i++)
    {
        chooseColor(play.shapeIndex[i]);
        topBar.draw(i);
    }

    drawAxes();
    drawGrid();

    // display the level of the stage.
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring((3*windowWidth/4-50),(windowHeight*0.70),0.0,play.lv);

    // display the warning for each stage.
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring((windowWidth/4-100),(windowHeight*0.03),0.0,play.centerShape);

    // display the win and loss status for the game.
    if(winStatus==0){
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring((3*windowWidth/4-100),(windowHeight*0.03),0.0,"                    ");
    }
    else if(winStatus==1){
        glColor4f(0.0,1.0,0.0,1.0);
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring((3*windowWidth/4-80),(windowHeight*0.03),0.0,"Great! Level Cleared");
    }
    if(winStatus==-1){
        glColor4f(1.0,0.0,0.0,1.0);
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring((3*windowWidth/4-80),(windowHeight*0.05),0.0,"Sorry! Try again    ");
    }

    // used for drawing the moving figures/shapes.
    item.draw(0,'s');
    item.draw(1,'s');
    item.draw(2,'s');
    item.draw(3,'s');
    item.draw(4,'s');
    item.draw(5,'s');

    // for drawing the solution
    item.draw(0,'r');
    item.draw(1,'r');
    item.draw(2,'r');
    item.draw(3,'r');
    item.draw(4,'r');
    item.draw(5,'r');

    // // swaps the front and back buffers.
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
    int count=0;
    printf("keyboard--%d->%c\n",key,char(key));
    switch (key)
    {
        case 27 :
        case 'q':
            printf("quit\n");
            exit(0);
            break;
        case 'W':
        case 'w':
        // play.shapeIndex[flag] is used to ensure only the
        // figure available is moved nothing else.
            if(mov[flag].yMov<=20&&play.shapeIndex[flag]==1)
                mov[flag].yMov++;
            break;
        case 'S':
        case 's':
        // play.shapeIndex[flag] is used to ensure only the
        // figure available is moved nothing else.
            if(mov[flag].yMov>=-20&&play.shapeIndex[flag]==1)
                mov[flag].yMov--;
            break;
        case 'A':
        case 'a':
        // play.shapeIndex[flag] is used to ensure only the
        // figure available is moved nothing else.
            if(mov[flag].xMov>=-20&&play.shapeIndex[flag]==1)
                mov[flag].xMov--;
            break;
        case 'D':
        case 'd':
            // play.shapeIndex[flag] is used to ensure only the
            // figure available is moved nothing else.
            if(mov[flag].xMov<=20&&play.shapeIndex[flag]==1)
                mov[flag].xMov++;
            break;
        case 13: // when enter is pressed.
            for(int i=0;i<6;i++)
            {
                printf("%d-->(%d,%d)\n",i,mov[i].xMov,mov[i].yMov);
                if(play.shapeIndex[i]==1)
                    if(mov[i].xMov==play.disp[i].xMov && mov[i].yMov==play.disp[i].yMov)
                        count++;
            }
            if(count==play.shapeCount){
                printf("win\n");
                winStatus=1;
                count=0;
            }
            else    {
                count=0;
                printf("loose\n");
                winStatus=-1;
            }
            break;
        case '1':flag=0;break;
        case '2':flag=1;break;
        case '3':flag=2;break;
        case '4':flag=3;break;
        case '5':flag=4;break;
        case '6':flag=5;break;
    }
    glutPostRedisplay();
}

static void processSpecialKeys(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT :
            if(mov[flag].xMov>=-20&&play.shapeIndex[flag]==1)
                mov[flag].xMov--;
			break;
		case GLUT_KEY_RIGHT :
            if(mov[flag].xMov<=20&&play.shapeIndex[flag]==1)
                mov[flag].xMov++;
			break;
		case GLUT_KEY_UP :
            if(mov[flag].yMov<=20&&play.shapeIndex[flag]==1)
                mov[flag].yMov++;
            break;
		case GLUT_KEY_DOWN :
            if(mov[flag].yMov>=-20&&play.shapeIndex[flag]==1)
                mov[flag].yMov--;
            break;
	}
    glutPostRedisplay();
}
// static void mouseMove(int x, int y) {
//     printf("Mouse-Coodinates:(%d,%d)\n",x,y );
// }
//
// static void mouseButton(int button, int state, int x, int y) {
//
// 	// only start motion if the left button is pressed
// 	if (button == GLUT_LEFT_BUTTON) {
//
// 		// when the button is released
// 		if (state == GLUT_UP) {
// 			printf("Mouse--LEFT--onKeyUp--(%d,%d)\n",x,y );
// 		}
// 		else  {// state = GLUT_DOWN
//             printf("Mouse--LEFT--onKeyDown--(%d,%d)\n",x,y );
// 		}
// 	}
//     else if (button == GLUT_RIGHT_BUTTON) {
//
//         // when the button is released
//         if (state == GLUT_UP) {
//             printf("Mouse--RIGHT--onKeyUp--(%d,%d)\n",x,y );
//         }
//         else  {// state = GLUT_DOWN
//             printf("Mouse--RIGHT--onKeyDown--(%d,%d)\n",x,y );
//         }
//     }
//     else {
//
//         // when the button is released
//         if (state == GLUT_UP) {
//             printf("Mouse--MIDDLE--onKeyUp--(%d,%d)\n",x,y );
//         }
//         else  {// state = GLUT_DOWN
//             printf("Mouse--MIDDLE--onKeyDown--(%d,%d)\n",x,y );
//         }
//     }
// }
