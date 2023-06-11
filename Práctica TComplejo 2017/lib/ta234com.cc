#include "ta234com.h"


TA234Com::TA234Com()
{
	raiz = NULL;
}

TA234Com::TA234Com(const TA234Com &o)
{
	if(!o.raiz)
		raiz = NULL;
	else
		raiz = new TA234Nodo(*(o.raiz));

}
TA234Com::~TA234Com()
{
	if(raiz)
	{
		delete raiz;
		raiz = NULL;
	}
}

TA234Com &TA234Com::operator=(const TA234Com &b)
{
	if(this != &b)
	{
		this->~TA234Com();
		if(!b.EsVacio())
		{
			raiz = new TA234Nodo;
			*raiz = *(b.raiz);
		}
	}
	return *this;
}

bool TA234Com::operator==(const TA234Com &b) const
{
	bool iguales;
	iguales = false;
	
	if(raiz == b.raiz)
		iguales = true;
	else if(raiz && b.raiz && raiz->itIz == b.raiz->itIz && raiz->itDe == b.raiz->itDe &&
		raiz->itMe == b.raiz->itMe && raiz->hijoDe == b.raiz->hijoDe && raiz->hijoMeIz == b.raiz->hijoMeIz &&
		raiz->hijoIz == b.raiz->hijoIz && raiz->hijoMeDe == b.raiz->hijoMeDe)
			iguales = true;

	return iguales;
}

bool TA234Com::operator!=(const TA234Com &b) const
{
	return !(*this == b);
}

bool TA234Com::EsVacio() const
{
	return raiz == NULL;
}

bool TA234Com::Insertar(const TComplejo &y)
{
	bool insertado, encontrado;
	TA234Nodo *p, *q;
	
	insertado = false;
	// no puede ser el complejo (0, 0)
	if(y.Re() != 0 || y.Im() != 0)
	{
		if(EsVacio())
		{
			raiz = new TA234Nodo();
			raiz->itIz = y;
			insertado = true;
		}
		else
		{
			if(Es4Nodo(raiz))
				DivideRaiz(raiz);
			q = p = raiz;
			insertado = false;
			encontrado = false;
			while(!insertado && !encontrado)
			{
				if(Es4Nodo(p))
				{
					if(Es3Nodo(q))
						DivideHijoDe3(p, q);
					else
						DivideHijoDe2(p, q);
					p = q;
				}
				switch(Comparar(y, p))
			        {
					case kIguales:
						encontrado = true;
						break;
					case kHoja:
						insertado = true;
						Poner(y, p);
						break;
					case kHijoIz:
						q = p;
						p = p->hijoIz.raiz;
						break;
					case kHijoMeIz:
						q = p;
						p = p->hijoMeIz.raiz;
						break;
					case kHijoMeDe:
						q = p;
						p = p->hijoMeDe.raiz;
						break;
					case kHijoDe:
						q = p;
						p = p->hijoDe.raiz;
						break;
				}
			}
		}

	}
	
	return insertado;
}

void TA234Com::DivideRaiz(TA234Nodo *nodo)
{
	const TComplejo vacio;
	TA234Nodo *ptN1, *ptN2;
	
	ptN1 = new TA234Nodo();
	ptN2 = new TA234Nodo();
	
	ptN1->itIz = nodo->itIz;
	ptN2->itIz = nodo->itDe;
	nodo->itIz = nodo->itMe;
	nodo->itMe = nodo->itDe = vacio;
	ptN1->hijoIz.raiz = nodo->hijoIz.raiz;
	ptN1->hijoMeIz.raiz = nodo->hijoMeIz.raiz;
	ptN2->hijoIz.raiz = nodo->hijoMeDe.raiz;
	ptN2->hijoMeIz.raiz = nodo->hijoDe.raiz;
	nodo->hijoIz.raiz = ptN1;
	nodo->hijoMeIz.raiz = ptN2;
	nodo->hijoMeDe.raiz = nodo->hijoDe.raiz = NULL;
}

