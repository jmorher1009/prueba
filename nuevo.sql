/* 
Diseñar la función facturacion(), la cual admite dos parámetros de entrada (un
teléfono y un año) y devuelve la facturación total de ese número en ese año. La
función debe controlar 2 tipos de excepciones:
->el teléfono no existe o el teléfono no ha realizado llamadas ese año.
->la facturación del teléfono es inferior a 1 euro.*/
SET SERVEROUTPUT ON;
CREATE OR REPLACE FUNCTION BD_072.facturacion(telefono IN LLAMADA.tf_origen%TYPE, año IN INTEGER) RETURN NUMBER IS
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
--Diseñar el procedimiento LlamadaFacturacion(año), el cual, para cada teléfono de
--la tabla LLAMADAS debe realizar una llamada a la función facturación y mostrar la
--facturación de dicho teléfono en el año que se le pasa como parámetro.

CREATE OR REPLACE PROCEDURE BD_072.LLAMADAFACTURACION(p_anio INTEGER) IS
      CURSOR c_telefonos IS SELECT DISTINCT tf_origen FROM MF."LLAMADA"
            WHERE EXTRACT(YEAR FROM fecha_hora)=p_anio;
BEGIN
      dbms_output.put_line('Nº telefono'||'     '||'Importe(en €)');
      dbms_output.put_line('-------------------------');
      FOR r_telefono IN c_telefonos LOOP  
            dbms_output.put_line(r_telefono.tf_origen ||'   '||facturacion(r_telefono.tf_origen, p_anio));
      END LOOP;
EXCEPTION
      WHEN OTHERS THEN
            dbms_output.put_line('Ha ocurrido un error');
END LLAMADAFACTURACION;

CALL LLAMADAFACTURACION(2006);

-------------------------------------------------------------------------
/*Crear un procedimiento que tenga como parámetros de entrada el nombre de una
compañía y una fecha. Dicho procedimiento debe realizar las siguientes
operaciones:
1. Comprobar que existen en la BD llamadas realizadas en la fecha que se pasa
como parámetro. En caso contrario lanzar una excepción y mostrar el
mensaje “No hay llamadas en la fecha <fecha> en la BD”.
2. Para cada teléfono de la compañía que se pasa por parámetro, el
procedimiento debe mostrar la siguiente información: número de teléfono,
número total de llamadas realizadas en la fecha indicada, número de
llamadas de duración mayor de 100 segundos realizadas en la fecha,
porcentaje que suponen estas últimas respecto al total de las realizadas.
3. Un resumen del número de llamadas realizadas por todos los teléfonos de la
compañía indicada en la fecha pasada por parámetro*/
CREATE OR REPLACE PROCEDURE BD_072.LLAMADAS_CIA(p_nombre MF."COMPAÑIA".nombre%TYPE, p_fecha VARCHAR2) IS
      n_filas_llamadas INTEGER;
      n_llamadas_total INTEGER;
      n_llamadas_per INTEGER;
      n_llamadas_c INTEGER;
      porcentaje NUMBER(5,2);
      not_found_fecha EXCEPTION;

      CURSOR c_telefonos IS SELECT tl.numero FROM MF."TELEFONO" tl
            INNER JOIN MF."COMPAÑIA" c ON tl.compañia=c.cif
                  WHERE p_nombre=c.nombre;
            
      CURSOR c_llamadas (tlf MF."LLAMADA".tf_origen%TYPE) IS
            SELECT tf_origen, tf_destino, duracion FROM MF."LLAMADA"
                  WHERE TO_CHAR(fecha_hora, 'dd/mm/yy')=p_fecha
                        AND tf_origen=tlf;
                  
