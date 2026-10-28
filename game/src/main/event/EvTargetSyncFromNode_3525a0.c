/* rgp:protos */
#define RGP_SELF_EvTargetSyncFromNode_3525a0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK s16d: 1 round trip, length 0x10C vs retail 0x100 (3 words over).
   Not yet diagnosed past the length delta -- candidates: the 9-word
   struct-copy loop's counter/pointer types, or the sp20/sp30/sp40/sp50
   quaternion-buffer declaration order (4 stack buffers passed to 9 calls).
   Left for a future pass with more round-trip budget. */
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

typedef struct { f32 x, y, z; } V3_3525a0;
typedef struct { s32 w[9]; } M9_3525a0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EvTargetSyncFromNode_3525a0(void *arg0)
{
    u8 sp50[0x40] __attribute__((aligned(16)));
    u8 sp40[0x10] __attribute__((aligned(16)));
    u8 sp30[0x10] __attribute__((aligned(16)));
    u8 sp20[0x10] __attribute__((aligned(16)));
    s32 *src;
    s32 *dst;
    s32 n;

    ((V3_3525a0 *)((u8 *)arg0 + 0x80))[0] = ((V3_3525a0 *)((u8 *)arg0 + 0x38))[0];
    ((V3_3525a0 *)((u8 *)arg0 + 0x80))[1] = ((V3_3525a0 *)((u8 *)arg0 + 0x38))[1];
    ((V3_3525a0 *)((u8 *)arg0 + 0x80))[2] = ((V3_3525a0 *)((u8 *)arg0 + 0x38))[2];
    n = 9;
    src = (s32 *)((u8 *)arg0 + 0x5C);
    dst = (s32 *)((u8 *)arg0 + 0xA4);
    do {
        *dst = *src;
        n -= 1;
        src += 1;
        dst += 1;
    } while (n > 0);


    FrameCalcWorldMatrix_148ff0(*(s32 *)((u8 *)arg0 + 0x34), sp50);
    MatDecomposeScaleRotPos_1cad20(sp40, sp30, sp20, sp50);
    EventObjSetScale_2e72e0((u8 *)arg0 + 0x38, sp40);
    EventObjSetRot_2e7240((u8 *)arg0 + 0x38, sp30);
    EventObjSetPos_2e7230((u8 *)arg0 + 0x38, sp20);
    TargetRefDetachFromParent_2e5890(arg0);
    TargetRefSetScale_2e5e10(arg0, sp40);
    TargetRefSetRotation_2e5d10(arg0, sp30);
    TargetRefSetTranslation_2e5bf0(arg0, sp20);
}
