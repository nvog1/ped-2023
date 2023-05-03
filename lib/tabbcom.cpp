#include "tabbcom.h"  
#include <queue>
TABBCom::TABBCom(){
  nodo = NULL;
}

TABBCom::TABBCom(const TABBCom& other){
  if(!other.EsVacio())
    nodo = new TNodoABB(*other.nodo);
  else nodo = NULL;
}

TABBCom::~TABBCom(){
  if(!EsVacio()) delete nodo;
  nodo = NULL;
}

TABBCom&
TABBCom::operator=(const TABBCom& other){
  if(!other.EsVacio()){
    TABBCom *aux = new TABBCom(other);
    if(!EsVacio()){
      delete nodo;
    }
    this->nodo = aux->nodo;
    aux->nodo = NULL;
    delete aux;
    aux = NULL;
  }
  else if(!EsVacio()){
    delete this->nodo;
    this->nodo = NULL;
  }
  return *this;
}

bool
TABBCom::operator==(const TABBCom& other) const{
  if(this == &other) return true;
  if(this->Nodos() == other.Nodos() && this->Inorden() == other.Inorden()) return true;
  else return false;
}

bool
TABBCom::EsVacio() const{
  if(nodo) return false;
  else return true;
}

bool 
TABBCom::Insertar(const TComplejo& c){
  if(EsVacio()){//inserto
    nodo = new TNodoABB();
    nodo->item = c;
    return true;
  }
  else{//intento insertar en los hijos
    if(nodo->item == c)return false;
    if(c < nodo->item) return nodo->iz.Insertar(c);
    else return nodo->de.Insertar(c);
  }
}

bool
TABBCom::Borrar(const TComplejo& c){
  if(EsVacio()) return false;
  else{
    if(nodo->item == c){//es el que tengo que borrar, lo borro
      if(nodo->iz.EsVacio() && nodo->de.EsVacio()){//es hoja
        delete nodo;
        nodo = NULL;
        return true;
      }
      else if(nodo->iz.EsVacio()){//1 hijo, sustituyo por hijo de
        TNodoABB *aux = nodo;
        nodo = nodo->de.nodo;
        aux->de.nodo = NULL;
        delete aux;
        aux = NULL;
        return true;
      }
      else if(nodo->de.EsVacio()){//1 hijo, sustituyo por hijo iz
        TNodoABB *aux = nodo;
        nodo = nodo->iz.nodo;
        aux->iz.nodo = NULL;
        delete aux;
        aux = NULL;
        return true;
      }
      else{//2 hijos
        //encuentro el mayor de la izquierda
        TABBCom *mayorIz = this;
        mayorIz = &nodo->iz;
        while(!mayorIz->nodo->de.EsVacio()){
          mayorIz = &mayorIz->nodo->de;
        }
        nodo->item = mayorIz->nodo->item;
        TComplejo mayorIzCom = mayorIz->nodo->item;
        mayorIz = NULL;
        return nodo->iz.Borrar(mayorIzCom);
        /*if(!mayorIz->iz.EsVacio()){
          if(mayorIz == anterior->iz.nodo){
            anterior->iz = mayorIz->iz;
          }
          else{
            anterior->de = mayorIz->iz;
          }
          mayorIz->iz.nodo = NULL;
        }
        */
      }
    }
    else if(c < nodo->item) return nodo->iz.Borrar(c);
    else return nodo->de.Borrar(c);
  }
}

bool
TABBCom::Buscar(const TComplejo& c) const{
  if(EsVacio()) return false;
  else{
    if(nodo->item == c) return true;
    else return nodo->iz.Buscar(c) || nodo->de.Buscar(c);
  }
}

TComplejo
TABBCom::Raiz() const{
  if(EsVacio()){
    TComplejo aux;
    return aux;
  }
  else return nodo->item;
}

int
TABBCom::Altura() const{
  if(EsVacio()) return 0;
  else return std::max(nodo->iz.Altura(),nodo->de.Altura()) + 1;
  return -1;
}

int
TABBCom::Nodos() const{
  if(EsVacio()) return 0;
  else return nodo->iz.Nodos() + nodo->de.Nodos() + 1;
}

int
TABBCom::NodosHoja() const{
  if(EsVacio()) return 0;
  else if(nodo->iz.EsVacio() && nodo->de.EsVacio()) return 1;
  else return nodo->iz.NodosHoja() + nodo->de.NodosHoja();
}

void 
TABBCom::InordenAux(TVectorCom& v, int& pos) const{
  if(EsVacio()) return;
  nodo->iz.InordenAux(v,pos);
  v[pos] = nodo->item;
  pos++;
  nodo->de.InordenAux(v,pos);
}

void 
TABBCom::PreordenAux(TVectorCom& v, int& pos) const{
  if(EsVacio()) return;
  v[pos] = nodo->item;
  pos++;
  nodo->iz.PreordenAux(v,pos);
  nodo->de.PreordenAux(v,pos);
}

void 
TABBCom::PostordenAux(TVectorCom& v, int& pos) const{
  if(EsVacio()) return;
  nodo->iz.PostordenAux(v,pos);
  nodo->de.PostordenAux(v,pos);
  v[pos] = nodo->item;
  pos++;
}

TVectorCom
TABBCom::Inorden() const{
  TVectorCom v(Nodos());
  int pos = 1;
  InordenAux(v,pos);
  return v;
}

TVectorCom
TABBCom::Preorden() const{
  TVectorCom v(Nodos());
  int pos = 1;
  PreordenAux(v,pos);

  return v;
}

TVectorCom
TABBCom::Postorden() const{
  TVectorCom v(Nodos());
  int pos = 1;
  PostordenAux(v,pos);

  return v;
}

TVectorCom
TABBCom::Niveles() const{
  TVectorCom v(Nodos());
  int i = 1;
  std::queue<TABBCom> c;
  TABBCom aux;
  if(!this->EsVacio()){
    c.push(*this);
    while(!c.empty()){
      aux = c.front();
      v[i] = aux.Raiz();
      c.pop();
      i++;
      if(!aux.nodo->iz.EsVacio()) c.push(aux.nodo->iz);
      if(!aux.nodo->de.EsVacio()) c.push(aux.nodo->de);
    }
  }

  return v;
}
   
ostream&
operator<<(ostream& os, const TABBCom& abb){
  os << abb.Niveles();
  return os;
}

//TNodoABB

TNodoABB::TNodoABB():item(),error(),iz(),de(){
}

TNodoABB::TNodoABB(const TNodoABB& other):item(other.item),error(other.error),iz(other.iz),de(other.de){
}

TNodoABB::~TNodoABB(){
}

TNodoABB&
TNodoABB::operator=(const TNodoABB& other){
  item = other.item;
  iz = other.iz;
  de = other.de;
  return *this;
}
