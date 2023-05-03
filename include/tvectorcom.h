//Nicolás Van Olmen Giménez, 74383864R
#ifndef __TVectorH__
#define __TVectorH__

#include <iostream>
using namespace std;

#include "tcomplejo.h"

class TVectorCom {

private:
  TComplejo *c;
  int tamano;
  TComplejo error;

public:
  TVectorCom();

  TVectorCom(int);

  TVectorCom(TVectorCom&);

  ~TVectorCom();

  TVectorCom& operator=(const TVectorCom&);

//METODOS

  bool
  operator==(const TVectorCom&) const;

  bool 
  operator!=(const TVectorCom&) const;

  TComplejo& 
  operator[](int);

  TComplejo
  operator[](int) const;

  int
  Tamano() const;

  int
  Ocupadas() const;

  bool
  ExisteCom(const TComplejo&) const;

  void
  MostrarComplejos(double) const;

  bool Redimensionar(int);

  friend ostream& operator<<(ostream&, const TVectorCom&);


};

#endif
