#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern void GameSceneDofDraw_1cefb0(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00461D18[];

void TaskDrawDof_2f6a00(void)
{
    s32 r0;

    r0 = GetCurrentScene_1f5be0();
    GameSceneDofDraw_1cefb0(r0, D_00461D18, 0x31B);
}
