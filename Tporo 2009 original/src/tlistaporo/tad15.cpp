#include <iostream>
#include "tporo.h"
#include "tlistaporo.h"

using namespace std;

int main(){

	TPoro p;
	TPoro p2(2,3,5.7);
	TPoro p3(2,3,5.7,(char*)"aZuL");
	TPoro p4(2,3,5.7,(char*)"verde");

	TListaPoro l;
	TListaPoro l2(l);
	TListaPosicion pos;
	TListaNodo n;

	if(l2.Insertar(p3) && l2.Insertar(p2) && l2.Insertar(p4) && l2.Insertar(p)){
		cout << "OK" << endl;
	}
	cout << l << endl;
	cout << l2 << endl;
	l=l2;
	cout << l << endl;

	if(l.Longitud()==4){
		cout << "OK" << endl;
	}
	TListaPoro lista_vacia;
	l2=lista_vacia;
	if(l2.Longitud()==0){
		cout << "OK" << endl;
	}
	l2=l.ExtraerRango(1,2);
	if(l.Longitud()==2){
		cout << "OK" << endl;
	}
	if(l2.Longitud()==2){
		cout << "OK" << endl;
	}
	cout << l << endl;
	cout << l2 << endl;

	l=l+l2;
	if(l.Longitud()==4){
		cout << "OK" << endl;
	}
	cout << l << endl;
	l2=l.ExtraerRango(-1,1);
	if(l.Longitud()==3){
		cout << "OK" << endl;
	}
	if(l2.Longitud()==1){
		cout << "OK" << endl;
	}
	cout << l << endl;
	cout << l2 << endl;
	l=l+l2;
	if(l.Longitud()==4){
		cout << "OK" << endl;
	}
	cout << l << endl;
	l2=l.ExtraerRango(3,2);
	if(l.Longitud()==4){
		cout << "OK" << endl;
	}
	if(l2.Longitud()==0){
		cout << "OK" << endl;
	}
	cout << l << endl;
	cout << l2 << endl;

	l=l+l2;
	if(l.Longitud()==4){
		cout << "OK" << endl;
	}
	cout << l << endl;

	l2=l.ExtraerRango(1,10);
	if(l.Longitud()==0){
		cout << "OK" << endl;
	}
	if(l2.Longitud()==4){
		cout << "OK" << endl;
	}
	cout << l << endl;
	cout << l2 << endl;

	l2.~TListaPoro();
	if(l2.Longitud()==0){
		cout << "OK" << endl;
	}
	cout << l2 << endl;
}

