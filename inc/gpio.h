#include <stdint.h>
#include <stdbool.h>

/************************************************************************************************
Copyright (c) 2023, Esteban Volentini <evolentini@herrera.unt.edu.ar>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#ifndef GPIO_H
#define GPIO_H

/** @file gpio.h
 ** @brief Definicion de la interfaz del driver de GPIO
 **/

/* === Headers files inclusions ================================================================ */

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/**
 * @brief Puntero a estructura que representa un GPIO
 */
typedef struct gpio_s * gpio_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Crea una nueva instancia de un objeto GPIO
 *
 * @param puerto Puerto del GPIO
 * @param bit Bit del GPIO
 * @return int Valor de retorno, cero si esta todo bien, negativo si hay un error
 */
gpio_t gpioCreate(uint8_t puerto, uint8_t bit);

/**
 * @brief Configura la dirección del GPIO
 *
 * @param gpio Instancia del GPIO (devuelta por \ref gpioCreate "gpioCreate")
 * @param output true para salida, false para entrada
 */
void gpioSetOutput(gpio_t gpio, bool output);

/**
 * @brief Configura el estado del GPIO
 *
 * @param gpio Instancia del GPIO (devuelta por \ref gpioCreate "gpioCreate")
 * @param state true para alto, false para bajo
 */
void gpioSetState(gpio_t gpio, bool state);

/**
 * @brief Obtiene el estado del GPIO
 *
 * @param gpio Instancia del GPIO (devuelta por \ref gpioCreate "gpioCreate")
 * @return true si el estado es alto, false si es bajo
 */
bool gpioGetState(gpio_t gpio);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */
