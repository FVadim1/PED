#ifndef TVECTORPORO_H_
#define TVECTORPORO_H_
#include "tporo.h"
#include "tlistaporo.h"
class TVectorPoro {
	// sobrecarga del operador salida
	friend ostream &operator<<(ostream &os, const TVectorPoro &tvp);
	private:
		int dimension;
		TPoro *datos;
		TPoro error;
	public:
		//--------------- FORMA CANONICA ---------------
		// Constructor por defecto
		TVectorPoro();
		// Constructor a partir de una dimension
		TVectorPoro(int);
		// Constructor de copia
		TVectorPoro(const TVectorPoro &tvp);
		// Destructor
		~TVectorPoro();
		// Sobrecarga del operado asignacion
		TVectorPoro &operator=(const TVectorPoro &tvp);
		// -------------- METODOS --------------------
		// Sobrecarga del operador igualdad
		bool operator==(const TVectorPoro &tvp) const;
		// Sobrecarga del operador desigualdad
		bool operator!=(const TVectorPoro &tvp) const;
		// Sobrecarga del operador corchete (PARTE IZQUIERDA)
		TPoro &operator[] (int);
		// Sobrecarga del operador corchete (PARTE DERECHA)
		TPoro operator[](int) const;
		// Devuelve la longitud (dimension) del vector
		int Longitud() const;
		// Devuelve la cantidad de posiciones ocupadas (no vacias en el vectro)
		int Cantidad() const;
		// REDIMENSIONAR el vector de TPoro
		bool Redimensionar(int);

		// FEBRERO 2008
       //int* Funcion2(const TListaPoro &tlp) const;

};

#endif
