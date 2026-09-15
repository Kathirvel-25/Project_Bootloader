/*
 * Nucleo_Driver.h
 *
 *  Created on: Sep 14, 2026
 *      Author: kathir
 */

#ifndef NUCLEO_DRIVER_H_
#define NUCLEO_DRIVER_H_
#include "stdint.h"

#define NVIC_BASEADDR              0xE000E100U
#define SYSCFG_BASEADDR            0x40013800U
#define EXTI_BASEADDR              0x40013C00U

/*BUS Base  Address*/
#define APB1PERIPH_BASEADDR          0x40000000U
#define APB2PERIPH_BASEADDR          0x40010000U
#define AHB1PERIPH_BASEADDR         0x40020000U


/*GPIO Base Address*/
#define GPIOA_BASEADDR                  0x40020000U
#define GPIOB_BASEADDR                  0x40020400U
#define GPIOC_BASEADDR                  0x40020800U

/*RCC Base Address*/
#define RCC_BASE_ADDR                   0x40023800U

/*SPI Base Address*/
#define SPI1_BASEADDR                    0x40013000U

/*NVIC Base Address*/
#define NVIC_BASEADDR                   0xE000E100U

/*USART Base Address*/
#define UART1_BASEADDR             0x40011000U
#define UART6_BASEADDR             0x40011400U
#define UART2_BASEADDR             0x40004400U

/*ADC1 Base Address*/
#define ADC1_BASEADDDR               0x40012000U


/*ADC1 Base Address*/
#define I2C1_BASEADDR           0x40005400U
#define I2C2_BASEADDR           0x40005800U

/*SCB BASDE ADDR*/
#define SCB_BASE_ADDR         0xE000ED00UL

/*TIM BASDE ADDR*/
#define TIM2_BASEADDR          0x40000000U


/*NVIC BASDE ADDR*/
#define NVIC_ISER_BASE         0xE000E100U
#define NVIC_ICER_BASE         0xE000E180U
#define NVIC_ISPR_BASE         0xE000E200U
#define NVIC_ICPR_BASE         0xE000E280U
#define NVIC_IABR_BASE         0xE000E300U
#define NVIC_IPR_BASE          0xE000E400U



/* FLASH INTERFACE BASE ADDR*/
#define FLASH_BASE_ADDR    0x40023C00U






/*GPIO Related Registers*/
typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;

}GPIO_RegDef;



/*RCC Related Registers*/
typedef struct{
   volatile	uint32_t CR;
   volatile	uint32_t PLLCFGR;
   volatile	uint32_t CFGR;
   volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
   volatile uint32_t AHB2RSTR;
   volatile uint32_t RESERVED1;
   volatile uint32_t RESERVED2;
   volatile uint32_t APB1RSTR;
   volatile uint32_t APB2RSTR;
   volatile uint32_t RESERVED3;
   volatile uint32_t RESERVED4;
   volatile uint32_t AHB1ENR;
   volatile uint32_t AHB2ENR;
   volatile uint32_t RESERVED5;
    volatile uint32_t RESERVED6; // 1 table
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED7;
	volatile uint32_t RESERVED8;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t RESERVED9;
	volatile uint32_t RESERVED10;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED11;
	volatile uint32_t RESERVED12;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED13;
	volatile uint32_t RESERVED14;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t DCKCFGR;

}RCC_RegDef;


/*EXTI Related Registers*/
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_RegDef;



/*SPI Related Registers*/
typedef struct
{
	volatile uint32_t  CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;

}SPI_RegDef;



/*FLASH Related Registers*/
typedef struct
{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t OPTCR;

}FLASH_RegDef;



/*SCB Related Register*/
typedef struct
{
	volatile uint32_t CPUID;
	volatile uint32_t ICSR;
	volatile uint32_t VTOR;
	volatile uint32_t AIRCR;
	volatile uint32_t SCR;
	volatile uint32_t CCR;
	volatile uint32_t SHPR1;
	volatile uint32_t SHPR2;
	volatile uint32_t SHPR3;
	volatile uint32_t SHPR4;
	volatile uint32_t SHCSR;
}SCB_RegDef;



