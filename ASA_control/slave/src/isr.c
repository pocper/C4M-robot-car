/**
 * @file isr.c
 * @author LiYu87
 * @brief 定義中斷服務常式以支援 ISR 以及 INTERNAL_ISR。
 * @date 2019.06.24
 *
 * Function vectXX() is used for avr-gcc linker intterupt.
 * Function __vectXX_routine()  is used by C4MLIB developper.
 * Function __vectXX_routine1() is for general app developper to use.
 * Both __vectXX_routine and __vectXX_routine1 is weak type, can be overwritted
 * in other files by use ISR and INTERNAL_ISR.
 */

#include "isr.h"

#include <avr/interrupt.h>

/* External Interrupt Request 0 */
void __INT0_vect_routine1() {
    ;
}
void INT0_vect_routine1() __attribute__((weak, alias("__INT0_vect_routine1")));
void __INT0_vect_routine() {
    INT0_vect_routine1();
};
void INT0_vect_routine() __attribute__((weak, alias("__INT0_vect_routine")));
void INT0_vect(void) __attribute__((signal, __INTR_ATTRS));
void INT0_vect(void) {
    INT0_vect_routine();
}

/* External Interrupt Request 1 */
void __INT1_vect_routine1() {
    ;
}
void INT1_vect_routine1() __attribute__((weak, alias("__INT1_vect_routine1")));
void __INT1_vect_routine() {
    INT1_vect_routine1();
};
void INT1_vect_routine() __attribute__((weak, alias("__INT1_vect_routine")));
void INT1_vect(void) __attribute__((signal, __INTR_ATTRS));
void INT1_vect(void) {
    INT1_vect_routine();
}

/* Timer/Counter2 Compare Match A */
void __TIMER2_COMPA_vect_routine1() {
    ;
}
void TIMER2_COMPA_vect_routine1()
    __attribute__((weak, alias("__TIMER2_COMPA_vect_routine1")));
void __TIMER2_COMPA_vect_routine() {
    TIMER2_COMPA_vect_routine1();
};
void TIMER2_COMPA_vect_routine()
    __attribute__((weak, alias("__TIMER2_COMPA_vect_routine")));
void TIMER2_COMPA_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER2_COMPA_vect(void) {
    TIMER2_COMPA_vect_routine();
}

/* Timer/Counter2 Compare Match B */
void __TIMER2_COMPB_vect_routine1() {
	;
}
void TIMER2_COMPB_vect_routine1()
__attribute__((weak, alias("__TIMER2_COMPB_vect_routine1")));
void __TIMER2_COMPB_vect_routine() {
	TIMER2_COMPB_vect_routine1();
};
void TIMER2_COMPB_vect_routine()
__attribute__((weak, alias("__TIMER2_COMPB_vect_routine")));
void TIMER2_COMPB_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER2_COMPB_vect(void) {
	TIMER2_COMPB_vect_routine();
}

/* Timer/Counter2 Overflow */
void __TIMER2_OVF_vect_routine1() {
    ;
}
void TIMER2_OVF_vect_routine1()
    __attribute__((weak, alias("__TIMER2_OVF_vect_routine1")));
void __TIMER2_OVF_vect_routine() {
    TIMER2_OVF_vect_routine1();
};
void TIMER2_OVF_vect_routine()
    __attribute__((weak, alias("__TIMER2_OVF_vect_routine")));
void TIMER2_OVF_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER2_OVF_vect(void) {
    TIMER2_OVF_vect_routine();
}

/* Timer/Counter1 Capture Event */
void __TIMER1_CAPT_vect_routine1() {
    ;
}
void TIMER1_CAPT_vect_routine1()
    __attribute__((weak, alias("__TIMER1_CAPT_vect_routine1")));
void __TIMER1_CAPT_vect_routine() {
    TIMER1_CAPT_vect_routine1();
};
void TIMER1_CAPT_vect_routine()
    __attribute__((weak, alias("__TIMER1_CAPT_vect_routine")));
void TIMER1_CAPT_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER1_CAPT_vect(void) {
    TIMER1_CAPT_vect_routine();
}

/* Timer/Counter1 Compare Match A */
void __TIMER1_COMPA_vect_routine1() {
    ;
}
void TIMER1_COMPA_vect_routine1()
    __attribute__((weak, alias("__TIMER1_COMPA_vect_routine1")));
