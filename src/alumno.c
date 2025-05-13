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

#ifndef CANTIDAD_MAXIMA_ALUMNOS
#define CANTIDAD_MAXIMA_ALUMNOS 2
#endif

/* === Private data type declarations ============================================================================== */

/** @struct alumno_s
 * @brief estructura que contiene los datos del alumno
 * @param nombre indica el nombre del alumno(20 caracteres max.)
 * @param apellido indica el apellido del alumno(20 caracteres max.)
 * @param DNI indica el documento del alumno
 */
struct alumno_s {
    char name[20];
    char lastname[20];
    uint32_t DNI;
    bool ocupado;
};

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/** @brief Estructura arreglo de estructuras con cantidad maxima definida en make*/
static struct alumno_s Arreglo_Alumnos[CANTIDAD_MAXIMA_ALUMNOS] = {0};

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/** @brief Funcion que busca en un arreglo de estructuras en la memoria de posicion fija
 * @return el puntero de la posicion de la estructura
 */
static puntero_alumno_s Crear_Arreglo_Alumnos() {

    // Asingo el valor NULL al puntero por defecto
    puntero_alumno_s alumno_s = NULL;

    // Busco una posicion que no se encuentre ocupada por una estructura
    for (int i = 0; i < CANTIDAD_MAXIMA_ALUMNOS; i++) {
        if (!Arreglo_Alumnos[i].ocupado) {
            alumno_s = &Arreglo_Alumnos[i];
            // Asigno como ocupado en caso de encontrar espacio
            Arreglo_Alumnos[i].ocupado = true;
            // retorno el puntero de la ubicacion de la estructura
            return alumno_s;
        }
    }
}

/** @brief Funcion que crea la estructura alumno en memoria Estatica
 * @param apellido indica el valor del campo lastname de la estrucutra
 * @param name indica el valor del campo name de la estrucutra
 * @param documento indica el valor del cambo DNI de la estrucutra
 * @return alumnno, puntero de la estructura alumno_s
 */
puntero_alumno_s Crear_Alumno_MEM_Estatica(char apellido[], char name[], uint32_t documento) {

    // Le asigno un arreglo de alumnos en la memoria, fijo y con una cantidad limite
    puntero_alumno_s alumno = Crear_Arreglo_Alumnos();

    // En caso de haber espacio, le asigno a los campos de la estructura su valor correspondiente
    if (alumno != NULL) {
        alumno->DNI = documento;
        strncpy(alumno->lastname, apellido, sizeof(alumno->lastname) - 1);
        strncpy(alumno->name, name, sizeof(alumno->name) - 1);
    }

    // Retorno el puntero de la estructura alumno_s
    return alumno;
}

/** @brief Funcion para serializar el nombre y apellido
 *  @param campo indica el campo de la estructura
 *  @param valor indica valor del campo
 *  @param chain es la cadena que se va a escribir
 *  @param espacio es el espacio que queda para escibir en la cadena
 *  @param posicion es la posicion de la cadena que se escribe
 *  @return -1 si sizeof(&valor)>espacio o snprintf()
 */
int Serialize_chain(char campo[], const char valor[], char chain[], uint32_t espacio, int posicion) {

    // Detecta si hay espacio en la cadena para poder escribir
    if (sizeof(&valor) > espacio) {
        return -1;
    }

    // Retorna la cantidad de caracteres escritos en total en la cadena
    return snprintf(chain + posicion, espacio, "\"%s\":\"%s\",", campo, valor);
}

/** @brief Funcion para serializar el DNI + APELLIDO&NOMBBRE
 *  @param campo indica el campo de la estructura
 *  @param valor indica valor del campo
 *  @param chain es la cadena que se va a escribir
 *  @param espacio es el espacio que queda para escibir en la cadena
 *  @param posicion es la posicion de la cadena que se escribe
 *  @return -1 si sizeof(&valor)>espacio o snprintf
 */
int Serialize_chain_dni(char campo[], uint32_t valor, char chain[], uint32_t espacio, int posicion) {

    // Detecta si hay espacio en la cadena para poder escribir
    if (sizeof(&valor) + 1 > espacio) {
        return -1;
    }

    // Retorna la cantidad de caracteres escritos en total en la cadena
    return snprintf(chain + posicion, espacio, "\"%s\":%u,", campo, valor);
}

/* === Public function implementation ============================================================================== */

int Serializar_Alumno(puntero_alumno_s alumno, char chain[], uint32_t espacio) {

    // Definicion de variables a utilizar y comienzo de formato JSON
    int posicion = 0;
    chain[0] = '{';
    chain[posicion++];
    int ocupado = 1;
    espacio = espacio - 1;

    // Serializo el nombre de la estructura alumno
    int Cant_caracteres = Serialize_chain("name", alumno->name, chain, espacio, posicion);
    // Encaso de desbordamiento de la cadena
    if (Cant_caracteres == -1) {
        return -1;
    }

    // Modifico las variables de control
    posicion = posicion + Cant_caracteres;
    ocupado = ocupado + Cant_caracteres;
    espacio = espacio - Cant_caracteres;

    // Serializo el apellido de la estructura alumno
    Cant_caracteres = Serialize_chain("apellido", alumno->lastname, chain, espacio, posicion);
    // En caso de desbordamiento de la cadena
    if (Cant_caracteres == -1) {
        return -1;
    }

    // Modifico las variables de control
    posicion += Cant_caracteres;
    ocupado += Cant_caracteres;
    espacio = espacio - Cant_caracteres;

    // Serializo el DNI de la estructura alumno
    Cant_caracteres = Serialize_chain_dni("DNI", alumno->DNI, chain, espacio, posicion);
    // Encaso de desbordamiento de la cadena
    if (Cant_caracteres == -1) {
        return -1;
    }

    // Modifico las variables de control
    chain[posicion + Cant_caracteres - 1] = '}';
    ocupado += Cant_caracteres;

    // Retorna el espacio ocupado de la cadena
    return ocupado;
}

/* === End of documentation ======================================================================================== */
