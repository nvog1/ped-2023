//Nicolás Van Olmen Giménez, 74383864R
#include "tcomplejo.h"
#include <math.h>

using namespace std;

TComplejo::TComplejo(){
  this->re = 0;
  this->im = 0;
}


TComplejo::TComplejo(double real){
  this->re = real;
  this->im = 0;
}


TComplejo::TComplejo(double real, double imaginario){
  re = real;
  im = imaginario;
}


TComplejo::TComplejo(const TComplejo& other){
  re = other.re;
  im = other.im;
}


TComplejo::~TComplejo(){
  re = 0;
  im = 0;
}

TComplejo&
TComplejo::operator=(const TComplejo& other){
  if(this != &other){
    this->~TComplejo();
    this->re = other.re;
    this->im = other.im;
  }

  return *this;
}

TComplejo
TComplejo::operator+(const TComplejo& other) const{
  TComplejo aux(*this);
  aux.re += other.re;
  aux.im += other.im;

  return aux;
}

TComplejo
TComplejo::operator-(const TComplejo& other) const{
  TComplejo aux(*this);
  aux.re -= other.re;
  aux.im -= other.im;

  return aux;
}

TComplejo
TComplejo::operator*(const TComplejo& other) const{
  TComplejo aux(*this);
  aux.re *= other.re;
  aux.im *= other.im;

  return aux;

}

TComplejo
TComplejo::operator+(double real) const{
  TComplejo aux(real);
  aux.re = this->re + aux.re;
  aux.im = this->im + aux.im;

  return aux;
}


TComplejo
TComplejo::operator-(double real) const{
  TComplejo aux(real);
  aux.re = this->re - aux.re;
  aux.im = this->im - aux.im;

  return aux;

}

TComplejo
TComplejo::operator*(double real) const{
  TComplejo aux(real);
  aux.re = this->re * aux.re;
  aux.im = this->im * aux.im;

  return aux;

}

bool
TComplejo::operator==(const TComplejo& other) const{
  if(this == &other || (this->re == other.re && this->im == other.im))
    return true;
  else
    return false;
}

bool
TComplejo::operator!=(const TComplejo& other) const{
  return !((*this) == other);

}

bool
TComplejo::operator<(const TComplejo& other) const{
  if(this->Mod() < other.Mod()) return true;
  else if(this->Mod() > other.Mod()) return false;
  else if(this->Re() < other.Re()) return true;
  else if(this->Re() > other.Re()) return false;
  else return this->Im() < other.Im();
}

bool
TComplejo::operator>(const TComplejo& other) const{
  return !((*this) < other || (*this) == other);

}

double
TComplejo::Re() const{
  return re;
}

double
TComplejo::Im() const{
  return im;
}

void
TComplejo::Re(double real){
  re = real;
}

void
TComplejo::Im(double imaginario){
  im = imaginario;
}

double
TComplejo::Arg() const{
  double aux = 0;  
  aux = atan2(im,re);
  return aux;
}

double
TComplejo::Mod() const{
  double aux = sqrt(pow(re,2)+pow(im,2));
  return aux;
}

TComplejo operator+(double d, const TComplejo& c){
  TComplejo aux(d);
  aux = c + aux;
  return aux;
}

TComplejo operator-(double d, const TComplejo& c){
  TComplejo aux(d);
  aux = aux - c;
  return aux;
}

TComplejo operator*(double d, const TComplejo& c){
  TComplejo aux(d);
  aux = c * aux;
  return aux;
}

ostream& operator<<(ostream& os, const TComplejo& c){
  os << "(" << c.re << " " << c.im << ")";
  return os;
}

