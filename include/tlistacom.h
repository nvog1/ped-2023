#ifndef H_TLISTACOM_H 
#define H_TLISTACOM_H

#include <iostream>
#include "tcomplejo.h"
using namespace std;

class TListaNodo {

friend class TListaPos;
friend class TListaCom;

private:
  TComplejo e;
  TListaNodo *anterior;
  TListaNodo *siguiente;

public:  
  TListaNodo();
  TListaNodo(const TListaNodo&);
  ~TListaNodo();
  TListaNodo& operator=(const TListaNodo&);
  bool operator==(const TListaNodo&) const;
  bool operator!=(const TListaNodo&) const;

};

class TListaPos {

friend class TListaCom;

private:
  TListaNodo *pos;

public:
  TListaPos();
  TListaPos(const TListaPos&);
  ~TListaPos();
  TListaPos& operator=(const TListaPos&);

  bool operator==(const TListaPos&) const;
  bool operator!=(const TListaPos&) const;
  TListaPos Anterior() const;
  TListaPos Siguiente() const;
  bool EsVacia() const;

};

class TListaCom {
private:
  TListaNodo *primero;
  TListaNodo *ultimo;

  TListaCom& Copiar(const TListaCom&);
  TListaCom& LiberarMemoria();

public:
  TListaCom();
  TListaCom(const TListaCom&);
  ~TListaCom();
  TListaCom& operator=(const TListaCom&);

  bool operator==(const TListaCom&) const;
  bool operator!=(const TListaCom&) const;
  TListaCom operator+(const TListaCom&) const;
  TListaCom operator-(const TListaCom&) const;
  bool EsVacia() const;
  bool InsCabeza(const TComplejo&);
  bool InsertarI(const TComplejo&, const TListaPos&);
  bool InsertarD(const TComplejo&, const TListaPos&);
  bool Borrar(const TComplejo&);
  bool BorrarTodos(const TComplejo&);
  bool Borrar(TListaPos&);
  TComplejo Obtener(const TListaPos&) const;
  bool Buscar(const TComplejo&) const;
  int Longitud() const;
  TListaPos Primera() const;
  TListaPos Ultima() const;

  friend ostream& operator<<(ostream&, TListaCom&);

};

#endif
