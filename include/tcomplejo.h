//Nicolás Van Olmen Giménez, 74383864R
#ifndef __TComplejoH__
#define __TComplejoH__

#include <iostream>
using namespace std;

class TComplejo {

private:
  double re;
  double im;

public:
  //Forma canónica
  TComplejo();

  TComplejo(double);

  TComplejo(double, double);

  TComplejo(const TComplejo&);

  ~TComplejo();

  TComplejo& operator=(const TComplejo&);

  //Métodos
  TComplejo operator+(const TComplejo&) const;

  TComplejo operator-(const TComplejo&) const;

  TComplejo operator*(const TComplejo&) const;

  TComplejo operator+(double) const;

  TComplejo operator-(double) const;

  TComplejo operator*(double) const;

  bool operator==(const TComplejo&) const;

  bool operator!=(const TComplejo&) const;

  bool operator<(const TComplejo&) const;

  bool operator>(const TComplejo&) const;

  //Getters y Setters
  double Re() const;
  double Im() const;
  void Re(double);
  void Im(double);

  double Arg(void) const;
  double Mod(void) const;

  friend ostream& operator<<(ostream& , const TComplejo&);
  friend TComplejo operator+(double, const TComplejo&);
  friend TComplejo operator-(double, const TComplejo&);
  friend TComplejo operator*(double, const TComplejo&);

};
#endif
