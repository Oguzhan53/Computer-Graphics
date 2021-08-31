#include <iostream>
#include <stdlib.h>

#include <GL/glut.h>


enum operation { Up, Down, Right, Left, RotateRight, RotateLeft, RotateUp, RotateDown, ScalePos, ScaleNeg, Empty }; /* Kullanici operasyonlari */

enum operation oper;
double angleHori = 30;	/* Dikey rotation acisi */
double angleVer = 0;	/* Yatay rotation acisi */
double horizontal = 10; /* Yatay translation hareket uzunlugu */
double vertical = 10;	/* Dikey translation hareket uzunlugu */
double scale_coef = 1;	/* Scaling katsayisi */
double depth = -200;	/* Ekran derinligi */


using namespace std;
void key_press(unsigned char key, int x, int y);
void construct_home();


int main(int argc, char** argv) {
	oper = Empty;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("3D Home Translation - Rotatin - Scaling ");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(construct_home);
	glutKeyboardFunc(key_press);
	glutMainLoop();
	return 0;
}




/*
*	Bu fonksiyon kullanici tusa bastiginda hangi islemi yapmak istedigini anlar ve oper degerine yapilacak islemi esitler
*/
void key_press(unsigned char key, int x, int y) {

	/*									   Islem				Tuslar	*/
	/*------------------------------------------------------------------*/
	if (key == 56)						/* Yukari Translation	(8)		*/
		oper = Up;
	else if (key == 50)					/* Asagi Translation	(2)		*/
		oper = Down;
	else if (key == 54)					/* Saga Translation		(6)		*/
		oper = Right;
	else if (key == 52)					/* Sola Translation		(4)		*/
		oper = Left;
	else if (key == 119 || key == 87)	/* Yukari Rotation		(w)		*/
		oper = RotateUp;
	else if (key == 115 || key == 83)	/* Asagi Rotation		(s)		*/
		oper = RotateDown;
	else if (key == 100 || key == 68)	/* Saga Rotation		(d)		*/
		oper = RotateRight;
	else if (key == 97 || key == 65)	/* Sola Rotation		(a)		*/
		oper = RotateLeft;
	else if (key == 43)					/* Buyutme (Scaling)	(+)		*/
		oper = ScalePos;
	else if (key == 45)					/* Kucultme (Scaling)	(-)		*/
		oper = ScaleNeg;
	else if (key == 27)					/* Cikis				(esc)	*/
		exit(0);
	else
		oper = Empty;

	glutPostRedisplay();
}




