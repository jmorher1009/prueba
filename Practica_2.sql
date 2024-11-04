select *
from mf.cliente
where dni = '35000001P';

select * from mf.llamada;

select nombre, f_nac, ciudad
from mf.cliente
where nombre like 'J%' and extract (year from f_nac) >= 1882
order by nombre asc;

--between '29/03/81' and '03/02/98'


select nombre, f_nac, ciudad
from mf.cliente
where nombre like 'J%' and extract (year from f_nac) >= 1882
order by nombre asc;

/*---------------------------------PRACTICA_2---------------------------------*/


--1.1
select cia.nombre
from mf.compañia cia
where cia.web like '%et%com';
--1.2
select cli.nombre, cli.direccion 
from mf.cliente cli
where extract(year from cli.f_nac) in ('1973','1985')--cli.f_nac = 1973 or cli.f_nac = 1985
and cli.cp like '15%'
order by cli.nombre asc, cli.direccion desc;
--1.3
select l.tf_destino
from mf.llamada l
where l.tf_origen = '666010101'
and extract(year from l.fecha_hora) = '2006';

--1.4
select l.tf_origen
from mf.llamada l
where l.tf_destino = '666010101'
    and to_char(fecha_hora, 'hh:mm') between '10:00' and '12:00';

--1.5
select distinct tlf.tarifa
from mf.telefono tlf
where tlf.cliente like '%2%' and tlf.tipo = 'C'
    and tlf.puntos between 10000 and 20000;
    
--1.6
select tlf.numero, tlf.tarifa
from mf.telefono tlf
where extract(month from f_contrato) = '05' and tarifa <> 'joven'
    and numero like '%9'
order by puntos desc;

--1.7
select distinct l.tf_destino
from mf.llamada l
where l.tf_origen = '654345345'
    and extract(month from l.fecha_hora) in('10','11')
    and l.duracion > 250;

--1.8 Obtener los nombres de los clientes que nacieron entre 1970 y 1985 y que pertenezcan a la provincia de
--Huelva, ordenados ascendentemente por ciudad y descendentemente por provincia.

select *
from mf.cliente cli
where extract(year from cli.f_nac) between 1970 and 1985
    and cli.provincia = 'Huelva'
order by ciudad asc, provincia desc;

--S2.1 Mostrar el c�digo y coste de las tarifas junto con el nombre de la compa��a que las ofrecen, de aquellas
--tarifas cuya descripci�n indique que otras personas deben estar tambi�n en la misma compa��a
select t.compa�ia as codigo , t.coste, c.nombre
from mf.compa�ia c
inner join mf.tarifa t on c.cif = t.compa�ia
where t.descripcion like '%en la compa��a%';

--S2.2 Nombre y n�mero de tel�fonos de aquellos abonados con contrato que tienen tarifas inferiores a 0,20 �.

select c.nombre, tf.numero
from mf.cliente c inner join mf.telefono tf on c.dni = tf.cliente
inner join mf.tarifa tar using(tarifa,compa�ia)
where tar.coste < 0.20 and tf.tipo = 'C';

--S2.3 Obtener el c�digo de las tarifas, el nombre de las compa��as, los n�meros de tel�fono y los puntos, de
--aquellos tel�fonos que se contrataron en el a�o 2006 y que hayan obtenido m�s de 200 puntos.

select tar.tarifa, c.nombre, tf.numero ,tf.puntos
from mf.compa�ia c 
    inner join mf.telefono tf on c.nombre = tf.compa�ia
    inner join mf.tarifa tar on tf.tarifa = tar.tarifa and tar.compa�ia = tf.compa�ia
where tf.puntos > 200 and to_char(tf.f_contrato,'yyyy') = '2006';

--S2.4 Obtener los n�meros de tel�fono (origen y destino), as� como el tipo de contrato, de los clientes que alguna
--vez hablaron por tel�fono entre las 8 y las 10 de la ma�ana

select llam.tf_origen, llam.tf_destino, tf_o.tipo as tipo_origen, tf_d.tipo as tipo_destino
from mf.llamada llam 
    inner join mf.telefono tf_o on tf_o.numero = llam.tf_origen -- contratos de tf_origen
    inner join mf.telefono tf_d on tf_d.numero = llam.tf_destino -- contratos de tf_destino
    inner join mf.cliente cli on cli.dni = tf_o.cliente
where to_char(llam.fecha_hora, 'hh:mm')between '08:00' and '10:00';

