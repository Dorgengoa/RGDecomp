#include "types.h"
/* insect 0x00514280 -- 68 bytes, 17 instructions, 3 calls.  The member load
 * sits in the FIRST call's delay slot, so it is evaluated before the inner
 * call in source too -- retail keeps the LOADED VALUE in $16 across the call,
 * not the object pointer, so the member is a named local -- and the CALL
 * RESULT needs its own named local too, or mwcc sinks the member load past
 * the call and saves the object pointer instead.  The guard branches
 * on `!= 0` INTO the call arm so the `return 0` merges into the epilogue. */

typedef struct Obj {
    u8  pad00[0x6C];
    s16 m6C;                        /* +0x6C */
} Obj;

typedef struct Ent {
    u8  pad000[0x1F0];
    s32 m1F0;                       /* +0x1F0 */
} Ent;

extern s32   func_1F5BE0(void);
extern Ent  *func_1C4A90(s32 h, s16 id);
extern s32   func_171D90(s32 *p, s32 v);

s32 insect_InsectPieceIsMotionDone_514280(Obj *o)
{
    Ent *e;
    s32  h;
    s16  id;

    id = o->m6C;
    h = func_1F5BE0();
    e = func_1C4A90(h, id);
    if (e != 0) {
        return func_171D90(&e->m1F0, -1);
    }
    return 0;
}
