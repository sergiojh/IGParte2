#include "Hipotrocoide.h"

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
	GLfloat t = 0.0f;
	vertice = new PuntoVector3D*[nQ*nP + nP];
	cara = new Cara*[nQ*nP];
	normal = new PuntoVector3D*[nQ*nP + nP];
	numeroNormales = nQ*nP + nP;
	numeroCaras = nQ*nP;
	numeroVertices = nQ*nP + nP;
	GLdouble incr = 2 * 3.1416 / nP;
	perfil = new PuntoVector3D*[nP];
	//creamos un perfil en el origen
	for (int i = 0; i < nP; i++){
		perfil[i] = new PuntoVector3D(0.8*cos(incr*i), 0.8* sin(incr*i), 0, 1);

	}
	cargarMatriz(t);
	int iC = 0;
	int iV = 0;
	//movemos el `primer perfil a su sitio
	for (int i = 0; i < nP; i++){
		vertice[iV]= aplicarMatriz(perfil[i]);
		iV++;
	}
	//mueve los demas perfiles a sus sitios
	//iV-iv+1-(iv-nP)-(iv-np+1)
	for (int i = 0; i < nQ; i++){

		t += 0.2f; 
		cargarMatriz(t);
		for (int i = 0; i < nP; i++){
			vertice[iV] = aplicarMatriz(perfil[i]);		
		}
		crearRodaja(iV,iC);
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
	PuntoVector3D *p = B(t);
	m[0] = p->getX();
	m[1] = p->getY();
	m[2] = p->getZ;
	m[3] = 0;
	p = N(t);
	m[4] = p->getX();
	m[5] = p->getY();
	m[6] = p->getZ;
	m[7] = 0;
	p = T(t);
	m[8] = p->getX();
	m[9] = p->getY();
	m[10] = p->getZ;
	m[11] = 0;
	p = C(t);
	m[12] = p->getX();
	m[13] = p->getY();
	m[14] = p->getZ;
	m[15] = 1;
}
PuntoVector3D* Hipotrocoide::aplicarMatriz(PuntoVector3D* p){
	return new PuntoVector3D(m[0]*p->getX()+m[4]*p->getY()+m[8]*p->getZ()+m[12],
		m[1] * p->getX() + m[5] * p->getY() + m[9] * p->getZ() + m[13],
		m[2] * p->getX() + m[6] * p->getY() + m[10] * p->getZ() + m[14],
		1);
}
void Hipotrocoide::crearRodaja(int indiceVertices,int indiceCaras){
	for (int i = indiceVertices-nP+1; i < indiceVertices; i++){
		VerticeNormal** vn = new VerticeNormal*[4];
		vn[0] = new VerticeNormal(i,indiceCaras);
		vn[1] = new VerticeNormal(i+1, indiceCaras);
		vn[2] = new VerticeNormal(i-nP, indiceCaras);
		vn[3] = new VerticeNormal(i-nP+1, indiceCaras);
		cara[indiceCaras] = new Cara(4, vn);
		
	}
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
