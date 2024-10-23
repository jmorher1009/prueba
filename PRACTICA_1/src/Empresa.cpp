
#include "Empresa.h"
#include "Contrato.h"
//el constructor de la clase empresa debe crear un array dinámico de tamaño inicial 10
//debe inicializar a 0 los contadores de clientes (ncli) y contratos (ncon)
//y debe inicializar la constante nmaxcli a 100 y la variable nmaxcon a 10
Empresa::Empresa():nmaxcli(100)
{
    this->ncli=0;
    this->ncon=0;
    this->contratos=new Contrato *[10]; //inicialmente capacidad para 10 Contratos
    this->nmaxcon=10;
}
//el destructor debe, además de eliminar el array dinámico creado en el constructor,
//eliminar los objetos clientes y contratos apuntados por ambos arrays
Empresa::~Empresa()
{
    for(int i=0; i<this->ncon; i++)   //primero elimino los objetos contratos
    {
        delete this->contratos[i];
    }
    delete [] this->contratos; //luego elimino el array de punteros
    for(int i=0; i<this->ncli; i++)   //primero elimino los objetos contratos
    {
        delete this->clientes[i];
    }
//delete [] this->clientes; //ERROR el array clientes no es dinámico
}
//método auxiliar usado por el método crearContrato
int Empresa::altaCliente(Cliente *c)   //añade cliente apuntado por c al array clientes
{
    int pos=-1; //devuelve -1 si no cabe y la posición donde
    if (this->ncli<nmaxcli)   //donde lo he metido si cabe
    {
        this->clientes[this->ncli]=c;
        pos=this->ncli;
        this->ncli++;
    }
    else
    {
        cout << "Lo siento, el cupo de clientes esta lleno";
        pos=-1;
    }
    return pos;
}
//método auxiliar usado por el método crearContrato
int Empresa::buscarCliente(long int dni) const   //si no existe devuelve -1 y si existe
{
//devuelve la posición del cliente
//A IMPLEMENTAR POR EL ALUMNO... //con ese dni en el array clientes
    int existe = -1;
    int i=0;
    while(i < ncli && existe ==-1)
    {
        if (clientes[i]->getDni() == dni)
            existe = clientes[i]->getDni();
        else i++;
    }
    return existe;
}
void Empresa::crearContrato()   //EL ALUMNO DEBE TERMINAR DE IMPLEMENTAR ESTE METODO
{
    long int dni;
    int pos;
    cout << "Introduce DNI: ";
    cin >> dni;
//supongo que hay un metodo buscarCliente(dni) que devuelve -1 si no existe y si
//existe devuelve la posicion del cliente en el array this->cli
    pos=this->buscarCliente(dni); //OJO ESTE METODO HAY QUE IMPLEMENTARLO
    if (pos==-1)   //el cliente no existe y hay que darlo de alta
    {
        int dia, mes, anio;
        char nombre[100];
        Cliente *c; //NO CREO NINGUN CLIENTE SINO SOLO UN PUNTERO A CLIENTE
        cout << "Introduce Nombre: ";
        cin >> nombre;
        cout << "Introduce Fecha (dd mm aaaa): ";
        cin >> dia >> mes >> anio;
        c=new Cliente(dni, nombre, Fecha(dia, mes, anio));
        pos=this->altaCliente(c); //OJO HAY QUE IMPLEMENTARLO
    }
//viendo cuanto vale la variable pos sé si el cliente se ha dado de alta o no
    if (pos!=-1)   //el cliente existe o se ha dado de alta
    {
//PREGUNTAR QUE TIPO DE CONTRATO QUIERE Y LOS DATOS NECESARIOS
//CREAR EL OBJETO CONTRATO CORRESPONDIENTE Y AÑADIR AL ARRAY
//contratos UN PUNTERO A DICHO OBJETO
    }
}

void Empresa::cargarDatos()
{
    Fecha f1(29,2,2001), f2(31,1,2002), f3(1,2,2002);
    this->clientes[0] = new Cliente(75547001, "Peter Lee", f1);
    this->clientes[1] = new Cliente(45999000, "Juan Perez", Fecha(29,2,2000));
    this->clientes[2] = new Cliente(37000017, "Luis Bono", f2);
    this->ncli=3;
    this->contratos[0] = new ContratoMovil(75547001, f1, 0.12, 110, "DANES"); //habla 110m a 0.12€/m
    this->contratos[1] = new ContratoMovil(75547001, f2, 0.09, 170, "DANES"); //habla 170m a 0.09€/m
    this->contratos[2] = new ContratoTP(37000017, f3, 250); //habla 250m (300m a 10€, exceso 0.15€/m)
    this->contratos[3] = new ContratoTP(75547001, f1, 312); //habla 312m (300m a 10€, exceso 0.15€/m)
    this->contratos[4] = new ContratoMovil(45999000, f2, 0.10, 202, "ESPAÑOL"); //habla 202m a 0.10/m
    this->contratos[5] = new ContratoMovil(75547001, f2, 0.15, 80, "DANES"); //habla 80m a 0.15€/m
    this->contratos[6] = new ContratoTP(45999000, f3, 400); //habla 400m (300m a 10€, exceso 0.15€/m)
    this->ncon=7;
