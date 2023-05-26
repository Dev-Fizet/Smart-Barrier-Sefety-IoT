use codigoiot; 
ALTER TABLE almacen MODIFY COLUMN datos FLOAT(32,3);
INSERT INTO almacen(nombre, datos) VALUES ('prueba','400');

		select * from almacen;