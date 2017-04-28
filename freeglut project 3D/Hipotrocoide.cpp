#include "Hipotrocoide.h"

//Constructora
//1. - Se crean los arrays de vértices, normales y caras
//2. - Bucle de la constructora
Hipotrocoide::Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->nP = nP;
	this->nQ = nQ;
	perfil = new PuntoVector3D*[nP];
	for (int i = 0; i < nQ; i++){
		t += 0.2f;
		cargarMatriz(t);
		crearRodaja(nP+i*nP,i*nP,i*nP);
	}
	newell();
}
PuntoVector3D* Hipotrocoide::C(GLfloat t){
	return curva(t);
}
PuntoVector3D* Hipotrocoide::C’(GLfloat t){
	return derivar(t);
}
PuntoVector3D* Hipotrocoide::C’’(GLfloat t){
	PuntoVector3D* aux = derivar2(t);
}
PuntoVector3D* Hipotrocoide::T(GLfloat t){
	PuntoVector3D* a = C’(t);
	a->normalizar();
	return a;
}
PuntoVector3D* Hipotrocoide::B(GLfloat t){
	PuntoVector3D* a = C’(t);
	PuntoVector3D* b = C’’(t);
	a->productoVectorial(b);
	a->normalizar();
	return a;
}
PuntoVector3D* Hipotrocoide::N(GLfloat t){
	PuntoVector3D* a = B(t);
	PuntoVector3D* b = T(t);
	a->productoVectorial(b);
	return a;
}
void Hipotrocoide::newell(){

}
void Hipotrocoide::cargarMatriz(GLfloat t){

}
void Hipotrocoide::crearRodaja(int blyat, int numeroPerfil, int numeroPefilCyka){

}
PuntoVector3D* Hipotrocoide::derivar(GLfloat t){
	return new PuntoVector3D(-(a - b)*sin(t) - c*((a - b) / b)*sin(t*((a - b) / b)),//coordenada 1
		0, //coordenada 2
		(a - b)*cos(t) - c*((a - b) / b)*cos(t*((a - b) / b)),//coordenada 3
		0);//coordenada p||v
}
PuntoVector3D* Hipotrocoide::derivar2(GLfloat t){
	return new PuntoVector3D(-(a - b)*cos(t) - c*((a - b) / b)*((a - b) / b)*cos(t*((a - b) / b)),
		0,
		-(a - b)*sin(t) + c*((a - b) / b)*sin(t*((a - b) / b))*((a - b) / b),
		0);
}
PuntoVector3D* Hipotrocoide::curva(GLfloat t){
	return new PuntoVector3D((a - b)*cos(t) + c*cos(t*((a - b) / b)), 
		0, 
		(a - b)*sin(t) - c*sin(t*((a - b) / b)), 
		0);
}
Hipotrocoide::~Hipotrocoide()
{
}
