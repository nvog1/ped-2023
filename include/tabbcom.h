#ifndef TABB_COM_H
#define TABB_COM_H

#include <iostream>
#include "tcomplejo.h"
#include "tvectorcom.h"

class TNodoABB;

class TABBCom{

private:
  TNodoABB *nodo;

  void InordenAux(TVectorCom& , int&) const;
  void PreordenAux(TVectorCom& , int&) const;
  void PostordenAux(TVectorCom& , int&) const;
  
public:

  TABBCom();

  TABBCom(const TABBCom&);

  ~TABBCom();

  TABBCom&
  operator=(const TABBCom&);

  bool
  operator==(const TABBCom&) const;

  bool
  EsVacio() const;

  bool 
  Insertar(const TComplejo&);

  bool
  Borrar(const TComplejo &);

  bool
  Buscar(const TComplejo &) const;

  TComplejo
  Raiz() const;

  int
  Altura() const;

  int
  Nodos() const;

  int
  NodosHoja() const;

  TVectorCom
  Inorden() const;

  TVectorCom
  Preorden() const;

  TVectorCom
  Postorden() const;

  TVectorCom
  Niveles() const;
   
  friend ostream&
  operator<<(ostream& os, const TABBCom&);

};

class TNodoABB{

friend class TABBCom;
private:
  TComplejo item, error;
  TABBCom iz, de;

public:

  TNodoABB();

  TNodoABB(const TNodoABB&);

  ~TNodoABB();

  TNodoABB&
  operator=(const TNodoABB&);

};
#endif
