#include "Fecha.h"

Fecha::Fecha(const int &dia,const int &mes,const int &anio)// debe ser con "const int &aux" en  vez de &&
{
    this->setFecha(dia,mes,anio);
}


bool Fecha::bisiesto() const
{
    return (((this->anio%4==0 && this->anio%100!=0) || this->anio%400==0)?(true):(false));
}

void Fecha::setFecha(const int &d,const int &m,const int &a)
{
    int meses[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};

    //A�O

    this->anio = a; //debemos asignar el a�o primero antes de comprobar si es bisiesto
    if(this->bisiesto()) // aqui comprueba si es bisiesto el a�o
    {
        meses[2]=29;
    }

    //MESES

    if(m < 1)          //mes incorrecto
        this->mes = 1;
    else if(m > 12)    //mes incorrecto
        this->mes = 12;
    else this->mes = m;//mes correcto

    //D�AS

    int dia_tope = meses[this->mes]; // comprobamos cuantos d�as tiene el mes

    if(dia_tope < d)           //d�a mayor al l�mite
        this->dia = dia_tope;
    else if(d < 1)             //d�a menor al l�mite
        this->dia = 1;
    else
        this->dia = d;         //d�a correcto
}

void Fecha::ver() const
{
    const char *meses[] = {"", "ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic"};
    cout << (this->getDia() < 10 ? "0" : "") << this->getDia() << " " << meses[this->getMes()] << " " << this->getAnio() << " ";
}

Fecha Fecha::operator++() //++i
{
    int meses[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(this->bisiesto())
        meses[2] = 29;
    int dia_tope = meses[this->mes];

    if (this->dia == dia_tope)
    {
        if(this->mes == 12)
        {
            this->anio++;       //caso : 31 / 12 / YYYY
            this->mes = 1;
        }
        else{
            this->mes++;        //caso : dia_tope / mes<12 / YYYY
        }
        this->dia=1;
    }
    else{
        this->dia++;            //caso : dia<dia_tope / mes<12 / YYYY
    }
    return(*this);              //devuelve una copia del objeto actual, pero ya incrementado
}

Fecha Fecha::operator++(int a) //i++
{
     const Fecha aux(*this);
        this->operator++();
    return aux; //devuelvo el que no est� incrementado
}


Fecha operator+(const int &aux,const Fecha &fecha_aux){ //cout << 2 + fecha

//uso la funci�n amiga porque para sumar dos fechas hacen falta fos par�metros,
// y en un m�todo no se puede sobrecargar con m�s de 1

Fecha x(fecha_aux);
for(int n = 0; n < aux; n++){
    x++;
}
return x;
}

Fecha Fecha::operator+(const int &aux) const // cout << fecha + 2 << endl;
{
    Fecha x(*this);

    for (int n = 0; n < aux; n++) {
    x++;
}
return x;

}

ostream& operator<<(ostream& s, const Fecha &f) {
const char *meses[] = {"", "ene", "feb", "mar", "abr", "may", "jun", "jul", "ago", "sep", "oct", "nov", "dic"};

s << (f.getDia() < 10 ? "0" : "") << f.getDia() << " " << meses[f.getMes()] << " " << f.getAnio();

return s;}
