#include "tavlcom.h"

TAVLCom::TAVLCom()
{
	raiz = NULL;
}

TAVLCom::~TAVLCom()
{
	if(raiz != NULL)
	{
		// (raiz->iz).~TAVLDir();
		// (nodo->de).~TAVLDir();
		delete raiz;
		raiz = NULL;
	}
	
}

TAVLCom::TAVLCom(const TAVLCom &de)
{
	if(!de.raiz)
		raiz = NULL;
	else
		raiz = new TAVLNodo(*(de.raiz));
}


TAVLCom &TAVLCom::operator=(const TAVLCom &de)
{
	if(this != &de)
	{
		this->~TAVLCom();
		if(de.raiz != NULL)
		{
			raiz = new TAVLNodo;
			*raiz = *(de.raiz);
		}
	}
	return *this;
}

// RECORRIDOS //////////////////////////
TVectorCom TAVLCom::Inorden() const{
	int posicion;
	TVectorCom v( Nodos() );

	posicion = 1;
	InordenAux(v, posicion);

	return v;
}

void TAVLCom::InordenAux(TVectorCom &v, int &posicion) const{
	if(raiz != NULL)
	{
		raiz->iz.InordenAux(v, posicion);
		v[posicion] = raiz->item;
		posicion++;
		raiz->de.InordenAux(v, posicion);
	}
}

TVectorCom TAVLCom::Preorden() const{
	int posicion;
	TVectorCom v( Nodos() );

	posicion = 1;
	PreordenAux(v, posicion);

	return v;
}

void TAVLCom::PreordenAux(TVectorCom &v, int &posicion) const{
	if(raiz != NULL)
	{
		v[posicion] = raiz->item;
		posicion++;
		raiz->iz.PreordenAux(v, posicion);
		raiz->de.PreordenAux(v, posicion);
	}
}

TVectorCom TAVLCom::Niveles() const{
	TVectorCom v(Nodos());
	queue<TAVLNodo *> cola;
	TAVLNodo *aux;
	int i;
	i = 1;
	cola.push(raiz);
	while(!cola.empty()){
		aux = cola.front();
		cola.pop();		
		if(aux != NULL){
			v[i] = aux->item;
			i++;
			cola.push(aux->iz.raiz);
			cola.push(aux->de.raiz);
		}	
	}
	return v;
}

TVectorCom TAVLCom::Postorden() const{
	int posicion;
	TVectorCom v( Nodos() );

	posicion = 1;
	PostordenAux(v, posicion);

	return v;
}

void TAVLCom::PostordenAux(TVectorCom &v, int &posicion) const{
	if(raiz != NULL){
		raiz->iz.PostordenAux(v, posicion);
		raiz->de.PostordenAux(v, posicion);
		v[posicion] = raiz->item;
		posicion++;
	}
}


// ------------------------- RECORRIDOS -------------- //


bool TAVLCom::Insertar(const TComplejo &c)
{
	bool insertado, crece;

	insertado = Insertar(c, crece);
	
	return insertado;
}

bool TAVLCom::Insertar(const TComplejo &c, bool &crece)
{
	bool creceIz, creceDe;
	bool insertado;

	creceIz = creceDe = false;	
	insertado = false;
	
	if(c.Re() != 0 || c.Im() != 0) // el avl no admite complejos vacios
	if(EsVacio())
	{
		raiz = new TAVLNodo;
		raiz->fe = 0;
		raiz->item = c;
		crece = true;
		insertado = true;
	}
	else
		if(raiz->item.Mod() != c.Mod())
		{
			if(c.Mod() < raiz->item.Mod())
				insertado = raiz->iz.Insertar(c, creceIz);
		
			else
				insertado = raiz->de.Insertar(c, creceDe);
			if(creceIz)
			{
				raiz->fe--;
				switch(raiz->fe)
				{
					case 0:
						crece = false;
					break;
					case -1:
						crece = true;
					break;
					case -2:
						crece = false;
						switch(raiz->iz.raiz->fe)
						{
							case -1:
								II();
							break;
							case +1:
								ID();
							break;						
						}
					break;
				}
			}
			else
				if(creceDe)
				{
					raiz->fe++;
					switch(raiz->fe)
					{
						case 0:
							crece = false;
						break;
						case 1:
							crece = true;
						break;
						case 2:
							crece = false;
							switch(raiz->de.raiz->fe)
							{
								case -1:
									DI();
								break;
								case +1:
									DD();
								break;
							}
						break;
					}
				}
		}
		else
			insertado = crece = false;

	return insertado;
}


