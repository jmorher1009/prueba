
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
    bool encontrado = false;
    int i = 0;
    while(i<ncli && !encontrado)
    {
        if(clientes[i]->getDni() == dni)
        {
            encontrado = true;
        }
        else
        {
            i++;
        }
    }
    if(!encontrado){
        i=-1;
        }
return i;
}

/*void Empresa::crearContrato()   //EL ALUMNO DEBE TERMINAR DE IMPLEMENTAR ESTE METODO
{
    long int dni;
    int pos;
    int dia, mes, anio;
    int m;
    int contr = 0;
    Fecha f(0,0,0);
    cout << "\nIntroduzca dni DNI: ";
    cin >> dni;
//supongo que hay un metodo buscarCliente(dni) que devuelve -1 si no existe y si
//existe devuelve la posicion del cliente en el array this->cli
    pos=this->buscarCliente(dni); //OJO ESTE METODO HAY QUE IMPLEMENTARLO
    if (pos==-1)   //el cliente no existe y hay que darlo de alta
    {

        char nombre[100];
        Cliente *c; //NO CREO NINGUN CLIENTE SINO SOLO UN PUNTERO A CLIENTE
        f.setFecha(dia,mes,anio);
        c=new Cliente(dni, nombre, f);
        pos=this->altaCliente(c); //OJO HAY QUE IMPLEMENTARLO
    }
//viendo cuanto vale la variable pos sé si el cliente se ha dado de alta o no
    if (pos!=-1)   //el cliente existe o se ha dado de alta
    {
        //PREGUNTAR QUE TIPO DE CONTRATO QUIERE Y LOS DATOS NECESARIOS
        //CREAR EL OBJETO CONTRATO CORRESPONDIENTE Y AÑADIR AL ARRAY
        //contratos UN PUNTERO A DICHO OBJETO
        contr = 0;
        cout << "Tipo de Contrato a abrir (1-Tarifa Plana, 2-Movil): ";
        cin >> contr;

        while(contr != 1 && contr != 2)
        {
            if(contr != 1 && contr != 2)
            {
                cout << "\Introduzca un valor correcto\n";
                cin >> contr;
            }
        }

        if(contr == 1) //ContratoTP
        {
            cout << "Fecha del contrato\n";
            cout << "dia: ";
            cin >> dia;
            cout << "mes: ";
            cin >> mes;
            cout << "anio: ";
            cin >> anio;
            cout << "minutos hablados: ";
            cin >> m;
            ContratoTP(dni,f,m);
        }
        else if(contr == 2) //ContratoMovil
        {
            int m;
            float p;
            char nac[30];
            cout << "Fecha del contrato\n";
            cout << "dia: ";
            cin >> dia;
            cout << "mes: ";
            cin >> mes;
            cout << "anio: ";
            cin >> anio;
            cout << "minutos hablados: ";
            cin >> m;
            cout << "Precio minuto: ";
            cin >> p;
            cout << "Nacionalidad: ";
            cin >> nac;
            ContratoMovil(dni,f,p,m,nac);
        }
    }
}
*/
int Empresa::altaContrato(Contrato *c)
{
    if(this->ncon == nmaxcon)
    {
        Contrato **aux;
        aux=contratos;
        contratos= new Contrato*[nmaxcon*2];
        for(int i=0; i<nmaxcon; i++)
        {
            contratos[i]=aux[i];
        }
        delete [] aux;
        nmaxcon=nmaxcon*2;

    }
    contratos[ncon]=c;
    ncon++;
    return ncon-1;
}

