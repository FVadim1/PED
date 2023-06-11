#include <iostream>
using namespace std;

#include "tporo.h"

int main(int argc, char const *argv[]){

	TPoro p;
	TPoro p2(2,3,5.7);
	TPoro p3(2,3,5.7,(char*)"aZuL");
	TPoro p4(p3);


	cout << p << endl; // ()
	cout << p2 << endl;// (2, 3) 5.7 -
	cout << p3 << endl;// (2, 3) 5.7 azul
	cout << p4 << endl;// (2, 3) 5.7 azul

	if(p.EsVacio()){
		cout << "OK" << endl;
	}

	p2.Color(p3.Color());

	p.Posicion(p2.PosicionX(),p3.PosicionY());

	p3.Volumen(p.Volumen());

	if(!p.EsVacio()){
		cout << "OK" << endl;
	}

	cout << p << endl; // (2, 3) 0.0 -
	cout << p2 << endl;// (2, 3) 5.7 azul
	cout << p3 << endl;// (2, 3) 0.0 azul

	if(p2!=p3){
		cout << "OK" << endl;
	}
	if(!(p==p2)){
		cout << "OK" << endl;
	}
	p=p2;
	cout << p << endl;// (2, 3) 5.7 azul
	cout << p2 << endl;// (2, 3) 5.7 azul

	if(p==p2){
		cout << "OK" << endl;
	}


}
