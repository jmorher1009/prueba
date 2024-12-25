package libClases;

import java.util.Scanner;

public class Empresa implements Cloneable {

    private Cliente clientes[];
    private int nCli;
    private int nMaxCli;

    public Empresa() {
        nCli = 0;
        nMaxCli = 10;
        clientes = new Cliente[nMaxCli];
    }

    public Empresa(Empresa e) {
        nCli = e.nCli;
        nMaxCli = e.nMaxCli;
        clientes = new Cliente[e.nMaxCli];
        for (int i = 0; i < nCli; i++) {
            clientes[i] = e.clientes[i];
        }
    }

    public int existe(String NIF) {
        boolean esta = false;
        int i;
        for (i = 0; i < nCli && esta == false; i++) {
            if (clientes[i].getNif().equals(NIF)) {
                esta = true;
            }
        }
        if (esta == true) {
            return i - 1;
        } else {
            return -1;
        }
    }

    public void alta(Cliente c) {
        if (existe(c.getNif()) == -1) {
            if (nCli != nMaxCli) {
                nCli++;
                clientes[nCli - 1] = c;
            } else {
                Cliente aux[] = clientes;
                nMaxCli += 10;
                clientes = new Cliente[nMaxCli];
                for (int i = 0; i < nCli; i++) {
                    clientes[i] = aux[i];
                }
                nCli++;
                clientes[nCli - 1] = c;
            }
        }
    }

    public void alta() {
        Scanner sc = new Scanner(System.in); //warning por no cerrarlo pero funciona
        System.out.print("DNI: ");
        String NIF = sc.nextLine();
        if (existe(NIF) != -1) {
            System.out.println("Ya existe un Cliente con ese dni:\n" + clientes[existe(NIF)].toString() + "\n");
        } else {
            System.out.print("Nombre: ");
            String nom = sc.nextLine();
            System.out.println("Fecha Nacimiento:");
            Fecha fNac = Fecha.pedirFecha();
            System.out.println("Fecha de Alta:");
            Fecha fAlta = Fecha.pedirFecha();
            System.out.print("Minutos que habla al mes: ");
            float minHablados = sc.nextFloat();
            int tipo;
            do {
                System.out.print("Indique tipo de cliente (1-Movil, 2-Tarifa Plana): ");
                tipo = sc.nextInt();
            } while (tipo != 1 && tipo != 2);
            if (tipo == 1) {
                System.out.print("Precio por minuto: ");
                float precioMin = sc.nextFloat();
                System.out.println("Fecha fin permanencia:");
                Fecha perm = Fecha.pedirFecha();
                if (nCli != nMaxCli) {
                    nCli++;
                    clientes[nCli - 1] = new ClienteMovil(NIF, nom, fNac, fAlta, perm, minHablados, precioMin);
                } else {
                    Cliente aux[] = clientes;
                    nMaxCli += 10;
                    clientes = new Cliente[nMaxCli];
                    for (int i = 0; i < nCli; i++) {
                        clientes[i] = aux[i];
                    }
                    nCli++;
                    clientes[nCli - 1] = new ClienteMovil(NIF, nom, fNac, fAlta, perm, minHablados, precioMin);
                }
            } else {
                sc.nextLine();
                System.out.println("Nacionalidad: ");
                String nac = sc.nextLine();
                if (nCli != nMaxCli) {
                    nCli++;
                    clientes[nCli - 1] = new ClienteTarifaPlana(NIF, nom, fNac, fAlta, minHablados, nac);
                } else {
                    Cliente aux[] = clientes;
                    nMaxCli += 10;
                    clientes = new Cliente[nMaxCli];
                    for (int i = 0; i < nCli; i++) {
                        clientes[i] = aux[i];
                    }
                    nCli++;
                    clientes[nCli - 1] = new ClienteTarifaPlana(NIF, nom, fNac, fAlta, minHablados, nac);
                }
            }
        }
    }

    public void baja(String NIF) {
        int indice = existe(NIF);
        if (indice != -1) {
            int i = indice + 1;
            while (i < nCli) {
                clientes[i - 1] = clientes[i];
                i++;
            }
            clientes[nCli - 1] = null;
            nCli--;
        }
    }

    public void baja() {
        Scanner sc = new Scanner(System.in); //warning por no cerrarlo pero funciona
        System.out.print("Introduzca nif cliente a dar de baja: ");
        String NIF = sc.next();
        if (existe(NIF) == -1) {
            System.out.println("No existe el Cliente");
        } else {
            System.out.println(clientes[existe(NIF)].toString());
            char e;
            do {
                System.out.print("Seguro que desea eliminarlo (s/n)? ");
                e = sc.next().charAt(0);
            } while (e != 's' && e != 'S' && e != 'n' && e != 'N');
            if (e == 'n' || e == 'N') {
                System.out.println("El cliente con nif " + NIF + " no se elimina\n");
            } else {
                String nom = clientes[existe(NIF)].getNombre();
                for (int i = existe(NIF) + 1; i < nCli; i++) {
                    clientes[i - 1] = clientes[i];
                }
                clientes[nCli - 1] = null;
                nCli--;
                System.out.println("El cliente " + nom + " con nif " + NIF + " ha sido elimado\n");
            }
        }
    }

    public String toString() {
        String str = clientes[0].toString() + "\n";
        for (int i = 1; i < nCli; i++) {
            str += clientes[i].toString() + "\n";
        }
        return str;
    }

    public float factura() {
        float f = 0.00f;
        for (int i = 0; i < nCli; i++) {
            if (clientes[i] instanceof ClienteMovil) {
                f += ((ClienteMovil) clientes[i]).factura();
            } else {
                f += ((ClienteTarifaPlana) clientes[i]).factura();
            }
        }
        return f;
    }

    public void descuento(int dto) {
        for (int i = 0; i < nCli; i++) {
            if (clientes[i] instanceof ClienteMovil) {
                ((ClienteMovil) clientes[i]).setPrecioMinuto(((ClienteMovil) clientes[i]).getPrecioMinuto() * (1.00f - ((float) dto / 100.00f)));
            }
        }
    }

    public int nClienteMovil() {
        int n = 0;
        for (int i = 0; i < nCli; i++) {
            if (clientes[i] instanceof ClienteMovil) {
                n++;
            }
        }
        return n;
    }

    public Object clone() {
        return new Empresa(this);
    }

    public int getN() {
        return nCli;
    }
}
