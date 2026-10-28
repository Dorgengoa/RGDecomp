/* rgp:protos */
#define RGP_SELF_insect_InsectPieceLoadFromSource_515da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00515DA0 -- 604 bytes, 151 instructions.
 *
 * Four `beql` compares INTO their blocks == a `switch`, so the source case
 * order is the compare chain (6, 5, 4, 3) REVERSED -- 3, 4, 5, 6 -- and the
 * block addresses (0x515EAC, 0x515EE4, 0x515F0C, 0x515F3C) agree with that.
 * `v = 0;` lands in the first compare's delay slot. */

typedef struct Host {
    u8  pad00[0x18];
    s32 f18;                        /* +0x18 */
    u8  pad1C[0x24 - 0x1C];
    s32 f24;                        /* +0x24 */
} Host;

typedef struct Rec {
    u8  pad00[0x14];
    s32 f14;                        /* +0x14 */
} Rec;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectPieceLoadFromSource_515da0(void *o, s32 kind, s32 a, s32 b, s32 p, s32 q)
{
    Host *h;
    Rec *r;
    s32 v;
    s32 t;
    s32 i;
    s32 tbl[0x20] __attribute__((aligned(16)));

    h = ((Host *)GetGameData_1fede0());
    if (h == 0) {
        return;
    }
    if (p == -1 && q == -1) {
        if (kind == 0) {
            for (i = 0; i < 0x20; i++) {
                tbl[i] = 0;
            }
            if (a == 0) {
                InvCollectInsects_3c4d90(h->f18, tbl, 0x20);
                v = tbl[b];
                if (v != 0) {
                    insect_InsectPieceLoadFromItem_516360(o, v, 0, 0);
                    insect_InsectPieceSetSide_516000(o, a);
                    insect_InsectPieceSetStatus_5132d0(o, 0x1B);
                }
            }
        } else {
            v = 0;
            switch (kind) {
            case 3:
                v = (s32)(((u8 *)RecordGetPayloadIfKind1E_430b70(h->f24)) + (a * 0x258) + (b * 0x28) + 0x10);
                break;
            case 4:
                t = (s32)(((u8 *)RecordGetPayloadIfKind28_430b50(h->f24)) + (b * 0x28));
                v = t + 0x14;
                if (a != 0) {
                    v = t + 0x288;
                }
                break;
            case 5:
                v = (s32)(((u8 *)RecordGetPayloadIfKind32_430b30(h->f24)) + (a * 0xE0) + (b * 0x28) + 0x28);
                break;
            case 6:
                v = (s32)(((u8 *)RecordGetPayloadIfKind3D_430af0(h->f24)) + (b * 0x28) + 0xF4);
                break;
            }
            if (v != 0) {
                insect_InsectPieceLoadFromVsRecord_516020(o, v);
                insect_InsectPieceSetSide_516000(o, a);
                insect_InsectPieceSetStatus_5132d0(o, 0x1B);
            }
        }
    } else {
        r = ((Rec *)InsectronEnemyTeamFindMaybe_3e8490(h, p, q + 1));
        if (r != 0) {
            v = r->f14 + (b * 0x28);
            if (v != 0) {
                insect_InsectPieceLoadFromStoryDef_516180(o, v);
                insect_InsectPieceSetSide_516000(o, a);
                insect_InsectPieceSetStatus_5132d0(o, 0x1B);
            }
        }
    }
}
