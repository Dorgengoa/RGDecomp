/* rgp:protos */
#define RGP_SELF_insect_InsectTeamBuild_513920 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00513920 -- 972 bytes, 244 instructions, 38 calls, 22 conditional
 * branches.  Loads a five-slot party/formation display.
 *
 * The a3 dispatch is a beq/beql CHAIN testing 6,5,4,3 so the SOURCE order is
 * the reverse: 3,4,5,6 -- and the block addresses (513AB4, 513AE0, 513B00,
 * 513B24) run forwards in that same order, which is the cross-check.
 *
 * `func_133710() % 5` is a mfhi site, so it is BARE -- no divbyzerocheck.
 *
 * The two early returns must share ONE `||` join: `if (a == 0) return;` +
 * `if (h == 0) return;` as two statements is EIGHT WORDS SHORT and both an
 * explicit `else` and the `&&` form are byte-identical to it (INERT).
 *
 * The last loop's element pointer is its OWN local `ep`, not a reuse of the
 * switch's `p`: reusing `p` splits the live range the wrong way for 8 bad
 * words, and the new local's DECLARATION POSITION is inert (3 positions, one
 * object e5a6da5b).
 *
 * The two discarded insect_InsectTeamSlotGetEnemyKeyMaybe_513e90/e80 calls at 513BF4/513BFC are real:
 * their results are never read and mwcc keeps the calls for their side effects.
 */

typedef struct Obj { u8 pad000[0x98E]; s8 f98E; } Obj;

typedef struct Hnd {
    u8  pad00[0x18];
    s32 f18;                    /* +0x18 */
    u8  pad1C[0x24 - 0x1C];
    s32 f24;                    /* +0x24 */
} Hnd;

typedef struct It {
    u8  pad00[0x4];
    s32 f04;                    /* +0x04 */
    s8  f08;                    /* +0x08 */
    u8  pad09[0x10 - 0x9];
    s8  f10;                    /* +0x10 */
    u8  pad11[0x14 - 0x11];
    s8 *f14;                    /* +0x14 */
} It;

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

void insect_InsectTeamBuild_513920(Obj *o, void *a, s32 idx, s32 kind)
{
    s32   t[0x20] __attribute__((aligned(16)));
    Hnd  *h;
    It   *it;
    s8   *p;
    s8   *b;
    s32   sel;
    s32   n;
    s32   v;
    s8   *ep;
    void *q;
    s32   i;

    h = ((Hnd *)GetGameData_1fede0());
    if (a == 0 || h == 0) {
        return;
    }
    {
    if (((short)insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(a)) == -1 || ((short)insect_InsectTeamSlotGetEnemyRowMaybe_513e80(a)) == -1) {
        if (insect_InsectTeamSlotIsFull_513f10(a) != 0) {
            if (kind == 0) {
                insect_InsectTeamSetName_513910(o, insect_InsectTeamSlotGetName_513e00(a));
                for (i = 0; i < 0x20; i++) {
                    t[i] = 0;
                }
                InvCollectInsects_3c4d90(h->f18, t, 0x20);
                for (i = 0; i < 5; i++) {
                    v = t[insect_InsectTeamSlotGetMember_513eb0(a, i)];
                    if (v != 0) {
                        q = insect_InsectTeamGetPiece_5138d0(o, i);
                        if (q != 0) {
                            insect_InsectPieceLoadFromItem_516360(q, v, 0, 0);
                            insect_InsectPieceSetSide_516000(q, o->f98E);
                            insect_InsectPieceSetStatus_5132d0(q, 0x1B);
                        }
                    }
                }
            } else {
                p = 0;
                sel = -1;
                switch (kind) {
                case 3:
                    p = ((s8 *)RecordGetPayloadIfKind1E_430b70(h->f24)) + idx * 0x258 + 0x10;
                    break;
                case 4:
                    b = ((s8 *)RecordGetPayloadIfKind28_430b50(h->f24));
                    p = b + 0x14;
                    if (idx != 0) {
                        sel = b[0x27F];
                        p = b + 0x288;
                    }
                    break;
                case 5:
                    b = ((s8 *)RecordGetPayloadIfKind32_430b30(h->f24)) + idx * 0xE0;
                    sel = b[0x1F];
                    p = b + 0x28;
                    break;
                case 6:
                    p = ((s8 *)RecordGetPayloadIfKind3D_430af0(h->f24)) + 0xF4;
                    break;
                }
                insect_InsectTeamSetField98CRelated_513900(o, Rand_133710() % 5);
                insect_InsectTeamSetName_513910(o, insect_InsectTeamSlotGetName_513e00(a));
                for (i = 0; i < 5; i++) {
                    n = insect_InsectTeamSlotGetMember_513eb0(a, i);
                    q = insect_InsectTeamGetPiece_5138d0(o, i);
                    if (q != 0) {
                        insect_InsectPieceLoadFromVsRecord_516020(q, p + n * 0x28);
                        insect_InsectPieceSetSide_516000(q, o->f98E);
                        insect_InsectPieceSetStatus_5132d0(q, 0x1B);
                        if (sel == i) {
                            insect_InsectPieceSetStatus_5132d0(q, 0x1A);
                        }
                    }
                }
            }
        }
    } else {
        insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(a);
        insect_InsectTeamSlotGetEnemyRowMaybe_513e80(a);
        it = ((It *)InsectronEnemyTeamFindMaybe_3e8490(h, ((short)insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(a)), ((short)insect_InsectTeamSlotGetEnemyRowMaybe_513e80(a)) + 1));
        if (it != 0) {
            insect_InsectTeamSetName_513910(o, it->f04);
            insect_InsectTeamSetField98CRelated_513900(o, it->f08);
            insect_InsectTeamSetFormation_5138f0(o, it->f10);
            for (i = 0; i < 5; i++) {
                ep = it->f14 + i * 0x28;
                if (ep != 0) {
                    q = insect_InsectTeamGetPiece_5138d0(o, i);
                    if (q != 0) {
                        insect_InsectPieceLoadFromStoryDef_516180(q, ep);
                        insect_InsectPieceSetSide_516000(q, o->f98E);
                        insect_InsectPieceSetStatus_5132d0(q, 0x1B);
                    }
                }
            }
        }
    }
    }
}
