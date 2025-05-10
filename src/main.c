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
 ** @brief Código fuente en lenguaje C del archivo principal 
 **/

/* === Headers files inclusions ==================================================================================== */
#include "alumno.h"
#include <stdint.h>
#include <stdio.h>
/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */
/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */
/** Definicion de una dato tipo estructura con mis datos, dato declarado en alumno.h */
static const struct alumno_s Mis_datos = {
    .nombre="Ulises Leandro",
    .apellido="Uberti",
    .DNI= 4436062,
};
/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */
int main(void){
    char chain[50];
    int ocupado_chain;
    printf("Size of main chain's");
    ocupado_chain=Serializar(&Mis_datos,chain,sizeof(chain));
    printf("Los datos del alumno ocupan: %i\n",ocupado_chain);
    if (ocupado_chain>0)
    {
        printf("Serializado: %s\n",chain);
    }
    else
    {
        printf("Error al Serializar");
    }
    return 0;
}
/* === Public function implementation ============================================================================== */

/* === End of documentation ======================================================================================== */
