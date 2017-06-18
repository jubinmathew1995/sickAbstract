#define SIZE 512

int windowWidth = 800,
    windowHeight = 600;
// coodinates of the center for the primitives objects.
int yPrimCoo,temp,xPrimCoo[6];

int flag=-1,winStatus=0;

int windowStatus = 1;

int currentLevel = 1;

int placingPrimitives[6] = {0,0,0,0,0,0};

int boxStatus = 0,i=1;

int numberOfTries = 3,
    difficulty = 3;
char triesString[17];

int score=0;
// level clearing score
// easy level 5
// medium level 10
// hard level 15
/*  bonus level--number_of_tries--points
          easy      3           3
          easy      2           2
          easy      1           1
          medium    2           4
          medium    1           3
          hard      1           5
*/
void calScore() {
    int tempScore = 0;
    switch(difficulty){
        case 3:// Easy level
                tempScore += 5 + numberOfTries;
                break;
        case 2://Medium difficulty
                tempScore += 10 + (numberOfTries==2?4:3);
                break;
        case 1://Hard difficulty
                tempScore += 15 + 5;
                break;
    }
    score+=tempScore;
}

int primitiveColor[6][3] = {{239,83,80},{56,142,60},{33,150,243},{255,152,0},{153,0,0},{255,0,255}};
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
void drawstring(float x, float y, float z, char *str)//To render the text on the screen
{
	char *c;
	glRasterPos3f(x, y, z);

	for (c = str;*c != '\0';c++)
		glutBitmapCharacter(currentfont, *c);
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

void chooseColor(int r,int g,int b,int stat)
{
    glColor4ub(r,g,b,255);
}

void drawTextBox(int x,int y)
{
    int bre=30, len=100;

    glBegin(GL_POLYGON);
        glVertex3f(x-len,y+bre,0.0);
        glVertex3f(x+len,y+bre,0.0);
        glVertex3f(x+len,y-bre,0.0);
        glVertex3f(x-len,y-bre,0.0);
    glEnd();
}

void chooseColorWindow(int stat)
{
    if(stat==1)
        glColor4ub(255,87,51,255);
    else
        glColor4ub(255,87,51,77);

}
void draw_rectangle(double xmin,double ymin,double xmax,double ymax)
{
    glBegin(GL_POLYGON);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();
}
void drawWindow2Square(int x,int y)
{
    int num=30;
    glBegin(GL_POLYGON);
        glVertex3f(x-20,y+35,0.0);
        glVertex3f(x+35,y+35,0.0);
        glVertex3f(x+35,y-20,0.0);
        glVertex3f(x-20,y-20,0.0);
    glEnd();
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
    char lv[10];
    int lvNo,shapeCount,shapeIndex[6],centerShapeIndex,completed;
    movement disp[6];
    level()
    {
        lvNo=2;
        strcpy(lv,"");
        shapeCount=3;

        shapeIndex[0]=0;
        shapeIndex[1]=0;
        shapeIndex[2]=1;
        shapeIndex[3]=1;
        shapeIndex[4]=1;
        shapeIndex[5]=0;

        disp[2].setDisp(0,0);
        disp[3].setDisp(0,5);
        disp[4].setDisp(0,-5);
    }

    void break_and_set_level(char *line,int n)
    {
        int temp=0;
        char *x=strtok(line,":");   // level number -atoi

        // checking if this is the level which is requested.
        if(atoi(x)!=n)
            return;

        char *y=strtok(NULL,":");   // level string -str
        char *z=strtok(NULL,":");   // shape count -atoi
        char *a=strtok(NULL,":");   // primitive status -atoi
        char *c=strtok(NULL,":");   // primitive object coodinates -str
        char *d=strtok(NULL,":");   // number for center object.
        char *innele=strtok(a,",");
        temp = 0;
        while( innele != NULL )
       {
            shapeIndex[temp++]=atoi(innele);
            innele = strtok(NULL, ",");
       }
        char *coo=strtok(c,",");
        temp = 0;
        while( coo != NULL )
        {
            int x = atoi(coo);
            coo = strtok(NULL, ",");

            int y = atoi(coo);
            coo = strtok(NULL, ",");
            disp[temp++].setDisp(x,y);
        }
        // set level number.
        lvNo = atoi(x);

        // set level string.
        strcpy(lv,y);

        // set shape count for the given level.
        shapeCount = atoi(z);

        // setting centerShapeIndex variable of the class level.
        centerShapeIndex = atoi(d);
    }

    void DataExtract(int n)
    {
        char data[100];
        FILE *fp;
        fp = fopen("config","r");
        while(fgets(data, 255, (FILE*) fp)) {
            char *line=strtok(data,";");
            break_and_set_level(line,n);
        }
        fclose(fp);
    }

    void selectLevel(int n)
    {
        DataExtract(n);
    }
}play;

class PrimiviteShapes
{
protected:
    ////////////////////////////////////////////////
    // for writing the object index in the screen.//
    ////////////////////////////////////////////////
    void drawObjectIndex(int x, int y, char name[])
    {
        setFont(GLUT_BITMAP_HELVETICA_18);
        drawstring(x,y+45,0.0,name);
    }
    ////////////////////////
    // drawing the object.//
    ////////////////////////
    void drawSquare(int x,int y)
    {
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
    /////////////////////////////////////////////////////////
    /// Drawing the object border if the object is active.///
    /////////////////////////////////////////////////////////
    void drawSquareBorder(int x,int y)
    {
        int num=33;
        glLineWidth(2.0);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINE_LOOP);
            glVertex3f(x-num,y+num,0.0);
            glVertex3f(x+num,y+num,0.0);
            glVertex3f(x+num,y-num,0.0);
            glVertex3f(x-num,y-num,0.0);
        glEnd();
    }
    void drawRectangleBorder(int x,int y)
    {
        int bre=33, len=53;
        glLineWidth(2.0);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINE_LOOP);
            glVertex3f(x-len,y+bre,0.0);
            glVertex3f(x+len,y+bre,0.0);
            glVertex3f(x+len,y-bre,0.0);
            glVertex3f(x-len,y-bre,0.0);
        glEnd();
    }
    void drawCircleBorder(float cx, float cy, float r, int num_segments)
    {
        glLineWidth(2.0);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINE_LOOP);
        for (int ii = 0; ii < num_segments; ii++)   {
            float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
            float x = r * cosf(theta);//calculate the x component
            float y = r * sinf(theta);//calculate the y component
            glVertex3f(x + cx, y + cy,0.0);//output vertex
        }
        glEnd();
    }
    void drawTriangleBorder(int cx,int cy)
    {
        glLineWidth(2.0);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINE_LOOP);
            glVertex3f(cx,cy+30+5,0.0);
            glVertex3f(cx-(30*0.8660)-4, cy-(50.0*0.5)-3, 0.0);
            glVertex3f(cx+(30*0.8660)+4, cy-(50.0*0.5)-3, 0.0);
        glEnd();
    }
    void drawHexagonBorder(int x,int y)
    {
        glLineWidth(2.0);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINE_LOOP);
            glVertex3f(x-34,y,0.0);
            glVertex3f(x-(30*0.5),y+(30*0.8660)+3,0.0);
            glVertex3f(x+(30*0.5),y+(30*0.8660)+3,0.0);
            glVertex3f(x+34,y,0.0);
            glVertex3f(x+(30*0.5),y-(30*0.8660)-3,0.0);
            glVertex3f(x-(30*0.5),y-(30*0.8660)-3,0.0);
        glEnd();
    }
    void drawKiteBorder(int x,int y)
    {
        glLineWidth(2.0);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINE_LOOP);
            glVertex3f(x,y+33,0.0);
            glVertex3f(x-33,y,0.0);
            glVertex3f(x,y-54,0.0);
            glVertex3f(x+33,y,0.0);
        glEnd();
    }

