#include <iostream>
#include "tporo.h"
#include "tlistaporo.h"

using namespace std;

int main(){

	TPoro p;
	TPoro p2(2,3,5.7);
	TPoro p3(2,3,5.7,(char*)"aZuL");
	TPoro p4(p3);

	TListaPoro l;
	TListaPoro l2(l);
	TListaPosicion pos;
	TListaNodo n;


//Metodos 2 insertar, longitud y operador <<
	if(l.Insertar(p2)==true){
		cout << "OK" << endl;
	}
	p2.Posicion(2,2);
	p2.Volumen(2);
	p2.Color((char*)"segundo");
	if(l.Insertar(p2)==true){
		cout << "OK" << endl;
	}
	if(l.Longitud()==2){ 
		cout << "OK" << endl;
	}
	if(l2.Longitud()==0){ 
		cout << "OK" << endl;
	}
	p4.Posicion(4,4);
	p4.Volumen(4);
	p4.Color((char*)"cuarto");
	if(l.Insertar(p4)==true){
		cout << "OK" << endl;
	}
	if(l.Longitud()==3){ 
		cout << "OK" << endl;
	}
	p3.Posicion(3,3);
	p3.Volumen(3);
	p3.Color((char*)"tercero");

	if(l.Insertar(p3)==true){
		cout << "OK" << endl;
	}
	if(l.Longitud()==4){ 
		cout << "OK" << endl;
	}
	cout << l << endl;
	l2=l;
	if(l2==l){
		cout << "OK" << endl;
	}
	cout << l2 << endl;

//Metodo buscar y borrar
	p.Posicion(1,3);
	p.Volumen(1.5);
	p.Color((char*)"primero");
	if(l.Insertar(p)==true){
		cout << "OK" << endl;
	}
	if(l2.Insertar(p)==true){
		cout << "OK" << endl;
	}
	if(l.Buscar(p)==true){
		cout << "OK" << endl;
	}
	TPoro poro_vacio;
	if(l2.Insertar(poro_vacio)){
		cout << "OK" << endl;
	}
	if(!l.Buscar(poro_vacio)){
		cout << "OK" << endl;
	}
	if(l.Borrar(p)){
		cout << "OK" << endl;
	}
	if(l.Longitud()==4){
		cout << "OK" << endl;
	}
	if(!l.Borrar(p)){
		cout << "OK" << endl;
	}
	if(!l.Borrar(pos)){
		cout << "OK" << endl;
	}
	pos=l2.Primera();
	if(!l.Borrar(pos)){
		cout << "OK" << endl;
	}
	pos=l.Primera();
	if(l.Borrar(pos)){
		cout << "OK" << endl;
	}
	if(l.Longitud()==3){
		cout << "OK" << endl;
	}
	pos=l.Ultima();
	if(l.Borrar(pos)){
		cout << "OK" << endl;
	}
	if(l.Longitud()==2){
		cout << "OK" << endl;
	}
	if(l.Insertar(poro_vacio)){
		cout << "OK" << endl;
	}
	if(l.Insertar(p)){
		cout << "OK" << endl;
	}
	pos=l.Primera().Siguiente();
	if(l.Longitud()==4){
		cout << "OK" << endl;
	}
	if(l.Borrar(pos)){
		cout << "OK" << endl;
	}
	if(l.Longitud()==3){
		cout << "OK" << endl;
	}

}
