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
        Permanencia = new Fecha(getFechaAlta().getDia(), getFechaAlta().getMes(), getFechaAlta().getAnio() + 1);
    }

    public ClienteMovil(ClienteMovil c) {
        super(c.getNif(), c.getNombre(), c.getFechaNac(), c.getFechaAlta());
        this.Permanencia = new Fecha(c.Permanencia);
        this.precioMinuto = c.precioMinuto;
        this.minutosHablados = c.minutosHablados;
    }

    public Object clone() {
        return new ClienteMovil(this);
    }

    public void setFPermanencia(Fecha f1) {
        Permanencia = new Fecha(f1);
    }

    public float factura() {
        return precioMinuto * minutosHablados;
    }

    public Fecha getFPermanencia() {
        return new Fecha(Permanencia);
    }

    public float getPrecioMinuto() {

        return precioMinuto;
    
    }

    void setPrecioMinuto(float aux) {
        
        this.precioMinuto = aux;
        
    }
}
