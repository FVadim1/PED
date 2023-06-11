#ifndef _ta234com
#define _ta234com

#include "tlistacom.h"
#include "tcomplejo.h"

#define kIguales 0
#define kHoja 1
#define kHijoIz 2
#define kHijoMeIz 3
#define kHijoMeDe 4
#define kHijoDe 5
class TA234Nodo;
class TA234Com
{
	private:
		TA234Nodo *raiz;
		int Comparar(const TComplejo &c, const TA234Nodo *) const;
		void Poner(const TComplejo &y, TA234Nodo *);
		void DivideRaiz(TA234Nodo *);
		void DivideHijoDe2(TA234Nodo *, TA234Nodo *);
		void DivideHijoDe3(TA234Nodo *, TA234Nodo *);
		bool Es2Nodo(const TA234Nodo *) const;
		bool Es3Nodo(const TA234Nodo *) const;
		bool Es4Nodo(const TA234Nodo *) const;
		void Combinar(TA234Nodo *p, TA234Nodo *q, TA234Nodo *r);
		void Rotar(TA234Nodo *p, TA234Nodo *q, TA234Nodo *r);
		void Quitar(const TComplejo &c, TA234Nodo *p);
		bool EsHoja(const TA234Nodo *n) const;
		TComplejo BuscarMayorIzquierda(const TComplejo &y, TA234Nodo *p);
		void Sustituir(const TComplejo &antiguo, const TComplejo &nuevo);
	public:
		TA234Com();
		TA234Com(const TA234Com &);
		~TA234Com();
		TA234Com &operator=(const TA234Com &);
		bool operator==(const TA234Com &) const;
		bool operator!=(const TA234Com &) const;
		bool EsVacio() const;
		bool Insertar(const TComplejo &);
		bool Buscar(const TComplejo &)const;
		int Altura() const;
		int Nodos() const;
		int NodosHoja() const;
		TListaCom Niveles() const;
		bool Borrar(const TComplejo &c);
};

class TA234Nodo
{
	friend class TA234Com;
	private:
		TComplejo itIz, itMe, itDe;
		TA234Com hijoIz, hijoMeIz, hijoMeDe, hijoDe;
	public:
		TA234Nodo();
		~TA234Nodo();
		TA234Nodo(const TA234Nodo &);
		TA234Nodo &operator=(const TA234Nodo &);
};

class TCola
{
	private:
		struct TNodo
		{
			void *item;
			TNodo *sig;		
		};
		TNodo *tope, *fondo;
	public:
		TCola();
		~TCola();
		void * Desencolar();
		void Encolar(void *);
		bool EsVacia() const {return tope == NULL;}
};

#endif
