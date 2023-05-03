#include "tvectorcom.h" 
#include "tcomplejo.h"

TVectorCom::TVectorCom(){
  tamano = 0;
  c = NULL;
}

TVectorCom::TVectorCom(int tam){
  if(tam<=0){
    tamano = 0;
    c = NULL;
  }
  else{
    c = new TComplejo[tam];
    tamano = tam;
  }
}

TVectorCom::TVectorCom(TVectorCom& other){
  tamano = other.tamano;
  c = new TComplejo[tamano];
  for(int i=0;i<tamano;i++){
    c[i] = other.c[i];
  }
}

TVectorCom::~TVectorCom(){
  if(c!=NULL) delete [] c;
  c = NULL;
  tamano = 0;
}

TVectorCom& 
TVectorCom::operator=(const TVectorCom& other){
  if(c!=NULL) delete [] c;
  c = NULL;

  if(other.tamano>0){
    tamano = other.tamano;
    c = new TComplejo[tamano];
    for(int i=0;i<tamano;i++){
      c[i] = other.c[i];
    }
  }
  else{
    tamano = 0;
    c = NULL;
  }

  return *this;
}

//METODOS

bool
TVectorCom::operator==(const TVectorCom& other) const{
  if(this == &other) return true;

  
  if(tamano == other.tamano){//si tiene el mismo tamano
  
    if(other.tamano==0){//si esta vacio el otro
    	if(tamano!=0 || c!=NULL) return false;//compruebo que este esté vacío también
    }
    else{// tienen el mismo tamano y algun contenido
		  for(int i=1;i<=tamano;i++){//compruebo que sean iguales
		    if((*this)[i] != other[i]) return false;
		  }
	  }
  }
  else return false;//no tienen el mismo tamano

  return true;
}

bool 
TVectorCom::operator!=(const TVectorCom& other) const{
  return !(*this == other);
}

TComplejo& 
TVectorCom::operator[](int pos){
  if(pos<1 || pos>tamano) {
    TComplejo aux;
    error = aux;
    return error;//que pasa si modifican el TComplejo devuelto, se modifica el error del vector?
  }

  return this->c[pos-1];
}

TComplejo
TVectorCom::operator[](int pos) const{
  if(pos<1 || pos>tamano) {
    TComplejo aux;
    return aux;
  }
  
  return c[pos-1];
}

int
TVectorCom::Tamano() const{
  return tamano;
}

int
TVectorCom::Ocupadas() const{
  int cont=0;
  TComplejo vacio;
  for(int i=1;i<=tamano;i++){
    if((*this)[i] != vacio) cont++;
  }

  return cont;
}

bool
TVectorCom::ExisteCom(const TComplejo& com) const{

  for(int i=1;i<=tamano;i++){
    if((*this)[i] == com) return true;
  }

  return false;
}

void
TVectorCom::MostrarComplejos(double real) const{
	bool primero = true;
	
	cout << "[";
  for(int i=1;i<=tamano;i++){
    if((*this)[i].Re() >= real) {
      if(!primero) cout << ", ";
    	else primero = false;
      cout << (*this)[i];
    }
  }
  cout << "]";

}

bool 
TVectorCom::Redimensionar(int nuevoTam){
  if(nuevoTam<=0 || nuevoTam==tamano) return false;
  if(nuevoTam > tamano){//hacerlo mas grande
    TComplejo *aux = new TComplejo[nuevoTam];
    for(int i=0;i<tamano;i++){
      aux[i] = this->c[i];
    }
    delete [] c;
    c = aux;
    aux = NULL;
    tamano = nuevoTam;
  }
  else{//hacerlo mas pequeño
    TComplejo *aux = new TComplejo[nuevoTam];
    for(int i=0;i<nuevoTam;i++){
      aux[i] = this->c[i];
    }
    delete [] c;
    c = aux;
    aux = NULL;
    tamano = nuevoTam;
  }

  return true;
}

ostream& operator<<(ostream& os, const TVectorCom& vec){
  os << "[";

  for(int i=1;i<=vec.Tamano();i++){
    if(i!=1){
      os << ", ";
    }
    os << "(" << i <<") " << vec[i];
  }

  os << "]";

  return os;
}

