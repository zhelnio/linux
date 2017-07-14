/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Zubair Lutfullah Kakakhel <Zubair.Kakakhel@imgtec.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#ifndef __MIPS_ASM_MACH_XILFPGA_IRQ_H__
#define __MIPS_ASM_MACH_XILFPGA_IRQ_H__

#ifdef CONFIG_XILFPGA_NEXYS4DDR
	#define NR_IRQS 32
#endif
#ifdef CONFIG_XILFPGA_DE10LITE
	#define NR_IRQS 8
#endif

#include_next <irq.h>

#endif /* __MIPS_ASM_MACH_XILFPGA_IRQ_H__ */
