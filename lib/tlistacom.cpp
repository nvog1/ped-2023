#include <iostream>
#include "tlistacom.h"
using namespace std;

//ListaNodo
TListaNodo::TListaNodo():e(){
  anterior = NULL;
  siguiente = NULL; 
}

TListaNodo::TListaNodo(const TListaNodo& other):e(other.e){
  anterior = other.anterior;
  siguiente = other.siguiente;
}

TListaNodo::~TListaNodo(){
  anterior = NULL;
  siguiente = NULL;
}

TListaNodo& 
TListaNodo::operator=(const TListaNodo& other){
  siguiente = other.siguiente;
  anterior = other.anterior;
  e = other.e;
  return *this;
}

bool
TListaNodo::operator==(const TListaNodo& other) const{
  if(e == other.e && anterior == other.anterior && siguiente == other.siguiente) return true;
  return false;
}

bool 
TListaNodo::operator!=(const TListaNodo& other) const{
  if(!((*this) == other)) return true;
  return false;
}

//ListaPos
TListaPos::TListaPos(){
  pos = NULL;
}

TListaPos::TListaPos(const TListaPos& other){
  pos = other.pos;
}

TListaPos::~TListaPos(){
  pos = NULL;
}

TListaPos& 
TListaPos::operator=(const TListaPos& other){
  pos = other.pos;
  return *this;
}

bool 
TListaPos::operator==(const TListaPos& other) const{
  if(pos == other.pos) return true;
  return false;
}

bool 
TListaPos::operator!=(const TListaPos& other) const{
  if(!((*this) == other)) return true;
  return false;
}

TListaPos 
TListaPos::Anterior() const{
  if(this->EsVacia()) return *this;
  TListaPos posAux;
  if(pos->anterior != NULL){
    posAux.pos = pos->anterior;
  }
  return posAux;
}

TListaPos 
TListaPos::Siguiente() const{
  if(this->EsVacia()) return *this;
  TListaPos posAux;
  if(pos->siguiente != NULL){
    posAux.pos = pos->siguiente;
  }
  return posAux;
}

bool 
TListaPos::EsVacia() const{
  if(pos == NULL) return true;
  return false;

}

//ListaCom
TListaCom&
TListaCom::LiberarMemoria(){
  if(primero!=NULL){//si no esta vacia
    TListaPos actual;
    actual.pos = primero;
    TListaPos aux = actual;
    do{
      aux = aux.Siguiente();
      delete actual.pos;
      actual = aux;
    }while(!actual.EsVacia());
    primero = NULL;
    ultimo = NULL;
  }

  return *this;
}

TListaCom&
TListaCom::Copiar(const TListaCom& other){

  if(other.primero != NULL){//si no esta vacia

    primero = new TListaNodo(*(other.primero));

    if(other.ultimo != other.primero){//si tiene mas de un elemento
      ultimo = new TListaNodo(*(other.ultimo));

      TListaPos miPrevia= this->Primera();
      TListaPos otherActual = other.Primera();
      TListaPos otherUltima = other.Ultima();
      otherActual = otherActual.Siguiente();

      while(otherActual != otherUltima){//mientras la actual de la otra no sea la ultima de la otra
        miPrevia.pos->siguiente = new TListaNodo(*(otherActual.pos));//hago una copia y apunto la anterior a la copia
        TListaNodo *aux = miPrevia.pos;//me guardo la posicion antes de avanzar para actualizar el puntero anterior cuando avance
        miPrevia = miPrevia.Siguiente();//avanzo a la copia
        miPrevia.pos->anterior = aux;//enlazo la copia con la anterior
        aux = NULL;
        otherActual = otherActual.Siguiente();//avanzo en la otra lista
      }
      miPrevia.pos->siguiente = ultimo;//enlazo la penultima con la ultima
      ultimo->anterior = miPrevia.pos;//enlazo la ultima con la penultima
    }
    else{//si solo tiene un elemento
      ultimo = primero;
    }


  }
  else{//si esta vacia
  primero = NULL;
  ultimo = NULL; 
  }

  return *this;
}

TListaCom::TListaCom(){
  primero = NULL;
  ultimo = NULL;
}


TListaCom::TListaCom(const TListaCom& other){
  this->Copiar(other);
}

TListaCom::~TListaCom(){
  this->LiberarMemoria();
}

TListaCom& 
TListaCom::operator=(const TListaCom& other){
  this->LiberarMemoria();
  if(!other.EsVacia())
    this->Copiar(other);
  
  return *this;
}

bool 
TListaCom::operator==(const TListaCom& other) const{
  if(this->Longitud() == other.Longitud()){//si tienen la misma longitud
    if(this->EsVacia()) return true;//si estan vacias -> cierto
    else{//si no estan vacias
      TListaPos esta = this->Primera();
      TListaPos otra = other.Primera();
      while(!esta.EsVacia()){//recorro las listas hasta el final
        if(*(esta.pos) != *(otra.pos)) return false;//si algun nodo es distinto -> falso
        esta = esta.Siguiente();
        otra = otra.Siguiente();
      }
      //son iguales
      return true;
    }
  }
  
  return false;

}

bool 
TListaCom::operator!=(const TListaCom& other) const{
  if(!((*this) == other)) return true;
  return false;
}