void __TIMER1_COMPA_vect_routine() {
    TIMER1_COMPA_vect_routine1();
};
void TIMER1_COMPA_vect_routine()
    __attribute__((weak, alias("__TIMER1_COMPA_vect_routine")));
void TIMER1_COMPA_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER1_COMPA_vect(void) {
    TIMER1_COMPA_vect_routine();
}

/* Timer/counter Compare Match B */
void __TIMER1_COMPB_vect_routine1() {
    ;
}
void TIMER1_COMPB_vect_routine1()
    __attribute__((weak, alias("__TIMER1_COMPB_vect_routine1")));
void __TIMER1_COMPB_vect_routine() {
    TIMER1_COMPB_vect_routine1();
};
void TIMER1_COMPB_vect_routine()
    __attribute__((weak, alias("__TIMER1_COMPB_vect_routine")));
void TIMER1_COMPB_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER1_COMPB_vect(void) {
    TIMER1_COMPB_vect_routine();
}

/* Timer/Counter1 Overflow */
void __TIMER1_OVF_vect_routine1() {
    ;
}
void TIMER1_OVF_vect_routine1()
    __attribute__((weak, alias("__TIMER1_OVF_vect_routine1")));
void __TIMER1_OVF_vect_routine() {
    TIMER1_OVF_vect_routine1();
};
void TIMER1_OVF_vect_routine()
    __attribute__((weak, alias("__TIMER1_OVF_vect_routine")));
void TIMER1_OVF_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER1_OVF_vect(void) {
    TIMER1_OVF_vect_routine();
}

/* Timer/Counter0 COMPAare Match A */
void __TIMER0_COMPA_vect_routine1() {
	;
}
void TIMER0_COMPA_vect_routine1()
__attribute__((weak, alias("__TIMER0_COMPA_vect_routine1")));
void __TIMER0_COMPA_vect_routine() {
	TIMER0_COMPA_vect_routine1();
};
void TIMER0_COMPA_vect_routine()
__attribute__((weak, alias("__TIMER0_COMPA_vect_routine")));
void TIMER0_COMPA_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER0_COMPA_vect(void) {
	TIMER0_COMPA_vect_routine();
}

/* Timer/Counter0 COMPBare Match B */
void __TIMER0_COMPB_vect_routine1() {
	;
}
void TIMER0_COMPB_vect_routine1()
__attribute__((weak, alias("__TIMER0_COMPB_vect_routine1")));
void __TIMER0_COMPB_vect_routine() {
	TIMER0_COMPB_vect_routine1();
};
void TIMER0_COMPB_vect_routine()
__attribute__((weak, alias("__TIMER0_COMPB_vect_routine")));
void TIMER0_COMPB_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER0_COMPB_vect(void) {
	TIMER0_COMPB_vect_routine();
}

/* Timer/Counter0 Overflow */
void __TIMER0_OVF_vect_routine1() {
    ;
}
void TIMER0_OVF_vect_routine1()
    __attribute__((weak, alias("__TIMER0_OVF_vect_routine1")));
void __TIMER0_OVF_vect_routine() {
    TIMER0_OVF_vect_routine1();
};
void TIMER0_OVF_vect_routine()
    __attribute__((weak, alias("__TIMER0_OVF_vect_routine")));
void TIMER0_OVF_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER0_OVF_vect(void) {
    TIMER0_OVF_vect_routine();
}

/* SPI0 Serial Transfer Complete */
void __SPI0_STC_vect_routine1() {
    ;
}
void SPI0_STC_vect_routine1()
    __attribute__((weak, alias("__SPI0_STC_vect_routine1")));
void __SPI0_STC_vect_routine() {
    SPI0_STC_vect_routine1();
};
void SPI0_STC_vect_routine()
    __attribute__((weak, alias("__SPI0_STC_vect_routine")));
void SPI0_STC_vect(void) __attribute__((signal, __INTR_ATTRS));
void SPI0_STC_vect(void) {
    SPI0_STC_vect_routine();
}

/* USART0, Rx Complete */
void __USART0_RX_vect_routine1() {
    ;
}
void USART0_RX_vect_routine1()
    __attribute__((weak, alias("__USART0_RX_vect_routine1")));