void TA234Com::DivideHijoDe2(TA234Nodo *p, TA234Nodo *q)
{
	TComplejo vacio;
	TA234Nodo *ptN;

	ptN = new TA234Nodo();
	ptN->itIz = p->itDe;
	ptN->hijoIz.raiz = p->hijoMeDe.raiz;
	ptN->hijoMeIz.raiz = p->hijoDe.raiz;
	p->hijoMeDe.raiz = p->hijoDe.raiz = NULL;
	if(p == q->hijoIz.raiz)
	{
		q->itMe = q->itIz;
		q->itIz = p->itMe;
		q->hijoMeDe.raiz = q->hijoMeIz.raiz;
		q->hijoMeIz.raiz = ptN;
	}
	else
	{
		q->itMe = p->itMe;
		q->hijoMeDe.raiz = ptN;
	}
	p->itMe = p->itDe = vacio;
	

}

void TA234Com::DivideHijoDe3(TA234Nodo *p, TA234Nodo *q)
{
	TComplejo vacio;
	TA234Nodo *ptN;

	ptN = new TA234Nodo();
	ptN->itIz = p->itDe;
	ptN->hijoIz.raiz = p->hijoMeDe.raiz;
	ptN->hijoMeIz.raiz = p->hijoDe.raiz;
	p->hijoMeDe.raiz = p->hijoDe.raiz = NULL;
	if(p == q->hijoIz.raiz)
	{
		q->itDe = q->itMe;
		q->itMe = q->itIz;
		q->itIz = p->itMe;
		q->hijoDe.raiz = q->hijoMeDe.raiz;
		q->hijoMeDe.raiz = q->hijoMeIz.raiz;
		q->hijoMeIz.raiz = ptN;
	}
	else
		if(p == q->hijoMeIz.raiz)
		{
			q->itDe = q->itMe;
			q->itMe = p->itMe;
			q->hijoDe.raiz = q->hijoMeDe.raiz;
			q->hijoMeDe.raiz = ptN;
		}
		else
		{
			q->itDe = p->itMe;
			q->hijoDe.raiz = ptN;
		}
	p->itDe = p->itMe = vacio;
}

void TA234Com::Poner(const TComplejo &y, TA234Nodo *nodo)
{
	TComplejo vacio;
	if(nodo)
        	if(Es2Nodo(nodo))
		{
			if(y.Mod() < nodo->itIz.Mod())
			{
				nodo->itMe = nodo->itIz;
				nodo->itIz = y;
			}
			else
				nodo->itMe = y;
		}
		else
			if(Es3Nodo(nodo))
			{
				if(y.Mod() < nodo->itIz.Mod())
				{
					nodo->itDe = nodo->itMe;
					nodo->itMe = nodo->itIz;
					nodo->itIz = y;
				}
				else
					if(y.Mod() < nodo->itMe.Mod())
					{
						nodo->itDe = nodo->itMe;
						nodo->itMe = y;
					
					}
					else
						nodo->itDe = y;
			}
}

int TA234Com::Comparar(const TComplejo &y, const TA234Nodo *nodo) const
{
	int caso;
        TComplejo vacio;
	
	caso = -1;
	if(nodo)
		if(y == nodo->itIz || y == nodo->itMe || y == nodo->itDe)
			caso = kIguales;
		else
			if(nodo->hijoIz.raiz == NULL)
				caso = kHoja;
			else
				if(y.Mod() < nodo->itIz.Mod())
					caso = kHijoIz;
				else
					if(nodo->itMe == vacio || y.Mod() < nodo->itMe.Mod())
						caso = kHijoMeIz;
					else
						if(nodo->itDe == vacio || y.Mod() < nodo->itDe.Mod())
							caso = kHijoMeDe;
						else
							caso = kHijoDe;
	return caso;
}

bool TA234Com::Buscar(const TComplejo &c) const
{
	// tambien se puede implementar facilmente
	// una version iterativa.
	bool encontrado;
		
	if(!raiz)
		encontrado = false;
	else
		switch(Comparar(c, raiz))
		{
			case kIguales:
				encontrado = true;
			break;

			case kHoja:
				encontrado = false;
				break;
			case kHijoIz:
				encontrado = raiz->hijoIz.Buscar(c);
			break;
		
			case kHijoMeIz:
				encontrado = raiz->hijoMeIz.Buscar(c);
			break;

			case kHijoMeDe:
				encontrado = raiz->hijoMeDe.Buscar(c);
			break;

			case kHijoDe:
				encontrado = raiz->hijoDe.Buscar(c);
			break;
		}

	return encontrado;
}

