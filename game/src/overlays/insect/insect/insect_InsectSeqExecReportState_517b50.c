/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecReportState_517b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00517B50 -- 300 bytes, 75 instructions, 10 calls. */

typedef struct Ent {
    u8  pad00[0x38];
    s8  f38;                        /* +0x38 */
    u8  pad39[0x5C - 0x39];
    s32 f5C;                        /* +0x5C */
} Ent;

typedef struct Obj {
    u8 pad00[0x506C];
    u8 f506C;                       /* +0x506C */
    u8 pad506D[0x5080 - 0x506D];
    u8 f5080;                       /* +0x5080 */
    u8 pad5081[0x5F82 - 0x5081];
    u8 f5F82;                       /* +0x5F82 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  Sprintf_1343b8(u8 *d, s32 s, s32 n);
/*rgp*/

s32 insect_InsectSeqExecReportState_517b50(void *p)
{
    Obj *h;
    Ent *a;
    Ent *b;
    u8 *p1;
    u8 *p2;
    u8 *p3;
    s32 k;

    h = ((Obj *)InsectBattleGet_31a8d0());
    if (p == 0 || h == 0) {
        return 1;
    }
    p1 = &h->f506C;
    p2 = &h->f5080;
    a = ((Ent *)insect_InsectBattleGetActorSlot_50db40(h, 0));
    b = ((Ent *)insect_InsectBattleGetActorSlot_50db40(h, 1));
    if (a == 0 || b == 0) {
        return 1;
    }
    p3 = &h->f5F82;
    if (a->f38 == 0xF) {
        if (insect_InsectPieceHasLandedHitMaybe_512e10(a) == 0) {
            return 1;
        }
        if (insect_InsectPieceTestStatus_513280(b, 5) == 0) {
            return 1;
        }
    }
    insect_InsectPieceClearStatus_513340(b, 5);
    k = 0x42;
    if (insect_InsectPieceIsFlipped_514c30(b) != 0) {
        k = 0x99;
    }
    Sprintf_1343b8(p3, ((s32)insect_InsectMsgGet_512b70(p1, k)), b->f5C);
    insect_InsectBattleLogPush_51c2f0(p2, p3, -5, -1, 0);
    return 1;
}
