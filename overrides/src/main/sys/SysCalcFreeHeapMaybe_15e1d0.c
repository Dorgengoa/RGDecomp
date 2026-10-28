/* rg-override: replaces game/src/main/sys/SysCalcFreeHeapMaybe_15e1d0.c sha256 599cd7e3678f0b28de6faaffd2cee837841b648821368e2d35ada801dc653f12
 * why: retail reads two LINK-TIME addresses as numbers (D_00030000 = the 0x30000 main
 *      stack size, D_00528200 = 0x004E9E80 + the largest overlay reservation =
 *      retail's heap start, "end") and computes the heap's capacity as
 *      32 MB - 0x2000 - stack size - heap start.  Since the stack sits right
 *      above the heap (EndOfHeap = 0x01FD0000 = 32 MB - 0x30000), that is the heap's
 *      size less 0x2000: natively, the size of the game heap the runtime allocated
 *      (rg_crt0_heap_size(), src/runtime/crt0.c = RG_PS2_HEAP_SIZE 0x1AA7E00) less
 *      0x2000.  Same value as retail (0x1AA5E00, returned - 0x10), no PS2 address
 *      (D9; was #define RG_PS2_ADDR_00030000 / _00528200 until 2026-10-25). */
/* rgp:protos */
#define RGP_SELF_SysCalcFreeHeapMaybe_15e1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
/*rgp*/
/*rgp*/

extern unsigned int rg_crt0_heap_size(void);   /* src/runtime/crt0.c */

s32 SysCalcFreeHeapMaybe_15e1d0(void)
{
    s32 t;

    t = (s32)rg_crt0_heap_size() - 0x2000;
    Free_130e30(((s32)Malloc_130dd8(t - 0x10)));
    Free_130e30(((s32)Malloc_130dd8(0x01900000)));
    return t - 0x10;
}
