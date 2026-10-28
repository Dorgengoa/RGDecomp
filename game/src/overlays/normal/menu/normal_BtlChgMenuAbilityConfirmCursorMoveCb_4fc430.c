/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuAbilityConfirmCursorMoveCb_4fc430 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FC430 -- copies four gp s16s into a 2x2 stack table, then feeds
 * one row of it, selected by a member index, to two calls.
 *
 * CLOSED 2026-09-01 (s22), 12 bad -> BYTE-IDENTICAL on ONE statement.  The four
 * element assignments are ONE AGGREGATE ASSIGNMENT THROUGH A CAST:
 *
 *     *(S4 *)t = *(S4 *)&D_004805B0;
 *
 * ★★ This GENERALISES [[mwcc-float-table-struct-copy]] off `f32`: that lever was
 * measured on four consecutive gp FLOAT externs and is stated in those terms.
 * The rule is about a CONTIGUOUS BLOCK of consecutive gp externs copied into a
 * contiguous local, and the element TYPE does not matter -- here they are s16
 * and the destination is a 2-D array, and the same cast lands retail's schedule
 * exactly.  The cast is load-bearing for the same reason: a declared struct
 * extern would read as aligned and collapse to a wider move.
 *
 * The elementwise arms measured first, all at the right length: source order
 * DESCENDING (the old base) 12 bad; ASCENDING 11; ascending with the last two
 * swapped 11 (a different object); with the first two swapped 12.  Four
 * distinct objects and none of them reaches it -- ⚠ an element-order sweep on
 * this shape is NOT the axis and its spread is misleading, because it moves the
 * count around while the batched-loads-then-stores pre-order that the aggregate
 * assignment produces is unreachable from any of them.
 */
typedef struct S4 { s16 a; s16 b; s16 c; s16 d; } S4;

typedef struct N {
    u8  pad000[0x10];
    s16 f10;
} N;

extern s16 D_004805B0;
extern s16 D_004805B2;
extern s16 D_004805B4;
extern s16 D_004805B6;
extern void *D_0048449C;

/*rgp*/

s32 normal_BtlChgMenuAbilityConfirmCursorMoveCb_4fc430(N *p)
{
    s16 t[2][2];
    s32 i;

    *(S4 *)t = *(S4 *)&D_004805B0;
    i = p->f10;
    UiSetSpriteU_28f930(D_0048449C, 0x46, t[i][0], 0);
    UiSetSpriteU_28f930(D_0048449C, 0x46, t[i][1], 1);
    return 1;
}
