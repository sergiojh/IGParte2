#include "Camara.h"

			//donde está posicionado	//donde mira		//hacia donde está orientado
Camara::Camara(PuntoVector3D * eye, PuntoVector3D * look, PuntoVector3D *up) :eye(this->eye), look(this->look), up(this->up)
{
	//valores del volumen de vista
	left = 15;
	right = 15;
	top = 15;
	bottom = 15;
	near_ = 1;
	far_ = 500;
	fovy = 15;
	aspect = 15;


	//matriz de proyeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, near_, far_);

	//matriz de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());

	//damos los valores a u,v y n
	setValores();
	//damos los valores a la matriz V
	calcularMatriz();

	d = new PuntoVector3D(0, eye->getY() - look->getY(), eye->getZ() - look->getZ(), 0);
}

Camara::~Camara()
{
	delete d;
	delete eye;
	delete look;
	delete up;
	delete u;
	delete v;
	delete n;
}

void Camara::roll(){
	//PASO 1. CALCULAMOS U Y V GLOBALES
	// coordenadas de u en globales
	PuntoVector3D* uGlobal = 
		new PuntoVector3D(u->getX()*cos(anguloRoll) + v->getX()*sin(anguloRoll),
		u->getY()*cos(anguloRoll) + v->getY()*sin(anguloRoll),
		u->getZ()*cos(anguloRoll) + v->getZ()*sin(anguloRoll),
		0);
	u = uGlobal;

	PuntoVector3D* vGlobal =
		new PuntoVector3D(-u->getX()*sin(anguloRoll) + v->getX()*cos(anguloRoll),
		-u->getY()*sin(anguloRoll) + v->getY()*cos(anguloRoll),
		-u->getZ()*sin(anguloRoll) + v->getZ()*cos(anguloRoll),
		0);
	v = vGlobal;
	//PASO 2.CALCULAR MATRIZ NUEVA 
	calcularMatriz();
	//PASO 3. NUEVA MATRIZ DE VISTA QUE ES LA INVERSA
	calculaInversaMatriz();
	//PASO 4. CARGAR LA MATRIZ RESULTANTE COMO LA NUEVA MATRIZ DE VISTA
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(V’);

	delete vGlobal;
	delete uGlobal;

}

void Camara::giraX(){
	//sumamos angulo
	anguloGiraX += 0.05;

	//radio
	//Raiz(y^2 + z^2);
	radio = sqrt(d->getY() + d->getZ() * d->getZ());

	//Ponemos el nuevo Ojo
	eye = new PuntoVector3D(eye->getX(), radio*sin(anguloGiraX), radio*cos(anguloGiraX), 1);

	//damos valores a n,u y v
	setValores();

	//calculamos la matriz V
	calcularMatriz();

	//matriz de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());


	
}

void Camara::setValores(){

	// n = (eye - look).normalizar();
	PuntoVector3D* nuevoN = new PuntoVector3D(
		eye->getX() - look->getX(),
		eye->getY() - look->getY(), 
		eye->getZ() - look->getZ(),
		0);
	
	nuevoN->normalizar();

	n = nuevoN;

	// u =(up x n).normalizar();
	PuntoVector3D* nuevoU = up->productoVectorial(n);
	nuevoU->normalizar();
	u = nuevoU;

	// v = n x u;
	v = n->productoVectorial(u);
	


}

void Camara::calcularMatriz(){

	//	V = {Ux,Uy,Uz,0,Vx,Vy,Vz,0,Nx,Ny,Nz,0,Eyex,Eyey,Eyez,1}

	V[0] = u->getX();
	V[1] = u->getY();
	V[2] = u->getZ();
	V[3] = 0;

	V[4] = v->getX();
	V[5] = v->getY();
	V[6] = v->getZ();
	V[7] = 0;

	V[8] = n->getX();
	V[9] = n->getY();
	V[10] = n->getZ();
	V[11] = 0;

	V[12] = eye->getX();
	V[13] = eye->getY();
	V[14] = eye->getZ();
	V[15] = 1;
}

void Camara::calculaInversaMatriz(){

	/*V’ = {Ux	Uy	Uz	-Eye * U
			Vx	Vy	Vz	-Eye * V
			Nx	Ny	Nz	-Eye * N
			0	0	0		1	}
			*/

	V’[0] = u->getX();
	V’[1] = v->getX();
	V’[2] = n->getX();
	V’[3] = 0;

	V’[4] = u->getY();
	V’[5] = v->getY();
	V’[6] = n->getY();
	V’[7] = 0;

	V’[8] = u->getZ();
	V’[9] = v->getZ();
	V’[10] = n->getZ();
	V’[11] = 0;

	V’[12] = -eye->productoEscalar(u);
	V’[13] = -eye->productoEscalar(v);
	V’[14] = -eye->productoEscalar(n);
	V’[15] = 1;
}
