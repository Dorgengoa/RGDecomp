#include "types.h"
/* normal 0x00503730 -- tail-call forwarder into func_291110 for widget 0x40.
 * The `andi $6,$4,0xFF` is the zero-extension of a u8 PARAMETER widened to the
 * callee's s32 slot, not a source-level mask. */

extern void *D_0048449C;          /* gp - 0xCD4 */

extern void func_291110(void *w, s32 id, s32 a, s32 b);

void normal_BtlChgMenuCursorShow_503730(u8 a)
{
    func_291110(D_0048449C, 0x40, a, 1);
}
