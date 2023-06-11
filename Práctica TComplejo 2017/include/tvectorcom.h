#ifndef __TVectorComplejo
#define __TVectorComplejo

#include "tcomplejo.h"

class TVectorCom
{
private:
		// PARTE PRIVADA
		// Para implementar el VECTOR de TComplejo
          TComplejo *c;
          int tamano;
		  TComplejo error; //Uso de Layering
                              // FORMA CANÓNICA
public:
/// Constructor por defecto
          TVectorCom();
/// Constructor a partir de un tamaño
          TVectorCom(int);
/// Constructor de copia
          TVectorCom(const TVectorCom &);
/// Destructor
          ~TVectorCom();
/// Sobrecarga del operador asignación
          TVectorCom & operator=(const TVectorCom &);
                              //Métodos
/// Sobrecarga del operador igualdad
          bool operator==(const TVectorCom &)const;
/// Sobrecarga del operador desigualdad
          bool operator!=(const TVectorCom &)const;
/// Sobrecarga del operador corchete (parte IZQUIERDA)
          TComplejo & operator[](int);
/// Sobrecarga del operador corchete (parte DERECHA)
          TComplejo operator[](int) const;
/// Tamaño del vector (posiciones TOTALES)
          int Tamano() const;
/// Cantidad de posiciones OCUPADAS (no vacías) en el vector
          int Cantidad() const;
/// Devuelve true si existe el Complejo en el vector
          bool ExisteCom(const TComplejo &) const;
/// Mostrar por pantalla mensajes de TComplejo en el vector, de fecha IGUAL O POSTERIOR a la pasada
          void MostrarComplejos(double re)const;

	bool Redimensionar(int tam);
	int Ocupadas() const;
                              //FUNCIONES AMIGAS
/// Sobrecarga del operador salida
          friend ostream & operator<<(ostream &,const  TVectorCom &);
};


#endif
