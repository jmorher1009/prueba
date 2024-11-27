package libClases;

public class Cliente implements Cloneable, Proceso {
	private final String nif; // final == constante
	private final int codCliente; //codigo único (y fijo) generado por la aplicación
	private String nombre; //nombre completo del cliente (SI se puede modificar) 
	private final Fecha fechaNac; //fecha nacimiento del cliente (NO se puede cambiar)
	private final Fecha fechaAlta;  //fecha de alta del cliente (SI se puede modificar)
	private static int cuenta=0;
	private static Fecha fech = new Fecha(1,1,2018);
	//constructores
	public Cliente (String NIF, String nom, Fecha fNac, Fecha fAlta) { 
		
		nif=NIF;
		nombre=nom;
		fechaNac=fNac;
		fechaAlta= new Fecha(fAlta);
		cuenta++;
		codCliente=cuenta;
	}
	public Cliente (String NIF, String nom, Fecha fNac) { 
		
		nif=NIF;
		nombre=nom;
		fechaNac=fNac;
		fechaAlta=fech;
		cuenta++;
		codCliente=cuenta;
	}
	public Cliente (Cliente c) {
		nif=c.nif;
		nombre=c.nombre;
		fechaNac=c.fechaNac;
		fechaAlta= new Fecha(c.fechaAlta);
		cuenta++;
		codCliente=cuenta;
	}
	
	public String toString() {
		String str = nif + " " + fechaNac.toString() + ": " + nombre + " (" + codCliente + " - " + fechaAlta.toString() + ")";
		return str;
	}
	public String getNombre() {
		return nombre;
	}
	public void setNombre(String nom) {
		nombre = nom;
	}
	public Fecha getFechaAlta() {
		return new Fecha(fechaAlta);
	}
	public void setFechaAlta(Fecha fAlta) {
		fechaAlta.setFecha(fAlta.getDia(), fAlta.getMes(), fAlta.getAnio());
	}
	public void ver() {
		System.out.println(this);
	}
	public static String getFechaPorDefecto() {
		return fech.toString();
	}
	public static void setFechaPorDefecto(Fecha f) {
		fech.setFecha(f.getDia(), f.getMes(), f.getAnio());
	}
	public Object clone() {
		return new Cliente(this);
	}
	public Fecha getFechaNac() {
		return new Fecha(fechaNac);
	}
	public String getNif() {
		return nif;
	}
	
	
	public boolean equals(Object c) {
		if(nif==((Cliente)c).nif && this.getClass()==c.getClass())
			return true;
		else
			return false;
	}
	public int getCodCliente() {
		return codCliente;
	}
}