void __USART0_RX_vect_routine() {
    USART0_RX_vect_routine1();
};
void USART0_RX_vect_routine()
    __attribute__((weak, alias("__USART0_RX_vect_routine")));
void USART0_RX_vect(void) __attribute__((signal, __INTR_ATTRS));
void USART0_RX_vect(void) {
    USART0_RX_vect_routine();
}

/* USART0 Data Register Empty */
void __USART0_UDRE_vect_routine1() {
    ;
}
void USART0_UDRE_vect_routine1()
    __attribute__((weak, alias("__USART0_UDRE_vect_routine1")));
void __USART0_UDRE_vect_routine() {
    USART0_UDRE_vect_routine1();
};
void USART0_UDRE_vect_routine()
    __attribute__((weak, alias("__USART0_UDRE_vect_routine")));
void USART0_UDRE_vect(void) __attribute__((signal, __INTR_ATTRS));
void USART0_UDRE_vect(void) {
    USART0_UDRE_vect_routine();
}

/* USART0, Tx Complete */
void __USART0_TX_vect_routine1() {
    ;
}
void USART0_TX_vect_routine1()
    __attribute__((weak, alias("__USART0_TX_vect_routine1")));
void __USART0_TX_vect_routine() {
    USART0_TX_vect_routine1();
};
void USART0_TX_vect_routine()
    __attribute__((weak, alias("__USART0_TX_vect_routine")));
void USART0_TX_vect(void) __attribute__((signal, __INTR_ATTRS));
void USART0_TX_vect(void) {
    USART0_TX_vect_routine();
}

/* ADC Conversion Complete */
void __ADC_vect_routine1() {
    ;
}
void ADC_vect_routine1() __attribute__((weak, alias("__ADC_vect_routine1")));
void __ADC_vect_routine() {
    ADC_vect_routine1();
};
void ADC_vect_routine() __attribute__((weak, alias("__ADC_vect_routine")));
void ADC_vect(void) __attribute__((signal, __INTR_ATTRS));
void ADC_vect(void) {
    ADC_vect_routine();
}

/* EEPROM Ready */
void __EE_READY_vect_routine1() {
    ;
}
void EE_READY_vect_routine1()
    __attribute__((weak, alias("__EE_READY_vect_routine1")));
void __EE_READY_vect_routine() {
    EE_READY_vect_routine1();
};
void EE_READY_vect_routine()
    __attribute__((weak, alias("__EE_READY_vect_routine")));
void EE_READY_vect(void) __attribute__((signal, __INTR_ATTRS));
void EE_READY_vect(void) {
    EE_READY_vect_routine();
}

/* Analog Comparator */
void __ANALOG_COMP_vect_routine1() {
    ;
}
void ANALOG_COMP_vect_routine1()
    __attribute__((weak, alias("__ANALOG_COMP_vect_routine1")));
void __ANALOG_COMP_vect_routine() {
    ANALOG_COMP_vect_routine1();
};
void ANALOG_COMP_vect_routine()
    __attribute__((weak, alias("__ANALOG_COMP_vect_routine")));
void ANALOG_COMP_vect(void) __attribute__((signal, __INTR_ATTRS));
void ANALOG_COMP_vect(void) {
    ANALOG_COMP_vect_routine();
}

/* 2-wire Serial Interface */
void __TWI0_vect_routine1() {
	;
}
void TWI0_vect_routine1() __attribute__((weak, alias("__TWI0_vect_routine1")));
void __TWI0_vect_routine() {
	TWI0_vect_routine1();
};
void TWI0_vect_routine() __attribute__((weak, alias("__TWI0_vect_routine")));
void TWI0_vect(void) __attribute__((signal, __INTR_ATTRS));
void TWI0_vect(void) {
	TWI0_vect_routine();
}
/*

/ * Store Program Memory Read * /
void __SPM_READY_vect_routine1() {
	;
}
void SPM_READY_vect_routine1()
__attribute__((weak, alias("__SPM_READY_vect_routine1")));
void __SPM_READY_vect_routine() {
	SPM_READY_vect_routine1();
};
void SPM_READY_vect_routine()
__attribute__((weak, alias("__SPM_READY_vect_routine")));
void SPM_READY_vect(void) __attribute__((signal, __INTR_ATTRS));
void SPM_READY_vect(void) {
	SPM_READY_vect_routine();
}
*/

