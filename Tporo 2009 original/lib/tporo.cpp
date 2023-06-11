#include "tporo.h"
TPoro::TPoro(){
	x = 0;
	y = 0;
	volumen = 0;
	color = NULL;
}
TPoro::TPoro(int x, int y, double volumen){
	this->x = x;
	this->y = y;
	this->volumen = volumen;
	color = NULL;
}
char* TPoro::colorMinuscula(char* c){
	char* caux = new char[strlen(c) + 1];
	int i = 0;
	while(c[i] != '\0'){
		caux [i] = tolower(c[i]);
		i++;
	}
	caux[i] = '\0';
	return caux;
}
TPoro::TPoro(int x, int y, double volumen, char* color){
	this->x = x;
	this->y = y;
	this->volumen = volumen;
	if(color == NULL){
		this->color = NULL;
	}
	else{
		char * caux = NULL;
		caux = new char[(strlen(color)) + 1];
		caux = colorMinuscula(color);
		this->color = NULL;
		this->color = new char[(strlen(color)) + 1];
		strcpy(this->color, caux);
	}
}
TPoro::TPoro(const TPoro &tp){
	x = tp.x;
	y = tp.y;
	volumen = tp.volumen;
	if(tp.color == NULL){
		color = NULL;
	}
	else{
		color = NULL;
		color = new char[strlen(tp.color) + 1];
		strcpy(color, tp.color);
	}
}
TPoro::~TPoro(){
	x = 0;
	y = 0;
	volumen = 0;
	if(color != NULL){
		delete [] color;
		color = NULL;
	}
}
TPoro & TPoro::operator=(const TPoro &tp){
	if(this != &tp){
		(*this).~TPoro();
		this->x = tp.x;
		this->y = tp.y;
		this->volumen = tp.volumen;
		if(tp.color == NULL){
			this->color = NULL;
		}
		else{
			this->color = new char[strlen(tp.color) + 1];
			strcpy(this->color, tp.color);
		}
	}
	return *this;
}
bool TPoro::operator==(const TPoro &tp) const{
	bool iguales = false;
	if(this->x == tp.x && this->y == tp.y && this->volumen == tp.volumen){
		if(this->color == NULL && tp.color == NULL){
			iguales = true;
		}
		else{
			if(this->color != NULL && tp.color != NULL){
				if(strcmp(this->color, tp.color) == 0){
					iguales = true;
				}
			}
		}
	}
	return iguales;
}
bool TPoro::operator !=(const TPoro &tp) const{
	return !(*this == tp);
}
void TPoro::Posicion(int vx, int vy){
	this->x = vx;
	this->y = vy;
}
void TPoro::Volumen(double vv){
	this->volumen = vv;
}
void TPoro::Color(char* vc){
	if(this->color != NULL){
		delete [] this->color;
		color = NULL;
	}
	if(vc != NULL){
		char * caux = NULL;
		caux = new char[(strlen(vc)) + 1];
		caux = colorMinuscula(vc);
		this->color = NULL;
		this->color = new char[(strlen(vc)) + 1];
		strcpy(this->color, caux);
	}
}
int TPoro::PosicionX() const{
	return x;
}
int TPoro::PosicionY() const{
	return y;
}
double TPoro::Volumen() const{
	return volumen;
}
char* TPoro::Color() const{
	return color;
}
bool TPoro::EsVacio() const{
	return (this->x == 0 && this->y == 0 && this->volumen == 0 && this->color == NULL);
}
ostream &operator<<(ostream &os, const TPoro &tp){
	if(!tp.EsVacio()){
		os.setf(ios::fixed);
		os.precision(2);
		os << "(" << tp.x << ", " << tp.y << ") " << tp.volumen << " ";
		if(tp.color != NULL){
			os << tp.color;
		}
		else{
			os << "-";
		}
	}
	else{
		os << "()";
	}
	return os;
}