int TA234Com::Altura() const
{
	// tambien se puede implementar facilmente
	// una version iterativa.
	int h;

	if(!raiz)
		h = 0;
	else
		h = 1 + raiz->hijoIz.Altura();
	
	return h;
}

int TA234Com::Nodos() const
{
	int n;

	if(!raiz)
		n = 0;
	else
		n = 1 + raiz->hijoIz.Nodos() + raiz->hijoMeDe.Nodos() + raiz->hijoMeIz.Nodos() 
			+ raiz->hijoDe.Nodos();

	return n;
}

int TA234Com::NodosHoja() const
{
	int nh;
	
	if( EsVacio() )
		nh = 0;
	else
		if(raiz->hijoIz.EsVacio())
			nh = 1;
		else
			nh = raiz->hijoIz.NodosHoja() + raiz->hijoMeDe.NodosHoja() +
				raiz->hijoMeIz.NodosHoja() + raiz->hijoDe.NodosHoja();

	return nh;
}

bool TA234Com::Es2Nodo(const TA234Nodo *nodo) const
{
	return nodo && (nodo->itIz.Re() != 0 || nodo->itIz.Im() != 0) && nodo->itMe.Re() == 0 && nodo->itMe.Im() == 0;
}

bool TA234Com::Es3Nodo(const TA234Nodo *nodo) const
{
	return nodo && (nodo->itIz.Re() != 0 || nodo->itIz.Im() != 0) && (nodo->itMe.Re() != 0 || nodo->itMe.Im() != 0)
		&& nodo->itDe.Re() == 0 && nodo->itDe.Im() == 0;
}

bool TA234Com::Es4Nodo(const TA234Nodo *nodo) const
{
	return nodo && (nodo->itIz.Re() != 0 || nodo->itIz.Im() != 0) && (nodo->itMe.Re() != 0 || nodo->itMe.Im() != 0)
		&& (nodo->itDe.Re() != 0 || nodo->itDe.Im() != 0);
}

TA234Nodo::TA234Nodo()
{ }

TA234Nodo::~TA234Nodo()
{ }

TA234Nodo::TA234Nodo(const TA234Nodo &o)
:itIz(o.itIz), itDe(o.itDe), itMe(o.itMe),
hijoIz(o.hijoIz), hijoMeIz(o.hijoMeIz), hijoMeDe(o.hijoMeDe), hijoDe(o.hijoDe)
{
	
}

TA234Nodo &TA234Nodo::operator=(const TA234Nodo &b)
{
	if(this != &b)
	{
		itIz = b.itIz;
		itMe = b.itMe;
		itDe = b.itDe;
		hijoIz = b.hijoIz;
		hijoMeIz = b.hijoMeIz;
		hijoMeDe = b.hijoMeDe;
		hijoDe = b.hijoDe;
	}
	return *this;
}

TListaCom TA234Com::Niveles() const
{
	TListaCom lista;
	TA234Nodo *aux;
	TCola cola;
	
	if(raiz)
		cola.Encolar(raiz);
	while(!cola.EsVacia())
	{
		aux = (TA234Nodo *)cola.Desencolar();
		if(Es2Nodo(aux))
		{
			if(lista.EsVacia()) lista.InsCabeza(aux->itIz);
			else lista.InsertarD(aux->itIz, lista.Ultima());
		}		
		else
			if(Es3Nodo(aux))
			{
				if(lista.EsVacia()) lista.InsCabeza(aux->itIz);
				else lista.InsertarD(aux->itIz, lista.Ultima());
               			if(lista.EsVacia()) lista.InsCabeza(aux->itMe);
				else lista.InsertarD(aux->itMe, lista.Ultima());

			}
			else
			{
				if(lista.EsVacia()) lista.InsCabeza(aux->itIz);
				else lista.InsertarD(aux->itIz, lista.Ultima());
				if(lista.EsVacia()) lista.InsCabeza(aux->itMe);
				else lista.InsertarD(aux->itMe, lista.Ultima());
				if(lista.EsVacia()) lista.InsCabeza(aux->itDe);
				else lista.InsertarD(aux->itDe, lista.Ultima());
			}
		if(aux->hijoIz.raiz)
			cola.Encolar(aux->hijoIz.raiz);
		if(aux->hijoMeIz.raiz)
			cola.Encolar(aux->hijoMeIz.raiz);
		if(aux->hijoMeDe.raiz)
			cola.Encolar(aux->hijoMeDe.raiz);
		if(aux->hijoDe.raiz)
			cola.Encolar(aux->hijoDe.raiz);
	}
	return lista;
}


