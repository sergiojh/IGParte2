#pragma once
#include "PuntoVector3D.h"
class Camara
{
public:
	Camara(PuntoVector3D * e, PuntoVector3D * l, PuntoVector3D *upp);
	~Camara();
	void setCameraCoord();
	void setMatrix();
	void lookAt(PuntoVector3D * e, PuntoVector3D * l, PuntoVector3D * u);
	void setOrtho(int left, int right, int bottom, int top, int nearr = -1, int farr = 1);
	void setViewPort(GLint x, GLint y, GLint x2, GLint y2);
	void roll();
private:

	//Eye es el punto donde está la camara
	PuntoVector3D * eye;

	//Look es el punto al que mira la camara
	PuntoVector3D * look;

	//Up es la orientación de la camara
	PuntoVector3D *	up;

	//El movimiento pitch es una rotación con respecto al eje U
	//El movimiento yaw es una rotación con respecto al eje V
	//El movimiento roll es una rotación con respecto al eje N
	PuntoVector3D * u;
	PuntoVector3D * v;
	PuntoVector3D * n;

	GLfloat W[16], Vp[16];

	int left;
	int right;
	int top;
	int bottom;
	int nearr;
	int farr;
	int fovy;
	int aspect;
};

