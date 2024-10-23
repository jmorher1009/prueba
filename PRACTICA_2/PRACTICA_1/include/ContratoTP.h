#ifndef CONTRATOTP_H
#define CONTRATOTP_H

#include <iostream> //cin, cout
#include "Fecha.h"
#include "Contrato.h"

using namespace std;

class ContratoTP: public Contrato {
  static int minutosTP;
  static float precioTP;
  int minutosHablados;
  static const float precioExcesoMinutos;

public:
  ContratoTP(long int dni, Fecha f, int m);
  //virtual ~ContratoTP(); //¿es necesario? pensar y reflexionad
  ContratoTP(const ContratoTP& aux);  //¿es necesario? pensar y reflexionad
  //ContratoTP& operator=(const ContratoTP& c); //¿es necesario? pensar y reflexionad

  //Todo metodo que pueda ser constante lo hacemos constante para que los objetos constantes puedan usarlos
  int getMinutosHablados()const {return minutosHablados;}
  void setMinutosHablados(const int &m){this->minutosHablados = m;}
  static int getLimiteMinutos() { return ContratoTP::minutosTP; }
  static float getPrecio() { return ContratoTP::precioTP; }
  static void setTarifaPlana(int m, float p); //el el .cpp se pone la cabecera sin la palabra static

  //A RELLENAR POR EL ALUMNO...
    void ver() const;
    float factura()const;
};

ostream& operator<<(ostream &s, const ContratoTP &c);

#endif // CONTRATOTP_H
