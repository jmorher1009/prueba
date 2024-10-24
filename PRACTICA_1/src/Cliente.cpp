#include "Cliente.h"
#include "Fecha.h"

Cliente::Cliente(const long int &d, char* nombre,const Fecha &fcli):fechacliente(fcli)
{
    this->dni = d;
    this->nombre = new char[strlen(nombre)+1]; // el +1 por el '/0'
    strcpy(this->nombre, nombre);
}

Cliente::~Cliente()
{
    delete [] nombre;
}

void Cliente::setNombre(char* nom)
{

    delete [] this->nombre;
    nombre = new char[strlen(nom) + 1];
    strcpy(this->nombre, nom);

}

/*void Cliente::setFecha(Fecha &&fechaux){
    this->fechacliente.setfecha(fechaux.getDia(),fechaux.getMes(),fechaux.getAnio());
}


long int Cliente::getDni(){}

char* Cliente::getNombre(){}

Fecha Cliente::getFecha(){}

*/
bool Cliente::operator==(const Cliente &aux)const
{

    bool esigual = false;

    if(strcmp (this->nombre,aux.nombre)==0)
    {
        if(this->dni == aux.dni)
        {
            if(fechacliente.getAnio()==aux.fechacliente.getAnio())
            {
                if(fechacliente.getMes()==aux.fechacliente.getMes())
                {
                    if(fechacliente.getDia()==aux.fechacliente.getDia())
                    {
                        esigual = true;
                    }
                }
            }
        }
    }
    return esigual;
}

ostream& operator<<(ostream& s,const Cliente &c)
{

    Fecha fechaux(1,1,1);
    fechaux = c.getFecha();
    s << c.getNombre() << " (" << c.getDni() << " - " << fechaux.getDia() << " " << fechaux.getMes() << " " << fechaux.getAnio() <<")\n";

    return s;
}





