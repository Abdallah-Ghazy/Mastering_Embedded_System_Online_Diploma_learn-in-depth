#include <stdint.h>

typedef volatile uint32_t vint32;

#define HIGH 1
#define LOW  0

#define RCC_BASE       0x40021000
#define PORTA_BASE     0x40010800

#define RCC_APB2ENR    *((volatile uint32_t*)(RCC_BASE + 0x18))
#define GPIOA_CRH      *((volatile uint32_t*)(PORTA_BASE + 0x04))
#define GPIOA_ODR      *((volatile uint32_t*)(PORTA_BASE + 0x0C))

#define RCC_APB2ENR_IOPAEN (1 << 2)

// Union for accessing GPIOA ODR register
typedef union {
    vint32 allFields;
    struct {
        vint32 reserved : 13;
        vint32 pin13 : 1;
    } pin;
} R_ODR_t;

unsigned char GVariables[3] ={1,2,3};
unsigned char const CGVariables[3] ={1,2,3};

int main(void) {
    // Pointer to GPIOA ODR register
    volatile R_ODR_t *R_ODR = (volatile R_ODR_t*) &GPIOA_ODR;

    // Enable GPIOA clock
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Configure PA13 as output push-pull
    GPIOA_CRH &= 0xff0fffff;  // Clear mode bits for PA13
    GPIOA_CRH |= 0x00200000;  // Set PA13 to output mode, max speed 2 MHz

    while (1) {
        // Set PA13 high
        R_ODR->pin.pin13 = HIGH;
        for (volatile int i = 0; i < 5000; i++);  // Delay

        // Set PA13 low
        R_ODR->pin.pin13 = LOW;
        for (volatile int i = 0; i < 5000; i++);  // Delay
    }

    return 0;
}
