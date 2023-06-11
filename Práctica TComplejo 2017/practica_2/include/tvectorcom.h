#ifndef _TVectorCom
#define _TVectorCom
#include "tcomplejo.h"

class TVectorCom{
	
	private:
	
		TComplejo *c;
		int tamano;
		TComplejo error;
		
	public:
	
		//FORMA CANONICA
		TVectorCom();// Constructor por defecto
		TVectorCom(int);// Constructor a partir de un tamaño
		TVectorCom(const TVectorCom &);// Constructor de copia
		~TVectorCom();// Destructor
		TVectorCom &operator=(const TVectorCom &);// Sobrecarga del operador asignación
	
		//METODOS
		bool operator==(const TVectorCom &) const;// Sobrecarga del operador igualdad
		bool operator!=(const TVectorCom &) const;// Sobrecarga del operador desigualdad
		TComplejo & operator[](int);// Sobrecarga del operador corchete (parte IZQUIERDA)
		TComplejo operator[](int) const;// Sobrecarga del operador corchete (parte DERECHA)
		int Tamano() const;// Tamaño del vector (posiciones TOTALES)
		int Ocupadas() const;// Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
		bool ExisteCom(const TComplejo &) const;// Devuelve TRUE si existe el TComplejo en el vector
		void MostrarComplejos(double) const;// Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL O POSTERIOR al argumento
		bool Redimensionar(int);// REDIMENSIONAR el vector de TComplejo	
		
		// Sobrecarga del operador salida
		friend ostream & operator<<(ostream &,const TVectorCom &);	
};

#endif