void TA234Com::Quitar(const TComplejo &c, TA234Nodo *p)
{
	if(p)
		if(c == p->itIz)
		{
			p->itIz = p->itMe;
			p->itMe = p->itDe;
			p->itDe = (0, 0);
		}
		else
			if(c == p->itMe)
			{
				p->itMe = p->itDe;
				p->itDe = (0, 0);
			}
			else
				if(c == p->itDe)
					p->itDe = (0, 0);

}

bool TA234Com::Borrar(const TComplejo &y)
{
	bool borrado, fin, intermedio;
	TA234Nodo *p, *q, *r;
	TComplejo yBorrar, mayorIzquierda;

	yBorrar = y;
	borrado = false;
	if(raiz)
	{
		borrado = false;
		fin = false;
		intermedio = false;
		p = raiz;
		while(!borrado && !fin)
		{
			if(EsHoja(p))
			{
				if(Comparar(yBorrar, p) == kIguales)
				{
					Quitar(yBorrar, p);
					borrado = true;
					// en el caso de que sea la raiz y sea 2-nodo
					// tendremos un dos nodo que hay que eliminar.
					if(raiz == p && p->itIz.Mod() == 0)
					{
						delete p;
						raiz = NULL;
					}
				}
				else
					fin = true;
			}
			else
			{
				if(Comparar(yBorrar, p) == kIguales)
				{
					mayorIzquierda = BuscarMayorIzquierda(yBorrar, p);
					intermedio = true;
					yBorrar = mayorIzquierda;
				}
			}
			if(!borrado && !fin)
			{
				switch(Comparar(yBorrar, p))
				{
					case kHijoIz:
						r = p->hijoMeIz.raiz;
						q = p->hijoIz.raiz;
						break;
					case kHijoMeIz:
						r = p->hijoIz.raiz;
						q = p->hijoMeIz.raiz;
						break;
					case kHijoMeDe:
						r = p->hijoMeIz.raiz;
						q = p->hijoMeDe.raiz;
						break;
					case kHijoDe:
						r = p->hijoMeDe.raiz;
						q = p->hijoDe.raiz;
						break;
				}
				if(Es2Nodo(q))
					if(Es2Nodo(r))
						Combinar(p, q, r);
					else
						Rotar(p, q, r);
				else
					p = q;
			} // if
		} // while
        	// en el caso de que hayamos borrado un intermedio,,,aun queda que sustituir.
		if(borrado && intermedio)
			Sustituir(y, mayorIzquierda);
	}		


	return borrado;
}

void TA234Com::Sustituir(const TComplejo &antiguo, const TComplejo &nuevo)
{
	TA234Nodo *p;
	bool encontrado;
	
	p = raiz;
	encontrado = false;
	while(p && !encontrado)
	{
		switch(Comparar(antiguo, p))
		{
			case kIguales:
				encontrado = true;
				if(antiguo == p->itIz)
					p->itIz = nuevo;
				if(antiguo == p->itMe)
					p->itMe = nuevo;
				if(antiguo == p->itDe)
					p->itDe = nuevo;
				break;
			case kHijoIz:
				p = p->hijoIz.raiz;
				break;
			case kHijoMeIz:
				p = p->hijoMeIz.raiz;
				break;
			case kHijoMeDe:
				p = p->hijoMeDe.raiz;
				break;
			case kHijoDe:
				p = p->hijoDe.raiz;
				break;
		}
	}
}

