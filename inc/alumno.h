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
typedef struct alumno_s * puntero_alumno_s;
// puntero_alumno_s es un tipo de dato que refiere a un puntero de la estructura alumno_s
// entonces si pongo puntero_alumno_s A; A es el puntero a alumno_s
// estrucutra alumno_s y puntero a la esstructura alumno_t, alumno_t ocupa 4 bytes
// alumno --> objeto
/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/** @brief Funcion Serializar
 * @param chain cadena de datos del alumno
 * @param espacio tamaño que ocupan los datos dentro de la cadena
 * @return int  retorna -1 si no hay espacio o la cant de caracteres ocupados
 */
int Serializar_Alumno(puntero_alumno_s alumno, char chain[], uint32_t espacio);

/** @brief Funcion CrearAlumno
 * @param apellido cadena del apellido del alumno
 * @param name cadena del nombre del alumno
 * @param DNI documento del alumno
 * @return alumno_t  retorna puntero a estructura para almacenar los datos o NULL si no se pudo crear
 */
puntero_alumno_s Crear_Alumno_MEM_Estatica(char apellido[], char name[], uint32_t DNI);
// creo el alumno y retorno el puntero del alumno
// Alumno es la clase y crear el metodo

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* ALUMNO_H_ */
