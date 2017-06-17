void window3(GLenum mode=GL_RENDER)
{
    if(numberOfTries==0)
        windowStatus = 5;
    // draw the top bar shapes with the specific color with which they are needed.
    for(int i=0;i<6;i++)
    {
        chooseColor(primitiveColor[i][0],primitiveColor[i][1],primitiveColor[i][2],play.shapeIndex[i]);
        topBar.draw(i,mode);
    }

    drawAxes();
    drawGrid();

    // display the level of the stage.
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring((3*windowWidth/4-50),(windowHeight*0.70),0.0,play.lv);

    // Display difficulty for the game.
    setFont(GLUT_BITMAP_HELVETICA_18);
    if(difficulty == 3){
      glColor4f(0,1,0,1);
      drawstring((windowWidth/10),(windowHeight*0.03),0.0,"EASY");}
    else if(difficulty == 2){
      glColor4f(1,1,0,1);
      drawstring((windowWidth/10),(windowHeight*0.03),0.0,"MEDIUM");}
    else if(difficulty == 1){
      glColor4f(1,0,0,1);
      drawstring((windowWidth/10),(windowHeight*0.03),0.0,"HARD");}

    sprintf(triesString,"Remaning tries %d",numberOfTries);
    drawstring((3.4*windowWidth/10),(windowHeight*0.03),0.0,triesString);

    glColor3f(1.0,1.0,1.0);
    char scoreString[15];
    sprintf(scoreString,"Score %d",score);
    drawstring((2*windowWidth/10),(windowHeight*0.03),0.0,scoreString);

    glColor4ub(255,87,51,255);


    // display the win and loss status for the game.
    if(winStatus==0){
        setFont(GLUT_BITMAP_HELVETICA_18);
        char name[]="                    ";
        drawstring((3*windowWidth/4-100),(windowHeight*0.03),0.0,name);
    }
    else if(winStatus==1){
        glColor4f(0.0,1.0,0.0,1.0);
        setFont(GLUT_BITMAP_HELVETICA_18);
        char name[]="Great! Level Cleared";
        drawstring((3*windowWidth/4-80),(windowHeight*0.12),0.0,name);

        // box for choose level.
        glColor4f(1.0,1.0,0.0,1.0);
        glLoadName(7);
        drawTextBox((3*windowWidth/4-120),(windowHeight*0.05));
        // box for next level.
        glColor4f(0.0,1.0,0.0,1.0);
        glLoadName(8);
        drawTextBox((3*windowWidth/4+120),(windowHeight*0.05));

        glColor4f(0.0,0.0,0.0,1.0);

        setFont(GLUT_BITMAP_HELVETICA_18);
        char name1[]="Next level (Press N)";
        drawstring((3*windowWidth/4+45),(windowHeight*0.04),0.0,name1);

        setFont(GLUT_BITMAP_HELVETICA_18);
        char name2[]="Select level (Press L)";
        drawstring((3*windowWidth/4-200),(windowHeight*0.04),0.0,name2);
    }
    if(winStatus==-1){
        glColor4f(1.0,0.0,0.0,1.0);
        setFont(GLUT_BITMAP_HELVETICA_18);
        char name[]="Sorry! Try again    ";
        drawstring((3*windowWidth/4-80),(windowHeight*0.08),0.0,name);
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

}
void keyboardWindow3(unsigned char key, int x, int y)
{
    int count=0;
    switch (key)
    {
        case 27 :
        case 'q':
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
        case 'l':
        case 'L':
            if(winStatus == 1){
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
                // reInitialize the score variable to 0 while going to level choosing screen.
                score = 0;
                break;
            }
            else break;
        case 'n':
        case 'N':
            // this if statement make sure that it should jump to next level
            // only when the currentLevel is cleared.
            if (winStatus == 1) {
              // if the player clear this level then in 'n'/'N'
              // we have to jump into the next level.
              currentLevel++;
              // if the game is in the final level and its already won
              // then make the screem to game finish.
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
            break;
        case 13: // when enter is pressed.
               for(int i=0;i<6;i++)
                {
                    if(play.shapeIndex[i]==1)
                        if((mov[i].xMov-mov[play.centerShapeIndex].xMov)==play.disp[i].xMov &&
                            (mov[i].yMov-mov[play.centerShapeIndex].yMov)==play.disp[i].yMov)
                            count++;
                }
                if(count==play.shapeCount){
                    //printf("win\n");
                    winStatus=1;
                    count=0;
                }
                else    {
                    count=0;
                    //printf("loose\n");
                    winStatus=-1;
                }
                if(numberOfTries>0 && winStatus != 1)
                  numberOfTries--;
                if(numberOfTries == 0 && winStatus != 1)
                    windowStatus = 5;
                
                if(winStatus==1)
                    calScore();
                break;
        case '1':flag=0;placingPrimitives[0]?placingPrimitives[0]=0:placingPrimitives[0]=1; break;
        case '2':flag=1;placingPrimitives[1]?placingPrimitives[1]=0:placingPrimitives[1]=1; break;
        case '3':flag=2;placingPrimitives[2]?placingPrimitives[2]=0:placingPrimitives[2]=1; break;
        case '4':flag=3;placingPrimitives[3]?placingPrimitives[3]=0:placingPrimitives[3]=1; break;
        case '5':flag=4;placingPrimitives[4]?placingPrimitives[4]=0:placingPrimitives[4]=1; break;
        case '6':flag=5;placingPrimitives[5]?placingPrimitives[5]=0:placingPrimitives[5]=1; break;
    }
}
void specialKeyboardWindow3(int key, int x, int y)
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
        case GLUT_KEY_F11:glutFullScreenToggle();break;
	}
}
void mouseWindow3(int button, int state, int x, int y)
{
    GLuint selectBuf[SIZE];
    GLint hits;
    GLint viewport[4];

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        glGetIntegerv (GL_VIEWPORT, viewport);

        glSelectBuffer (SIZE, selectBuf);
        glRenderMode(GL_SELECT);

        glInitNames();
        glPushName(0);

        glMatrixMode (GL_PROJECTION);
        glPushMatrix ();
        glLoadIdentity ();
        /* create 5x5 pixel picking region near cursor location */
        gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                      5.0, 5.0, viewport);
        gluOrtho2D (0, windowWidth, 0, windowHeight);
        window3(GL_SELECT);


        glMatrixMode (GL_PROJECTION);
        glPopMatrix ();
        glFlush ();

        hits = glRenderMode (GL_RENDER);
        processHits (hits, selectBuf);

        glutPostRedisplay();
        glutSwapBuffers();
    }
}

