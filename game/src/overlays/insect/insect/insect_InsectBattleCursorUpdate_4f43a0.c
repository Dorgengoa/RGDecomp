/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCursorUpdate_4f43a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F43A0 -- 388 bytes.  Thirteen parameters: eight in $4..$11 and
 * five in the 8-byte incoming stack slots at $29+0xA0..0xC0.  Two Node handles
 * are picked out of insect_D_00525FF0 by index and each falls back to o->f87C when the
 * element address is null. */

typedef struct Node {
    u8 pad00[0x14];                 /* stride 0x14 */
} Node;

typedef struct Rec {
    u8 pad00[0x8];
    s8 f08;                         /* +0x08 */
    s8 f09;                         /* +0x09 */
} Rec;

typedef struct Ins {
    u8    pad0000[0x87C];
    void *f87C;                     /* +0x087C */
    u8    pad0880[0x4F90 - 0x880];
    u8    f4F90[4];                 /* +0x4F90 */
} Ins;

extern Node insect_D_00525FF0[];

/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleCursorUpdate_4f43a0(Ins *o, s32 k, s32 i0, s32 i1, s32 dx, s32 dy,
                         s32 a7, s32 a8, s32 a9, s32 id0, s32 id1,
                         s32 tx, s32 ty)
{
    s32   xa;
    s32   xb;
    Rec  *r;
    void *p;
    void *q;
    s32   n8;
    s32   n9;

    r = ((Rec *)insect_InsectCursorSetFindPage_511e60(o->f4F90, k));
    p = &insect_D_00525FF0[i0];
    q = &insect_D_00525FF0[i1];
    if (p == 0) {
        p = o->f87C;
    }
    if (q == 0) {
        q = o->f87C;
    }
    if (r == 0) {
        return;
    }
    n8 = r->f08;
    n9 = r->f09;
    xb = 0;
    xa = 0;
    if (id0 != -1) {
        UiGetWidgetAbsPos_290fc0(p, id0, &xa, &xb);
    }
    insect_InsectBattleCursorPlace_4f4260(o, xa + dx, xb + dy, n8, n9, a7, a8, a9);
    if (id1 != -1) {
        UiSetWidgetPos_290f60(q, id1, tx, ty + n9 * a8);
    }
    if (UiGetWidgetAlpha_290770(o->f87C, 0xC37E) <= 0.0f) {
        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
    }
}
