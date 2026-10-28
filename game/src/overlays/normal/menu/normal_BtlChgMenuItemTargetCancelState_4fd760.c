/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuItemTargetCancelState_4fd760 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FD760 -- re-open the 0x55F3 record's frame.  The negative row
 * offset is `n * -50` (mwcc builds it out of shifts), the 0x25 slot uses the
 * CONTRACTED adda.s/madd.s form so the product must NOT be named here, and
 * only the SECOND out-parameter pair of func_2910A0 is written. */

typedef struct Rec {
    u8  pad00[8];
    s16 f08;
    s16 f0A;
    u8  pad0C[0x14 - 0xC];
    s16 f14;
    s16 f16;
    u8  pad18[2];
    s16 f1A;
} Rec;

typedef struct Node { u8 pad00[0x20]; s16 f20; } Node;
typedef struct Widget { u8 pad00[0x20]; Node *f20; } Widget;

extern void    *D_0048449C;       /* gp - 0xCD4  */
extern void    *D_004844A0;       /* gp - 0xCD0  */
extern void    *D_00484498;       /* gp - 0xCD8  */
extern s16      D_004844A8;       /* gp - 0xCC8  */
extern s16      D_004844AA;       /* gp - 0xCC6  */
extern s16      D_004844AC;       /* gp - 0xCC4  */
extern f32      D_004844B0;       /* gp - 0xCC0  */
extern s32      D_00480500;       /* gp - 0x4C70 */
extern s32      D_00480504;       /* gp - 0x4C6C */
extern s32      D_00480508;       /* gp - 0x4C68 */
extern u8 normal_D_005278E0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/

s32 normal_BtlChgMenuItemTargetCancelState_4fd760(void *unused, s32 show)
{
    Widget *w;
    Rec    *r;
    s32     n;
    s32     x;
    s32     y;

    if (show != 0) {
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x2A, 0, 1);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x43, 0, 1);
    }
    w = ((Widget *)UiFindWidget_290460(D_0048449C, 0x2A));
    if (w != NULL) {
        if (w->f20 != NULL) {
            w->f20->f20 = -1;
        }
    }
    r = ((Rec *)UiEntryListFindByTag_28ea40(D_004844A0, 0x55F3));
    r->f14 = D_004844A8;
    r->f16 = D_004844AA;
    n = D_004844AC;
    r->f1A = n;
    if (n < 0) {
        n = 0;
    }
    UiGetWidgetPos_2910a0(D_0048449C, 0x26, &x, &y);
    n = n * -50;
    UiSetWidgetPos_290f60(D_0048449C, 0x26, 0x1A, n + 0x1D);
    UiSetWidgetPos_290f60(D_0048449C, 0x27, 0x3C, n + 0x37);
    UiSetWidgetPos_290f60(D_0048449C, 0x23, 0, 0);
    UiSetWidgetPos_290f60(D_0048449C, 0x25, 0x183,
                (s32)(30.0f + (f32)r->f1A * D_004844B0));
    UiSelFrameSetRect_28db40(normal_D_005278E0, 0x28, r->f14 * r->f08 + 0x19,
                r->f16 * r->f0A + 0x17, 0x2A, 0x30, 0x2B, 0xD1);
    D_00480500 = r->f14;
    D_00480504 = r->f16;
    D_00480508 = r->f1A;
    StateMachineSetState_28ede0(D_00484498, 0x55FA, 0);
    return 1;
}
