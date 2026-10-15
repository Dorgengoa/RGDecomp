#include "types.h"
/* normal 0x004F2280 -- BYTE-IDENTICAL (s23).  Two levers, and NEITHER is
 * reachable on its own axis -- they are the two coordinates of one cell.
 *
 * (1) THE LOOP LATCH IS THE OR-EQUAL FORM.  Retail's latch compare lands in
 *     `$at` (`slti $1, $17, 0x9C` feeding a `bnel`); [[at-compare-class]] says
 *     at a LATCH only the "or-equal" spellings give `$at`.  So `i <= 0x9B`,
 *     not `i < 0x9C`.  That fix left the bad count at 11 and moved `slti $3`
 *     to `slti $1` -- judged on the count alone it reads inert.
 *
 * (2) THE CALLEE-SAVED QUARTET IS A 2-D LATTICE: WHERE `n` IS INITIALISED x
 *     THE DECLARATION ORDER.  Ours was $16..$19 = v,n,h,i; retail is v,i,h,n.
 *     s22 swept each axis ALONE -- 120 declaration permutations (floor 11, 5
 *     counts) and 5 placements of `n` (4 objects, floor 11) -- and both floors
 *     are 11 because the winning cell is OFF BOTH AXES.  Measured here:
 *       - declaration order alone, on the s22 base: floor 11.
 *       - `n = 0` position alone, on the s22 declaration order: floor 11.
 *       - `n` declared BEFORE `h` and `h` before `i` (any positions for `e`
 *         and `t`), with `n = 0` moved after the four `v->` stores: MATCH.
 *     24 further cells on the winning declaration base: 8 objects, and only
 *     `n = 0` immediately before the `func_1FDB50` call reaches it -- `n = 0`
 *     as the FIRST statement (the s22 spelling) is 23 bad on this base.
 *  => Same discipline as [[normal-cse-cost-split]]'s close: a sweep that moves
 *  ONE variable of a coupled pair only ever tests a LINE through the lattice,
 *  and every such line here has the same floor.  Sweep the SECOND axis on the
 *  winner of the first, not on the base you started from.
 */
typedef struct V {
    s32 f00;
    s32 f04;
    s32 f08;
    f32 f0C;
} V;

typedef struct E {
    u8  pad000[0xA44];
    s32 fA44;
} E;

typedef struct T {
    u8 pad000[0x10];
} T;

extern s32  func_1FDB50(void);
extern E   *func_233B50(s32 h, s32 id);
extern void func_2388A0(E *e, T *out);
extern void func_1CBDC0(V *a, V *b, T *t);
extern void func_1CBBC0(V *a, V *b, f32 n);

void normal_FieldHudGetEnemyCentroid_4f2280(V *v)
{
    E  *e;
    s32 n;
    s32 h;
    s32 i;
    T   t;

    v->f00 = 0;
    v->f04 = 0;
    v->f08 = 0;
    v->f0C = 1.0f;
    n = 0;
    h = func_1FDB50();
    for (i = 0x80; i <= 0x9B; i++) {
        e = func_233B50(h, i);
        if (e != NULL) {
            if (!(e->fA44 & 0x80000)) {
                func_2388A0(e, &t);
                func_1CBDC0(v, v, &t);
                n++;
            }
        }
    }
    if (n > 0) {
        func_1CBBC0(v, v, (f32)n);
    }
}
