#include "types.h"
/* insect 0x004E9F00 -- 100 bytes, 25 instructions.
 * The handle at +0x1D8 is loaded for the guard, reused as the argument of
 * func_1F59D0, and RE-LOADED for func_1CD340's second argument -- the nested
 * call expression keeps the outer argument alive across the inner call.
 */

typedef struct Obj {
    u8  pad000[0x1D8];
    s32 m1D8;                       /* +0x1D8 */
    s32 m1DC;                       /* +0x1DC */
    s32 m1E0;                       /* +0x1E0 */
} Obj;

extern s32 func_1F59D0(s32);
extern void func_1CD340(s32, s32);
extern void insect_InsectSeqSetState_4ea3c0(Obj *, s32);

void insect_InsectSeqLoadRelease_4e9f00(Obj *o)
{
    s32 h;

    h = o->m1D8;
    if (h != -1) {
        h = func_1F59D0(h);
        func_1CD340(h, o->m1D8);
        o->m1DC = 2;
        o->m1E0 = 0;
        insect_InsectSeqSetState_4ea3c0(o, 3);
        o->m1D8 = -1;
    }
}