/*I2C Related Registers*/
typedef struct{

	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;

}I2C_RegDef;



/*TIM Related Registers*/
typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RESERVED;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t RESERVE;
	volatile uint32_t DCR;
	volatile uint32_t DMR;
	volatile uint32_t OR;

}TIM_RegDef;




/*ADC1 Related Register*/
typedef struct {

	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t  SMPR2;
	volatile uint32_t  JOFR1;
	volatile uint32_t JOFR2;
	volatile uint32_t JOFR3;
	volatile uint32_t JOFR4;
	volatile uint32_t  HTR;
	volatile uint32_t  LTR;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t JSQR;
	volatile uint32_t  JDR1;
	volatile uint32_t JDR2;
	volatile uint32_t JDR3;
	volatile uint32_t JDR4;
	volatile uint32_t DR;
}ADC1_RegDef;




/*SYSCFG Related Registers*/
typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTi[4];
	volatile uint32_t R1;
	volatile uint32_t R2;
	volatile uint32_t CMPCR;
	volatile uint32_t R3;
	volatile uint32_t R4;
	volatile uint32_t CFGR;

}SYSCFG_RegDef;




/*USART Related Register */
typedef struct {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}UART_RegDef;




/*GPIO Mapped to the Register*/
#define GPIOA   ((GPIO_RegDef*)GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef*)GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef*)GPIOC_BASEADDR)

/*RCC Mapped to Register*/
#define RCC     ((RCC_RegDef*)RCC_BASE_ADDR)

/*RCC Mapped to Register*/
#define UART1   ((UART_RegDef*)UART1_BASEADDR)
#define UART2   ((UART_RegDef*)UART2_BASEADDR)


/*SPI Mapped to the Register*/
#define SPI1          ((SPI_RegDef*)SPI1_BASEADDR)

/*I2C Mapped to the Register*/
#define I2C1     ((I2C_RegDef*)I2C1_BASEADDR)
#define I2C2     ((I2C_RegDef*)I2C2_BASEADDR)


/*NVIC Mapped Register */
#define NVIC_ISERX_BASE       ((volatile uint32_t*)NVIC_BASEADDR)
#define NVIC_IPRX_BASE        ((volatile uint8_t*)0xE000E400U)

/*FLASH Mapped to the Register*/
#define FLASH      ((FLASH_RegDef *)FLASH_BASE_ADDR)

/* SCB Mapped to the Register*/
#define SCB        ((SCB_RegDef*)SCB_BASE_ADDR)



/*TIM Mapped to the Register*/
#define TIM2                  ((TIM_RegDef*)TIM2_BASEADDR)


/* SYSCFG Mapped to the Register*/
#define SYS_CFG        ((SYSCFG_RegDef*)SYSCFG_BASEADDR)


/*EXTI Mapped to the Register*/
#define EXTI           ((EXTI_RegDef*)EXTI_BASEADDR)





#define NVIC_ISER   ((volatile uint32_t *)NVIC_ISER_BASE)
#define NVIC_ICER   ((volatile uint32_t *)NVIC_ICER_BASE)
#define NVIC_ISPR   ((volatile uint32_t *)NVIC_ISPR_BASE)
#define NVIC_ICPR   ((volatile uint32_t *)NVIC_ICPR_BASE)
#define NVIC_IABR   ((volatile uint32_t *)NVIC_IABR_BASE)
#define NVIC_IPR    ((volatile uint32_t *)NVIC_IPR_BASE)



/* =========================================================
 * Core register functions
 * ========================================================= */
static inline void disable_interrupts(void)
{
	__asm volatile ("cpsid i" ::: "memory");
}

static inline void enable_interrupts(void)
{
	__asm volatile ("cpsie i" ::: "memory");
}

static inline void set_msp(uint32_t val)
{
	__asm volatile ("msr msp, %0" : : "r" (val) : "memory");
}

static inline void data_sync_barrier(void)
{
     __asm volatile ("dsb" ::: "memory");
}

static inline void instruction_sync_barrier(void)
{
	__asm volatile ("isb" ::: "memory");
}



#endif /* NUCLEO_DRIVER_H_ */
