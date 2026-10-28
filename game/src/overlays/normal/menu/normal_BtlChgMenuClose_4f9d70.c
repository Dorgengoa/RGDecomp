/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuClose_4f9d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9D70 (496 B / 124 words) -- the gameplay panel's re-entry:
 * clear every row of panel normal_D_00527020, reset the two s16 cursor fields of the
 * global Obj, publish the 1/2 mode flag, then walk the party list once and
 * cancel any entry whose state reads 0xF.
 *
 * Read off the listing:
 *  - `bgezl $2 / bltzl $2` with the SAME gp reload in both delay slots is one
 *    `if (*q >= 0)`; the third `lw $2,-0xD1C($28)` at 0x004F9E10 is the
 *    branch-likely duplication, not a third load.
 *  - `beql/addiu $2,$0,1` + the duplicated `sh $2,-0xD0C($28)` is a single
 *    store site fed by an if/else, not two stores.
 *  - `addiu $18,$2,0x450` next to `lh $4,0x450($2)` is &o->f450 materialised
 *    once while the two argument loads fold the displacement
 *    (levers.d/mwcc-member-address-no-cse.md).
 */
typedef struct World World;
typedef struct Ctx  { u8 pad00[0x18]; World *f18; } Ctx;
typedef struct Obj  { u8 pad000[0x440]; s32 f440;
                      u8 pad444[0x450 - 0x444]; s16 f450; s16 f452; } Obj;
typedef struct Node { u8 pad00[0xC]; s16 *f0C; } Node;

extern u8 D_004B2570[];
extern u8 normal_D_00527020[];

extern Obj  *D_00484454;          /* gp - 0xD1C  */
extern s16   D_00484468;          /* gp - 0xD08  */
extern s16   D_00484464;          /* gp - 0xD0C  */
extern s16   D_004804DC;          /* gp - 0x4C94 */
extern s16   D_004804F0;          /* gp - 0x4C80; SCALAR so mwcc
                                   * small-data-addresses it: an
                                   * `s16 [7]` extern is 14 B > the
                                   * 8 B sdata threshold and costs a
                                   * lui/addiu pair instead of
                                   * retail's `addiu $6,$28,-0x4C80`
                                   * (levers.d/im-gp-array-sdata-threshold.md) */

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

void normal_BtlChgMenuClose_4f9d70(void)
{
    Ctx  *c;
    s32   i;
    s32   j;
    s16  *q;
    void *h;
    void *e;
    void *t;
    Node *r;
    s16  *src;
    s16  *dst;
    s32   cnt;
    s32   n;
    s32 __w72;
    s16   buf[7];

    c = ((Ctx *)GetGameData_1fede0());
    __w72 = PartyCountMembers_3c2010(c->f18, 1, 1);
    n = __w72;
    for (i = 0; i < n; i++) {
        normal_FieldHudPanelSetRaised_4f5310(normal_D_00527020, i, 0);
    }
    D_00484468 = 0;
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    q = &D_00484454->f450;
    ItemIconTexRelease_204c90(D_00484454->f450, D_00484454->f452);
    if (*q >= 0 || *q >= 0) {
        D_00484454->f450 = -1;
        D_00484454->f452 = -1;
    }
    if (D_00484454->f440 != 0) {
        D_00484464 = 2;
    } else {
        D_00484464 = 1;
    }
    normal_FieldHudAllySuggestShow_4f08a0(normal_D_00527020);
    h = normal_UiPageGetLayout_289b60(D_00484454);
    if (h == 0) {
        return;
    }
    src = &D_004804F0;
    dst = buf;
    for (cnt = 7; cnt > 0; cnt--) {
        *dst = *src;
        src++;
        dst++;
    }
    UiSetWidgetListVisible_28c120(h, buf, 0);
    for (j = 0; j < n; j++) {
        t = PartyGetMemberId_3c2490(c->f18, j);
        e = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), t);
        if (e == 0) {
            continue;
        }
        r = ((Node *)CharaGetExecInfo_2149f0(e));
        if (r == 0) {
            continue;
        }
        if (r->f0C == 0) {
            continue;
        }
        if (InvHasItemInCategory_3c7f40(c->f18, *r->f0C, 0, 0) != 0) {
            continue;
        }
        CharaRemoveFlags_212480(e, (unsigned long long)(0x20000000));
        if (((short)CharaGetActionKind_213840(e)) == 0xF) {
            CharaResetBattleStateMaybe_212f20(e, 0);
        }
    }
    D_004804DC = -1;
}
