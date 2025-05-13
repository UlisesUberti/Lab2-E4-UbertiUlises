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
// Este archivo representa la clase y el Alumno el objeto

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
// PERMITE DEFINIR POR MAKE antes de tomar el valor definido e el codigo
// Para elegir si utilizo memoria dinamica o estatica deberia agregar una bandera
/* === Private data type declarations ============================================================================== */

/** @struct alumno_s
 * @brief estructura que contiene los datos del alumno
 * @param nombre indica el nombre del alumno(20 caracteres max.)
 * @param apellido indica el apellido del alumno(20 caracteres max.)
 * @param DNI indica el documento del alumno
 */
// la estrucuta se define ahora con la cantidad de bytes que ocupara, entonces no puede cambiarse desde main
struct alumno_s // la estrucutura la declare en el h entonces ahora defino
{
    char name[20];     //!< Nombre del alumno
    char lastname[20]; //!< Apellido del alumno
    uint32_t DNI;      //!< Documento del alumno
#ifndef USAR_MEMORIA_DINAMICA
    bool ocupado;
#endif
};

/* === Private function declarations =============================================================================== */
/* === Private variable definitions ================================================================================ */
static struct alumno_s Arreglo_Alumnos[CANTIDAD_MAXIMA_ALUMNOS] = {0};
// estoy creando un arrglo con 2 estructuras, es decir, dos alumnos distintos
/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */
// Ahora que tengo una arreglo de alumnos, necesito crearlo
static puntero_alumno_s Crear_Arreglo_Alumnos() {
    // Crear_Arreglo_Alumno retorna un puntero
    // AL crear el arreglo le asigno a cada alumno un espacio
    // pero no debo sobrescribir los alumnos dentro del arreglo entonces, debo buscar los espacios vacios dentro
    puntero_alumno_s alumno_s = NULL; // al alumno le asigno NULL, en caso de encontrar espacio le asigno el puntero
    for (int i = 0; i < CANTIDAD_MAXIMA_ALUMNOS; i++) {
        if (!Arreglo_Alumnos[i].ocupado) // si el espacio del alumno i no esta ocupado enotnces
        {
            alumno_s = &Arreglo_Alumnos[i];    // le asigno la direccion correspondiente al esapcio vacio
            Arreglo_Alumnos[i].ocupado = true; // marco ahora como ocupado el espacio
            printf("Este Espacio no estaba ocupado, cargando alumno en posicion %i\n", i);
            return alumno_s;
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
int Serialize_chain(char campo[], const char valor[], char chain[], uint32_t espacio, int posicion) {
    if (sizeof(&valor) > espacio) {
        return -1;
    }
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
    /**Condicional si resta espacio suficiente para DNI y la ultima llave */
    if (sizeof(&valor) + 1 > espacio) {
        return -1;
    }
    return snprintf(chain + posicion, espacio, "\"%s\":%u,", campo, valor);
}

puntero_alumno_s Crear_Alumno(char apellido[], char name[], uint32_t documento) {
    // Esta funcion se encarga de Crear el puntero que apuntara a la estructura del alumno en memoria dinamica
    //  alumno_t es la direccion del incio de un bloque de memoria
    //  para obtener y asignar esta direc de memoria utilizo malloc, para que el compilador me de los bytes
    //   la memoria tiene 3 partes --> las variables estaticas globales
    //--> la memoria restante tiene 2 señaladores
    //   en una subrutina se guarda informacion se mueve un puntero
    //   se genera una pila de informacion
    //   si malloc no tiene memoria malloc devuelve NULL
    //  la funcion tiene como argumento el nombre, el apellido y el documento
    // puntero_alumno_s alumno = malloc(sizeof(struct alumno_s));
    // alumno es el puntero al struct alumno_s, alumno almacena la direc de memoria para almacenar el struct
    // el tamaño de alumno_s se corresponde con los campos del struct alumno_s
    // malloc reserva un bloque de memoria dinamica
    // esta funcion obliga al usuario a utilizar memoria dinamica
    // sizeof me da la cantidad de bytes de la estructura
    // malloc retorna un puntero
    // alumno sera un puntero a la estrutura alumno_s, alumno almacena la direc de memoria
    // que pasa si no hay memoria?
    // Un puntero NULL no apunta a ninguna direc de memoria
    puntero_alumno_s alumno = Crear_Arreglo_Alumnos();
    if (alumno != NULL) // si alumno es distinto de null hay memoria y le asigno a cada campo su valor
    {
        printf("Se encontro espacio en el arreglo ahora se cargaran los datos del alumno\n");
        // guardo en el campo DNI el documento
        alumno->DNI = documento;
        // STRNCPY es una funcion que copia el valor 'apellido' en el campo apellido de la estructura
        // el ultimo argumento indica el tamaño de los caracteres a copiar
        // si name es mayor que sizeof --> trunca el nombre
        strncpy(alumno->lastname, apellido, sizeof(alumno->lastname) - 1);
        strncpy(alumno->name, name, sizeof(alumno->name) - 1);
    }
    return alumno; // si se puede crear el alumno retorna !=null
}

/* === Public function implementation ============================================================================== */

int Serializar_Alumno(puntero_alumno_s alumno, char chain[], uint32_t espacio) {
    printf("Ahora se agarro el puntero de alumno y se serializan sus datos\n");
    int posicion = 0;
    chain[0] = '{';
    chain[posicion++];
    int ocupado = 1;
    espacio = espacio - 1;
    /** @brief Cant_Caracteres recibe la cantidad de caracteres escritos si es que se escribio la cadena*/
    int Cant_caracteres = Serialize_chain("name", alumno->name, chain, espacio, posicion);
    if (Cant_caracteres == -1) {
        return -1;
    }
    posicion = posicion + Cant_caracteres;
    ocupado = ocupado + Cant_caracteres;
    espacio = espacio - Cant_caracteres;
    Cant_caracteres = Serialize_chain("apellido", alumno->lastname, chain, espacio, posicion);
    if (Cant_caracteres == -1) {
        return -1;
    }
    posicion += Cant_caracteres;
    ocupado += Cant_caracteres;
    espacio = espacio - Cant_caracteres;
    Cant_caracteres = Serialize_chain_dni("DNI", alumno->DNI, chain, espacio, posicion);
    if (Cant_caracteres == -1) {
        return -1;
    }
    chain[posicion + Cant_caracteres - 1] = '}';
    ocupado += Cant_caracteres;
    return ocupado;
}
/* === End of documentation ======================================================================================== */
