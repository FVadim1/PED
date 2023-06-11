#include <iostream>

using namespace std;
#include "tporo.h"
#include "tvectorporo.h"

int main(int argc, char const *argv[]){

	TPoro p;
	TPoro p2(2,3,5.7);
	TPoro p3(2,3,5.7,(char*)"aZuL");
	TPoro p4(p3);


	TVectorPoro v;
	TVectorPoro v2(5);
	TVectorPoro v3(v);

	cout << v << endl; 
	cout << v2 << endl;
	cout << v3 << endl;

	v2[2]=p2;
	v2[5]=p3;

	cout << v << endl; 
	cout << v2 << endl;
	cout << v3 << endl;

	if(v.Redimensionar(1)){
		cout << "OK" << endl;
		if(v.Longitud()==1){
			cout << "OK" << endl;
		}
	}
	
	cout << v << endl; 
	cout << v2 << endl;
	cout << v3 << endl;

	if(v2.Redimensionar(6)){
		cout << "OK" << endl;
		if(v2.Longitud()==6){
			cout << "OK" << endl;
		}
	}
	cout << v << endl; 
	cout << v2 << endl;
	cout << v3 << endl;

	if(v2.Redimensionar(4)){
		cout << "OK" << endl;
		if(v2.Longitud()==4){
			cout << "OK" << endl;
		}
	}
	cout << v << endl; 
	cout << v2 << endl;
	cout << v3 << endl;
	int longitud=v3.Longitud();
	if(!v3.Redimensionar(0)){
		cout << "OK" << endl;
		if(v3.Longitud()==longitud){
			cout << "OK" << endl;
		}
	}
	cout << v << endl; 
	cout << v2 << endl;
	cout << v3 << endl;

	if(v2.Redimensionar(6)){
		cout << "OK" << endl;
		if(v2.Longitud()==6){
			cout << "OK" << endl;
		}
	}
	cout << v << endl;
	cout << v2 << endl;
	cout << v3 << endl;

	cout << v2.Cantidad() << endl;
	cout << v2.Longitud() << endl;
	

}