bool TAVLCom::Buscar(const TComplejo &c) const
{
	bool encontrado;

	if(raiz != NULL)
		encontrado = raiz->iz.Buscar(c) || raiz->de.Buscar(c) || raiz->item == c;
	else
		encontrado = false;
	
	return encontrado;
}


int TAVLCom::Nodos() const
{
	int nodos;

	if(!raiz)
		nodos = 0;
	else
		nodos = 1 + raiz->iz.Nodos() + raiz->de.Nodos();
	return nodos;
}

int TAVLCom::NodosHoja() const
{
	int nodosHoja;

	if(!raiz)
		nodosHoja = 0;
	else	
		if(raiz->iz.EsVacio() && raiz->de.EsVacio())
			nodosHoja = 1;
		else
			nodosHoja = raiz->iz.NodosHoja() + raiz->de.NodosHoja();
	
	return nodosHoja;
}

int TAVLCom::Altura() const
{
	int alturaTotal, alturaIz, alturaDe;
	
	if(!raiz)
		alturaTotal = 0;
	else
	{
		alturaIz = raiz->iz.Altura();
		alturaDe = raiz->de.Altura();
		if(alturaIz > alturaDe)
			alturaTotal = alturaIz + 1;
		else
			alturaTotal = alturaDe + 1;
	}
	
	return alturaTotal;
}

bool TAVLCom::EsVacio() const
{
	return !raiz;	
}

bool TAVLCom::operator==(const TAVLCom &de) const
{
	bool iguales;

	if(EsVacio() && de.EsVacio())
		iguales = true;
	else
		if(!EsVacio() && !de.EsVacio())
			iguales = raiz->iz == de.raiz->iz && raiz->de == de.raiz->de && raiz->item == de.raiz->item;
		else
			iguales = false;
	return iguales;
}

bool TAVLCom::operator!=(const TAVLCom &de) const
{
	return !(*this == de);

}

void TAVLCom::DD()
{
	TAVLNodo *auxR;
	
	auxR = raiz;
	raiz = auxR->de.raiz;
	auxR->de.raiz = raiz->iz.raiz;
	raiz->iz.raiz = auxR;
	if(raiz->fe == 0)
	{
		raiz->fe = -1;
		raiz->iz.raiz->fe = 1;
	}
	else
	{
		raiz->fe = 0;
		raiz->iz.raiz->fe = 0;
	}
}

void TAVLCom::II()
{
	TAVLNodo *auxR;
	
	auxR = raiz;
	raiz = auxR->iz.raiz;
	auxR->iz.raiz = raiz->de.raiz;
	raiz->de.raiz = auxR;
	if(raiz->fe == 0)
	{
		raiz->fe = 1;
		raiz->de.raiz->fe = -1;
	}
	else
	{
		raiz->fe = 0;
		raiz->de.raiz->fe = 0;
	}
}

void TAVLCom::ID()
{
	TAVLNodo *auxR, *auxIz, *auxDe;
	
	auxR = raiz;
	raiz = raiz->iz.raiz->de.raiz;
	auxIz = raiz->iz.raiz;
	auxDe = raiz->de.raiz;
	raiz->iz.raiz = auxR->iz.raiz;
	raiz->de.raiz = auxR;
	auxR->iz.raiz = auxDe;
	raiz->iz.raiz->de.raiz = auxIz;
	if(raiz->fe == 0)
		raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;
	else
		if(raiz->fe == -1)
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = 0;
			raiz->de.raiz->fe = 1;	
		}
		else
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = -1;	
			raiz->de.raiz->fe = 0;	
		}
}

void TAVLCom::DI()
{
	TAVLNodo *auxR, *auxIz, *auxDe;
	
	auxR = raiz;
	raiz = raiz->de.raiz->iz.raiz;
	auxIz = raiz->iz.raiz;
	auxDe = raiz->de.raiz;
	raiz->de.raiz = auxR->de.raiz;
	raiz->iz.raiz = auxR;
	auxR->de.raiz = auxIz;
	raiz->de.raiz->iz.raiz = auxDe;
	if(raiz->fe == 0)
		raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;
	else
		if(raiz->fe == -1)
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = 0;
			raiz->de.raiz->fe = 1;	
		}
		else
		{
			raiz->fe = 0;
			raiz->iz.raiz->fe = -1;
			raiz->de.raiz->fe = 0;	
		}
}



