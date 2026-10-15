#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

extern uint32_t _estack, _sidata, _sdata, _edata, _sbss, _ebss;
int main(void);
void Reset_Handler(void);
static void Default_Handler(void) { while (1) {} }

__attribute__((section(".isr_vector"), used))
const uintptr_t vectors[] = {
    (uintptr_t)&_estack, (uintptr_t)Reset_Handler,
    (uintptr_t)Default_Handler, (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler, (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler, 0, 0, 0, 0,
    (uintptr_t)Default_Handler, (uintptr_t)Default_Handler, 0,
    (uintptr_t)Default_Handler, (uintptr_t)Default_Handler
};

void Reset_Handler(void) {
    for (uint32_t *dst = &_sdata, *src = &_sidata; dst < &_edata; ) *dst++ = *src++;
    for (uint32_t *dst = &_sbss; dst < &_ebss; ) *dst++ = 0;
    (void)main();
    while (1) {}
}

static __attribute__((noinline)) void delay(void) {
    for (volatile uint32_t i = 0; i < 800000u; ++i) {}
}

int main(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    while (1) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); // D2, PN0
        delay();
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
        delay();
    }
}
