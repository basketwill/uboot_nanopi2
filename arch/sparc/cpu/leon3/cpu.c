/* CPU specific code for the LEON3 CPU
 *
 * (C) Copyright 2007
 * Daniel Hellstrom, Gaisler Research, daniel@gaisler.com
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <netdev.h>

#include <asm/io.h>
#include <asm/processor.h>

DECLARE_GLOBAL_DATA_PTR;

extern void _reset_reloc(void);

int checkcpu(void)
{
	/* check LEON version here */
	printf("CPU: LEON3\n");
	return 0;
}

/* ------------------------------------------------------------------------- */

void cpu_reset(void)
{
	/* Interrupts off */
	disable_interrupts();

	/* jump to restart in flash */
	_reset_reloc();
}

int do_reset(cmd_tbl_t * cmdtp, int flag, int argc, char * const argv[])
{
	cpu_reset();

	return 1;

}

u64 flash_read64(void *addr)
{
	return __raw_readq(addr);
}

/* ------------------------------------------------------------------------- */

#ifdef CONFIG_GRETH
int cpu_eth_init(bd_t *bis)
{
	return greth_initialize(bis);
}
#endif