/* USART1, Rx Complete */
void __USART1_RX_vect_routine1() {
    ;
}
void USART1_RX_vect_routine1()
    __attribute__((weak, alias("__USART1_RX_vect_routine1")));
void __USART1_RX_vect_routine() {
    USART1_RX_vect_routine1();
};
void USART1_RX_vect_routine()
    __attribute__((weak, alias("__USART1_RX_vect_routine")));
void USART1_RX_vect(void) __attribute__((signal, __INTR_ATTRS));
void USART1_RX_vect(void) {
    USART1_RX_vect_routine();
}

/* USART1, Data Register Empty */
void __USART1_UDRE_vect_routine1() {
    ;
}
void USART1_UDRE_vect_routine1()
    __attribute__((weak, alias("__USART1_UDRE_vect_routine1")));
void __USART1_UDRE_vect_routine() {
    USART1_UDRE_vect_routine1();
};
void USART1_UDRE_vect_routine()
    __attribute__((weak, alias("__USART1_UDRE_vect_routine")));
void USART1_UDRE_vect(void) __attribute__((signal, __INTR_ATTRS));
void USART1_UDRE_vect(void) {
    USART1_UDRE_vect_routine();
}

/* USART1, Tx Complete */
void __USART1_TX_vect_routine1() {
    ;
}
void USART1_TX_vect_routine1()
    __attribute__((weak, alias("__USART1_TX_vect_routine1")));
void __USART1_TX_vect_routine() {
    USART1_TX_vect_routine1();
};
void USART1_TX_vect_routine()
    __attribute__((weak, alias("__USART1_TX_vect_routine")));
void USART1_TX_vect(void) __attribute__((signal, __INTR_ATTRS));
void USART1_TX_vect(void) {
    USART1_TX_vect_routine();
}

/* Timer/Counter3 Capture Event */
void __TIMER3_CAPT_vect_routine1() {
	;
}
void TIMER3_CAPT_vect_routine1()
__attribute__((weak, alias("__TIMER3_CAPT_vect_routine1")));
void __TIMER3_CAPT_vect_routine() {
	TIMER3_CAPT_vect_routine1();
};
void TIMER3_CAPT_vect_routine()
__attribute__((weak, alias("__TIMER3_CAPT_vect_routine")));
void TIMER3_CAPT_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER3_CAPT_vect(void) {
	TIMER3_CAPT_vect_routine();
}

/* Timer/Counter3 Compare Match A */
void __TIMER3_COMPA_vect_routine1() {
	;
}
void TIMER3_COMPA_vect_routine1()
__attribute__((weak, alias("__TIMER3_COMPA_vect_routine1")));
void __TIMER3_COMPA_vect_routine() {
	TIMER3_COMPA_vect_routine1();
};
void TIMER3_COMPA_vect_routine()
__attribute__((weak, alias("__TIMER3_COMPA_vect_routine")));
void TIMER3_COMPA_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER3_COMPA_vect(void) {
	TIMER3_COMPA_vect_routine();
}

/* Timer/Counter3 Compare Match B */
void __TIMER3_COMPB_vect_routine1() {
	;
}
void TIMER3_COMPB_vect_routine1()
__attribute__((weak, alias("__TIMER3_COMPB_vect_routine1")));
void __TIMER3_COMPB_vect_routine() {
	TIMER3_COMPB_vect_routine1();
};
void TIMER3_COMPB_vect_routine()
__attribute__((weak, alias("__TIMER3_COMPB_vect_routine")));
void TIMER3_COMPB_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER3_COMPB_vect(void) {
	TIMER3_COMPB_vect_routine();
}

/* Timer/Counter3 Overflow */
void __TIMER3_OVF_vect_routine1() {
	;
}
void TIMER3_OVF_vect_routine1()
__attribute__((weak, alias("__TIMER3_OVF_vect_routine1")));
void __TIMER3_OVF_vect_routine() {
	TIMER3_OVF_vect_routine1();
};
void TIMER3_OVF_vect_routine()
__attribute__((weak, alias("__TIMER3_OVF_vect_routine")));
void TIMER3_OVF_vect(void) __attribute__((signal, __INTR_ATTRS));
void TIMER3_OVF_vect(void) {
	TIMER3_OVF_vect_routine();
}