void Empresa::crearContrato()
{

    long int dni;
    int pos;
    int tipoContrato;
    int dia, mes, anio;
    int minutos;
    float precio;
    char nacionalidad[30];
    cout << "Introduce el DNI: ";
    cin >> dni;
    pos=buscarCliente(dni);
    if(pos==-1)
    {
        int dia, mes, anio;
        char nombre[100];
        Cliente *c; //Puntero a cliente
        cout << "Introduce el nombre: ";
        cin.ignore();
        cin.getline(nombre,50);
        cout << "dia: ";
        cin >> dia;
        cout << "mes: ";
        cin >> mes;
        cout << "año: ";
        cin >> anio;

        c = new Cliente(dni, nombre, Fecha(dia,mes,anio));
        pos=altaCliente(c);
        if(pos==-1)
        {
            cout<<"\nLa empresa no admite mas clientes \n";
            delete c;
        }
    }

    Contrato * contr;
    if(pos!=-1)
    {
        cout << "Tipo de Contrato (1-Tarifa Plana, 2-Movil): ";
        cin >> tipoContrato;
        while(tipoContrato!=1 && tipoContrato!=2)
        {
            cout << "\nIntroduce un tipo correcto (1-Tarifa Plana, 2-Movil): ";
            cin >> tipoContrato;
        }
        if(tipoContrato==1)
        {
            cout<< "Fecha del contrato \n";
            cout << "dia: ";
            cin >> dia;
            cout << "mes: ";
            cin >> mes;
            cout << "año: ";
            cin >> anio;
            cout << "Minutos hablados: ";
            cin >> minutos;
            cout << "\n";
            contr = new ContratoTP(dni,Fecha(dia,mes,anio), minutos);

        }
        else if(tipoContrato==2)
        {
            cout<< "Fecha del contrato \n";
            cout << "dia: ";
            cin >> dia;
            cout << "mes: ";
            cin >> mes;
            cout << "año: ";
            cin >> anio;
            cout << "Minutos hablados: ";
            cin >> minutos;
            cout << "Precio minuto: ";
            cin>> precio;
            cout << "Nacionalidad: ";
            cin>> nacionalidad;
            cout << "\n";
            cin.ignore();
            contr=new ContratoMovil(dni, Fecha(dia,mes,anio), precio, minutos, nacionalidad);

        }
        altaContrato(contr);
    }

}
void Empresa::cargarDatos()
{
    Fecha f1(29,2,2001), f2(31,1,2002), f3(1,2,2002);
    this->clientes[0] = new Cliente(75547001, (char *)"Peter Lee", f1);
    this->clientes[1] = new Cliente(45999000, (char *)"Juan Perez", Fecha(29,2,2000));
    this->clientes[2] = new Cliente(37000017, (char *)"Luis Bono", f2);
    this->ncli=3;
    this->contratos[0] = new ContratoMovil(75547001, f1, 0.12, 110, (char *)"DANES"); //habla 110m a 0.12€/m
    this->contratos[1] = new ContratoMovil(75547001, f2, 0.09, 170, (char *)"DANES"); //habla 170m a 0.09€/m
    this->contratos[2] = new ContratoTP(37000017, f3, 250); //habla 250m (300m a 10€, exceso 0.15€/m)
    this->contratos[3] = new ContratoTP(75547001, f1, 312); //habla 312m (300m a 10€, exceso 0.15€/m)
    this->contratos[4] = new ContratoMovil(45999000, f2, 0.10, 202, (char *)"ESPAÑOL"); //habla 202m a 0.10/m
    this->contratos[5] = new ContratoMovil(75547001, f2, 0.15, 80, (char *)"DANES"); //habla 80m a 0.15€/m
    this->contratos[6] = new ContratoTP(45999000, f3, 400); //habla 400m (300m a 10€, exceso 0.15€/m)
    this->ncon=7;
}

void Empresa::ver()const
{

    cout << "\nLa empresa tiene " << this->ncli << " clientes y " << this->ncon << " contratos\n";
    cout << "Clientes:\n";
    for(int i=0; i<ncli; i++)
    {
        cout << *clientes[i];
    }
    cout << "\nContratos:\n";
    for(int i=0; i<ncon; i++)
    {
        contratos[i]->ver();
    }
}

int Empresa::nContratosTP() const
{
    int n = 0;
    for(int i=0; i<ncon; i++)
    {
        if(typeid(*contratos[i])==typeid(ContratoTP))
            n++;
    }
    return n;
}



bool Empresa::cancelarContrato(int idContrato){
    bool encontrado = false;
    int i = 0;
    while(!encontrado && i < this->ncon){
        if(contratos[i]->getIdContrato() == idContrato)
        {
            encontrado = true;
            //se procede a eliminar el contraro
            for(int j=i; j<ncon-1; j++)
            {
                contratos[j]=contratos[j+1];
            }
            ncon--;
        }
        else{
            i++;
        }
    }
    return encontrado;
}

bool Empresa::bajaCliente(long int dni) {
bool eliminado = false;
    int pos = buscarCliente(dni);
    if(pos!=-1)
    {
        for(int i=ncon; i>=0; i--)
        {
            if(contratos[i]->getDniContrato()==dni)
            {
                cancelarContrato(contratos[i]->getIdContrato());
            }
        }
                delete clientes[pos];
        for(int i=pos; i<ncli-1; i++)
        {
            clientes[i]=clientes[i+1];
        }
        ncli--;
        eliminado = true;
    }
    return eliminado;
}

int Empresa::descuento(float porcentaje) const{

    porcentaje= 1-porcentaje/100;
    for(int i=0; i<ncon;i++){
        if(ContratoMovil *aux = dynamic_cast<ContratoMovil*>(contratos[i]))
        {
            aux->setPrecioMinuto(aux->getPrecioMinuto()*porcentaje);
        }
    }
}

