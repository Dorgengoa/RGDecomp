/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecEffectOn_518d40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00518D40 -- 228 bytes, 57 instructions. */

typedef struct Obj {
    u8  pad00[0xC];
    s8  f0C;                        /* +0x0C */
    u8  pad0D[0x0E - 0x0D];
    s8  f0E;                        /* +0x0E */
    s8  f0F;                        /* +0x0F */
    s8  f10;                        /* +0x10 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/


s32 insect_InsectSeqExecEffectOn_518d40(Obj *a)
{
    void *b;
    s32 h0;
    s32 h3;
    s32 r;
    void *q;
    s32 p1;
    s32 p4;

    b = InsectBattleGet_31a8d0();
    if (a == 0 || b == 0) {
        return 1;
    }
    h0 = insect_InsectBattleGetActorSlot_50db40(b, 0);
    h3 = insect_InsectBattleGetActorSlot_50db40(b, 3);
    r = insect_InsectBattleGetSpecialRec_50db30(b);
    q = (u8 *)b + 0x5178;
    if (h0 == 0) {
        return 1;
    }
    if (h3 == 0) {
        h3 = h0;
    }
    if (r == 0) {
        return 1;
    }
    p1 = h3;
    p4 = 0;
    if (a->f0E == 0) {
        p1 = h0;
    }
    if (a->f10 != 0) {
        p4 = h3;
    }
    insect_InsectBattleEffectsSpawn_51dc30(q, p1, a->f0C, a->f0F, p4,
                        -1, -1, 1, 0);
    return 1;
}