/*
*	Bu fonksiyon eve kullanicinin istedigi islemi uygular ve evi 3D olarak yeniden olusturur
*/
void construct_home() {

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(30, 1.0, 1.0, 20000.0);  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPopMatrix();
	glPushMatrix();
	gluLookAt( 
		200.0f, 25.0f, 400.0f,
		30.0f, 20.0f, 20.0f,
		0.0f, 1.0f, 0.0f
	);


	switch (oper)
	{
	case Up:			/*  Yukari Translation */
		oper = Empty;
		vertical += 10;
		break;
			
	case Down:			/* Asagi Translation */
		vertical -= 10;
		oper = Empty;
		break;

	case Right:			/* Saga Translation	*/
		horizontal += 10;
		oper = Empty;
		break;

	case Left:			/* Sola Translation */
		horizontal -= 10;
		oper = Empty;
		break;

	case RotateRight:	/* Saga Rotation */
		angleHori += 1.0f;
		if (angleHori > 360)
			angleHori -= 360;
		oper = Empty;
		break;

	case RotateLeft:	/* Sola Rotation */
		angleHori -= 1.0f;
		if (angleHori < 0)
			angleHori += 360;
		oper = Empty;
		break;

	case RotateUp:		/* Yukari Rotation */
		angleVer += 1.0f;
		if (angleVer > 360)
			angleVer -= 360;
		oper = Empty;
		break;

	case RotateDown:	/* Asagi Rotation */
		angleVer -= 1.0f;
		if (angleVer < 360)
			angleVer += 360;
		oper = Empty;
		break;

	case ScalePos:		/* Buyutme (Scaling) */
		scale_coef *= 1.2;
		oper = Empty;
		break;

	case ScaleNeg:		/* Kucultme (Scaling) */
		scale_coef /= 1.2;
		oper = Empty;
		break;

	default:
		break;
	}
	glTranslatef(horizontal, vertical, depth); /* Translation fonksiyonu */
	glRotatef(angleHori, 0, 1, 0);  /* Rotatiton fonksiyonu */
	glRotatef(angleVer, 1, 0, 0); /* Rotatiton fonksiyonu */
	glScalef(scale_coef, scale_coef, scale_coef); /* Scaling fonksiyonu */


	/* Arka taraf */
	glColor3f(0.5f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-10, -10, -5);
	glVertex3f(60, -10, -5);
	glVertex3f(60, 30, -5);
	glVertex3f(-10, 30, -5);
	glEnd();

	/* Arka pencere 1 */
	glColor3f(0.0f, 0.2f, 0.8f);
	glBegin(GL_POLYGON);
	glVertex3f(5, 10, -5.1);
	glVertex3f(5, 25, -5.1);
	glVertex3f(15, 25, -5.1);
	glVertex3f(15, 10, -5.1);
	glEnd();

	/* Arka pencere 2 */
	glColor3f(0.0f, 0.2f, 0.8f);
	glBegin(GL_POLYGON);
	glVertex3f(40, 10, -5.1);
	glVertex3f(40, 25, -5.1);
	glVertex3f(50, 25, -5.1);
	glVertex3f(50, 10, -5.1);
	glEnd();


	/* On taraf */
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-10, -10, 45);
	glVertex3f(60, -10, 45);
	glVertex3f(60, 30, 45);
	glVertex3f(-10, 30, 45);
	glEnd();

	/* Kapi */
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(45, -10, 45.1);
	glVertex3f(45, 20, 45.1);
	glVertex3f(55, 20, 45.1);
	glVertex3f(55, -10, 45.1);
	glEnd();
	/* On pencere 2 */
	glColor3f(0.0f, 0.2f, 0.8f);
	glBegin(GL_POLYGON);
	glVertex3f(0, 10, 45.1);
	glVertex3f(0, 25, 45.1);
	glVertex3f(10, 25, 45.1);
	glVertex3f(10, 10, 45.1);
	glEnd();

	/* On pencere 2 */
	glColor3f(0.0f, 0.2f, 0.8f);
	glBegin(GL_POLYGON);
	glVertex3f(25, 10, 45.1);
	glVertex3f(25, 25, 45.1);
	glVertex3f(35, 25, 45.1);
	glVertex3f(35, 10, 45.1);
	glEnd();


	/* Sag taraf */
	glColor3f(1.0f, 0.5f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-10, -10, 45);
	glVertex3f(-10, -10, -5);
	glVertex3f(-10, 30, -5);
	glVertex3f(-10, 30, 45);
	glEnd();

	/* Sol Taraf */
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	glVertex3f(60, -10, 45);
	glVertex3f(60, -10, -5);
	glVertex3f(60, 30, -5);
	glVertex3f(60, 30, 45);
	glEnd();

	/* Sag cati */
	glColor3f(0.0f, 0.5f, 0.5f);
	glBegin(GL_TRIANGLES);
	glVertex3f(60, 30, -5);
	glVertex3f(60, 30, 45);
	glVertex3f(60, 60, 20);
	glEnd();

	/* Sol cati */
	glColor3f(2.0f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-10, 30, -5);
	glVertex3f(-10, 30, 45);
	glVertex3f(-10, 60, 20);
	glEnd();

	/* Arka cati */
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-10, 30, -5);
	glVertex3f(60, 30, -5);
	glVertex3f(60, 60, 20);
	glVertex3f(-10, 60, 20);
	glEnd();

	/* On cati */
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-10, 30, 45);
	glVertex3f(60, 30, 45);
	glVertex3f(60, 60, 20);
	glVertex3f(-10, 60, 20);
	glEnd();

	/* Taban */
	glColor3f(0.7f, 0.2f, 0.1f);
	glBegin(GL_POLYGON);
	glVertex3f(-10, -10, -5);
	glVertex3f(60, -10, -5);
	glVertex3f(60, -10, 45);
	glVertex3f(-10, -10, 45);
	glEnd();


	glFlush();
	glPopMatrix();
	glutSwapBuffers();


}



