typedef unsigned int uint32_t;
typedef unsigned int uintptr_t;

#define REG32(addr) (*(volatile uint32_t *)(addr))
#define SYSCTL_RCGCGPIO REG32(0x400FE608u)
#define SYSCTL_PRGPIO   REG32(0x400FEA08u)
#define GPIO_PORTN_DATA REG32(0x400643FCu)
#define GPIO_PORTN_DIR  REG32(0x40064400u)
#define GPIO_PORTN_DEN  REG32(0x4006451Cu)

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
    SYSCTL_RCGCGPIO |= (1u << 12); // Port N clock
    while ((SYSCTL_PRGPIO & (1u << 12)) == 0) {}
    GPIO_PORTN_DIR |= 1u;
    GPIO_PORTN_DEN |= 1u;
    while (1) {
        GPIO_PORTN_DATA ^= 1u; // D2, PN0
        delay();
    }
}