public:
    void draw(int stat,GLenum mode)
    {
        glLoadName(stat+1);
        switch(stat)
        {
            case 0: // drawing the shape 
                    drawSquare(xPrimCoo[0],yPrimCoo);
                    // labeling the object index in the screen.
                    drawObjectIndex(xPrimCoo[0],yPrimCoo,"1.");
                    if (flag==0) //Checking for active object for making border around it
                        drawSquareBorder(xPrimCoo[0],yPrimCoo);
                    break;
            case 1: drawRectangle(xPrimCoo[1],yPrimCoo);
                    drawObjectIndex(xPrimCoo[1],yPrimCoo,"2.");
                    if (flag==1)
                        drawRectangleBorder(xPrimCoo[1],yPrimCoo);
                    break;
            case 2: drawCircle(xPrimCoo[2],yPrimCoo,30,100);
                    drawObjectIndex(xPrimCoo[2],yPrimCoo,"3.");
                    if (flag==2)
                        drawCircleBorder(xPrimCoo[2],yPrimCoo,33,100);
                    break;
            case 3: drawTriangle(xPrimCoo[3], yPrimCoo);
                    drawObjectIndex(xPrimCoo[3],yPrimCoo,"4.");
                    if (flag==3)
                        drawTriangleBorder(xPrimCoo[3], yPrimCoo);
                    break;
            case 4: drawHexagon(xPrimCoo[4],yPrimCoo);
                    drawObjectIndex(xPrimCoo[4],yPrimCoo,"5.");
                    if (flag==4)
                        drawHexagonBorder(xPrimCoo[4],yPrimCoo);
                    break;
            case 5: drawKite(xPrimCoo[5],yPrimCoo);
                    drawObjectIndex(xPrimCoo[5],yPrimCoo,"6.");
                    if (flag==5)
                        drawKiteBorder(xPrimCoo[5],yPrimCoo);
                    break;
        }
    }
}topBar;
class PrimiviteMovShapes:private PrimiviteShapes
{
public:
    void drawMovSquare(char a)
    {
        int x,y;
        if(a=='s'){
            chooseColor(primitiveColor[0][0],primitiveColor[0][1],primitiveColor[0][2],play.shapeIndex[0]);
            x = (windowWidth*0.25)+(10.0*mov[0].xMov);
            y = (windowHeight*0.35)+(10.0*mov[0].yMov);
        }
        else if(a=='r'){
            x = (windowWidth*0.75)+(10.0*play.disp[0].xMov);
            y = (windowHeight*0.35)+(10.0*play.disp[0].yMov);
        }
        drawSquare(x,y);
    }
    void drawMovRectangle(char a)
    {
        float x,y;
        int bre=30, len=50;
        if(a=='s'){
            chooseColor(primitiveColor[1][0],primitiveColor[1][1],primitiveColor[1][2],play.shapeIndex[1]);
            x = (windowWidth*0.25)+(10.0*mov[1].xMov);
            y = (windowHeight*0.35)+(10.0*mov[1].yMov);
        }
        else if(a=='r'){
            x = (windowWidth*0.75)+(10.0*play.disp[1].xMov);
            y = (windowHeight*0.35)+(10.0*play.disp[1].yMov);
        }
        drawRectangle(x,y);
    }
    void drawMovCircle(char a) {
        float num_segments=300,r=30,cx,cy;

        if(a=='s'){
            chooseColor(primitiveColor[2][0],primitiveColor[2][1],primitiveColor[2][2],play.shapeIndex[2]);
            cx = (windowWidth*0.25)+(10.0*mov[2].xMov);
            cy = (windowHeight*0.35)+(10.0*mov[2].yMov);
        }
        else if(a=='r'){
            cx = (windowWidth*0.75)+(10.0*play.disp[2].xMov);
            cy = (+windowHeight*0.35)+(10.0*play.disp[2].yMov);
        }
        drawCircle(cx,cy,r,num_segments);
    }
    void drawMovTriangle(char a)
    {
        int cx,cy;

        if(a=='s'){
            chooseColor(primitiveColor[3][0],primitiveColor[3][1],primitiveColor[3][2],play.shapeIndex[3]);
            cx = (windowWidth*0.25)+(10.0*mov[3].xMov);
            cy = (windowHeight*0.35)+(10.0*mov[3].yMov);
        }
        else if(a=='r'){
            cx = (windowWidth*0.75)+(10.0*play.disp[3].xMov);
            cy = (windowHeight*0.35)+(10.0*play.disp[3].yMov);
        }
        drawTriangle(cx,cy);
    }
    void drawMovHexagon(char a)
    {
        int x,y;

        if(a=='s'){
            chooseColor(primitiveColor[4][0],primitiveColor[4][1],primitiveColor[4][2],play.shapeIndex[4]);
            x = (windowWidth*0.25)+(10.0*mov[4].xMov);
            y = (windowHeight*0.35)+(10.0*mov[4].yMov);
        }
        else if(a=='r'){
            x = (windowWidth*0.75)+(10.0*play.disp[4].xMov);
            y = (windowHeight*0.35)+(10.0*play.disp[4].yMov);
        }
        drawHexagon(x,y);
    }
    void drawMovKite(char a)
    {
        int x,y;

        if(a=='s'){
            chooseColor(primitiveColor[5][0],primitiveColor[5][1],primitiveColor[5][2],play.shapeIndex[5]);
            x = (windowWidth*0.25)+(10.0*mov[5].xMov);
            y = (windowHeight*0.35)+(10.0*mov[5].yMov);
        }
        else if(a=='r'){
            x = (windowWidth*0.75)+(10.0*play.disp[5].xMov);
            y = (windowHeight*0.35)+(10.0*play.disp[5].yMov);
        }
        drawKite(x,y);
    }
    void draw(int stat, char a)
    {
        // a='r' means result to be displayed in the right side of the screen
        // a='s' means solution to be displayed in the left side of the screen.
        if(a=='r')
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4ub(255,87,51,255);
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
        else
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            switch(stat)
            {
                case 0:if(placingPrimitives[0]==1)drawMovSquare(a);break;
                case 1:if(placingPrimitives[1]==1)drawMovRectangle(a);break;
                case 2:if(placingPrimitives[2]==1)drawMovCircle(a);break;
                case 3:if(placingPrimitives[3]==1)drawMovTriangle(a);break;
                case 4:if(placingPrimitives[4]==1)drawMovHexagon(a);break;
                case 5:if(placingPrimitives[5]==1)drawMovKite(a);break;
            }
        }

    }

}item;

