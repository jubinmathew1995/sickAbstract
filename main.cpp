#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>

// window TITLE, WIDTH and HEIGHT
#define WINDOW_TITLE_PREFIX "Sick Abstract"
int windowWidth = 800,
    windowHeight = 600;

// coodinates of the center for the primitives objects.
int yPrimCoo,temp,xPrimCoo[6];


// movement global variables.
class movement
{
    public:
        int xMov,yMov;
        movement()
        {
            xMov=yMov=0;
        }
        void setDisp(int x,int y)
        {
            xMov=x;
            yMov=y;
        }
}mov[6];
class level
{
public:
    char *lv,*centerShape;
    int shapeCount,shapeIndex[6],centerShapeIndex,completed;
    movement disp[6];
    level()
    {
        lv="LEVEL-002";
        shapeCount=3;

        shapeIndex[0]=0;
        shapeIndex[1]=0;
        shapeIndex[2]=1;
        shapeIndex[3]=1;
        shapeIndex[4]=1;
        shapeIndex[5]=0;

        centerShape="Figure 3 MUST be at center";

        disp[2].setDisp(0,0);
        disp[3].setDisp(0,5);
        disp[4].setDisp(0,-5);
    }
}play;

int flag=0,winStatus=0;

// function prototype
static void ResizeFunction(int, int);
static void displayFunction(void);
static void idleFunction(void);
static void keyFunction(unsigned char, int, int);
static void processSpecialKeys(int, int, int);
static void mouseMove(int, int);
static void mouseButton(int, int, int, int);

// recalculate the centers for the objects.
void calCenters()
{
    yPrimCoo = windowHeight-(0.15*windowHeight);
    temp = windowWidth/7;
    xPrimCoo[0] = temp;
    xPrimCoo[1] = 2*temp;
    xPrimCoo[2] = 3*temp;
    xPrimCoo[3] = 4*temp;
    xPrimCoo[4] = 5*temp;
    xPrimCoo[5] = 6*temp;
}

void *currentfont;
void setFont(void *font) //function to change the font of the text
{
	currentfont = font;
}
void drawstring(float x, float y, float z, char *string)//To render the text on the screen
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string;*c != '\0';c++)
		glutBitmapCharacter(currentfont, *c);
}
class PrimiviteShapes
{
public:
    void drawSquare(int x,int y)
    {
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring(x,y+45,0.0,"1.");

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
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring(x,y+45,0.0,"2.");

        int bre=30, len=50;

        glBegin(GL_POLYGON);
            glVertex3f(x-len,y+bre,0.0);
            glVertex3f(x+len,y+bre,0.0);
            glVertex3f(x+len,y-bre,0.0);
            glVertex3f(x-len,y-bre,0.0);
        glEnd();
    }
    void drawCircle(float cx, float cy, float r, int num_segments)
    {
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring(cx,cy+45,0.0,"3.");

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
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring(cx,cy+45,0.0,"4.");

        glBegin(GL_TRIANGLES);
            glVertex3f(cx,cy+30,0.0);
            glVertex3f(cx-(30*0.8660), cy-(50.0*0.5), 0.0);
            glVertex3f(cx+(30*0.8660), cy-(50.0*0.5), 0.0);
        glEnd();
    }
    void drawHexagon(int x, int y)
    {
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring(x,y+45,0.0,"5.");

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
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring(x,y+45,0.0,"6.");

        glBegin(GL_POLYGON);
            glVertex3f(x,y+30,0.0);
            glVertex3f(x-30,y,0.0);
            glVertex3f(x,y-50,0.0);
            glVertex3f(x+30,y,0.0);
        glEnd();
    }
    void draw(int stat)
    {
        switch(stat)
        {
            case 0:drawSquare(xPrimCoo[0],yPrimCoo);break;
            case 1:drawRectangle(xPrimCoo[1],yPrimCoo);break;
            case 2:drawCircle(xPrimCoo[2],yPrimCoo,30,100);break;
            case 3:drawTriangle(xPrimCoo[3], yPrimCoo);break;
            case 4:drawHexagon(xPrimCoo[4],yPrimCoo);break;
            case 5:drawKite(xPrimCoo[5],yPrimCoo);break;
        }
    }
}topBar;

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

