package libClases;

public class ClienteMovil extends Cliente{
	
	private float precioMinuto;
	private float minutosHablados;
	private Fecha Permanencia;
	
	public ClienteMovil(String NIF, String nom, Fecha fNac, Fecha fAlta, Fecha perm, float minHablados, float precioMin) {
		super(NIF, nom, fNac, fAlta);
		precioMinuto = precioMin;
		minutosHablados = minHablados;
		Permanencia = new Fecha(perm);
	}
	
	public ClienteMovil(String NIF, String nom, Fecha fNac, float minHablados, float precioMin) {
		super(NIF, nom, fNac);
		precioMinuto = precioMin;
		minutosHablados = minHablados;
		Permanencia = new Fecha(getFechaAlta().getDia(), getFechaAlta().getMes(), getFechaAlta().getAnio()+1);
	}
	public ClienteMovil(ClienteMovil c) {
		super(c.getNif(), c.getNombre(), c.getFechaNac(), c.getFechaAlta());
		precioMinuto = c.precioMinuto;
		minutosHablados = c.minutosHablados;
		Permanencia = new Fecha(c.Permanencia);
	}
	public void setFPermanencia(Fecha f1) {
		Permanencia = new Fecha(f1);
	}
	public Fecha getFPermanencia() {
		return new Fecha(Permanencia);
	}
	public Object clone() {
		return new ClienteMovil(this);
	}
	public String toString() {
		String str = super.toString() + " " + Permanencia + " " + minutosHablados + " x " + precioMinuto + " --> " + factura();
		return str;
	}
	public float factura() {
		return precioMinuto * minutosHablados;
	}
	public float getPrecioMinuto() {
		return precioMinuto;
	}
	public float getMinutosHablados() {
		return minutosHablados;
	}
	public void setMinutosHablados(float minHablados) {
		minutosHablados = minHablados;
	}
	public void setPrecioMinuto(float precioMin) {
		precioMinuto = precioMin;
	}
}