void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint names, *ptr;

   ptr = (GLuint *) buffer;
   for (i = 0; i < hits; i++)
   { /*  for each hit  */
      names = *ptr;
      ptr+=3;
      for (j = 0; j < names; j++)
      { /*  for each name */
         if( *ptr == 8 )
         {
            // if the player clear this level then in 'n'/'N'
            // we have to jump into the next level.
            currentLevel++;
            if(currentLevel > 7 ){
                windowStatus = 4;
            }
            // reset the winStatus to initial before going to new level.
            winStatus=0;
            // load the data of the new level.
            play.selectLevel(currentLevel);
            // Resetting the displacement of each of the primitives to
            // their actual value.
            for(int i=0;i<6;i++)
            {
                mov[i].setDisp(0,0);
                // reInitializing the selected shapes.
                placingPrimitives[i]=0;
            }
            // making the selected object back to its default position.
            flag=-1;
            break;
         }
         else if( *ptr == 7 )
         {
            // reset the winStatus to initial before going to new level.
            winStatus=0;
            // Resetting the displacement of each of the primitives to
            // their actual value.
            for(int i=0;i<6;i++)
            {
                mov[i].setDisp(0,0);
                // reInitializing the selected shapes.
                placingPrimitives[i]=0;
            }
            // making the selected object back to its default position.
            flag=-1;
            windowStatus = 2;
            break;
         }
         flag=*ptr-1;
         placingPrimitives[flag]?placingPrimitives[flag]=0:placingPrimitives[flag]=1;
         ptr++;
      }
   }
}
void resetParameters() {
    // reset the winStatus to initial before going to new level.
    winStatus=0;

    // Resetting the displacement of each of the primitives to
    // their actual value.
    for(int i=0;i<6;i++) {
        // setting the displacement to center.
        mov[i].setDisp(0,0);
        // reInitializing the selected shapes.
        placingPrimitives[i]=0;
    }                             

    // removing the previous active object.
    flag=-1;                                    
}