bool TAVLCom::Borrar(const TComplejo &c)
{
	bool decrece = false;
	return Borrar(c, decrece);
}

bool TAVLCom::Borrar(const TComplejo &c, bool &decrece)
{
	bool borrado, decreceIz, decreceDe;
	TComplejo mayorIz;
	TAVLNodo *ptB, *raizAux;

	// si el arbol esta vacio o llegamos a arbol vacio, no se puede borrar.
	decrece = false;
	decreceIz = decreceDe = false;
	if(!raiz)
		decrece = borrado = false;
	else	// si encontramos el nodo.
		if(c.Mod() < raiz->item.Mod())
			borrado = raiz->iz.Borrar(c, decreceIz);
		else
			if(c.Mod() > raiz->item.Mod())
				borrado = raiz->de.Borrar(c, decreceDe);
			else
				if(raiz->item == c)
					if(raiz->iz.EsVacio() && raiz->de.EsVacio())	// NODO HOJA
					{
						delete raiz;
						raiz = NULL;
						decrece = borrado = true;
					}
					else
						if(!raiz->iz.EsVacio() && raiz->de.EsVacio())	// SOLO HIJO IZQUIERDO
						{
							ptB = raiz;
							raiz = raiz->iz.raiz;
							ptB->iz.raiz = ptB->de.raiz = NULL;
							delete ptB;
							decrece = borrado = true;
						}
						else
							if(raiz->iz.EsVacio() && !raiz->de.EsVacio())	// SOLO HIJO DERECHO	
							{
								ptB = raiz;
								raiz = raiz->de.raiz;
								ptB->iz.raiz = ptB->de.raiz = NULL;
								delete ptB;
								decrece = borrado = true;	
							}
							else	// DOS HIJOS.
							{
								mayorIz = raiz->iz.BuscarMayor();
								// OJO OJO OJO OJO !!!!!!!!!!!!!
								// hago esto porque la rotacion puede cambiar la raiz ;)
								raizAux = raiz;
								borrado = Borrar(mayorIz, decrece);
								raizAux->item = mayorIz;
							}
	// En el proceso de vuelta comprobamos si es necesario hacer
	// reestructuraciones.
	if(borrado)
	{
		if(decreceIz)
		{
			raiz->fe++;
			switch(raiz->fe)
			{
				case 0:
					decrece = true;
					break;
				case 1:
					decrece = false;	
					break;
				case 2:
					switch(raiz->de.raiz->fe)
					{
						case -1:
							DI();
							decrece = true;	
						break;
						case 0:
							DD();
							decrece = false;
						break;
						case 1:
							DD();
							decrece = true;
						break;
					}
				break;
	
			}
		}
		else
			if(decreceDe)
			{
				raiz->fe--;
				switch(raiz->fe)
				{
					case 0:
						decrece = true;
						break;
					case -1:
						decrece = false;
						break;
					case -2:
						switch(raiz->iz.raiz->fe)
						{
							case -1:
								II();
								decrece = true;
								break;
							case 0:
								II();
								decrece = false;
								break;
							case 1:
								ID();
								decrece = true;
								break;
						}
				}
			}
	}
	return borrado;
}


TComplejo TAVLCom::BuscarMayor() const
{
	TComplejo mayor;
	if(raiz)
		if(raiz->de.raiz)
			mayor = raiz->de.BuscarMayor();
		else
			mayor = raiz->item;
	return mayor;

}

TAVLNodo::TAVLNodo()
{
	fe = 0;
}

TAVLNodo::TAVLNodo(const TAVLNodo &o)
:iz(o.iz), de(o.de), item(o.item), fe(o.fe)
{ }

TAVLNodo &TAVLNodo::operator=(const TAVLNodo &de)
{
	iz = de.iz;
	this->de = de.de;
	item = de.item;
	fe = de.fe;
	
	return *this;
}

TAVLNodo::~TAVLNodo()
{
	fe = 0;
}

TColaAVLNodo::TColaAVLNodo()
{
	tope = fondo = NULL;
}

TColaAVLNodo::~TColaAVLNodo()
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

void * TColaAVLNodo::Desencolar()
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

void TColaAVLNodo::Encolar(void *elemento)
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