--S2.5 Interesa conocer los nombres y n�meros de tel�fono de los clientes (origen y destino) que, perteneciendo
--a compa��as distintas, mantuvieron llamadas que superaron los 15 minutos. Se desea conocer, tambi�n, la
--fecha y la hora de dichas llamadas as� como la duraci�n de esas llamadas

select cli_o.nombre as nombre_origen, tf_o.numero as n_orig, tf_d.numero as n_dest,cli_d.nombre as nombre_destino, llam.duracion, llam.fecha_hora
from mf.cliente cli_o
    inner join mf.telefono tf_o on cli_o.dni = tf_o.cliente
    inner join mf.llamada llam on tf_o.numero = llam.tf_origen
    inner join mf.telefono tf_d on llam.tf_destino = tf_d.numero
    inner join mf.cliente cli_d on cli_d.dni = tf_d.cliente
where llam.duracion > 15*60 and tf_o.compa�ia <> tf_d.compa�ia;

-- Ejemplo operador IN y NOT IN =,<=,<,>=,>,ALL,ANY
select *
from mf.telefono tlf
where tlf.compa�ia =ANY(select comp.cif
                        from mf.compa�ia comp
                        where nombre = 'Kietostar' or nombre = 'Petaf�n');
                        
                        
--S3.1 Obtener la fecha (d�a-mes-a�o) en la que se realiz� la llamada de mayor duraci�n

select to_char(ll.fecha_hora, 'dd-mm-yyyy') as fecha
from mf.llamada ll
where ll.duracion >=ALL(select ll2.duracion     --mayor o igual que todas (es decir la de m�xima duraci�n)
                         from mf.llamada ll2);
                         
--S3.2 Obtener el nombre de los abonados de la compa��a �Aotra� con el mismo tipo de tarifa que la del telefono �654123321�            
            
select cli.nombre
from mf.cliente cli inner join mf.telefono tf on tf.cliente = cli.dni
where tf.tarifa in(
                     select tf2.tarifa
                     from mf.telefono tf2
                     where tf2.numero = '654123321'
                     )
and tf.compa�ia in(
                    select cia.cif
                    from mf.compa�ia cia
                    where cia.nombre = 'Aotra'
                    );


--S3.3 Mostrar, utilizando para ello una subcobsulta, el n�mero de tel�fono, fecha de contrato y tipo de los
--abonados que han llamado a tel�fonos de clientes de fuera de la provincia de La Coru�a durante el mes de
--octubre de 2006

select distinct tlf2.numero, tlf2.f_contrato, tlf2.tipo
from mf.llamada ll inner join mf.telefono tlf2 on(tlf2.numero = ll.tf_origen)
where ll.tf_destino in(
                        select tlf.numero
                        from mf.cliente cli inner join mf.telefono tlf on(tlf.cliente=cli.dni)
                        where cli.provincia <> 'La Coru�a');
                        
                        

--S3.4 Se necesita conocer el nombre de los clientes que tienen tel�fonos con tarifa �d�o� pero no �aut�nomos�.
--Utiliza subconsultas para obtener la soluci�n.

select cli.nombre
from mf.cliente cli inner join mf.telefono tf on cli.dni = tf.cliente
where tf.tarifa in(
                    select tar.tarifa
                    from mf.tarifa tar
                    where tar.tarifa = 'd�o'
                    )
and tf.tarifa not in(
                    select tar.tarifa
                    from mf.tarifa tar
                    where tar.tarifa = 'aut�nomos'
    );   
    
--S3.5 Obtener mediante subconsultas los nombres de clientes y n�meros de tel�fono que aquellos que hicieron
--llamadas a tel�fonos de la compa��a Petaf�n pero no Aotra

select cli.nombre, tf.numero
from mf.cliente cli inner join mf.telefono tf on cli.dni = tf.cliente 
where tf.numero in(
                    select ll.tf_origen
                    from mf.llamada ll inner join mf.telefono tf_dest on tf_dest.numero = ll.tf_destino
                    where tf_dest.compa�ia in(
                                            select cia.cif
                                            from mf.compa�ia cia
                                            where cia.nombre = 'Petaf�n'
                        )
                    )
        and tf.numero not in(
                    select ll.tf_origen
                    from mf.llamada ll inner join mf.telefono tf_dest on tf_dest.numero = ll.tf_destino
                    where tf_dest.compa�ia in(
                                            select cia.cif
                                            from mf.compa�ia cia
                                            where cia.nombre = 'Aotra'
                        )
                    );
                    
                        
