/*
 * Xilfpga platform setup
 *
 * Copyright (C) 2015 Imagination Technologies
 * Author: Zubair Lutfullah Kakakhel <Zubair.Kakakhel@imgtec.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */

#include <linux/of_fdt.h>

#include <asm/prom.h>
#include <asm/setup.h>

#include <linux/io.h>
#include <linux/serial_core.h>
#include <linux/serial_reg.h>
#include <linux/printk.h>

#define XILFPGA_UART_BASE		0xb0401000
#define XILFPGA_UART_REG_SHIFT	2

const char *get_system_type(void)
{
	return "MIPSfpga";
}

void __init plat_mem_setup(void)
{
	__dt_setup_arch(__dtb_start);
	strlcpy(arcs_cmdline, boot_command_line, COMMAND_LINE_SIZE);
}

#define DLAB            0x80

#define TXR             0       /*  Transmit register (WRITE) */
#define RXR             0       /*  Receive register  (READ)  */
#define IER             1       /*  Interrupt Enable          */
#define IIR             2       /*  Interrupt ID              */
#define FCR             2       /*  FIFO control              */
#define LCR             3       /*  Line control              */
#define MCR             4       /*  Modem control             */
#define LSR             5       /*  Line Status               */
#define MSR             6       /*  Modem Status              */
#define DLL             0       /*  Divisor Latch Low         */
#define DLH             1       /*  Divisor latch High        */

#define MFP_UART_LSR_TFE        (1 << 5)        /* Transmitter FIFO empty */

#define DEFAULT_BAUD 	115200
#define DIVISOR_50M     (50*1000*1000 / (16*115200))
#define UART_TIMEOUT	50000;

//extern void prom_putchar(char c);

// void __attribute__ ((interrupt, keep_interrupts_masked)) general_exception_handler (void)
// {
    
// }

static inline u8 serial_in(int offset)
{
	return readb(((void __iomem *)XILFPGA_UART_BASE) + (offset << XILFPGA_UART_REG_SHIFT));
}

static inline void serial_out(int offset, char value)
{
	writeb(value, ((void __iomem *)XILFPGA_UART_BASE) + (offset << XILFPGA_UART_REG_SHIFT));
}

static void early_serial_hw_init(unsigned divisor)
{
        unsigned char c;

        serial_out(LCR, 0x3);	/* 8n1 */
        serial_out(IER, 0);		/* no interrupt */
        serial_out(FCR, 0);		/* no fifo */
        serial_out(MCR, 0x3);	/* DTR + RTS */

        c = serial_in(LCR);
        serial_out(LCR, c | DLAB);
        serial_out(DLL, divisor & 0xff);
        serial_out(DLH, (divisor >> 8) & 0xff);
        serial_out(LCR, c & ~DLAB);
}

void prom_putchar(char c)
{
	unsigned int timeout;
	unsigned char status;

	timeout = UART_TIMEOUT;

	do {
		status = serial_in(LSR);
		if(--timeout == 0)
			return;
	} while (!(status & MFP_UART_LSR_TFE));

	serial_out(TXR, c);
}

void testTransmit(const char *s)
{
    while (*s)
	{
		prom_putchar(*s);
		s++;
	}
    prom_putchar('\n');
}

void __init prom_init(void)
{
	early_serial_hw_init(DIVISOR_50M);
	//setup_8250_early_printk_port(XILFPGA_UART_BASE, 2, 200000);

	prom_putchar('U');
	prom_putchar('A');

	testTransmit("RT_Ok\n");
}

void __init prom_free_prom_memory(void)
{
}

void __init device_tree_init(void)
{
	if (!initial_boot_params)
		return;

	unflatten_and_copy_device_tree();
}


