#include "tdas/list.h"
#include "tdas/queue.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


typedef struct tiempo
{
  int horas;
  int minutos;
  int segundos; 

}tiempo;


typedef struct categoria
{  
  char nombreCategoria[100];
  List* listaTareas;
}categoria;


typedef struct tarea
{
  char nombreTarea[100];
  char descripcion[200];
  tiempo horaRegistro;
  categoria* categoriaTarea;
}tarea;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión de Tareas");
  puts("========================================");

  puts("1) Nueva Categoría");
  puts("2) Eliminar Categoría");
  puts("3) Mostrar Categorías");
  puts("4) Registrar Tarea");
  puts("5) Atender Siguiente Tarea");
  puts("6) Visualización del Tablero General");
  puts("7) Filtrado por Categoría");
  puts("8) Salir");
}


int main() {
  char opcion;
  List *categorias = list_create(); // Lista para almacenar categorías
  Queue* colaTareas = queue_create(); // Cola para almacenar las tareas

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior
    printf("\n");
    switch (opcion) 
    {
      
    case '1':
      //Lógica para registrar una nueva categoría
      
      printf("Registrar nueva categoría: ");

      char nombre[100];
      scanf(" %[^\n]", nombre);

      if(list_first(categorias) != NULL)
      {
        bool repetido = false;
        categoria* catTemp = list_first(categorias);
        while(catTemp != NULL)
        {
          if(strcmp(catTemp->nombreCategoria, nombre) == 0)
          {
            printf("\nYa existe una categoría con ese nombre\n");
            repetido = true;
            break;
          }
          catTemp = list_next(categorias);
        }
        
        if(repetido == true) break;

      } 
      
      categoria* nueva_cat = (categoria*) malloc(sizeof(categoria));
      strcpy(nueva_cat->nombreCategoria, nombre);
      nueva_cat->listaTareas = list_create();

      list_pushBack(categorias, nueva_cat);
      printf("\nCategoría registrada exitosamente \n");
        
      break;
      
    case '2':
      // Lógica para eliminar una categoría

      if (list_first(categorias) == NULL)
      {
        printf("\nNo hay categorías \n");
        break;
      }
      
      printf("Categoría a eliminar: ");

      char eliminar[100];
      scanf(" %[^\n]", eliminar);

      categoria* catAux = list_first(categorias);
      
      while(catAux != NULL)
      {
        if (strcmp(catAux->nombreCategoria, eliminar) == 0)
        {
          tarea* tareaAux = list_first(catAux->listaTareas);
          while (tareaAux != NULL)
          {
            tarea* tareaTemp = tareaAux;
            tareaAux = list_next(catAux->listaTareas);
            free(tareaTemp);
          }  
          list_clean(catAux->listaTareas);
          free(catAux->listaTareas);

          Queue* colaAuxiliar = queue_create();
          tarea* tareaEnCola = queue_front(colaTareas);

          while(tareaEnCola != NULL)
          {
            queue_insert(colaAuxiliar, tareaEnCola);
            queue_remove(colaTareas);
            tareaEnCola = queue_front(colaTareas);
          }
              
          tareaEnCola = queue_front(colaAuxiliar);
              
          while(tareaEnCola != NULL)
          {
            if(tareaEnCola->categoriaTarea != catAux)
            {
              queue_insert(colaTareas, tareaEnCola);
            }
            tareaEnCola = queue_next(colaAuxiliar);
            queue_remove(colaAuxiliar);
          }
        
          free(colaAuxiliar);
            
        list_popCurrent(categorias);
        free(catAux);
        
        printf("\nCategoría eliminada \n");    
        break;
      }
      catAux = list_next(categorias);
    }

    if (catAux == NULL) printf("\nNo existe una categoría con ese nombre \n");
    break;
      
    case '3':
      // Mostrar categorías
      
      printf("Categorías:\n");

      categoria* catAux1 = list_first(categorias);

      if (catAux1 == NULL)
      {
        printf("\nNo hay categorías \n");
        break;
      }
      while(catAux1 != NULL)
      {
        printf("%s \n", catAux1->nombreCategoria);
        catAux1 = list_next(categorias);
      }
      break;
      
    case '4':
      // Lógica para añadir una tarea
      
      if (list_first(categorias) == NULL)
      {
        printf("\nNo hay categorías \n");
        break;
      }
      
      printf("Nombre de la tarea: ");
      
      tarea* nuevaTarea = (tarea*) malloc(sizeof(tarea));
      char nombreCategoriaTarea[100];
      scanf(" %[^\n]", nuevaTarea->nombreTarea);
      
      printf("Descripción de la tarea: ");
      scanf(" %[^\n]", nuevaTarea->descripcion);
      
      printf("Categoría de la tarea: ");
      scanf(" %[^\n]", nombreCategoriaTarea);

      time_t  t;
      struct tm *tiempo;

      t = time(NULL);
      
      tiempo = localtime(&t);

      printf("Hora de registro de la tarea: \n");
      printf("%2d : %2d : %2d \n", tiempo->tm_hour, tiempo->tm_min, tiempo->tm_sec);
      
      categoria* catAux2 = list_first(categorias);
      
      while(catAux2 != NULL)
      {
        if (strcmp(catAux2->nombreCategoria, nombreCategoriaTarea) == 0)
        {
          nuevaTarea->categoriaTarea = catAux2;
          list_pushBack(catAux2->listaTareas, nuevaTarea);
          queue_insert(colaTareas, nuevaTarea);
          
          nuevaTarea->horaRegistro.horas = tiempo->tm_hour;
          nuevaTarea->horaRegistro.minutos = tiempo->tm_min;
          nuevaTarea->horaRegistro.segundos = tiempo->tm_sec;
          
          printf("\nTarea añadida exitosamente \n");
          break;
        }
        catAux2 = list_next(categorias);
      }
      if (catAux2 == NULL) 
      {
        printf("\nNo existe una categoría con ese nombre \n");
        free(nuevaTarea);
        break;
      }
      
      break;
      
    case '5':
      // Lógica para atender la siguiente tarea

      if (queue_front(colaTareas) == NULL)
      {
        printf("\n¡Libre de pendientes! \n");
        break;
      }
      
      printf("Siguiente tarea: \n");
      tarea* siguiente = queue_front(colaTareas);
      
      printf("Atendiendo: %s\n", siguiente->nombreTarea);
      printf("Descripción: %s\n", siguiente->descripcion);
      printf("Categoría: %s\n", siguiente->categoriaTarea->nombreCategoria);
      printf("Registrada a las: %2d : %2d : %2d \n", siguiente->horaRegistro.horas, siguiente->horaRegistro.minutos, siguiente->horaRegistro.segundos);
      
      queue_remove(colaTareas);
      
      categoria* catAux3 = list_first(categorias);
      
      while(catAux3 != NULL)
      {
        if (catAux3 == siguiente->categoriaTarea)
        {
          tarea* tareaAux1 = list_first(catAux3->listaTareas);
          while (tareaAux1 != NULL)
          {
            if (tareaAux1 == siguiente)
            {
              list_popCurrent(catAux3->listaTareas);
              break;
            }
            tareaAux1 = list_next(catAux3->listaTareas);
          }
          break;
        }
        catAux3 = list_next(categorias);
      }
    
      printf("\nTarea atendida exitosamente \n");
      free(siguiente);
      
      break;
      
    case '6':
      // Lógica para mostrar el tablero general
    
      printf("Tablero general: \n\n");

      tarea* tareaActual = queue_front(colaTareas);
      
      if (tareaActual == NULL)
      {
        printf("No hay tareas para mostrar \n");
        break;
      }
        
      while (tareaActual != NULL)
      {
        printf("%s | %s \n", tareaActual->nombreTarea, tareaActual->categoriaTarea->nombreCategoria);
        tareaActual = queue_next(colaTareas);
      }
      printf("\n");
      break;
      
    case '7':
      // Lógica para filtrar por categoría
      
      if (list_first(categorias) == NULL)
      {
          printf("\nNo hay categorías \n");
          break;
      }
      
      tarea* tareaEnCola1 = queue_front(colaTareas);
      if (tareaEnCola1 == NULL)
      {
        printf("\nNo hay tareas \n");
        break;
      }
      
      printf("Categoría seleccionada: ");

      char filtro[100];
      scanf(" %[^\n]", filtro);

      categoria* catAux4 = list_first(categorias);
      while (catAux4 != NULL)
      {
        if (strcmp(catAux4->nombreCategoria, filtro) == 0)
        {
          break;
        }
        catAux4 = list_next(categorias);
      }
      if (catAux4 == NULL) 
      {
        printf("\nNo existe una categoría con ese nombre \n");
        break;
      }
      
      printf("\nTareas de categoría %s: \n\n", filtro);
      while(tareaEnCola1 != NULL)
      {
        if (strcmp(tareaEnCola1->categoriaTarea->nombreCategoria, filtro) == 0)
        {
          printf("%s \n",tareaEnCola1->nombreTarea);
        }
        tareaEnCola1 = queue_next(colaTareas);
      }
      break;
      
    case '8':
      puts("Saliendo del sistema de gestión de tareas...");
      break;
      
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    
    printf("\n");
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  // Liberar recursos, si es necesario
  
  categoria* catAux5 = list_first(categorias);
  
  while (catAux5 != NULL)
  {
    tarea* tareaAux2 = list_first(catAux5->listaTareas);
    
    while(tareaAux2 != NULL)
    {
      tarea* tareaAux3 = tareaAux2;
      tareaAux2 = list_next(catAux5->listaTareas);
      free(tareaAux3);
    }
    list_clean(catAux5->listaTareas);
    free(catAux5->listaTareas);

    categoria* catAux6 = catAux5;
    catAux5 = list_next(categorias);
    free(catAux6);
  }
  
  list_clean(categorias);
  free(categorias);
  
  while(queue_front(colaTareas) != NULL)
  {
    queue_remove(colaTareas);    
  }  
  
  free(colaTareas);

  
  return 0;
}
