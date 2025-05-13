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
 * @brief Código fuente del archivo principal
 * @author Uberti, Ulises Leandro
 * */

/* === Headers files inclusions ==================================================================================== */
#include "alumno.h"
#include <stdint.h>
#include <stdio.h>
/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */
/* === Private function declarations =============================================================================== */
/* === Private variable definitions ================================================================================ */
/* === Public variable definitions ================================================================================= */
/* === Private function definitions ================================================================================ */

/** @brief Funcion Principal
 * @return 0
 */
int main(void) {
    char chain1[60], chain2[62], chain3[60];
    int ocupado_chain;
    // Busco espacio en memoria dinamica para crear el alumno
    puntero_alumno_s A = Crear_Alumno("Uberti", "Ulises Leandro", 44476062);
    puntero_alumno_s B = Crear_Alumno("Leandro", "Fernandez", 44062376);
    puntero_alumno_s C = Crear_Alumno("Esteban", "uBERTI", 23555777);
    // En caso de no tener espacio en memoria dinamica el puntero a la estructura
    // A es el puntero que retorna Crear Alumno
    //  Si se creo un alumno en la direc de memoria estaran sus datos
    //  Si A es null entonces no se pudo crear
    if (A == NULL) {
        printf("Error al Crear Alumno\n");
        return 0;
    } else {
        ocupado_chain = Serializar_Alumno(A, chain2, sizeof(chain2));
        if (ocupado_chain > 0) {
            printf("Serializado: %s\n", chain2);
        } else {
            printf("Error al Serializar / CADENA INSUFICIENTE\n");
        }
    }

    if (B == NULL) {
        printf("Error al Crear Alumno\n");
        return 0;
    } else {
        ocupado_chain = Serializar_Alumno(B, chain1, sizeof(chain1));
        if (ocupado_chain > 0) {
            printf("Serializado: %s\n", chain1);
        } else {
            printf("Error al Serializar / CADENA INSUFICIENTE\n");
        }
    }

    if (C == NULL) {
        printf("Error al Crear Alumno\n");
        return 0;
    } else {
        ocupado_chain = Serializar_Alumno(C, chain3, sizeof(chain3));
        if (ocupado_chain > 0) {
            printf("Serializado: %s\n", chain3);
        } else {
            printf("Error al Serializar / CADENA INSUFICIENTE\n");
        }
    }

    return 0;
}
/* === Public function implementation ============================================================================== */

/* === End of documentation ======================================================================================== */
