/* rgp:protos */
#define RGP_SELF_normal_ShopMenuOpenState_50a390 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* MATCHED, s32 lane nc32n.  The 7-word residue the last three sessions parked
 * was a $2/$3 TRANSPOSE in loop 1: retail puts the i*38 row chain in $2 and the
 * i+9 widget id in $3, we had them the other way round and the `lui %hi` two
 * slots late.  The lever is that BOTH ids in loop 1 are the SAME VARIABLE `k`
 * with TWO definitions -- `k = i + 9;` (single use, its mask goes straight to
 * $5) then `k = i + 6;` (used twice, its mask lands in the callee-saved $17
 * that the row chain has just vacated).  One variable, two webs: the second
 * definition is what orders the two temps, and no amount of naming the row or
 * the id SEPARATELY reaches it -- a separate `u16 j` for the first id is
 * byte-identical to writing `i + 9` inline.
 * MEASURED HERE: 24 hand-built loop-1 spellings (row local, compound-assign
 * row, i*19*2, (u16) casts, id locals in both orders, operand reversal, arg
 * splits, do-while, s32 id param, u8* pointer param) all collapsed onto ONE
 * object, and the WHOLE 6,593-arm mwcc pragma surface (3,280 names x on/off
 * plus the numeric family) left loop 1 untouched: 17 live names, none of them
 * at the right length except opt_dead_assignments (9 bad).  The transpose was
 * never a spelling of the row or of the id -- it was the IDENTITY of the
 * variable that carries them. */
/* normal 0x0050A390 -- one-shot build of the normal_D_00527C40 panel's status block:
 * the 0x4/0x5 frame, two rows of 0x9+i / 0x6+i labels 38 apart, the two 0x16+i
 * gauges (whose f08/f0A are written through func_290460's f20 record), the
 * 0x10/0x11 corner marks and the 0x33 caption.  The 0xB tint depends on
 * func_3E7E10.  The tail runs on EVERY call and re-arms the 0x7532 event when
 * the 0x4 widget has gone.
 *
 * `$4` is never read -- another member of the f(void *, s32) state-handler
 * family; the guard is on `b`, and the function returns 1.
 * Loop 1's two ids are ONE u16 local `k` assigned twice: the first assignment
 * is single-use so its mask goes straight to $5, the second is used by two
 * calls so its mask takes the callee-saved $17.
 * `mtc1 / cvt.s.w / cvt.w.s / mfc1 / nop / sh` is an int that goes through
 * f32 and back: assigning an `(f32)` expression to an s16 field.  The `nop` is
 * the mfc1 hazard (levers.d/normal-mfc1-hazard-nop) and here it comes out of
 * the plain one-store spelling.
 * `addiu $4,$28,-0xBB8` is the ADDRESS of a gp scalar, not a load -- so
 * D_004845B8 has to stay under the small-data threshold.
 * `addiu $5,$0,0x5 / daddu $6,$5,$0 / daddu $7,$5,$0` is mwcc SHARING one
 * constant across three arguments, not three source constants. */

typedef struct Gauge { u8 pad00[8]; s16 f08; s16 f0A; } Gauge;
typedef struct Hold  { u8 pad00[0x20]; Gauge *f20; } Hold;

extern u8 normal_D_00527C40[];

extern s32 D_004845B8;            /* gp - 0xBB8  */

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

s32 normal_ShopMenuOpenState_50a390(void *a, s32 b)
{
    Gauge *g;
    u16    k;
    s32    i;

    if (b != 0) {
        UiSetWidgetsVisibleById_291110(normal_D_00527C40, 4, 1, 1);
        UiSetWidgetPos_290f60(normal_D_00527C40, 5, 5, 5);
        UiSetWidgetColor_2905b0(normal_D_00527C40, 5, 0.0f, 0.0f, 0.0f, 0.4f);
        UiSetWidgetPos_290f60(normal_D_00527C40, 4, -0x30, -0xF);
        UiMoveWidgetUniform_290f50(normal_D_00527C40, 4, 0, 0, 0.2f, 0);
        UiFadeWidgetAlpha_290690(normal_D_00527C40, 4, 1.0f, 0.05f, 0.0f);
        for (i = 0; i < 2; i++) {
            k = i + 9;
            UiSetWidgetPos_290f60(normal_D_00527C40, k, -0x40, i * 38 + 0x32);
            k = i + 6;
            UiSetWidgetPos_290f60(normal_D_00527C40, k, -0x3D, i * 38 + 0x35);
            UiSetWidgetColor_2905b0(normal_D_00527C40, k, 0.0f, 0.0f, 0.0f, 0.4f);
        }
        for (i = 0; i < 2; i++) {
            g = ((Hold *)UiFindWidget_290460(normal_D_00527C40, i + 0x16))->f20;
            g->f0A = (f32)(0x79 - i * 32);
            g->f08 = 0x93;
        }
        UiSetWidgetPos_290f60(normal_D_00527C40, 0x11, 0x104, -0x14);
        UiSetWidgetPos_290f60(normal_D_00527C40, 0x10, 0x107, -0x11);
        UiSetWidgetsVisibleById_291110(normal_D_00527C40, 0x33, 1, 1);
        UiSetWidgetAlpha_2907a0(normal_D_00527C40, 0x33, 0.0f);
        if (ShopListGetRowCount_3e7e10(GetGameData_1fede0()) == 0) {
            UiSetWidgetColor_2905b0(normal_D_00527C40, 0xB, 0.6f, 0.6f, 0.6f, 1.0f);
        } else {
            UiSetWidgetColor_2905b0(normal_D_00527C40, 0xB, 1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
    if (UiWidgetIsMoving_290d30(normal_D_00527C40, 4) == 0) {
        StateMachineSetState_28ede0(&D_004845B8, 0x7532, 1);
    }
    return 1;
}
