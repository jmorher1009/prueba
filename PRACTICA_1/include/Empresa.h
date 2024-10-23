#ifndef EMPRESA_H
#define EMPRESA_H
#include "Contrato.h"
#include "Cliente.h"
class Empresa
{
    Cliente *clientes[100]; //array est�tico (tama�o 100) de punteros a Clientes
    const int nmaxcli; //constante que indica cu�ntos caben en el array clientes (100)
    int ncli; //para saber cu�ntos clientes hay en el array (al principio 0)
    int ncon; // numero de contratos activos (al principio 0)
    Contrato **contratos; //array din�mico de punteros a contratos
    int nmaxcon; //numero maximo de contratos (no es constante porque se modifica seg�n la tabla se llene)
protected: //m�todos auxiliares usados por los m�todos p�blicos

public:
    //EL CONTRUCTOR DE COPIA Y EL OPERADOR DE ASIGNACION NO LO IMPLEMENTAMOS
    //PORQUE EXPLICITAMENTE SE INDICA EN LA PRACTICA QUE NO SE HAGA
    Empresa();
    int altaCliente(Cliente *c);
    int buscarCliente(long int dni) const;   //si no existe devuelve -1 y si existe
    void crearContrato();
    void cargarDatos();
    virtual ~Empresa();

protected:

private:
};

#endif // EMPRESA_H
