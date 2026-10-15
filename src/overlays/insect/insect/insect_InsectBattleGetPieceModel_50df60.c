#include "types.h"
/* insect 0x0050DF60 -- 48 bytes.  Retail issues the object's handle BEFORE the
 * entity's field.  The lever is the CALLEE PARAMETER WIDTH: with the second
 * parameter declared s16 the two loads come out in the other order, and five
 * source spellings (inline, one/two named locals in either order, a pointer
 * field) are ONE INERT object.  s32 -- or no prototype at all -- matches. */

typedef struct Obj {
    u8  pad000[0x870];
    s32 f870;                       /* +0x870 */
} Obj;

typedef struct Ent {
    u8  pad00[0x6C];
    s16 f6C;                        /* +0x6C */
} Ent;

extern s32 func_1C4A90(s32 a, s32 b);

s32 insect_InsectBattleGetPieceModel_50df60(Obj *o, Ent *e)
{
    s32 h;

    if (e != 0) {
        h = o->f870;
        return func_1C4A90(h, e->f6C);
    }
    return 0;
}
