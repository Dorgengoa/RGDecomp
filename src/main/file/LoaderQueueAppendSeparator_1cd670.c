#include "types.h"

/* Sibling of LoaderCountQueued_1cd620 -- same {ptr,max,count} sub-object at +0x20 off
   `this`, read via the already-closed S16ArrayGetCount_1ce1b0/S16ArrayGetChecked_1ce170. Callers
   (src/bodies2/MenuIconAllTexLoadRequest_2057f0.c, src/p21a/MenuBattleEndResRequest_2045e0.c, etc, all already
   merged) declare `this` as `s32` (pointer-as-int, this project's pass-11
   auto-generated convention) and mostly discard the return value (some
   declare `extern void LoaderQueueAppendSeparator_1cd670(s32);`) -- $2 at return is just
   whatever the last-called callee happened to leave there, so this is a
   void function.

   Logic: read the sub-object's current count, look up the value at index
   count-1 (S16ArrayGetChecked_1ce170 returns -1 out-of-range, else the s16 table entry
   sign-extended to s32); if that value is NOT the 0x3FFF sentinel, append
   the SENTINEL ITSELF (0x3FFF, a leftover argument register from the
   comparison constant -- see the "leftover argument register IS a real
   argument" lever) via S16ArrayAppend_1ce110 -- marking this slot done/full. */

typedef struct Obj_FUN_001ce1b0 {
    u8 pad000[0x6];
    s16 field;
} Obj_FUN_001ce1b0;

extern s32 S16ArrayGetCount_1ce1b0(Obj_FUN_001ce1b0 *o);
extern s32 S16ArrayGetChecked_1ce170(void *p0, s32 p1);
extern s32 S16ArrayAppend_1ce110(void *list, s16 val);

void LoaderQueueAppendSeparator_1cd670(s32 arg0)
{
    s32 idx;
    s32 val;

    idx = S16ArrayGetCount_1ce1b0((Obj_FUN_001ce1b0 *)(arg0 + 0x20)) - 1;
    val = S16ArrayGetChecked_1ce170((void *)(arg0 + 0x20), idx);
    if ((s16)val != 0x3FFF) {
        S16ArrayAppend_1ce110((void *)(arg0 + 0x20), 0x3FFF);
    }
}