void TA234Com::Rotar(TA234Nodo *p, TA234Nodo *q, TA234Nodo *r)
{
	TComplejo *lugarEnPadre;
	if(q == p->hijoIz.raiz)
	{
		q->itMe = p->itIz;
		p->itIz = r->itIz;
		r->itIz = r->itMe;
		r->itMe = r->itDe;
		r->itDe = (0, 0);
		q->hijoMeDe.raiz = r->hijoIz.raiz;
		r->hijoIz.raiz = r->hijoMeIz.raiz;
		r->hijoMeIz.raiz = r->hijoMeDe.raiz;
		r->hijoMeDe.raiz = r->hijoDe.raiz;
		r->hijoDe.raiz = NULL;
	}
	else
	{
		if(q == p->hijoMeIz.raiz)
				lugarEnPadre = &(p->itIz);
			else
				if(q == p->hijoMeDe.raiz)
					lugarEnPadre = &(p->itMe);
				else	// q == p->hijoDe.raiz
					lugarEnPadre = &(p->itDe);
		q->itMe = q->itIz;
		q->hijoMeDe.raiz = q->hijoMeIz.raiz;
		q->hijoMeIz.raiz = q->hijoIz.raiz;
		if(Es3Nodo(r))
		{
			q->itIz = *lugarEnPadre;
			*lugarEnPadre = r->itMe;
			r->itMe = (0, 0);
			q->hijoIz.raiz = r->hijoMeDe.raiz;
			r->hijoMeDe.raiz = NULL;
		}
		else	// r es 4 nodo
		{
			q->itIz = *lugarEnPadre;
			*lugarEnPadre = r->itDe;
			r->itDe = (0, 0);
			q->hijoIz.raiz = r->hijoDe.raiz;
			r->hijoDe.raiz = NULL;
		}
	}
}

void TA234Com::Combinar(TA234Nodo *p, TA234Nodo *q, TA234Nodo *r)
{
	TA234Nodo *aux;

	if(Es2Nodo(p))
	{
		if(q == p->hijoMeIz.raiz)
		{
			aux = q;
			q = r;
			r = aux;
		}
		p->itMe = p->itIz;
		p->itIz = q->itIz;
		p->itDe = r->itIz;
		p->hijoIz.raiz = q->hijoIz.raiz; 
		p->hijoMeIz.raiz = q->hijoMeIz.raiz;
		p->hijoMeDe.raiz = r->hijoIz.raiz;
		p->hijoDe.raiz = r->hijoMeIz.raiz;
		q->hijoIz.raiz = q->hijoMeIz.raiz = r->hijoIz.raiz = r->hijoMeIz.raiz = NULL;
		delete q;
		delete r;
	}
	else
		if(Es3Nodo(p))
		{
			// si q esta apuntado al hijo medio izquierdo
			// la combinacion se realiza de la misma forma
			// que si estuviera apuntado al hijoIz
			if(q == p->hijoMeIz.raiz) // q apuntara al hijoIz y r al hijoMeDe
			{
				aux = q;
				q = r;
				r = aux;
			}
			if(q == p->hijoIz.raiz)
			{
				q->itMe = p->itIz;	// 1.
				q->itDe = r->itIz;	// 2.
				p->itIz = p->itMe;	// 3.
				p->itMe = p->itDe = (0, 0);	// 4, 5.
				q->hijoMeDe.raiz = r->hijoIz.raiz;	// 6.
				q->hijoDe.raiz = r->hijoMeIz.raiz;	// 7.
				p->hijoMeIz.raiz = p->hijoMeDe.raiz;	// 8.
				p->hijoMeDe.raiz = NULL;		// 9.
				r->hijoIz.raiz = r->hijoMeIz.raiz = NULL;
				delete r;
			}
			else
				if(q == p->hijoMeDe.raiz)
				{
					r->itMe = p->itMe;	// 1.
					p->itMe = (0, 0);	// 1.
					r->itDe = q->itIz;	// 2.
					r->hijoMeDe.raiz = q->hijoIz.raiz;	// 3.
					r->hijoDe.raiz = q->hijoMeIz.raiz;	// 4.
					p->hijoMeDe.raiz = NULL;		// 5.
					q->hijoIz.raiz = q->hijoMeIz.raiz = NULL;
					delete q;
				}
		}
		else
			if(Es4Nodo(p))
			{
				if(q == p->hijoMeIz.raiz)
				{
					aux = q;
					q = r;
					r = aux;
				}
				if(q == p->hijoIz.raiz)
				{
					q->hijoMeDe.raiz = r->hijoIz.raiz;
					q->hijoDe.raiz = r->hijoMeIz.raiz;
					p->hijoMeIz.raiz = p->hijoMeDe.raiz;
					p->hijoMeDe.raiz = p->hijoDe.raiz;
					p->hijoDe.raiz = NULL;
					q->itMe = p->itIz;
					q->itDe = r->itIz;
					p->itIz = p->itMe;
					p->itMe = p->itDe;
					p->itDe = (0, 0);
					r->hijoIz.raiz = r->hijoMeIz.raiz = NULL;
					delete r;
				}
				else
					if(q == p->hijoMeDe.raiz)
					{
						r->itDe = q->itIz;
						r->itMe = p->itMe;
						p->itMe = p->itDe;
						p->itDe = (0, 0);
						r->hijoMeDe.raiz = q->hijoIz.raiz;
						r->hijoDe.raiz = q->hijoMeIz.raiz;
						p->hijoMeDe.raiz = p->hijoDe.raiz;
						p->hijoDe.raiz = NULL;
						q->hijoIz.raiz = q->hijoMeIz.raiz = NULL;
						delete q;	
					}
					else
					{
						r->itMe = p->itDe;
						r->itDe = q->itIz;
						p->itDe = (0, 0);
						r->hijoMeDe.raiz = q->hijoIz.raiz;
						r->hijoDe.raiz = q->hijoMeIz.raiz;
						p->hijoDe.raiz = NULL;
						q->hijoIz.raiz = q->hijoMeIz.raiz = NULL;
						delete q;
					}
			}
}

