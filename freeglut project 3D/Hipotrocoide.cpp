#include "Hipotrocoide.h"
#include <vector>
#include <iostream>
using namespace std;
//Constructora
//1. - Se crean los arrays de vértices, normales y caras
//2. - Bucle de la constructora
Hipotrocoide::Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c)
{
	//incrementar T 0.2
	this->a = a;
	this->b = b;
	this->c = c;
	this->nP = nP;
	this->nQ = nQ;
	t = 0.0f;
	vector<PuntoVector3D*>vertices(nQ*nP + nP);
	vector<Cara*>caras(nQ*nP);
	vector<PuntoVector3D*>normales(nQ*nP);
	vertice = new PuntoVector3D*[nQ*nP + nP];
	cara = new Cara*[nQ*nP];
	normal = new PuntoVector3D*[nQ*nP];
	numeroNormales = nQ*nP;
	numeroCaras = nQ*nP;
	numeroVertices = nQ*nP + nP;
	GLdouble incr = 2 * 3.1416 / nP;
	perfil = new PuntoVector3D*[nP];

	//creamos un perfil en el origen
	for (int l = 0; l < nP; l++){
		perfil[l] = new PuntoVector3D(0.8*cos(incr*l), 0.8* sin(incr*l), 0, 1);
	}
	cargarMatriz(t);
	int iC = 0;
	int iV = 0;
	//movemos el `primer perfil a su sitio
	for (int y = 0; y < nP; y++){
		vertice[iV]= aplicarMatriz(perfil[y]);
		vertices[iV] = aplicarMatriz(perfil[y]);
		iV++;
	}
	//mueve los demas perfiles a sus sitios
	//iV-iv+1-(iv-nP)-(iv-np+1)
	//EN LA MATRIZ LA Y ES 0
	for (int i = 0; i < nQ; i++){

		t += 0.2f; 
		cargarMatriz(t);
		for (int j = 0; j < nP; j++){
			vertice[iV+j] = aplicarMatriz(perfil[j]);
			vertices[iV + j] = aplicarMatriz(perfil[j]);
			//metemos la nueva cara
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(iV + ((j + 1) % nP)-nP, iC + j);
			vn[1] = new VerticeNormal(iV + (j + 1) % nP, iC + j);
			vn[2] = new VerticeNormal(iV + j, iC + j);
			vn[3] = new VerticeNormal(iV + j - nP, iC+j);
			cara[iC+j] = new Cara(4, vn);
			caras[iC + j] = new Cara(4,vn);
		}
		iV += nP;
		iC += nP;
	}
	
	for (int z = 0; z < numeroNormales; z++){
		normal[z]=newell(cara[z]);
	//	normales[z] = newell(cara[z]);
	}
}
PuntoVector3D* Hipotrocoide::C(GLfloat t){
	return curva(t);
}
PuntoVector3D* Hipotrocoide::C’(GLfloat t){
	return derivar(t);
}
PuntoVector3D* Hipotrocoide::C’’(GLfloat t){
	PuntoVector3D* aux = derivar2(t);
	return aux;
}
PuntoVector3D* Hipotrocoide::T(GLfloat t){
	PuntoVector3D* a = C’(t)->clonar();
	a->normalizar();
	return a;
}
PuntoVector3D* Hipotrocoide::B(GLfloat t){
	PuntoVector3D* a = C’(t)->clonar();
	PuntoVector3D* b = C’’(t)->clonar();
	PuntoVector3D* aux = a->productoVectorial(b);
	aux->normalizar();
	return aux;
}
PuntoVector3D* Hipotrocoide::N(GLfloat t){
	PuntoVector3D* a = B(t)->clonar();
	PuntoVector3D* b = T(t)->clonar();
	PuntoVector3D* aux = a->productoVectorial(b);
	return aux;
}
PuntoVector3D* Hipotrocoide::newell(Cara* cara){
	PuntoVector3D* normal;
	GLfloat a, b, c;
	a = b = c = 0;
	PuntoVector3D* verticeAc;
	PuntoVector3D* verticeSig;
	for (int i = 0; i < cara->getNumeroVertices(); i++){
		verticeAc = vertice[cara->getIndiceVerticeK(i)];
		verticeSig = vertice[cara->getIndiceVerticeK((i+1)% cara->getNumeroVertices())];
		a += ((verticeAc->getY() - verticeSig->getY()) * (verticeAc->getZ() + verticeSig->getZ()));
		b += ((verticeAc->getZ() - verticeSig->getZ()) * (verticeAc->getX() + verticeSig->getX()));
		c += ((verticeAc->getX() - verticeSig->getX()) * (verticeAc->getY() + verticeSig->getY()));
	}
	normal = new PuntoVector3D{ a, b, c, 0 };
	normal->normalizar();
	normal->escalar(-1);
	return normal;
}
void Hipotrocoide::cargarMatriz(GLfloat t){
	PuntoVector3D *p = B(t);
	m[0] = p->getX();
	m[1] = p->getY();
	m[2] = p->getZ();
	m[3] = 0;
	p = N(t);
	m[4] = p->getX();
	m[5] = p->getY();
	m[6] = p->getZ();
	m[7] = 0;
	p = T(t);
	m[8] = p->getX();
	m[9] = p->getY();
	m[10] = p->getZ();
	m[11] = 0;
	p = C(t);
	m[12] = p->getX();
	m[13] = p->getY();
	m[14] = p->getZ();
	m[15] = 1;
}
PuntoVector3D* Hipotrocoide::aplicarMatriz(PuntoVector3D* p){
	return new PuntoVector3D(
		m[0] * p->getX() + m[4] * p->getY() + m[8] * p->getZ() + m[12],
		m[1] * p->getX() + m[5] * p->getY() + m[9] * p->getZ() + m[13],
		m[2] * p->getX() + m[6] * p->getY() + m[10] * p->getZ() + m[14],
		1);
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
