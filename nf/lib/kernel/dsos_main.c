#include <assert.h>
#include <stddef.h>

#include "dsos_pci.h"
#include "dsos_vga.h"

/* Kernel main */
extern int main(void);
/* NF main */
extern int nf_main(int argc, char *argv[]);
/* Initialize filesystem */
extern void stub_stdio_files_init(struct dsos_pci_nic *devs, int n);
/* Start and end of constructor list */
extern int __CTORS_START, __CTORS_END;

#ifdef VIGOR_STUB_HARDWARE
extern struct dsos_pci_nic *stub_hardware_get_nics(int *n);
#endif

int main(void)
{
	static char *argv[] = { NF_ARGUMENTS, NULL, };

	static const int argc = (sizeof(argv) / sizeof(argv[0])) - 1;

	int num_devs;
	struct dsos_pci_nic *devs;

#ifdef VIGOR_STUB_HARDWARE
	devs = stub_hardware_get_nics(&num_devs);
#else
	devs = dsos_pci_find_nics(&num_devs);
#endif

	if (devs == NULL) {
		dsos_vga_write_str("Error getting PCI devices\n");
		return -1;
	}

	stub_stdio_files_init(devs, num_devs);

#ifndef KLEE_VERIFICATION
	/* Yeah maybe this isn't the best way to call constructors but it should work */

	/* Pointer to a function with no argument and no return value */
	void (**ctor)(void) = (void (**)(void))&__CTORS_START;
	void (**ctors_end)(void) = (void (**)(void))&__CTORS_END;

	while (ctor != ctors_end) {
		(*ctor)();
		ctor++;
	}
#endif

	dsos_vga_write_str("Calling NAT...\n");
	nf_main(argc, argv);
	dsos_vga_write_str("Done\n");

	return 0;
}
