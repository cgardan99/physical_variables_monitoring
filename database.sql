create database final_electronica;
use final_electronica;
create table lecturas_periodicas (id int auto_increment primary key, temperatura float, vibraciones float, humedad float);
select * from lecturas_periodicas;
alter table lecturas_periodicas add fecha datetime;
alter table lecturas_periodicas modify fecha datetime DEFAULT CURRENT_TIMESTAMP;
create table movimientos (id int auto_increment primary key, fecha datetime DEFAULT CURRENT_TIMESTAMP);
