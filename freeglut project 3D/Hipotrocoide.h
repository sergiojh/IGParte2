#pragma once
#include "Malla.h"
class Hipotrocoide: public Malla
{
public: 
	Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c);
	~Hipotrocoide();
	
	GLfloat a, b, c; //parámetros de la curva
	int nP; //número de lados del polígono que aproxima el grosor de la curva
	int nQ; //número de de muestras que se toman en la curva
	GLfloat m[16]; //matriz para pasar el perfil a la curva
	PuntoVector3D** perfil; //polígono de nP lados
		//Métodos
	PuntoVector3D* C(GLfloat t);
	PuntoVector3D* C’(GLfloat t);
	PuntoVector3D* C’’(GLfloat t);
	PuntoVector3D* T(GLfloat t);
	PuntoVector3D* B(GLfloat t);
	PuntoVector3D* N(GLfloat t);
	void newell();
	void cargarMatriz(GLfloat t);
	void crearRodaja(int indiceVertices,int indiceCaras);
	PuntoVector3D* derivar(GLfloat t);
	PuntoVector3D* curva(GLfloat t);
	PuntoVector3D* derivar2(GLfloat t);
	PuntoVector3D* aplicarMatriz(PuntoVector3D* p);
	//PuntoVector3D* C(t), C’(t), C’’(t), T(t), B(t), N(t); métodos necesarios para rellenar la matriz m
		//Constructora

		//1. - Se crean los arrays de vértices, normales y caras
		//2. - Bucle de la constructora :
	//Crear el perfil;

	//Crear vértices iniciales;
	//Repetir nQ veces :
	//Aumentar t;
	//Calcular m(t);
	//Crear nuevos vértices;
	//Unirlos con los vértices anteriores formando caras;

};




///la cara se crea con (i,i-nP,(i+1) -nP, i+1)