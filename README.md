# Planificador Dinámico de Tareas

## Descripción 
Este programa permite a los usuarios ordenar y atender sus tareas. Los usuarios pueden registrar nuevas categorías,
registrar nuevas tareas con su respectiva descripción y categoría, mostrar las categorías, eliminar categorías y las 
tareas que correspondan a esa categoría, mostrar las tareas, atender las tareas y filtrar las tareas que pertenezcan 
a cierta categoría. Esta herramienta está diseñada para organizar las tareas según el orden en el que son registradas.



## Pasos para compilar y ejecutar:

1.  Ir a la página de replit
2.  Haz clic en "Import code or design"
3.  Selecciona Github
4.  En "GitHub Repo URL" pega el siguiente link: https://github.com/martindiazm/martindiazm-Tarea1
5.  Haz clic en "Import from Github"


Para ejecutar el código primero debemos compilar en la Shell de replit
````
gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1
````

Y luego ejecutar:
````
./tarea1
````
## Funcionalidades 

- ### Crear categorías
Se ingresa el nombre de la categoría, no se permiten categorías
con exactamente el mismo nombre y cada categoría tiene su propia
lista de tareas

- ### Eliminar categorías
Se ingresa el nombre de una categoría ya existente, se eliminan
las tareas de esa categoría de la lista de tareas y de la cola
global de tareas

- ### Mostrar categorías 
Se muestran los nombres de todas las categorías

- ### Registrar tareas
Se ingresa el nombre, la descripción y la categoría de la 
tarea, además se registra la hora a la que fue ingresada.
Cada tarea se almacena en la lista de su categoría y en la cola
global de tareas
  
- ### Atender tareas (FIFO)
Se atiende la primer tarea ingresada, se muestran sus datos
y se elimina en la lista de su categoría y en la cola
global de tareas
  
- ### Visualizar tareas y su categoría
Muestra todas las tareas pendientes por orden de llegada
junto con su categoría

- ### Filtrar tareas por su categoría
Se ingresa una categoría existente y se muestran unicamente
las tareas pertenecientes a esa categoría 



## Problemas conocidos
- El programa no está diseñado para recibir un archivo
  de datos

- Al registrar la hora en replit no se asigna la hora de
Chile

## A mejorar
- No se pueden modificar los datos de una tarea durante
el proceso

- Se pueden ingresar tareas con el mismo nombre y descripción

## Ejemplo de uso 

### Crear una categoría:
  Opción: 1

  Entrada:
  ````
  Trabajo
  ````
### Crear otra categoría:
  Opción: 1
  
  Entrada:
  ````
  Personal
  ````
### Registrar una tarea:
  Opción: 4

  Entrada:
  ````
  Nombre: Hacer informe
  Descripción: Informe de ventas mensual
  Categoría: Trabajo
  ````
### Registrar otra tarea:
  Opción: 4

  Entrada:
  ````
  Nombre: Comprar comida
  Descripción: Ir al supermercado
  Categoría: Personal
  ````
### Ver tablero general:
  Opción: 6

  Salida esperada:
  ````
  Hacer informe | Trabajo
  Comprar comida | Personal
  ````
### Filtrar por categoría:
 
  Opción: 7

  Entrada:
  ````
  Trabajo
  ````
  Salida:
  ````
  Hacer informe
  ````
### Atender una tarea:
  Opción: 5

  Salida:
  ````
  Atendiendo: Hacer informe
  Descripción: Informe de ventas mensual
  Categoría: Trabajo
  ````
### Ver tablero actualizado:
  Opción: 6

  Salida:
  ````
  Comprar comida | Personal
  ````
### Salir del programa:
  Opción: 8