#include "tavlcom.h"

TAVLCom::TAVLCom(){raiz = NULL;}

TAVLCom::~TAVLCom(){
	if(raiz != NULL){delete raiz;raiz = NULL;}
}

TAVLCom::TAVLCom(const TAVLCom &de){
	if(!de.raiz){raiz = NULL;}
	else{raiz = new TAVLNodo(*(de.raiz));}
}


TAVLCom &TAVLCom::operator=(const TAVLCom &de){
	if(this != &de){this->~TAVLCom(); if(de.raiz != NULL){raiz = new TAVLNodo;*raiz = *(de.raiz);} }
	return *this;
}

TVectorCom TAVLCom::Inorden() const{
	int p=1;
	TVectorCom v( Nodos() );
	InordenAux(v, p);
	return v;
}

void TAVLCom::InordenAux(TVectorCom &v, int &p) const{
	if(raiz != NULL){ raiz->iz.InordenAux(v, p); v[p] = raiz->item; p++; raiz->de.InordenAux(v, p);}
}

TVectorCom TAVLCom::Preorden() const{
	int p=1;
	TVectorCom v( Nodos() );
	PreordenAux(v, p);
	return v;
}

void TAVLCom::PreordenAux(TVectorCom &v, int &p) const{
	if(raiz != NULL){ v[p] = raiz->item; p++;raiz->iz.PreordenAux(v, p); raiz->de.PreordenAux(v, p);}
}

TVectorCom TAVLCom::Niveles() const{
	TVectorCom v(Nodos());
	queue<TAVLNodo *> cola;
	TAVLNodo *aux;
	int i=1;
	cola.push(raiz);
	while(!cola.empty()){
		aux = cola.front();
		cola.pop();		
		if(aux != NULL){ v[i] = aux->item; i++; cola.push(aux->iz.raiz); cola.push(aux->de.raiz);}	
	}
	return v;
}

TVectorCom TAVLCom::Postorden() const{
	int p=1;
	TVectorCom v( Nodos() );
	PostordenAux(v, p);
	return v;
}

void TAVLCom::PostordenAux(TVectorCom &v, int &p) const{
	if(raiz != NULL){raiz->iz.PostordenAux(v, p); raiz->de.PostordenAux(v, p); v[p] = raiz->item; p++;}
}

bool TAVLCom::Insertar(const TComplejo &c){bool i, cr; i=Insertar(c, cr); return i;}

