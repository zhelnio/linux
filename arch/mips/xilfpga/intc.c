/*
 * Xilfpga interrupt controller setup
 *
 * Copyright (C) 2015 Imagination Technologies
 * Author: Zubair Lutfullah Kakakhel <Zubair.Kakakhel@imgtec.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */

#include <linux/of.h>
#include <linux/of_irq.h>

#include <asm/irq_cpu.h>

/*
static struct of_device_id of_irq_ids[] __initdata = {
	{ .compatible = "mti,cpu-interrupt-controller", .data = mips_cpu_irq_of_init },
	{},
};
*/

void __init arch_init_irq(void)
{	
//	cp0_compare_irq = 7;
	mips_cpu_irq_init();

//	set_c0_status(IE_SW0 | IE_SW1 | IE_IRQ0 | IE_IRQ1 |
//		      IE_IRQ2 | IE_IRQ3 | IE_IRQ4 | IE_IRQ5);

//	of_irq_init(of_irq_ids);

}
