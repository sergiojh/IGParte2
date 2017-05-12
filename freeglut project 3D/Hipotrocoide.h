#pragma once
#include "Malla.h"
class Hipotrocoide: public Malla
{
public: 
	Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c);
	~Hipotrocoide();
	
	GLfloat a, b, c; //par�metros de la curva
	int nP; //n�mero de lados del pol�gono que aproxima el grosor de la curva
	int nQ; //n�mero de de muestras que se toman en la curva
	GLfloat m[16]; //matriz para pasar el perfil a la curva
	PuntoVector3D** perfil; //pol�gono de nP lados
		//M�todos
	PuntoVector3D* C(GLfloat t);
	PuntoVector3D* C�(GLfloat t);
	PuntoVector3D* C��(GLfloat t);
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
	//PuntoVector3D* C(t), C�(t), C��(t), T(t), B(t), N(t); m�todos necesarios para rellenar la matriz m
		//Constructora

		//1. - Se crean los arrays de v�rtices, normales y caras
		//2. - Bucle de la constructora :
	//Crear el perfil;

	//Crear v�rtices iniciales;
	//Repetir nQ veces :
	//Aumentar t;
	//Calcular m(t);
	//Crear nuevos v�rtices;
	//Unirlos con los v�rtices anteriores formando caras;

};




///la cara se crea con (i,i-nP,(i+1) -nP, i+1)