bool TAVLCom::Insertar(const TComplejo &c, bool &crece){
	bool creceIz =false, creceDe=false, insertado=false;
	
	if(c.Re() != 0 || c.Im() != 0){
		if(EsVacio()){raiz = new TAVLNodo; raiz->fe = 0; raiz->item = c; crece = true; insertado = true;}
		else
			if(raiz->item.Mod() != c.Mod())
			{
				if(c.Mod() < raiz->item.Mod()){insertado = raiz->iz.Insertar(c, creceIz);}
				else{insertado = raiz->de.Insertar(c, creceDe);}
				if(creceIz)
				{
					raiz->fe--;
					switch(raiz->fe)
					{
						case 0: crece = false;
						break;
						case -1: crece = true;
						break;
						case -2: crece = false;
							switch(raiz->iz.raiz->fe)
							{
								case -1: II();
								break;
								case +1: ID();
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
							case 0: crece = false;
							break;
							case 1: crece = true;
							break;
							case 2: crece = false;
									switch(raiz->de.raiz->fe)
									{
										case -1: DI();
										break;
										case +1: DD();
										break;
									}
							break;
						}
					}
			}
			else{insertado = false; crece = false;}
	}
	return insertado;
}

bool TAVLCom::Buscar(const TComplejo &c) const{
	bool e;
	if(raiz != NULL){e = raiz->iz.Buscar(c) || raiz->de.Buscar(c) || raiz->item == c;}
	else{e = false;}
	return e;
}

int TAVLCom::Nodos() const{
	int n;
	if(!raiz){n = 0;}
	else{n = 1 + raiz->iz.Nodos() + raiz->de.Nodos();}
	return n;
}

int TAVLCom::NodosHoja() const{
	int nh;
	if(raiz==false){nh=0;}
	else{
		if(raiz->iz.EsVacio() && raiz->de.EsVacio()){nh = 1;}
		else{nh = raiz->iz.NodosHoja() + raiz->de.NodosHoja();}
	}
	return nh;
}

int TAVLCom::Altura() const{
	int at,ai,ad;
	if(raiz==false){at = 0;}
	else{
		ai = raiz->iz.Altura();
		ad = raiz->de.Altura();
		if(ai > ad){at = ai + 1;}
		else{at = ad + 1;}
	}
	return at;
}

bool TAVLCom::EsVacio() const{return !raiz;}

bool TAVLCom::operator==(const TAVLCom &de) const{
	bool i;

	if(EsVacio() && de.EsVacio()){i = true;}
	else{
		if(!EsVacio() && !de.EsVacio()){i = raiz->iz == de.raiz->iz && raiz->de == de.raiz->de && raiz->item == de.raiz->item;}
		else{i = false;}
	}
	return i;
}

bool TAVLCom::operator!=(const TAVLCom &de) const{return !(*this == de);}

void TAVLCom::DD(){
	TAVLNodo *a=raiz;

	raiz = a->de.raiz;
	a->de.raiz = raiz->iz.raiz;
	raiz->iz.raiz = a;
	
	if(raiz->fe == 0){raiz->fe = -1;raiz->iz.raiz->fe = 1;}
	else{raiz->fe = 0;raiz->iz.raiz->fe = 0;}
}

void TAVLCom::II(){
	TAVLNodo *a;
	
	a = raiz;
	raiz = a->iz.raiz;
	a->iz.raiz = raiz->de.raiz;
	raiz->de.raiz = a;
	
	if(raiz->fe == 0){raiz->fe = 1;raiz->de.raiz->fe = -1;}
	else{raiz->fe = 0;raiz->de.raiz->fe = 0;}
}

void TAVLCom::ID(){
	TAVLNodo *ar, *ai, *ad;
	
	ar = raiz;
	raiz = raiz->iz.raiz->de.raiz;
	ai = raiz->iz.raiz;
	ad = raiz->de.raiz;
	raiz->iz.raiz = ar->iz.raiz;
	raiz->de.raiz = ar;
	ar->iz.raiz = ad;
	raiz->iz.raiz->de.raiz = ai;
	if(raiz->fe == 0){raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;}
	else{
		if(raiz->fe == -1){raiz->fe = 0;raiz->iz.raiz->fe = 0;raiz->de.raiz->fe = 1;}
		else{raiz->fe = 0;raiz->iz.raiz->fe = -1;	raiz->de.raiz->fe = 0;}
	}
}

void TAVLCom::DI(){
	TAVLNodo *ar, *ai, *ad;
	
	ar = raiz;
	raiz = raiz->de.raiz->iz.raiz;
	ai = raiz->iz.raiz;
	ad = raiz->de.raiz;
	raiz->de.raiz = ar->de.raiz;
	raiz->iz.raiz = ar;
	ar->de.raiz = ai;
	raiz->de.raiz->iz.raiz = ad;
	
	if(raiz->fe == 0){raiz->fe = raiz->iz.raiz->fe = raiz->de.raiz->fe = 0;}
	else{
		if(raiz->fe == -1){raiz->fe = 0;raiz->iz.raiz->fe = 0;raiz->de.raiz->fe = 1;}
		else{raiz->fe = 0;raiz->iz.raiz->fe = -1;raiz->de.raiz->fe = 0;}
	}
}

bool TAVLCom::Borrar(const TComplejo &c){bool d = false;return Borrar(c, d);}

bool TAVLCom::Borrar(const TComplejo &c, bool &dec)
{
	bool borrado, di=false, dd=false; dec=false;
	TComplejo mi;
	TAVLNodo *ptB, *raiz;

	if(raiz==false){dec = borrado = false;}
	else
		if(c.Mod() < raiz->item.Mod()){borrado = raiz->iz.Borrar(c, di);}
		else{
			if(c.Mod() > raiz->item.Mod()){borrado = raiz->de.Borrar(c, dd);}
			else{
				if(raiz->item == c){
					if(raiz->iz.EsVacio() && raiz->de.EsVacio()){delete raiz;raiz = NULL;dec=borrado=true;}
					else{
						if(!raiz->iz.EsVacio() && raiz->de.EsVacio()){ptB = raiz;raiz = raiz->iz.raiz;ptB->iz.raiz = ptB->de.raiz = NULL;delete ptB;dec=borrado=true;}
						else{
							if(raiz->iz.EsVacio() && !raiz->de.EsVacio()){ptB = raiz;raiz = raiz->de.raiz;ptB->iz.raiz = ptB->de.raiz = NULL;delete ptB;dec=borrado=true;	}
							else{mi = raiz->iz.BuscarMayor();raiz = raiz;borrado = Borrar(mi, dec);raiz->item = mi;}
						}
					}
				}
			}
		}

	if(borrado){
		if(di){
			raiz->fe++;
			switch(raiz->fe)
			{
				case 0:dec=true;
				break;
				case 1:dec=false;	
				break;
				case 2:
					switch(raiz->de.raiz->fe)
					{
						case -1: DI();dec=true;	
						break;
						case 0: DD();dec=false;
						break;
						case 1: DD();dec=true;
						break;
					}
				break;
	
			}
		}
		else
			if(dd)
			{
				raiz->fe--;
				switch(raiz->fe)
				{
					case 0: dec=true;
					break;
					case -1: dec=false;
					break;
					case -2:
						switch(raiz->iz.raiz->fe)
						{
							case -1: II();dec=true;
							break;
							case 0: II();dec=false;
							break;
							case 1: ID();dec=true;
							break;
						}
				}
			}
	}
	return borrado;
}


TComplejo TAVLCom::BuscarMayor() const{
	TComplejo m;
	if(raiz){
		if(raiz->de.raiz){m = raiz->de.BuscarMayor();}
		else{m = raiz->item;}
	}
	return m;

}

TAVLNodo::TAVLNodo(){fe = 0;}

TAVLNodo::TAVLNodo(const TAVLNodo &o)
:iz(o.iz), de(o.de), item(o.item), fe(o.fe)
{ }

TAVLNodo &TAVLNodo::operator=(const TAVLNodo &de){iz = de.iz;this->de = de.de;item = de.item;fe = de.fe;return *this;}

TAVLNodo::~TAVLNodo(){fe=0;}

TColaAVLNodo::TColaAVLNodo(){tope=fondo=NULL;}

TColaAVLNodo::~TColaAVLNodo(){
	TNodo *ptB;
	ptB = tope;
	while(ptB){tope = tope->sig;delete ptB;ptB = tope;}
}

void * TColaAVLNodo::Desencolar(){
	void *a;
	TNodo *ptB;
	if(tope){
		a = tope->item;
		ptB=tope;
		tope = tope->sig;
		if(!tope){fondo=NULL;}
		delete ptB;
	}
	return a;
}

void TColaAVLNodo::Encolar(void *e){
	TNodo *ptN;
	
	ptN = new TNodo;
	ptN->item = e;
	ptN->sig = NULL;
	
	if(fondo){fondo->sig = ptN;fondo = ptN;}
	else{fondo = tope = ptN;}
}

