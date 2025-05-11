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
/* === Macros definitions ========================================================================================== */
/* === Private data type declarations ============================================================================== */
/* === Private function declarations =============================================================================== */
/* === Private variable definitions ================================================================================ */
/* === Public variable definitions ================================================================================= */
/* === Private function definitions ================================================================================ */

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
/* === Public function implementation ============================================================================== */

int Serializar(alumno_t alumno,char chain[],uint32_t espacio){
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
