/* rgp:protos */
#define RGP_SELF_insect_InsectTeamReset_513d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00513D00 -- 136 bytes, 34 instructions.  Five 0x1E8-byte slots. */

typedef struct Ent {
    u8  pad00[0xE4];
    f32 fE4;                        /* +0xE4 */
    u8  padE8[0x1E8 - 0xE8];
} Ent;

typedef struct Obj {
    Ent a[5];                       /* +0x000 */
    s32 f988;                       /* +0x988 */
    s8  f98C;                       /* +0x98C */
    s8  f98D;                       /* +0x98D */
    s8  f98E;                       /* +0x98E */
    u8  pad98F[1];
    f32 f990;                       /* +0x990 */
} Obj;

/*rgp*/

void insect_InsectTeamReset_513d00(Obj *o, f32 v)
{
    s32 i;
    Ent *e;

    o->f990 = v;
    for (i = 0; i < 5; i++) {
        e = &o->a[i];
        insect_InsectPieceReset_514740(e);
        e->fE4 = v;
    }
    o->f988 = 0;
    o->f98C = -1;
    o->f98D = -1;
    o->f98E = 0;
}
