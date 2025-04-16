/* Файл с полезными макросами для работы, подключать в каждый файл всех проектов */
#ifndef __STANDARD_H__
#define __STANDARD_H__
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#ifdef __AVR__
#define CRITICAL_ZONE_START() char cSREG; cSREG = SREG; cli(); 
#define CRITICAL_ZONE_END() SREG = cSREG;
#define __enable_interrupt() sei();
#endif

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define i8 int8_t
#define i16 int16_t
#define i32 int32_t

#define READ_REG(REG) REG
#define READ_BIT(REG, BIT) REG & BIT
#define WRITE_REG(REG,VALUE) REG = VALUE
#define SET_BIT(REG,BIT) REG |= (1<<BIT)
#define CLEAR_BIT(REG,BIT) REG = REG &= ~(1<<BIT)
#define MODIFY_REG(REG,BITS_TO_ZERO,BITS_TO_ONE) REG = REG | (1<<BITS_TO_ONE) & ~(1<<BITS_TO_ZERO)

#endif /*__STANDARD_H__*/

/*
Здесь прописана архитектура модулей для связки железозависимой части и абстракции



*/