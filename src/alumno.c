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
 *  @return -1 si sizeof(&valor)>espacio o snprintf()
 */
int Serialize_chain(char campo[],const char valor[],char chain[],uint32_t espacio,int posicion){
    /**Retorna la cantidad de caracteres que escribio si la cadena tiene el tamaño para hacerlo
     * en caso de no ser asi retorna -1
    */
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
/* === Public function implementation ============================================================================== */
/** @brief Funcion para Serializar los campos de una estructura
 * @param alumno es el nombre del struct
 * @param chain es la cadena a escribir 
 * @param espacio es la longitud de la cadena 
 * @return Caracteres ocupados si la cadena fue suficiente o -1 si la cadena fue insuficiente 
 */
int Serializar(alumno_t alumno,char chain[],uint32_t espacio){
    int posicion=0;
    /**Se coloca { al inicio para dar formato JSON */
    chain[0]='{';  
    /**La cadena se coloca en la posicion despues de { */
    chain[posicion++]; 
    /**Ocupado indica cuantos caracteres se van colocando en la cadena */
    int ocupado=1;
    /** El tamaño de la cadena se reduce en 1 */
    espacio=espacio-1; 
    /** @brief Cant_Caracteres recibe la cantidad de caracteres escritos si es que se escribio */
   int Cant_caracteres = Serialize_chain("name",alumno->nombre,chain,espacio,posicion); 
    /** En caso de desbordamiento de la cadena: */
   if (Cant_caracteres==-1)
   {
    return -1;
   }
   /**Se mueve la posicion de la cadena, se cambian los caracteres ocupados y se determina el espacio restante */
   posicion= posicion+Cant_caracteres;
   ocupado = ocupado + Cant_caracteres;
   espacio=espacio-Cant_caracteres;
   /**Funcion Serialize_chain para el apellido */
   Cant_caracteres=Serialize_chain("apellido",alumno->apellido,chain,espacio,posicion);
   /** En caso de desbordamiento de la cadena: */
    if (Cant_caracteres==-1)
   {
    return -1;
   }
   posicion+=Cant_caracteres;
   ocupado += Cant_caracteres;
   espacio=espacio-Cant_caracteres;
   /**Funcion Serialize_chain_dni para el documento */
   Cant_caracteres=Serialize_chain_dni("DNI",alumno->DNI,chain,espacio,posicion);
      /** En caso de desbordamiento de la cadena: */

     if (Cant_caracteres==-1)
   {
    return -1;
   }
   /**agrego la ultima } */
   chain[posicion+Cant_caracteres-1]='}';
   ocupado += Cant_caracteres;
   return ocupado; 
}
/* === End of documentation ======================================================================================== */
