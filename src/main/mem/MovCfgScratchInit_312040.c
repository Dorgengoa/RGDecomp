#include "types.h"

extern void * GetCurrentScene_1f5be0(void);
extern s32 AlignUp16_1cacd0(s32);
extern s32 MemStackHeapAllocFront_14dd10(s32, s32);
extern void MovCfgScratchRewind_312080(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004829B0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x180C];
    s32 m180C;
};

void MovCfgScratchInit_312040(void)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = GetCurrentScene_1f5be0();
    t0 = r0->m180C;
    r1 = AlignUp16_1cacd0(0x1000);
    r2 = MemStackHeapAllocFront_14dd10(t0, r1);
    D_004829B0 = r2;
    MovCfgScratchRewind_312080();
}
