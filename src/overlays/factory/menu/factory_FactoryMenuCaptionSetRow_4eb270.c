#include "types.h"

/* factory.bin overlay, 0x004EB270 -- reposition the shared caption window onto
 * one of eight fixed rectangles, taken from a stack copy of the table.
 * 164 bytes, 41 instructions, 1 conditional branch, 2 calls.
 *
 * ★★ THE COPY LOOP'S UNIT SIZE COMES FROM THE EXTERN'S DECLARED FORM, NOT FROM
 * ITS MEMBERS.  `extern Tbl D_0050B480; t = D_0050B480;` copies in QUADWORDS --
 * `lq/lq/sq/sq` with a 0x20 stride and a trip count of 4 -- because mwcc gives a
 * complete struct object 16-byte alignment.  The INCOMPLETE ARRAY spelling
 * `extern Tbl D_0050B480[]; t = D_0050B480[0];` is 4-aligned, so the same
 * compiler-generated copy comes out as `lw/lw/sw/sw` with a 0x8 stride and a
 * trip count of 0x10 -- retail exactly.  Measured: 7 wrong words -> 0.
 * The member spelling is a MEASURED NULL on this: `s32 v[32]`, `Pair p[16]`,
 * `Rect{Pair,Pair}` and `#pragma optimization_level 3` all produce a
 * BYTE-IDENTICAL object to the 16-byte-unit baseline.
 *
 * * `lw $16, -0x498C($28)` sits ABOVE the loop because a gp load will not move
 * above a store -- naming the handle BEFORE the copy is what puts it there
 * ([[factory-gp-load-placement]]).
 *
 * * `daddu $9, $6, $0` is mwcc reusing the register that already holds 0x14 for
 * the sixth argument: both really are the literal 20.
 */

typedef struct Rect {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
} Rect;                                         /* 0x10 */

typedef struct Tbl {
    Rect r[8];
} Tbl;                                          /* 0x80 */

extern void *D_004807E4;                        /* _gp - 0x498C */
extern Tbl   D_0050B480[];

extern void func_28FD70(void *w, s32 id, s32 x, s32 y, s32 cx, s32 cy, s32 n);
extern void func_28F9D0(void *w, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);

void factory_FactoryMenuCaptionSetRow_4eb270(s32 i)
{
    Tbl   t;
    void *w;

    w = D_004807E4;
    t = D_0050B480[0];
    func_28FD70(w, 0xD, 0x14, 0x16, 0x56, 0x14, 0);
    func_28F9D0(w, 0xD, t.r[i].f00, t.r[i].f04, t.r[i].f08, t.r[i].f0C, 0);
}
