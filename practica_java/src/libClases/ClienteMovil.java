package libClases;

public class ClienteMovil extends Cliente {

    private float precioMinuto;
    private float minutosHablados;
    private Fecha Permanencia;

    public ClienteMovil(String NIF, String nom, Fecha fNac, Fecha fAlta, Fecha perm, float minHablados, float precioMin) {
        super(NIF, nom, fNac, fAlta);
        precioMinuto = precioMin;
        minutosHablados = minHablados;
        Permanencia = (Fecha) perm.clone(); // Otra forma -> Permanencia = new Fecha(perm);
    }

   public ClienteMovil(String NIF, String nom, Fecha fNac, float minHablados, float precioMin) {
		super(NIF, nom, fNac);
		precioMinuto = precioMin;
		minutosHablados = minHablados;
		Permanencia = new Fecha(getFechaAlta().getDia(), getFechaAlta().getMes(), getFechaAlta().getAnio()+1);
	}

}
