#include "types.h"

/* ContainerViewGetAtFwd_405b30 -- ONE 80-byte symbol spanning TWO entry points (mwcc emits
 * one .text per function; the two sizes SUM to retail's 0x50).
 *   +0x00   4 words: tail call of virtual slot 2 (vptr at 0, entry 8+2*4=0x10)
 *   +0x10  16 words: bounds-checked element address, stride from the two slls
 * The tail call needs C++ (`jr $25`); plain C emits `jr $2`.
 * The guard is a FLAG, not two returns: `ok=0; if (i>=0) if (i<n) ok=1;`
 * is the only spelling of ~25 that gives retail's `bnel` INTO the arm plus
 * the `b` to the shared `return 0` -- every early-return spelling is one
 * word short.
 */

struct Elem_00405B30 { s32 w[17]; };

struct Obj_00405B30 {
    virtual void v0();
    virtual void v1();
    virtual Elem_00405B30 *v2(s32 i);
    u8 pad04[0x7C - 0x04];
    s16 m7C;
    u8 pad7E[0x8C - 0x7E];
    Elem_00405B30 *m8C;
};


extern "C" Elem_00405B30 *ContainerViewGetAtFwd_405b30(Obj_00405B30 *o, s32 i)
{
    return o->v2(i);
}

extern "C" Elem_00405B30 *func_00405B30_e1(Obj_00405B30 *o, s32 i)
{
    s32 ok;
    ok = 0;
    if (i >= 0) {
        if (i < o->m7C) {
            ok = 1;
        }
    }
    if (ok != 0) {
        return &o->m8C[i];
    }
    return 0;
}
