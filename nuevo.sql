SET SERVEROUTPUT ON;
CREATE OR REPLACE FUNCTION facturacion(telefono IN LLAMADA.tf_origen%TYPE, año IN INTEGER) RETURN NUMBER IS
    noExisteTelefono EXCEPTION;
    facturaInferior EXCEPTION;
    duracionTotal INTEGER := 0;
    costeMinuto TARIFA.coste%TYPE := 0;
    facturacion NUMBER(4,2) := -1;
    numero INTEGER;
BEGIN
    SELECT COUNT(*)
    INTO numero
    FROM TELEFONO
    WHERE TELEFONO.numero = telefono;

    IF numero <= 0 THEN 
        RAISE noExisteTelefono;
    END IF;

    FOR variableLocal IN (SELECT duracion FROM LLAMADA WHERE EXTRACT(YEAR FROM fecha_hora) = año AND tf_origen = telefono) LOOP
        duracionTotal := duracionTotal + variableLocal.duracion;
    END LOOP;

    SELECT T.coste
    INTO costeMinuto
    FROM TARIFA T
    INNER JOIN TELEFONO Tfo ON T.tarifa = Tfo.tarifa
    WHERE Tfo.numero = telefono;

    facturacion := costeMinuto * duracionTotal / 60;

    IF facturacion < 1 THEN 
        RAISE facturaInferior;
    END IF;

    RETURN facturacion;

EXCEPTION
    WHEN noExisteTelefono THEN 
        dbms_output.put_line('El teléfono no existe o no ha realizado llamadas ese año');
        return -1;
    WHEN facturaInferior THEN 
        dbms_output.put_line('La facturación del teléfono es inferior a 1 euro');
        return -1;
    WHEN OTHERS THEN 
        dbms_output.put_line('Ha ocurrido un error');
        RETURN -1;
END facturacion;

------------------------------------------------------------------
