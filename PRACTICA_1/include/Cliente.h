#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
#include <string.h>
#include "Fecha.h"

class Cliente
{
private:
    long int dni;
    char * nombre;
    Fecha fechacliente;
public:

    Cliente(const long int &d, char* nombre,const Fecha &fcli);
    virtual ~Cliente();

    void setNombre(char* nom);
    inline void setFecha(const Fecha &fechaux)
    {
        this->fechacliente.setFecha(fechaux.getDia(),fechaux.getMes(),fechaux.getAnio());
    }

    inline long int getDni()const
    {
        return (this -> dni);
    }
    inline const char* getNombre()const{
        return this->nombre;
      //el const antes del puntero a char es para que no se pueda hacer strcpy(aux.getNombre(),"otronombre");
   }
    inline Fecha getFecha()const{
        return this->fechacliente;
    }

    bool operator==(const Cliente &aux) const;

};

ostream& operator<<(ostream& s, const Cliente &c);

#endif // CLIENTE_H
