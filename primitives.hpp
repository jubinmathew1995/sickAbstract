int windowWidth = 800,
    windowHeight = 600;
// coodinates of the center for the primitives objects.
int yPrimCoo,temp,xPrimCoo[6];

int flag=0,winStatus=0;

void *currentfont;

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
