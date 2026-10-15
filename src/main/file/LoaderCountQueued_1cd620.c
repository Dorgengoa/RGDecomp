#include "types.h"

/* Sums three s16 "count" fields read via the already-closed S16ArrayGetCount_1ce1b0
   accessor, at three 8-byte-spaced sub-object offsets (0x30/0x28/0x20) off
   `this`. Callers (src/bodies2/EvCmdLoaderIsBusy_248db0.c, src/bodies2/EvCmdLoaderIdleCheck_25cef0.c,
   src/mb/FactoryModeUpdate_27db40.c, etc, all already merged) declare this
   `extern s32 LoaderCountQueued_1cd620(s32);` -- pointer-as-s32 per this project's
   pass-11 auto-generated convention -- and use the s32 return value. */

typedef struct Obj_FUN_001ce1b0 {
    u8 pad000[0x6];
    s16 field;
} Obj_FUN_001ce1b0;

extern s32 S16ArrayGetCount_1ce1b0(Obj_FUN_001ce1b0 *o);

s32 LoaderCountQueued_1cd620(s32 arg0)
{
    return S16ArrayGetCount_1ce1b0((Obj_FUN_001ce1b0 *)(arg0 + 0x30))
         + S16ArrayGetCount_1ce1b0((Obj_FUN_001ce1b0 *)(arg0 + 0x28))
         + S16ArrayGetCount_1ce1b0((Obj_FUN_001ce1b0 *)(arg0 + 0x20));
}
