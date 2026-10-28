/* rgp:protos */
#define RGP_SELF_insect_InsectPieceTakeDamage_515020 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00515020 -- 116 bytes, 29 instructions, 2 calls, 3 conditional
 * branches.  0x4C is an `lb`, 0x1C an `lh`; the parameter itself is the
 * variable that gets zeroed, and it is also the return value.
 */

typedef struct Obj {
    u8  pad00[0x1C];
    s16 f1C;                        /* +0x1C */
    u8  pad1E[0x4C - 0x1E];
    s8  f4C;                        /* +0x4C */
} Obj;

/*rgp*/
/*rgp*/

s32 insect_InsectPieceTakeDamage_515020(Obj *o, s32 n)
{
    s32 d;

    if (n <= 0) {
        return 0;
    }
    if (o->f4C != 0) {
        insect_InsectPieceBallDamage_514f10((void *)o, (int)n);
        n = 0;
    }
    d = o->f1C - n;
    if (d <= 0) {
        d = 0;
    }
    insect_InsectPieceSetHp_512ee0(o, d);
    return n;
}