--S3.6 Nombre de los clientes de la compa��a Kietostar que hicieron las llamadas de mayor duraci�n en
--septiembre de 2006

select distinct c.nombre, ll.tf_origen, ll.tf_destino,ll.duracion,to_char(ll.fecha_hora,'mm/yyyy') as Fecha,cia.nombre
from mf.cliente c inner join mf.telefono tf on tf.cliente=c.dni
    inner join mf.compa�ia cia on cia.cif = tf.compa�ia
    inner join mf.llamada ll on tf.numero = ll.tf_origen
where to_char(fecha_hora,'mm/yyyy')='09/2006'
      and cia.nombre = 'Kietostar'
      and ll.duracion >= all(
                        select llam.duracion 
                        from mf.llamada llam
                        where to_char(fecha_hora,'mm/yyyy')='09/2006'
                              and cia.nombre = 'Kietostar');

--S3.7 Se necesita conocer el nombre de los clientes que tienen tel�fonos con fecha de contrataci�n anterior a
--alguno de los tel�fonos de Ram�n Mart�nez Sabina, excluido, claro, el propio Ram�n Mart�nez Sabina


select c.nombre, to_char(tf.f_contrato, 'mm/yyyy') as f_contrato
from mf.telefono tf inner join mf.cliente c on c.dni = tf.cliente
where c.nombre <> 'Ram�n Mart�nez Sabina' and tf.f_contrato < any(
                        select tel.f_contrato
                        from mf.telefono tel inner join mf.cliente cli on cli.dni = tel.cliente
                        where cli.nombre = 'Ram�n Mart�nez Sabina');
     
--ejemplos de consultas correlacionadas
--no puedes realizar las consultas por separado 
select *    --clientes que tienen algun telefono asociado
from mf.cliente cli
where exists (select *
             from mf.telefono tf
             where tf.cliente = cli.dni); 
             
--S4.1 Utilizando consultas correlacionadas, mostrar el nombre de los abonados que han llamado el d�a �16/10/06�

select cli.nombre
from mf.cliente cli inner join mf.telefono tf on cli.dni = tf.cliente
where exists(select *
            from mf.llamada llam
            where llam.tf_origen = tf.numero
                and to_char(llam.fecha_hora,'dd/mm/yy') = '16/10/06');
                
--S4.2 Utilizando consultas correlacionadas, obtener el nombre de los abonados que han realizado llamadas de
--menos de 1 minuto y medio

select *
from mf.cliente cli inner join mf.telefono tf on cli.dni = tf.cliente
where exists(select *
            from mf.llamada llam
            where llam.tf_origen = tf.numero
                and llam.duracion < 90);

--S4.3 Utilizando consultas correlacionadas, obtener el nombre de los abonados de la compa��a �KietoStar� que no
--hicieron ninguna llamada el mes de septiembre
 
select cli.nombre
from mf.cliente cli inner join mf.telefono tf on cli.dni = tf.cliente
                    inner join mf.compa�ia cia on tf.compa�ia = cia.cif
where cia.nombre = 'Kietostar'
and not exists(select *
                from mf.llamada llam
                where llam.tf_origen = tf.numero
                    and extract(month from llam.fecha_hora) = 09);
                
--S4.4 Utilizando consultas correlacionadas, mostrar todos los datos de los telefonos que hayan llamado al
--n�mero 654234234 pero no al 666789789
                    
select *
from mf.telefono tf
where exists(select *
            from mf.llamada llam
            where llam.tf_destino = 654234234
            and llam.tf_origen = tf.numero)
    and not exists(select *
            from mf.llamada llam
            where llam.tf_destino = 666789789
            and llam.tf_origen = tf.numero);

--S4.5 Utilizando consultas correlacionadas, obtener el nombre y n�mero de tel�fono de los clientes de la
--compa��a Kietostar que no han hecho llamadas a otros tel�fonos de la misma compa��a

select cli.nombre, tf.numero
from mf.cliente cli inner join mf.telefono tf on tf.cliente = cli.dni
                    inner join mf.compa�ia cia on cia.cif = tf.compa�ia
where cia.nombre = 'Kietostar'
and not exists(select *
                from mf.llamada llam inner join mf.telefono tf1 on tf1.numero = llam.tf_destino
                where llam.tf_origen = tf.numero
                and tf1.compa�ia = tf.compa�ia);

       
                