void window1()
{
    //glClearColor(1.0,1.0,1.0,0);
    if(boxStatus==1)
        chooseColorWindow(1);
    else
        chooseColorWindow(0);
    
    draw_rectangle((windowWidth/2)-50,windowHeight-600,(windowWidth/2)+50,windowHeight-570);

    if(boxStatus==2)
        chooseColorWindow(1);
    else
        chooseColorWindow(0);

    draw_rectangle((windowWidth/2)-50,windowHeight-700,(windowWidth/2)+50,windowHeight-670);

    glColor4f(0.0,1.0,0.0,1.0);
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    drawstring((windowWidth/2)-100,windowHeight-100,0.0,"SICK ABSTRACT!");
    glBegin(GL_LINES);
        glVertex2f((windowWidth/2)-100,windowHeight-120);
        glVertex2f((windowWidth/2)+100,windowHeight-120);
    glEnd();
    drawstring((windowWidth/2)-34,windowHeight-595,0.0,"PLAY");
    drawstring((windowWidth/2)-34,windowHeight-695,0.0,"EXIT");
}
void keyboardWindow1(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 13:
            if(boxStatus==2)
                exit(0);
            else if(boxStatus==1)
                windowStatus=2;
            break;
        case 27 :
        case 'q':
            exit(0);
            break;
    }
    glutPostRedisplay();
}
void specialKeyboardWindow1(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP :
            boxStatus=1;
            break;
        case GLUT_KEY_DOWN :
             boxStatus=2;
             break;
        case GLUT_KEY_F11:glutFullScreenToggle();break;
    }
    glutPostRedisplay();
}
void window2()
{
    winStatus=0;
    for(int i=0;i<6;i++)
    {
      mov[i].setDisp(0,0);
      // reInitializing the selected shapes.
      placingPrimitives[i]=0;
    }
    // making the selected object back to its default position.
    flag=-1;
    if(windowStatus!=3 && difficulty == 3){numberOfTries = 3;}
    if(windowStatus!=3 && difficulty == 2){ numberOfTries = 2;}
    if(windowStatus!=3 && difficulty == 1){ numberOfTries = 1;}
    drawstring((windowWidth/2)-100,windowHeight-100,0.0,"CHOOSE LEVEL!");
    glBegin(GL_LINES);
    glVertex2f((windowWidth/2)-100,windowHeight-120);
    glVertex2f((windowWidth/2)+100,windowHeight-120);
    glEnd();

    int coo[8][4] = {
                                    {-30,-205,30,-155},
                                    {120,-205,180,-155},
                                    {270,-205,330,-155},
                                    {420,-205,480,-155},
                                    {570,-205,630,-155},
                                    {720,-205,780,-155},
                                    {870,-205,930,-155}
                                };
    for(int tempi=0;tempi<8;tempi++) {
        if(boxStatus==tempi+1)
            chooseColorWindow(1);
        else
            chooseColorWindow(0);
        draw_rectangle((windowWidth/8)+coo[tempi][0],
                        (windowHeight)+coo[tempi][1],
                        (windowWidth/8)+coo[tempi][2],
                        (windowHeight)+coo[tempi][3]);
    }
    
    glColor4ub(255,255,255,255);
    drawstring((windowWidth/8)-10,windowHeight-190,0.0,"1.");
    drawstring((windowWidth/8)+140,windowHeight-190,0.0,"2.");
    drawstring((windowWidth/8)+290,windowHeight-190,0.0,"3.");
    drawstring((windowWidth/8)+450,windowHeight-190,0.0,"4.");
    drawstring((windowWidth/8)+590,windowHeight-190,0.0,"5.");
    drawstring((windowWidth/8)+750,windowHeight-190,0.0,"6.");
    drawstring((windowWidth/8)+890,windowHeight-190,0.0,"7.");
}
void keyboardWindow2(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 13:
            if(boxStatus==1)
            {
                windowStatus=3;
                currentLevel=1;
                play.selectLevel(currentLevel);

            }
            else if(boxStatus==2)
            {
                windowStatus=3;
                currentLevel=2;
                play.selectLevel(currentLevel);
            }
            else if(boxStatus==3)
            {
                windowStatus=3;
                currentLevel=3;
                play.selectLevel(currentLevel);
            }
            else if(boxStatus==4)
            {
                windowStatus=3;
                currentLevel=4;
                play.selectLevel(currentLevel);
            }
            else if(boxStatus==5)
            {
                windowStatus=3;
                currentLevel=5;
                play.selectLevel(currentLevel);
            }
            else if(boxStatus==6)
            {
                windowStatus=3;
                currentLevel=6;
                play.selectLevel(currentLevel);
            }
            else if(boxStatus==7)
            {
                windowStatus=3;
                currentLevel=7;
                play.selectLevel(currentLevel);
            }
            break;
        case 27 :
        case 'q':
            exit(0);
            break;
    }
    glutPostRedisplay();
}
void specialKeyboardWindow2(int key, int x, int y)
{

    switch (key) {
        case GLUT_KEY_LEFT :
            {if(i>1)
                i--;}
            break;
        case GLUT_KEY_RIGHT :
             {if(i<8)
                 i++;}
             break;
        case GLUT_KEY_F11:glutFullScreenToggle();break;
    }
    boxStatus=i;
}
void window4()
{
    glColor4ub(255,255,255,255);
    drawstring((windowWidth/2-150),windowHeight/2,0.0,"Congragulations Game Completed !");

    glColor4ub(255,255,255,255);
    char temp[50];
    sprintf(temp, "Total Score : %d",score);
    drawstring((windowWidth/2-80),windowHeight/3,0.0,temp);

    glColor4ub(255,255,255,255);
    drawstring((windowWidth/2-100),windowHeight/4,0.0,"Press 'esc' or 'q' to exit.");
    drawstring((windowWidth/2-155),windowHeight/5,0.0,"Press 'l' or 'L' to goto to level menu.");
}
void keyboardWindow4(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'l':
        case 'L':
            // key to go back to level choose window.
            windowStatus=2;
            score=0;
            winStatus=0;
            break;
    }
    glutPostRedisplay();
}
void specialKeyboardWindow4(int key, int x, int y)
{

    switch (key) {
        case GLUT_KEY_F11:glutFullScreenToggle();break;
    }
}
void window5()
{
    glColor4ub(255,0,0,255);
    drawstring((windowWidth/2-80),windowHeight/2,0.0,"Game Over !");

    glColor4ub(255,255,255,255);
    char temp[50];
    sprintf(temp, "Total Score : %d",score);
    drawstring((windowWidth/2-80),windowHeight/3,0.0,temp);

    glColor4ub(255,255,255,255);
    drawstring((windowWidth/2-100),windowHeight/4,0.0,"Press 'esc' or 'q' to exit.");
    drawstring((windowWidth/2-155),windowHeight/5,0.0,"Press 'l' or 'L' to goto to level menu.");
}
void keyboardWindow5(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'l':
        case 'L':
            // key to go back to level choose window.
            windowStatus=2;
            score=0;
            winStatus=0;
            break;
    }
    glutPostRedisplay();
}
void specialKeyboardWindow5(int key, int x, int y)
{

    switch (key) {
        case GLUT_KEY_F11:glutFullScreenToggle();break;
    }
}
