#include "ContratoTP.h"

int ContratoTP::minutosTP=300;
float ContratoTP::precioTP=10;
const float ContratoTP::precioExcesoMinutos=0.15;


//static se pone en el .h (no se pone en el .cpp)
void ContratoTP::setTarifaPlana(int m, float p) {
  ContratoTP::minutosTP=m; //puedo poner minutosTP=m ...pongo ContratoTP::minutosTP para recordar que es estatico
  ContratoTP::precioTP=p;  //puedo poner precioTP=p  ...pongo ContratoTP::precioTP para recordar que es estatico
}

//RESTO DE METODOS Y FUNCIONES A RELLENAR POR EL ALUMNO...

ContratoTP::ContratoTP(long int dni, Fecha f, int m):Contrato(dni, f){ //debemos ver cuales son los atributos de la clase padre

    this->minutosHablados = m;

}

ContratoTP::ContratoTP(const ContratoTP &aux):Contrato(aux.getDniContrato(),aux.getFechaContrato()){ //HACE FALTA PARA INCREMENTAR LA VARIABLE ESTÁTICA
    this->minutosHablados = aux.getMinutosHablados();
}

void ContratoTP::ver() const{
    Contrato::ver();
    cout <<" "<< this->minutosHablados << "m, " << minutosTP << " (" << precioTP << ") - " << this->factura() << "€ \n";
}

float ContratoTP::factura()const{
    if(minutosHablados > minutosTP){
        return (ContratoTP::precioTP + ContratoTP::precioExcesoMinutos * (minutosHablados - ContratoTP::minutosTP));
    }
    else
        return ContratoTP::precioTP;
}


ostream& operator<<(ostream&s, const ContratoTP &c)
{

    s<< c.getDniContrato() << " (" << c.getIdContrato() << " - " << c.getFechaContrato() << ")"
    << c.getMinutosHablados() << " min, " << c.getLimiteMinutos() << "(" << c.getPrecio() << ") - " << c.factura() << " € " <<"\n";
    return s;

}
