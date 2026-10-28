/* rgp:protos */
#define RGP_SELF_normal_ShopMenuStep_50a6f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050A6F0 -- the shop/list panel's three-object build (0x27C40,
 * 0x27C60, 0x27C80), the 8 x 0x20 palette blit, then the phase-2 poll.
 * # m2c gives func_42C950 SIX arguments; the last four are the LEFTOVER
 * registers of the bitfield store above it -- the call takes two.
 * # func_15DE40 takes NO argument; `lh $4, -0xB90` is the compare operand of
 * the guard, left sitting in $4. */

extern u8 normal_D_00525A30;
extern u8 D_004B2570[0x10];            /* main-image object; retail materialises it
                                    as lui/addiu, i.e. an ADDRESS not an int */

typedef struct Panel {
    u8   pad000[8];
    s32  f008;
} Panel;
extern Panel normal_D_00527C40;          /* +0x08 = normal_D_00527C48 */
extern Panel normal_D_00527C60;          /* +0x08 = normal_D_00527C68 */

/* normal_D_00527C98 / normal_D_00527CA0 / normal_D_00527CA1 are MEMBERS of normal_D_00527C80, not small
 * globals: retail addresses all three with lui/%lo, and a separate 1/4-byte
 * extern lands in SMALL DATA and comes out GPREL16 -- right instruction, wrong
 * relocation, and four words short.  Same for D_004B2570, which needs a size
 * over the small-data threshold to be materialised as an address. */
typedef struct Obj3 {
    u8   pad000[0x18];
    s32  f018;
    u8   pad01C[4];
    u8   b020 : 1;
    s8   f021;
} Obj3;
extern Obj3 normal_D_00527C80;

extern s16   D_004845E0;          /* gp - 0xB90 */
extern u8    D_004845DC;          /* gp - 0xB94 */
extern void *D_004845AC;          /* gp - 0xBC4 */
extern s32   D_004845A8;          /* gp - 0xBC8 */
extern s16   D_004845B8;          /* gp - 0xBB8 */
extern s32   D_004845BC;          /* gp - 0xBB4 */
extern s32   D_004845C0;          /* gp - 0xBB0 */
extern s16   D_00480638;          /* gp - 0x4B38 */
extern f32   D_0047D934;          /* gp - 0x783C */

typedef struct Ent {
    u8   pad000[4];
    s32  f004;
    u8   pad008[2];
    u16  f00A;
} Ent;

typedef struct Slot {
    void *f00;
    s16   f04;
    s16   f06;
    s16   f08;
    s16   f0A;
    u16   f0C;
} Slot;

typedef struct Wid {
    u8   pad000[0x24];
    s32  f024;
} Wid;

extern void memcpy(s32 dst, const u8 *src, s32 n);
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_ShopMenuStep_50a6f0(void)
{
    Slot sl __attribute__((aligned(16)));
    Ent *e;
    s32 o;
    s32 n;
    u64 h;
    s32 dst;
    s32 i;
    s32 t;

    if (D_004845E0 != 0) {
        if (D_004845DC != 0) {
            o = ((s32)GetMenuResGroup_206a40());
            e = ((Ent *)ResGroupListFindById_42c500(o, 5));
            n = e->f004;
            h = ((u64)e->f00A << 48) >> 50;
            UiWidgetListReset_2912e0(&normal_D_00527C40);
            UiInitWidgetPool_290390(&normal_D_00527C40, D_004845AC, (int)(h));
            UiAddWidgets_2901d0(&normal_D_00527C40, n, 0);
            normal_D_00527C40.f008 = 0x32D;
            UiTextStyleReset_290450();
            sl.f00 = &normal_D_00527C40;
            sl.f04 = 0x3D;
            sl.f06 = 0x3C;
            sl.f08 = 0x3E;
            sl.f0A = 0x38;
            sl.f0C = 0x39;
            MenuPanelGridAlloc_28b660(D_004845AC, &sl);
            dst = ((Wid *)UiFindWidget_290460(sl.f00, sl.f0C))->f024;
            i = 0;
            do {
                memcpy(dst, &normal_D_00525A30, 0x20);
                i += 1;
                dst += 0x20;
            } while (i < 8);
            e = ((Ent *)ResGroupListFindById_42c500(o, 6));
            n = e->f004;
            h = ((u64)e->f00A << 48) >> 50;
            UiWidgetListReset_2912e0(&normal_D_00527C60);
            UiInitWidgetPool_290390(&normal_D_00527C60, D_004845AC, (int)(h));
            UiAddWidgets_2901d0(&normal_D_00527C60, n, 0);
            normal_D_00527C60.f008 = 0x32D;
            UiTextStyleReset_290450();
            e = ((Ent *)ResGroupListFindById_42c040(o, 5));
            n = e->f004;
            h = ((u64)e->f00A << 48) >> 50;
            UiEntryListReset_28ec80(&normal_D_00527C80);
            UiEntryListAlloc_28e0c0(&normal_D_00527C80, D_004845AC, (int)(h));
            UiEntryListLoad_28eb70(&normal_D_00527C80, n, &normal_D_00527C40);
            normal_D_00527C80.f018 = D_004845A8;
            normal_D_00527C80.b020 = 0;
            normal_D_00527C80.f021 = 0;
            D_004845BC = 0;
            D_004845C0 = 0;
            D_004845B8 = 0;
            D_004845C0 = MenuStateTableForId_42c950(o, 5);
            PadClearRepeatAll_183960(D_004B2570);
            PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xC, 7);
            PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
            UiSetWidgetsVisibleById_291110(&normal_D_00527C40, 4, 0, 1);
            UiSetWidgetAlpha_2907a0(&normal_D_00527C40, 4, 0.0f);
            UiSetWidgetPos_290f60(&normal_D_00527C40, 0xE, 0, -0x1E);
            UiSetWidgetsVisibleById_291110(&normal_D_00527C40, 1, 1, 1);
            UiFadeWidgetAlpha_290690(&normal_D_00527C40, 1, 1.0f, D_0047D934, 0.0f);
            UiSetWidgetsVisibleById_291110(&normal_D_00527C40, 3, 1, 1);
            UiFadeWidgetAlpha_290690(&normal_D_00527C40, 3, 1.0f, D_0047D934, 0.0f);
            D_004845DC = 0;
            D_004845E0 = 2;
        }
        if (D_00480638 == 1) {
            if (D_004845E0 == 2) {
                t = ((s32)GetWorldDataMgr_1fedf0());
                if (!(UiGetWidgetAlpha_290770(&normal_D_00527C40, 1) < 1.0f)) {
                    if (WorldDataMgrNoRequestPending_3eef10(t) != 0) {
                        D_00480638 = 0;
                        StateMachineSetState_28ede0(&D_004845B8, 0x7531, 1);
                    }
                }
            }
        }
        normal_ShopMenuResPoll_50ae40();
        if (D_004845E0 == 2) {
            t = GetDrawCtxNameTable_15de40();
            if (t != 0) {
                TexGroupUpdateAnim_157ca0(t, 0x32E, 1.0f);
            }
            UiUpdateWidgets_2913a0(&normal_D_00527C40);
            UiUpdateWidgets_2913a0(&normal_D_00527C60);
            StateMachineUpdate_28ed70(&D_004845B8);
        }
    }
}
