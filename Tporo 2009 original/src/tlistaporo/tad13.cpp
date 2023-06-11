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

	//operador <<
		cout << l.Longitud() << endl;
		cout << l << endl;

	//operador ==
		if(pos==pos.Anterior()){
			cout << "OK" << endl;
		}
		if(l==l2){
		cout << "OK" << endl;
		}
		if(l.Primera()==l2.Primera()){
			cout << "OK" << endl;
		}
		if(pos.EsVacia()){
			cout << "OK" << endl;
		}

	//Metodo obtener
		p.Posicion(1,1);
		p.Volumen(1);
		p.Color((char*)"azul");
		if(l.Insertar(p)){
			cout << "OK" << endl;
		} 
		if(l.Longitud()==1){
			cout << "OK" << endl;
		}
		p2=l.Obtener(l.Primera());
		cout << p2 << endl;

		cout << l.Obtener(l2.Primera()) << endl;
		TListaPosicion pos_null;
		cout << l.Obtener(pos_null) << endl;
		if(l.Longitud()==1){
			cout << "OK" << endl;
		}

	//Copia exacta de lista
		if(l2.Longitud()==0){
			cout << l2 << endl;
		}	
		l2=l;
		if(l2.Longitud()==l.Longitud()){
			cout << l2 << endl;
		}	

	
}
