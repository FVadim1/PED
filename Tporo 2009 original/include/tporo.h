#ifndef TPORO_H_
#define TPORO_H_
#include <iostream>
#include <cstring>
using namespace std;

class TPoro {
	// Sobrecarga del operador salida
	friend ostream &operator<<(ostream &os, const TPoro &tp);
	private:
		int x;
		int y;
		double volumen;
		char* color;
		char* colorMinuscula(char* m);
	public:
		// ---------------- FORMA CANONICA -------------------
		// Constructor por Defecto
		TPoro();
		// Constructor parametrizado por posicion y volumen
		TPoro(int, int, double);
		// Constructor parametrizado por posicion, volumen y color
		TPoro(int, int, double, char*);
		// Constructor de copia
		TPoro(const TPoro &tp);
		// Destructor
		~TPoro();
		// Sobrecarga del operador asignacion
		TPoro &operator=(const TPoro &tp);
		// ------------------ METODOS -----------------------
		// Sobrecarga del operador igualdad
		bool operator==(const TPoro &tp) const;
		// Sobrecarga del operador desigualdad
		bool operator!=(const TPoro &tp) const;
		// Modifica la posicion
		void Posicion(int, int);
		// Modifica el volumen
		void Volumen(double);
		// Modifica el color
		void Color(char*);
		// Devuelve la coordenada x de la posicion
		int PosicionX() const;
		// Devuelve la coordenada y de la posicion
		int PosicionY() const;
		// Devuelve el volumen
		double Volumen() const;
		// Develve el colo
		char* Color() const;
		// Devuelve cierto si el poro esta vacio
		bool EsVacio() const;
};
#endif
