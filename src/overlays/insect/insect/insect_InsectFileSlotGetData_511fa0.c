#include "types.h"
/* insect 0x00511FA0 -- 104 bytes, 26 instructions, 2 calls.  The two guards are
 * ONE `if` joined by `||`: short-circuit ordering is what keeps
 * `lw $5,0x24($17)` AFTER the first test and what leaves the join `b`'s delay
 * slot EMPTY at 00511FE0.  The out-word at $29+0x3C is zeroed in the FIRST
 * call's delay slot, so `v = 0;` precedes it. */

typedef struct Obj {
    u8  pad00[0x24];
    s32 f24;                        /* +0x24 */
} Obj;

extern s32 func_1F59D0(void);
extern s32 func_1CD490(s32 h, s32 k, s32 *out);

s32 insect_InsectFileSlotGetData_511fa0(Obj *o, s32 *dst)
{
    s32 v;
    s32 h;
    s32 r;

    v = 0;
    h = func_1F59D0();
    if (h == 0 || o->f24 == -1) {
        return 0;
    }
    r = func_1CD490(h, o->f24, &v);
    *dst = v;
    return r;
}
