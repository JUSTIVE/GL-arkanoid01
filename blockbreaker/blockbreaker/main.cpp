#include<Windows.h>
#include<string>
#include<fstream>
#include<gl\glut.h>
#include<gl\gl.h>
#include<gl\glu.h>
#include<iostream>
//#include"glew.h"
GLint stage=0;

using namespace std;
GLboolean beginning = false, ballup = false, befree = false, comboAnimTrig = false;
GLfloat barX = 1.0, barY = 0.2, barWidth = 5.0;
GLfloat ballX = 0.6, ballY = 0.5, ballRad = 0.02, velo = 0.00005,acc=0;
GLfloat slant = -2, intercept = 5,crushrange=ballRad,comboX=1,comboY=1;
GLint crushCase = 4,life=3,combo=0,comboAnimDuration=0;

//yumenoohimesama
void MyDisplay(){
	switch (stage)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;

	default:
		break;
	}
	if(life>-1)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		char Life[6] = "life:";
		glPushMatrix();
		glScalef(1 / 200.0, 1 / 200.0, 1 / 200.0);
		glTranslatef(0.2, 1.8, 0);
		for (int i = 0; i < 5; i++) {
			glColor3f(0.5, 0.5, 0.5);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, Life[i]);
		}
		glColor3f(1, 1, 1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, life + '0');
		glPopMatrix();

		glPushMatrix(); {
			char combos[10];
			_itoa_s(combo, combos, 10);
			glTranslatef(comboX, comboY, 0);
			glScalef(1 / 1000.0, 1 / 1000.0, 1 / 1000.0);
			for (int i = 0; i < strlen(combos);i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, combos[i]);
		}
		glPopMatrix();

		glPushMatrix(); {
			glTranslatef(barX, barY, 0);
			glScalef(barWidth, 1.0, 1.0);
			glutSolidCube(0.05);
		}
		glPopMatrix();
		glPointSize(4.0f);
		glBegin(GL_POINTS);{
			glVertex3f(ballX,ballY,0);
			//glutSolidSphere(ballRad, 500, 500);
		}		
		glEnd();
		barX = ballX;
		crushCase = 4;
		printf("%lf \t %lf\n",ballX,ballY);
		
		if(comboAnimTrig){
			if (comboAnimDuration < 10) {
				if (comboAnimDuration % 2) {
					comboX = 1.01;
				}
				else {
					comboX = 0.99;
				}
				comboAnimDuration++;
			}
			else {
				comboAnimTrig = false;
				comboAnimDuration = 0;
				comboX = 1;
				comboY = 1;
			}
		}
		
		
		
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT);
		char Over[2][10] = { "GAME","OVER" };
		glPushMatrix();
		glTranslatef(-0.14, 0.33, 0);
		glScalef(1 / 150.0, 1 / 150.0, 1 / 150.0);
		for (int j = 0; j < 5; j++) {
			glColor3f(0.3, 0.3, 0.3);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, Over[1][j]);
		}
		glPopMatrix();
		
		
		glPushMatrix();
		glTranslatef(-0.15, 1, 0);
		glScalef(1 / 150.0, 1 / 150.0, 1 / 150.0);
		for (int j = 0; j < 5; j++) {
			glColor3f(1, 1, 1);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, Over[0][j]);
		}
		glPopMatrix();
	}
	glutSwapBuffers();
}
void ballMove(){
	{
		if ((ballY > 2 - crushrange) && (ballX > 2 - crushrange)) { crushCase = 4; befree = true; printf("case 4\n"); }//오른쪽 위
		else if ((ballY > 2 - crushrange) && (ballX < 0 + crushrange)) { crushCase = 5; befree = true; printf("case 5\n");}//왼쪽 위
		else if (ballY > 2 - crushrange) { crushCase = 0; ballup = !ballup; befree = true; printf("case 0\n");}//위
		else if (ballY < 0 + crushrange) { crushCase = 3; ballup = !ballup; befree = true; printf("case 3\n");}//아래
		else if (ballX > 2 - crushrange){ crushCase = 1; befree = true; printf("case 1\n");}//오른쪽
		else if (ballX < 0 + crushrange){ crushCase = 2; befree = true; printf("case 2\n");}//왼쪽
		else if (((ballX < barX + (0.025*barWidth)) && (ballX > barX - (0.025*barWidth))) &&
					(ballY - ballRad < barY+0.03)&&!ballup){//바
			crushCase = 6;
			ballup = !ballup;
			befree = true;
		}
		else {//충돌없음
			befree = false;
		}

		if(befree){
			acc += 0.001;
			switch (crushCase)
			{
			case 0://위			
				slant = 0 - slant;
				intercept = ballY - ballX*slant;
				ballY = 2.0;
				break;
			case 1://오른쪽
				slant = 0 - slant;
				intercept = ballY - ballX*slant;
				ballX = 2.0;
				break;
			case 2://왼쪽
				slant = 0 - slant;
				intercept = ballY - ballX*slant;
				ballX = 0.0;
				break;
			case 3://아래
				ballX = 2.0;
				ballY = 0.6;
				slant = -2, intercept = 1;
				ballup = !ballup;
				acc = 0;
				combo = 0;
				life--;
				getchar();
				break;
			case 4://오른쪽 위
				ballup = !ballup;
				ballX = 2 - ballRad;
				ballY = 2 - ballRad;
				break;
			case 5://왼쪽 위	
				ballup = !ballup;
				ballX = 0 + (2*ballRad);
				ballY = 0+ (2 * ballRad);
				break;
			default://판에 맞은 경우				
				slant = 0 - slant;
				intercept = ballY - ballX*slant;
				combo++;
				comboAnimTrig = true;
				break;
			}
		}
		//공 움직임
		
	}
	if (ballup){
		ballY = ballY += (velo+acc);
		ballX = (GLfloat)(ballY - intercept) / (GLfloat)slant;
	}
	else{
		ballY = ballY -= (velo+acc);
		ballX = (GLfloat)(ballY - intercept) / (GLfloat)slant;
	}

	if (ballX < -0.1 || ballX>2.1 || ballY<-0.1||ballY>2.1) {
		
	}
	velo = (ballY / 50) + 0.02;	
	
	glutPostRedisplay();
}
void MyReshape(int width, int height){	
	glutReshapeWindow(500, 500);
}
void MyKeyboard(unsigned char KeyPressed, int X, int Y){
	if (KeyPressed == 'a')
	{
		if (barX > 0 + (barWidth*0.05 / 2))
		{
			barX -= (0.1+acc);			
		}
	}
	else if (KeyPressed == 'd'){
		if (barX < 2 - (barWidth*0.05 / 2)){
			barX += (0.1+acc);		
		}
	}
	else if (KeyPressed == 'r') {
		life=3;
	}
}
void mousemove(int x, int y) {
	barX = ((GLfloat)x/ (GLfloat)250);
	glutPostRedisplay();
}
int main(int argc,char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Roll the Ball");	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutInitWindowSize(500, 500);
	glOrtho(0, 2, 0, 2, -1, 1);
	glViewport(0, 0, 500, 500);	
	glMatrixMode(GL_MODELVIEW);
	glutIdleFunc(ballMove);
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(MyDisplay);
	glutPassiveMotionFunc(mousemove);
	glutKeyboardFunc(MyKeyboard);

	glutMainLoop();
	return 0;
}