TComplejo TA234Com::BuscarMayorIzquierda(const TComplejo &y, TA234Nodo *p)
{
	TComplejo mayor, vacio;
	TA234Nodo *aux;
	
	if(y == p->itIz)
		aux =  p->hijoIz.raiz;
	if(y == p->itMe)
		aux = p->hijoMeIz.raiz;
	if(y == p->itDe)
		aux = p->hijoMeDe.raiz;
	while(aux)
	{
		if(aux->itMe == vacio)	// 2-nodo
		{
			mayor = aux->itIz;			
			aux = aux->hijoMeIz.raiz;
		}
		else
			if(aux->itDe == vacio)	// 3-nodo
			{
				mayor = aux->itMe;
				aux = aux->hijoMeDe.raiz;
			}			
			else	// 4-nodo
			{
				mayor = aux->itDe;
				aux = aux->hijoDe.raiz;
			}
	}

	return mayor;
}

bool TA234Com::EsHoja(const TA234Nodo *n) const
{
	return n && !n->hijoIz.raiz && !n->hijoMeIz.raiz &&
		!n->hijoMeDe.raiz && !n->hijoDe.raiz;

}

TCola::TCola()
{
	tope = fondo = NULL;
}

TCola::~TCola()
{
	TNodo *ptB;
	ptB = tope;
	while(ptB)
	{
		tope = tope->sig;
		delete ptB;
		ptB = tope;
	}
}

void * TCola::Desencolar()
{
	void *aux;
	TNodo *ptB;
	if(tope)
	{
		aux = tope->item;
		ptB = tope;
		tope = tope->sig;
		if(!tope)
			fondo = NULL;
		delete ptB;
	}
	
	return aux;
}

void TCola::Encolar(void *elemento)
{
	TNodo *ptN;
	
	ptN = new TNodo;
	ptN->item = elemento;
	ptN->sig = NULL;
	
	if(fondo)
	{
		fondo->sig = ptN;
		fondo = ptN;
	}
	else
		fondo = tope = ptN;
}