static void ResizeFunction(int width, int height)
{
    // windowHeight=height;
    // windowWidth=width;
    glutReshapeWindow(windowWidth,windowHeight);
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
class PrimiviteMovShapes
{
public:
    void drawMovSquare(char a)
    {
        int x,y;
        if(a=='s'){
            x = (windowWidth*0.25)+(10.0*mov[0].xMov);
                y = (windowHeight*0.35)+(10.0*mov[0].yMov);
        }
        else if(a=='r'){
            x = (windowWidth*0.75)+(10.0*play.disp[0].xMov);
                y = (windowHeight*0.35)+(10.0*play.disp[0].yMov);
        }
        glColor4ub(255,87,51,255);
        int num=30;
        glBegin(GL_POLYGON);
            glVertex3f(x-num,y+num,0.0);
            glVertex3f(x+num,y+num,0.0);
            glVertex3f(x+num,y-num,0.0);
            glVertex3f(x-num,y-num,0.0);
        glEnd();
    }
    void drawMovRectangle(char a)
    {
        float x,y;
        glColor4ub(255,87,51,255);
        int bre=30, len=50;
        if(a=='s'){
            x = (windowWidth*0.25)+(10.0*mov[1].xMov);
                    y = (windowHeight*0.35)+(10.0*mov[1].yMov);
        }
        else if(a=='r'){
            x = (windowWidth*0.75)+(10.0*play.disp[1].xMov);
                    y = (windowHeight*0.35)+(10.0*play.disp[1].yMov);
        }


        glBegin(GL_POLYGON);
            glVertex3f(x-len,y+bre,0.0);
            glVertex3f(x+len,y+bre,0.0);
            glVertex3f(x+len,y-bre,0.0);
            glVertex3f(x-len,y-bre,0.0);
        glEnd();
    }
    void drawMovCircle(char a) {
        float num_segments=300,r=30,cx,cy;

        if(a=='s'){
            cx = (windowWidth*0.25)+(10.0*mov[2].xMov);
            cy = (windowHeight*0.35)+(10.0*mov[2].yMov);
        }
        else if(a=='r'){
            cx = (windowWidth*0.75)+(10.0*play.disp[2].xMov);
            cy = (windowHeight*0.35)+(10.0*play.disp[2].yMov);
        }

        glColor4ub(255,87,51,255);

        glBegin(GL_POLYGON);
        for (int ii = 0; ii < num_segments; ii++)   {
            float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
            float x = r * cosf(theta);//calculate the x component
            float y = r * sinf(theta);//calculate the y component
            glVertex3f(x + cx, y + cy,0.0);//output vertex
        }
        glEnd();
    }
    void drawMovTriangle(char a)
    {
        int cx,cy;

        if(a=='s'){
            cx = (windowWidth*0.25)+(10.0*mov[3].xMov);
            cy = (windowHeight*0.35)+(10.0*mov[3].yMov);
        }
        else if(a=='r'){
            cx = (windowWidth*0.75)+(10.0*play.disp[3].xMov);
            cy = (windowHeight*0.35)+(10.0*play.disp[3].yMov);
        }

        glColor4ub(255,87,51,255);

        glBegin(GL_TRIANGLES);
            glVertex3f(cx,cy+30,0.0);
            glVertex3f(cx-(30*0.8660), cy-(50.0*0.5), 0.0);
            glVertex3f(cx+(30*0.8660), cy-(50.0*0.5), 0.0);
        glEnd();
    }
    void drawMovHexagon(char a)
    {
        int x,y;

        if(a=='s'){
            x = (windowWidth*0.25)+(10.0*mov[4].xMov);
            y = (windowHeight*0.35)+(10.0*mov[4].yMov);
        }
        else if(a=='r'){
            x = (windowWidth*0.75)+(10.0*play.disp[4].xMov);
            y = (windowHeight*0.35)+(10.0*play.disp[4].yMov);
        }
        glColor4ub(255,87,51,255);

        glBegin(GL_POLYGON);
            glVertex3f(x-30,y,0.0);
            glVertex3f(x-(30*0.5),y+(30*0.8660),0.0);
            glVertex3f(x+(30*0.5),y+(30*0.8660),0.0);
            glVertex3f(x+30,y,0.0);
            glVertex3f(x+(30*0.5),y-(30*0.8660),0.0);
            glVertex3f(x-(30*0.5),y-(30*0.8660),0.0);
        glEnd();
    }
    void drawMovKite(char a)
    {
        int x,y;

        if(a=='s'){
            x = (windowWidth*0.25)+(10.0*mov[5].xMov);
            y = (windowHeight*0.35)+(10.0*mov[5].yMov);
        }
        else if(a=='r'){
            x = (windowWidth*0.75)+(10.0*play.disp[5].xMov);
            y = (windowHeight*0.35)+(10.0*play.disp[5].yMov);
        }
        glColor4ub(255,87,51,255);
        glBegin(GL_POLYGON);
            glVertex3f(x,y+30,0.0);
            glVertex3f(x-30,y,0.0);
            glVertex3f(x,y-50,0.0);
            glVertex3f(x+30,y,0.0);
        glEnd();
    }
    void draw(int stat, char a)
    {
        // a='r' means result to be displayed in the right side of the screen
        // a='s' means solution to be displayed in the left side of the screen.
        switch(stat)
        {
            case 0:if(play.shapeIndex[0]==1)drawMovSquare(a);break;
            case 1:if(play.shapeIndex[1]==1)drawMovRectangle(a);break;
            case 2:if(play.shapeIndex[2]==1)drawMovCircle(a);break;
            case 3:if(play.shapeIndex[3]==1)drawMovTriangle(a);break;
            case 4:if(play.shapeIndex[4]==1)drawMovHexagon(a);break;
            case 5:if(play.shapeIndex[5]==1)drawMovKite(a);break;
        }
    }

}item;
void chooseColor(int stat)
{
    if(stat==1)
        glColor4ub(255,87,51,255);
    else
        glColor4ub(255,87,51,77);

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
