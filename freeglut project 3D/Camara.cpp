#include "Camara.h"


Camara::Camara(PuntoVector3D * e, PuntoVector3D * l, PuntoVector3D *upp) :eye(e), look(l), up(upp)
{
	//camera set up
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());

	setCameraCoord();

	// Viewport set up
	right= 10;
	left= -10;
	top = 10;
	bottom = -10;
	nearr = 1;
	farr = 1000;

	// Frustum set up
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, nearr, farr);
}


Camara::~Camara()
{
	delete eye;
	delete look;
	delete up;
	delete u;
	delete v;
	delete n;
}

void Camara::setCameraCoord(){
	n = new PuntoVector3D(eye->getX() - look->getX(), eye->getY() - look->getY(), eye->getZ() - look->getZ(), 0);
	n->normalizar();
	u = up->clonar();
	u->productoVectorial(n);
	u->normalizar();
	v = n->productoVectorial(u);
}



void Camara::setMatrix(){
	W[0] = u->getX(); W[4] = u->getY(); W[8] = u->getZ();  W[12] = -eye->productoEscalar(u);
	W[1] = v->getX(); W[5] = v->getY(); W[9] = v->getZ();  W[13] = -eye->productoEscalar(v);
	W[2] = n->getX(); W[6] = n->getY(); W[10] = n->getZ(); W[14] = -eye->productoEscalar(n);
	W[3] = 0;         W[7] = 0;         W[11] = 0;         W[15] = 1;
}



void Camara::lookAt(PuntoVector3D * eye, PuntoVector3D * look, PuntoVector3D * up){
	this->eye = eye;
	this->look = look;
	this->up = up;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getX(), up->getZ());
}
void Camara::setOrtho(int left, int right, int bottom, int top, int nearr = -1, int farr = 1){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	left = left;
	right = right;
	bottom = bottom;
	top = top;
	glOrtho(left, right, bottom, top, nearr, farr);
}
void Camara::setViewPort(GLint x, GLint y, GLint x2, GLint y2){
	glViewport(x, y, x2, y2);
}

void Camara::roll(){

	GLfloat angulo = 5 * 3.141592 / 180;
	PuntoVector3D* auxV = new PuntoVector3D(cos(angulo)*v->getX() - sin(angulo)*u->getX(), cos(angulo)*v->getY() - sin(angulo)*u->getY(), cos(angulo)*v->getZ() - sin(angulo)*u->getZ(), 0);
	PuntoVector3D* auxU = new PuntoVector3D(cos(angulo)*u->getX() + sin(angulo)*v->getX(), cos(angulo)*u->getY() + sin(angulo)*v->getY(), cos(angulo)*u->getZ() + sin(angulo)*v->getZ(), 0);


	u = new PuntoVector3D(auxU->getX(), auxU->getY(), auxU->getZ(), 0);
	v = new PuntoVector3D(auxV->getX(), auxV->getY(), auxV->getZ(), 0);


	setMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(W);
}
