#include "types.h"

extern void PadSysInit_185080(void);
extern void PadPortOpen_184ed0(void *, s32, s32, void *);
extern void PadWaitReady_1849e0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B2570[];
extern u8 D_004B27E0[];
extern u8 D_004B2A80[];
extern u8 D_004B2B80[];

void PadOpenPorts_1c6bf0(void)
{
    PadSysInit_185080();
    PadPortOpen_184ed0(D_004B2570, 0, 0, D_004B2A80);
    PadPortOpen_184ed0(D_004B27E0, 1, 0, D_004B2B80);
    PadWaitReady_1849e0(D_004B2570);
}
