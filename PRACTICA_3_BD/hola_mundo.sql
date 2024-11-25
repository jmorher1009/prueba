set serveroutput on;
call hola_mundo('Hola');

call dbms_output.put_line(facturacion('654123321', 2006));
