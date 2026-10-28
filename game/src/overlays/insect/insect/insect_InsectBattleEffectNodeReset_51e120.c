/* rgp:protos */
#define RGP_SELF_insect_InsectBattleEffectNodeReset_51e120 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051E120 -- 40 bytes, 10 instructions.  A field-clear.  The store
 * order in retail is 0x0, 0x8, 0x14, 0x10, 0xC then the three halfwords, which
 * is taken as the SOURCE order (mwcc emits stores in source order). */

typedef struct Obj {
    s32 m00;                        /* +0x00 */
    u8  pad04[0x08 - 0x04];
    s32 m08;                        /* +0x08 */
    s32 m0C;                        /* +0x0C */
    s32 m10;                        /* +0x10 */
    s32 m14;                        /* +0x14 */
    u8  pad18[0x1A - 0x18];
    s16 m1A;                        /* +0x1A */
    s16 m1C;                        /* +0x1C */
    s16 m1E;                        /* +0x1E */
} Obj;

void insect_InsectBattleEffectNodeReset_51e120(Obj *o)
{
    o->m00 = 0;
    o->m08 = 0;
    o->m14 = 0;
    o->m10 = 0;
    o->m0C = 0;
    o->m1A = -1;
    o->m1C = -1;
    o->m1E = -1;
}
