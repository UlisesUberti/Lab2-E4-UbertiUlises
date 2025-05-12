/*********************************************************************************************************************
Copyright (c) 2025, Uberti,Ulises Leandro <ubertileandro0@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file alumno.c
 * @brief Código fuente del modulo alumno
 * @author Uberti, Ulises Leandro
 * */

/* === Headers files inclusions ==================================================================================== */
#include "alumno.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* === Macros definitions ========================================================================================== */
#ifndef ALUMNOS_MAX_INSTANCIA
#define ALUMNOS_MAX_INSTANCIA 2
// DEFINO LA CANTIDAD MAXIMA DE ALUMNOS Y PUEDO PASARSELA AL MAKEFILE 
#endif
/* === Private data type declarations ============================================================================== */

/** @struct alumno_s
 * @brief estructura que contiene los datos del alumno
 * @param nombre indica el nombre del alumno(20 caracteres max.)
 * @param apellido  indica el apellido del alumno(20 caracteres max.)
 * @param DNI indica el documento del alumno 
*/
struct alumno_s  //la estrucutura la declare en el h entonces ahora defino
{
    char nombre[20]; //!<Nombre del alumno
    char apellido[20]; //!<Apellido del alumno
    uint32_t DNI; //!<Documento del alumno
    bool ocupado; // indica si la instancia esta ocupada 
}; //!< Puntero a la estructura alumno_s; 

/* === Private function declarations =============================================================================== */
/* === Private variable definitions ================================================================================ */
/* === Public variable definitions ================================================================================= */
static struct alumno_s instancias[ALUMNOS_MAX_INSTANCIA]={0}; 
// 2 es la cant maxima de alumnos 
// lo defino como stati para que ocupe memoria estatica 

/* === Private function definitions ================================================================================ */

int Crear_Instancia(){
   // esta funcion busca el primer desocupado en el array y obtiene su direccion de memoria 
   alumno_t alumno = NULL;  // peor de los casos --> no encontrar espacio 
   for (int i = 0; i < ALUMNOS_MAX_INSTANCIA; i++)
   {
      //sizeof(instancias)/sizeof(instancias[0] es la cantidad de instancias que tengo
      if (!instancias[i].ocupado)
      {
         instancias[i].ocupado=true; 
         alumno = &instancias[i];
         break;
      }
   }
}
/** @brief Funcion para serializar el nombre y apellido
 *  @param campo indica el campo de la estructura 
 *  @param valor indica valor del campo 
 *  @param chain es la cadena que se va a escribir
 *  @param espacio es el espacio que queda para escibir en la cadena  
 *  @param posicion es la posicion de la cadena que se escribe
 *  @return -1 si sizeof(&valor)>espacio o snprintf()
 */
int Serialize_chain(char campo[],const char valor[],char chain[],uint32_t espacio,int posicion)
{
   if (sizeof(&valor)>espacio)
   {
      return -1;
   }
   return snprintf(chain+posicion,espacio,"\"%s\":\"%s\",",campo,valor);  
}

   /** @brief Funcion para serializar el DNI + APELLIDO&NOMBBRE
 *  @param campo indica el campo de la estructura 
 *  @param valor indica valor del campo 
 *  @param chain es la cadena que se va a escribir
 *  @param espacio es el espacio que queda para escibir en la cadena  
 *  @param posicion es la posicion de la cadena que se escribe
 *  @return -1 si sizeof(&valor)>espacio o snprintf
 */
int Serialize_chain_dni(char campo[], uint32_t valor,char chain[],uint32_t espacio,int posicion)
{
   /**Condicional si resta espacio suficiente para DNI y la ultima llave */
   if (sizeof(&valor)+1>espacio)
   {
      return -1;
   }
   return snprintf(chain+posicion,espacio,"\"%s\":%u,",campo,valor); 
}

alumno_t Crear_Alumno(char apellido[], char name[],uint32_t DNI)
{
   //alumno_t es la direccion del incio de un bloque de memoria
   //para obtener asignar esta direc de memoria utilizo malloc, para el compilador me de los bytes 
   // la memoria tiene 3 partes --> las variables estaticas globales 
   //--> la memoria restante tiene 2 señaladores 
   // en una subrutina se guarda informacion se mueve un puntero 
   // se genera una pila de informacion 
   // si malloc no tiene memoria malloc devuelve NULL
   alumno_t alumno = Crear_Instancia();
   alumno_t alumno = malloc(sizeof(struct alumno_s));
   // malloc reserva un bloque de memoria dinamica 
   // esta funcion obliga al usuario a utilizar memoria dinamica 
   // sizeof me da la cantidad de bytes de la estructura 
   // malloc retorna un puntero 
   // alumno sera un puntero a la estrutura alumno_s, alumno almacena la direc de memoria 
   // que pasa si no hay memoria?
   if (alumno != NULL) //si alumno es distinto de null hay memoria y le asigno a cada campo su valor
   {
      // guardo en el campo DNI el documento
      alumno->DNI = DNI; 
      // STRNCPY es una funcion que copia el valor 'apellido' en el campo apellido de la estructura
      // el ultimo argumento indica el tamaño de los caracteres a copiar 
      // si name es mayor que sizeof --> trunca el nombre 
      strncpy(alumno->apellido,apellido,sizeof(alumno->apellido)-1);
      strncpy(alumno->nombre,name,sizeof(alumno->nombre)-1);
   }
   return alumno; //si se puede crear el alumno retorna !=null
}
 
/* === Public function implementation ============================================================================== */

int Serializar_Alumno(alumno_t alumno,char chain[],uint32_t espacio){
   int posicion=0;
   chain[0]='{';  
   chain[posicion++]; 
   int ocupado=1;
   espacio=espacio-1; 
   /** @brief Cant_Caracteres recibe la cantidad de caracteres escritos si es que se escribio la cadena*/
   int Cant_caracteres = Serialize_chain("name",alumno->nombre,chain,espacio,posicion); 
   if (Cant_caracteres==-1)
   {
      return -1;
   }
   posicion= posicion + Cant_caracteres;
   ocupado = ocupado + Cant_caracteres;
   espacio=espacio-Cant_caracteres;
   Cant_caracteres=Serialize_chain("apellido",alumno->apellido,chain,espacio,posicion);
   if (Cant_caracteres==-1)
   {
      return -1;
   }
   posicion+=Cant_caracteres;
   ocupado += Cant_caracteres;
   espacio=espacio-Cant_caracteres;
   Cant_caracteres=Serialize_chain_dni("DNI",alumno->DNI,chain,espacio,posicion);
   if (Cant_caracteres==-1)
   {
      return -1;
   }
   chain[posicion+Cant_caracteres-1]='}';
   ocupado += Cant_caracteres;
   return ocupado; 
}
/* === End of documentation ======================================================================================== */
