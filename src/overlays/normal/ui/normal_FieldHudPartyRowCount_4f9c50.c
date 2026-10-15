#include "types.h"
/* normal 0x004F9C50 -- "is the shop/quest gate open?" predicate on the global
 * entity root.  Returns func_3C2010's count, forced to 1 by any of three
 * independent conditions.
 *
 * `addiu $5,$0,1 / daddu $6,$5,$0` is mwcc SHARING the constant between
 * arguments 2 and 3 -- one source literal, copied.
 * The two `beql`/`bnel` in the tail with `addiu $17,$0,1` in the delay slot
 * are the two arms of a single `||`, both assigning the same 1. */

typedef struct Ent { u8 pad00[0x10]; void *f10; u8 pad14[4];
                     void *f18; u8 pad1C[4];
                     void *f20; } Ent;

extern Ent  *func_1FEDE0(void);
extern s32   func_3C2010(void *a, s32 b, s32 c);
extern s32   func_3CCD70(void *a, s32 b);
extern s32   func_3A36D0(void *a);

s32 normal_FieldHudPartyRowCount_4f9c50(void)
{
    s32  r;
    Ent *e;
    s32  t;

    e = func_1FEDE0();
    if (e == 0) {
        return 0;
    }
    r = func_3C2010(e->f18, 1, 1);
    if (func_3CCD70(e->f10, 0xB6) != 0) {
        r = 1;
    }
    t = func_3A36D0(e->f20);
    if (t == 0x271B || t == 0x3F9) {
        r = 1;
    }
    return r;
}
