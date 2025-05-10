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

/** @file main.c
 ** @brief Código fuente del modulo alumno  
 **/

/* === Headers files inclusions ==================================================================================== */
#include "alumno.h"
#include <stdio.h>
#include <stdint.h>
/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */
/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */
/** @brief Funcion para serializar el nombre
 *  @param campo indica el campo de la estructura 
 *  @param valor indica valor del campo 
 *  @param chain es la cadena que se va a escribir
 *  @param espacio es el espacio que queda para escibir en la cadena  
 *  @param posicion es la posicion de la cadena que se escribe
 */
int Serialize_chain(char campo[],const char valor[],char chain[],uint32_t espacio,int posicion){
    /**Retorna la cantidad de caracteres que escribio si la cadena tiene el tamaño para hacerlo
     * en caso de no ser asi retorna NULL
    */
   //printf("Entro en la funcion Serialize_chain\n");
   // espacio = sizeof(chain);
   return snprintf(chain+posicion,espacio,"\"%s\":\"%s\",",campo,valor); 
   //chain es la cadena donde se escribira 
   //espacio es el limite de la caracteres en la cadena 
   //"\"%s\":\"%s\" el primero indica el campo y el segundo el valor 
   
   /** @brief Funcion para serializar el DNI + APELLIDO&NOMBBRE
 *  @param campo indica el campo de la estructura 
 *  @param valor indica valor del campo 
 *  @param chain es la cadena que se va a escribir
 *  @param espacio es el espacio que queda para escibir en la cadena  
 *  @param posicion es la posicion de la cadena que se escribe
 */
}
int Serialize_chain_dni(char campo[], uint32_t valor,char chain[],uint32_t espacio,int posicion)
{
    printf("Entro a la funcion que cargara el DNI:\n ");
    return snprintf(chain+posicion,espacio,"\"%s\":%u,",campo,valor); 
}
/* === Public function implementation ============================================================================== */
/** @brief Funcion para Serializar los campos de una estructura
 * @param alumno es el nombre del struct
 * @param chain es la cadena a escribir 
 * @param espacio es la longitud de la cadena 
 */
int Serializar(alumno_t alumno,char chain[],uint32_t espacio){
    //printf("Arranco la funcion Serializar\n");
    printf("El espacio de la cadena es: %i\n",espacio);
    int posicion=0;
    chain[0]='{';  //el primer elemento de la cadena es una llave del formato 
    chain[posicion++]; /**La cadena se coloca en la posicion despues de { */
    //printf("Se escribio una llave y se movio de lugar la cadena: %s , %i\n",chain,posicion);
    int ocupado=1;
    espacio=espacio-1; /** El tamaño de la cadena se reduce en 1 */
    /** @brief Cant_Caracteres recibe la cantidad de caracteres escritos si es que se escribio */
   int Cant_caracteres = Serialize_chain("name",alumno->nombre,chain,espacio,posicion); 
   /** En caso de desbordamiento de la cadena: */
   if (Cant_caracteres<0)
   {
    return -1;
   }
   /** Chain se posiciona en '{ + caracteres escritos' */
   printf("Se escribio el nombre en la cadena y quedo de la forma: %s\n",chain);
   posicion= posicion+Cant_caracteres;
   //chain[posicion++]; //se ubica la posicion de la cadena luego de los caracteres cargados
   //printf("La posicion de la cadena luego del nombre es: %i\n",posicion);
   ocupado = ocupado + Cant_caracteres;
   /**El tamaño de la cadena se reduce debido a los caracteres escritos */
   espacio=espacio-Cant_caracteres;
   printf("el espacio que queda luego de poner el nombre es: %i\n",espacio);
   /**Nuevamente para el campo apellido: */
   Cant_caracteres=Serialize_chain("apellido",alumno->apellido,chain,espacio,posicion);
   printf("Se escribio el apellido y la cadena quedo de la forma: %s\n",chain);
    if (Cant_caracteres<0)
   {
    return -1;
   }
   /** Chain se posiciona en '{ + caracteres escritos' */
   posicion+=Cant_caracteres;
   ocupado += Cant_caracteres;
   /**El tamaño de la cadena se reduce debido a los caracteres escritos */
   espacio=espacio-Cant_caracteres;
   //chain[posicion]='}';
   /**Nuevamente para el campo apellido */
   Cant_caracteres=Serialize_chain_dni("DNI",alumno->DNI,chain,espacio,posicion);
      if (Cant_caracteres<0)
   {
    return -1;
   }
   chain[posicion+Cant_caracteres-1]='}';
   ocupado += Cant_caracteres;
   return ocupado; 
}

/* === End of documentation ======================================================================================== */
