package libClases;

public class ClienteTarifaPlana extends Cliente {
	private static float tarifa = 20.00f;
	private static float limite = 300.00f;
	private float minutosHablados;
	private String nacionalidad;
	
	public ClienteTarifaPlana(String NIF, String nom, Fecha fNac, Fecha fAlta, float minHablados, String nac) {
		super(NIF, nom, fNac, fAlta);
		minutosHablados = minHablados;
		nacionalidad = nac;
	}
	public ClienteTarifaPlana(String NIF, String nom, Fecha fNac, float minHablados, String nac) {
		super(NIF, nom, fNac);
		minutosHablados = minHablados;
		nacionalidad = nac;
	}
	public ClienteTarifaPlana(ClienteTarifaPlana c) {
		super(c.getNif(), c.getNombre(), c.getFechaNac(), c.getFechaAlta());
		minutosHablados = c.minutosHablados;
		nacionalidad = c.nacionalidad;
	}
	public void setMinutos(int m) {
		minutosHablados = m;
	}
	public float getMinutosHablados() {
		return minutosHablados;
	}
	public String getNacionalidad () {
		return nacionalidad;
	}
	public void setNacionalidad(String str) {
		nacionalidad = str;
	}
	public static void setTarifa(float i, float j) {
		limite = i;
		tarifa = j;
	}
	public static float getTarifa() {
		return tarifa;
	}
	public static float getLimite() {
		return limite;
	}
	public float factura() {
		float excLimMin=0.00f;
		if(minutosHablados>limite)
			excLimMin = minutosHablados-limite;
		return (tarifa+excLimMin * 0.15f);
	}
	public String toString() {
		String s = super.toString() + " " + nacionalidad + " [" + limite + " por " + tarifa + "] " + minutosHablados + " --> " + this.factura();
		return s;
	}
	public static void setPrecioTarifa(float f) {
		tarifa = f;
	}
	public Object clone() {
		return new ClienteTarifaPlana(this);
	}
}
