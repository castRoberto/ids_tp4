/************************************************************************************************
Copyright (c) <year>, <copyright holders>

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

/** \brief GPIO Driver Implementation
 **
 ** Driver para manejar pines GPIO con patron ADT en C.
 **
 ** \addtogroup GPIO GPIO Driver
 ** \brief Driver para manejar pines GPIO con patron ADT en C.
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "gpio.h"

/* === Macros definitions ====================================================================== */

#define USE_DYNAMIC_MEM

/**
 * @brief Cantidad máxima de instancias de GPIO que se pueden crear
 *
 * Cuando se usa memoria estática, esta constante define la cantidad
 * máxima de instancias que se pueden crear. Si se usa memoria dinámica @ref USE_DYNAMIC_MEM,
 * esta constante no tiene efecto.
 */
#ifndef GPIO_MAX_INSTANCES
#define GPIO_MAX_INSTANCES 10
#endif

/* === Private data type declarations ========================================================== */

/**
 * @brief Estructura con los atributos de un GPIO
 */
struct gpio_s {
    uint8_t port; /**< Puerto del GPIO */
    uint8_t bit;  /**< Bit del GPIO */
    bool output;  /**< true si es salida, false si es entrada */
#ifndef USE_DYNAMIC_MEM
    bool used; /**< true si la instancia está en uso, false si está libre */
#endif
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

#ifndef USE_DYNAMIC_MEM
static gpio_t allocateInstance() {
    static struct gpio_s instances[GPIO_MAX_INSTANCES] = {0};

    gpio_t result = NULL;
    for (int index = 0; index < GPIO_MAX_INSTANCES; index++) {
        if (!instances[index].used) {
            result = &instances[index].used;
            result->used = true;
            break;
        }
    }
    return result;
}
#endif

/* === Public function implementation ========================================================== */

gpio_t gpioCreate(uint8_t puerto, uint8_t bit) {
#ifdef USE_DYNAMIC_MEM
    gpio_t self = malloc(sizeof(struct gpio_s));
#else
    gpio_t self = allocateInstance();
#endif
    if (self) {
        self->port = puerto;
        self->bit = bit;
        self->output = false;
    }
    return self;
}

void gpioSetOutput(gpio_t self, bool output) {
    if (self) {
        self->output = output;
        // HAL_GPIO_SET_OUTPUT(self->port, self->bit);
        printf("GPIO: Configurado puerto %d, bit %d como %s\n", self->port, self->bit,
               output ? "salida" : "entrada");
    }
}

void gpioSetState(gpio_t self, bool state) {
    if (self && self->output) {
        // HAL_GPIO_SET_STATE(self->port, self->bit, state);
        printf("GPIO: Puerto %d, bit %d seteado en %d\n", self->port, self->bit, state);
    }
}

bool gpioGetState(gpio_t self) {
    bool state = false;
    if (self) {
        state = true; // HAL_GPIO_GET_STATE(self->port, self->bit);
        printf("GPIO: Puerto %d, bit %d leido en %d\n", self->port, self->bit, state);
    }
    return state;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