BEGIN 
      SELECT COUNT(*) INTO n_filas_llamadas
            FROM (MF."LLAMADA" ll INNER JOIN MF."TELEFONO" tl ON ll.tf_origen=tl.numero)
                  INNER JOIN MF."COMPAÑIA" c ON c.cif=tl.compañia
                        WHERE TO_CHAR(ll.fecha_hora, 'dd/mm/yy')=p_fecha
                              AND c.nombre=p_nombre;
      IF (n_filas_llamadas=0) THEN
            RAISE not_found_fecha;
      END IF;
      
      dbms_output.put_line('Tlf. Origen Nº Total Nº+100 %');
      dbms_output.put_line('-------------------------------------------------------');
      n_llamadas_c:=0;
      FOR r_telefonos IN c_telefonos LOOP
            n_llamadas_total:=0;
            n_llamadas_per:=0;      
      FOR r_llamadas IN c_llamadas(r_telefonos.numero) LOOP
            IF (r_llamadas.duracion>100) THEN
                  n_llamadas_per:=n_llamadas_per+1;
            END IF;
            n_llamadas_total:=n_llamadas_total+1;
            n_llamadas_c:=n_llamadas_c+1;
      END LOOP;
            IF n_llamadas_per<>0 THEN
                  porcentaje:=(n_llamadas_per/n_llamadas_total)*100;
            ELSE porcentaje:=0;
            END IF;
            dbms_output.put_line( rpad(r_telefonos.numero,13) || rpad(n_llamadas_total,8) || rpad(n_llamadas_per,13) || rpad(porcentaje|| '%',7) );
      END LOOP;
      
      dbms_output.put_line('Numero total de llamadas: ' || n_llamadas_c);
EXCEPTION
      WHEN not_found_fecha THEN
            dbms_output.put_line('No existe la fecha');
      WHEN OTHERS THEN
            dbms_output.put_line('Ha ocurrido un error');
END LLAMADAS_CIA;

CALL LLAMADAS_CIA('Kietostar', '16/10/06');

----------------------------------------------------------------------------------

CREATE OR REPLACE PROCEDURE TELEFONOS_COMPAÑIA(p_nombre MF."COMPAÑIA".nombre%TYPE) IS

duracion_total FLOAT;

coste_total NUMBER(5,2);

coste NUMBER(5,2);



CURSOR c_telefonos IS SELECT tl.numero FROM MF."TELEFONO" tl

INNER JOIN MF."COMPAÑIA" c ON tl.compañia=c.cif

WHERE p_nombre=c.nombre;

CURSOR c_llamadas (tlf MF."LLAMADA".tf_origen%TYPE) IS

SELECT ll.tf_origen, ll.tf_destino, ll.duracion, tf.coste FROM MF."LLAMADA" ll

INNER JOIN MF."TELEFONO" tl ON tl.numero=ll.tf_origen INNER JOIN MF."COMPAÑIA" c ON tl.compañia=c.cif

INNER JOIN MF."TARIFA" tf ON tf.compañia=c.cif

WHERE p_nombre=c.nombre AND ll.tf_origen=tlf;

not_found_compania EXCEPTION;

BEGIN

IF ((p_nombre <> 'Aotra') AND (p_nombre <> 'Petafón')) THEN

RAISE not_found_compania;

END IF;

dbms_output.put_line(' Telefono | Duracion total | Coste total');

dbms_output.put_line('-----------------------------------------------------');

FOR r_telefonos IN c_telefonos LOOP

duracion_total:=0;

coste:=0;

coste_total:=0;

FOR r_llamadas IN c_llamadas(r_telefonos.numero) LOOP

duracion_total:=duracion_total+r_llamadas.duracion;

coste:=r_llamadas.coste;

END LOOP;

duracion_total:=duracion_total-(duracion_total/2);

coste_total:=((duracion_total * coste)/60);

dbms_output.put_line( rpad(r_telefonos.numero,25) || rpad(duracion_total,15) || coste_total);

END LOOP;

EXCEPTION

WHEN not_found_compania THEN

dbms_output.put_line('No hay ninguna compañía cuyo nombre sea ' || p_nombre);

WHEN OTHERS THEN

dbms_output.put_line('Ha ocurrido un error');

END TELEFONOS_COMPAÑIA;
