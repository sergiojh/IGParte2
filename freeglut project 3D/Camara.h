#pragma once
#include "Malla.h"
class Camara
{
public:
	Camara(PuntoVector3D*eye, PuntoVector3D*look, PuntoVector3D*up);
	~Camara();
	void roll();
	void giraX();
private:
	//permiten definir la orientacion de la camara y su sistema de coordenadas.
	PuntoVector3D*eye;
	PuntoVector3D*look;
	PuntoVector3D*up;
	PuntoVector3D* u;
	PuntoVector3D* v;
	PuntoVector3D* n;
	//distancia de dibujado
	PuntoVector3D*d;
	//atributos que permiten definir las dimensiones del volumen de vista.
	//tienen que ser floats para el metodo glLoadMatrix
	GLfloat left;
	GLfloat right;
	GLfloat top;
	GLfloat bottom;
	GLfloat near_;
	GLfloat far_;
	GLfloat fovy;
	GLfloat aspect;
	//radio de la circunferencia del giraX
	GLfloat radio;
	//matriz de coodenadas globales
	GLfloat V[16];
	//matriz de vista
	GLfloat V’[16];

	//angulos para ambas funciones
	GLfloat anguloRoll = 0.05;
	GLfloat anguloGiraX = 0;


	void calcularMatriz();
	void setValores();
	void calculaInversaMatriz();
};

