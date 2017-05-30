#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Hipotrocoide.h"
#include <GL/freeglut.h>
#include "Camara.h"
//#include <GL/glut.h>
#include <vector>

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 500;
GLfloat t = 0;
// Viewing frustum parameters
GLdouble xRight=10, xLeft=-xRight, yTop=10, yBot=-yTop, N=1, F=1000;

// Camera parameters
GLdouble eyeX=100.0, eyeY=100.0, eyeZ=100.0;
GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
GLdouble upX=0, upY=1, upZ=0;

PuntoVector3D* eye;
PuntoVector3D* look;
PuntoVector3D* up;
// Scene variables
std::vector <GLUquadric*> tapas(4);
std::vector <GLUquadric*> ruedas(4);

GLfloat angX, angY, angZ; 
Hipotrocoide* hipo;
Camara* camara;
void CreaCoche(){

	//inicializo las ruedas
	for (unsigned int i = 0; i < 4; i++){
		tapas[i] = gluNewQuadric();
		
		ruedas[i] = gluNewQuadric();
	}	
	glPushMatrix();

	glScaled(0.3, 0.3, 0.3);
	glutSolidCube(3);
	glPushMatrix();
	
		glRotated(45, 0, 1, 0);
		GLfloat lightpos[4] = { 0, 0, -1, 0 };
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glPopMatrix();

	glEnable(GL_LIGHT1);
	//GLfloat dir[] = { hipo->C(t)->getX(), hipo->C(t)->getY(), hipo->C(t)->getZ(),1.0f };*/
	//glLightfv(GL_LIGHT1, GL_POSITION, dir);

	glPopMatrix();
}
void buildSceneObjects() {	 
    angX=0.0f;
    angY=0.0f;
    angZ=0.0f;	
	eye = new PuntoVector3D(eyeX, eyeY, eyeZ, 1);
	look = new PuntoVector3D(lookX, lookY, lookZ, 0);
	up = new PuntoVector3D(upX, upY, upZ, 0);
	camara = new Camara(eye, look, up);
}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
      
	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.9f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH); // Shading by default

	buildSceneObjects();

	// Light0
	glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    GLfloat d[]={0.7f,0.5f,0.5f,1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    GLfloat a[]={0.3f,0.3f,0.3f,1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat s[]={1.0f,1.0f,1.0f,1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, s);
	GLfloat p[]={25.0f, 25.0f, 25.0f, 1.0f};	 
	glLightfv(GL_LIGHT0, GL_POSITION, p);
	// Camera set up
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();     
	glOrtho(xLeft, xRight, yBot, yTop, N, F);

	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);  	
 }

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	

	glMatrixMode(GL_MODELVIEW);	 
	glPushMatrix();
	
		// Rotating the scene
		glRotatef(angX, 1.0f, 0.0f, 0.0f);
        glRotatef(angY, 0.0f, 1.0f, 0.0f);
        glRotatef(angZ, 0.0f, 0.0f, 1.0f);
		
		glLineWidth(1.5f);
		// Drawing axes
		glBegin( GL_LINES );			
			glColor3f(1.0,0.0,0.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(20, 0, 0);	     
	 
			glColor3f(0.0,1.0,0.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(0, 20, 0);	 
	 
			glColor3f(0.0,0.0,1.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 20);	     
		glEnd();
		 		
		// Drawing the scene	 		 
		glColor3f(1.0, 1.0, 1.0);
		//hipo->dibuja();
		glPushMatrix();
		glTranslated(t, 0, 0);
		float movimientoCoche = 0;
		movimientoCoche = 0;/*atan2((double)hipo->C�(t)->getX(), (double)hipo->C�(t)->getZ()) * 180 / 3.141519;*/
		glRotated(movimientoCoche , 0, 1, 0);
		CreaCoche();
		 //Sphere: radius=6, meridians=50, parallels=60
	glPopMatrix();
	glutSolidSphere(6, 50, 60);
	
	glFlush();
	glutSwapBuffers();
}


void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;
   
	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	glOrtho(xLeft, xRight, yBot, yTop, N, F);
}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop (); 
			break;		 
		case 'a': angX=angX+5; break;
		case 'z': angX=angX-5; break; 
		case 's': angY=angY+5; break;
		case 'x': angY=angY-5; break;
		case 'd': angZ=angZ+5; break;
		case 'c': angZ=angZ-5; break;  
		case 'w': t += 0.15; break;
		case 'e': t -= 0.15; break;
		case 'q':
			camara->roll();
			break;
		case '1':
			camara->giraX();
			break;
		case 'h':
			glEnable(GL_LIGHT0);
			break;
		case 'n':
			glDisable(GL_LIGHT0);
			break;
		case 'g':
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			break;

		case 'b':
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			break;

		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (0, 0);
	//glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");
    
	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting

	initGL();


	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	return 0;
}