TListaCom 
TListaCom::operator+(const TListaCom& other) const{
  if(!this->EsVacia()){
    TListaCom lis(*this);

    TListaPos cola = lis.Ultima();
    for(TListaPos actual=other.Primera(); !actual.EsVacia(); actual = actual.Siguiente()){
      lis.InsertarD(other.Obtener(actual),cola);
      cola = cola.Siguiente();
    }

    return lis;
  }
  else{//si la primera lista esta vacia
    TListaCom lis(other);
    return lis;
  }
}

TListaCom 
TListaCom::operator-(const TListaCom& other) const{
  if(this->EsVacia()) return *this;
  TListaCom lis(*this);
  for(TListaPos actual=other.Primera(); !actual.EsVacia(); actual=actual.Siguiente()){
    lis.BorrarTodos(other.Obtener(actual));
  }
  return lis;

}

bool 
TListaCom::EsVacia() const{
  if(primero == NULL && ultimo == NULL) return true;
  return false;

}

bool 
TListaCom::InsCabeza(const TComplejo& com){
  TListaNodo *nuevo = new TListaNodo(); //como compruebo que no de segmentation fault?
  nuevo->e = com;
  if(this->EsVacia()){
    primero = ultimo = nuevo;
    nuevo = NULL;
    return true;
  }
  else{
    nuevo->siguiente = primero;
    primero->anterior = nuevo;
    primero = nuevo;
    nuevo = NULL;
    return true;
  }

}

bool 
TListaCom::InsertarI(const TComplejo& com, const TListaPos& der){
  if(der.EsVacia()) return false;

  if(der == this->Primera()){
    return this->InsCabeza(com);
  }
  else{
    TListaPos izq = der.Anterior();
    TListaNodo *medio = new TListaNodo();
    medio->e = com;
    medio->anterior = izq.pos;
    medio->siguiente = der.pos;
    izq.pos->siguiente = medio;
    der.pos->anterior = medio;
    medio = NULL;
    return true;
  }
  return false;
}

bool 
TListaCom::InsertarD(const TComplejo& com, const TListaPos& izq){
  if(izq.EsVacia()) return false;

  TListaNodo *medio = new TListaNodo();
  medio->e = com;
  if(izq == this->Ultima()){
    medio->anterior = izq.pos;
    izq.pos->siguiente = medio;
    ultimo = medio;
    medio = NULL;
    return true;
  }
  else{//se añade en medio de dos
    TListaPos der = izq.Siguiente();
    medio->anterior = izq.pos;
    medio->siguiente = der.pos;
    izq.pos->siguiente = medio;
    der.pos->anterior = medio;
    medio = NULL;
    return true;
  }
  return false;

}

bool 
TListaCom::Borrar(const TComplejo& com){
  for(TListaPos actual=this->Primera(); !actual.EsVacia(); actual=actual.Siguiente()){
    if(this->Obtener(actual) == com){
      return this->Borrar(actual);
    }
  }
  return false;
}

bool 
TListaCom::BorrarTodos(const TComplejo& com){
  bool borrado = false;
  while(this->Borrar(com)){ borrado = true;}
  return borrado;
}

bool 
TListaCom::Borrar(TListaPos& pos){
  if(pos.EsVacia()) return false;//no hay elementos
  if(pos.pos->anterior == NULL && pos.pos->siguiente == NULL){//solo hay un elemento
    delete pos.pos;
    pos.pos = primero = ultimo = NULL;
    return true;
  }
  else if(pos.pos->anterior == NULL && pos.pos->siguiente != NULL){//es el primero
    primero = pos.Siguiente().pos;
    pos.Siguiente().pos->anterior = NULL;
    delete pos.pos;
    pos.pos = NULL;
    return true;
  }
  else if(pos.pos->anterior != NULL && pos.pos->siguiente == NULL){//es el ultimo 
    ultimo = pos.Anterior().pos;
    pos.Anterior().pos->siguiente = NULL;
    delete pos.pos;
    pos.pos = NULL;
    return true;
  }
  else if(pos.pos->anterior != NULL && pos.pos->siguiente != NULL){//esta entre dos
    TListaPos anterior = pos.Anterior();
    TListaPos siguiente = pos.Siguiente();
    anterior.pos->siguiente = siguiente.pos;
    siguiente.pos->anterior = anterior.pos;
    delete pos.pos;
    pos.pos = NULL;
    return true;
  }

  return false;

}

TComplejo 
TListaCom::Obtener(const TListaPos& pos) const{
  TComplejo vacio;
  if(pos.EsVacia()) return vacio;
  return (*(pos.pos)).e;
}

bool 
TListaCom::Buscar(const TComplejo& com) const{
  for(TListaPos actual=this->Primera(); !actual.EsVacia(); actual=actual.Siguiente()){
    if(this->Obtener(actual) == com) return true;
  }
  return false;
}

int 
TListaCom::Longitud() const{
  int lon = 0;
  for(TListaPos actual=this->Primera(); !actual.EsVacia(); actual=actual.Siguiente()){
    lon++;
  }
  return lon;
}

TListaPos 
TListaCom::Primera() const{
  TListaPos pos;
  pos.pos = primero;
  return pos;

}

TListaPos 
TListaCom::Ultima() const{
  TListaPos pos;
  pos.pos = ultimo;
  return pos;
}

ostream& operator<<(ostream& os, TListaCom& lis){
  os << "{";

  for(TListaPos pos = lis.Primera(); !pos.EsVacia(); pos = pos.Siguiente()){
    if(!(pos == lis.Primera())) os << " ";
    os << lis.Obtener(pos);
  }

  os << "}";

  return os;
}
