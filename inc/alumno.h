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

#ifndef ALUMNO_H_
#define ALUMNO_H_

/** @file alumno.h
 ** @brief Codigo cabecera para el modulo alumno, incluye solo declaraciones
 **/

/* === Headers files inclusions ==================================================================================== */
#include <stdint.h>
/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/* === Public variable declarations ================================================================================ */

/** @struct alumno_s
 * @brief estructura que contiene los datos del alumno
 * @param nombre indica el nombre del alumno(20 caracteres max.)
 * @param apellido  indica el apellido del alumno(20 caracteres max.)
 * @param DNI indica el documento del alumno 
*/
typedef struct alumno_s 
{
    char nombre[20]; //!<Nombre del alumno
    char apellido[20]; //!<Apellido del alumno
    uint32_t DNI; //!<Documento del alumno
} const * alumno_t; //!< Puntero a la estructura alumno_s; 

/* === Public function declarations ================================================================================ */
/** @brief Funcion Serializar 
 * @param  alumno Puntero a la estrucutura alumno
 * @param chain cadena de datos del alumno 
 * @param espacio tamaño que ocupan los datos dentro de la cadena 
 * @return int  retorna -1 si no hay espacio o la cant de caracteres ocupados 
 */
int Serializar(alumno_t alumno, char chain[],uint32_t espacio);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ALUMNO_H_ */
