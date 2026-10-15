/* normal 0x00514BB0 -- MATCH (byte-identical), session 31, lane n31e.
 * 2 scoring round trips (1 dv_osbuild + 2 nsweep sweeps, 19 arms).
 *
 * The s30 park record was ONE WORD SHORT (0x258 vs 0x25c) and every other
 * word was right.  The missing word is a HAZARD NOP retail carries between
 * `mtc1 v0,$f0` (the 3.0f constant) and `add.s $f0,$f0,$f21` at 0x00514CB8:
 * our schedule had an integer instruction left over to fill that slot and
 * retail did not.
 *
 * ****** THE LEVER IS VARIABLE REUSE, NOT STATEMENT ORDER.  The second
 * func_290F50 call's id must be assigned into the SAME local `id` the first
 * call used, not into a fresh `id2`.  `id` is dead after the first call (its
 * register s0 is overwritten by 38*i before the call even issues), so a
 * second definition of it is legal -- and it is what forces mwcc to emit
 * `addiu v0,s1,30006` / `andi a1,v0,0xFFFF` BEFORE the `lui v0,0x4040` of the
 * float constant.  With a fresh `id2` mwcc treats the value as a pure
 * argument temp, sinks it below the float, and the sunk `addiu a3,s0,82` then
 * fills the mtc1 hazard slot.  The two orders differ by a WAR edge on v0.
 *
 * MEASURED NULLS on this unit (18 arms, all still 151 words):
 *  - statement order around the second call: off2-first, sum-first, sum
 *    inlined in the call, id2 inlined, everything inlined, a named (s32)
 *    conversion local, a named 3.0f local, `sy + 3.0f` instead of `3.0f + sy`
 *    -- NINE arms, ONE object (61eb0bd9).  The source-order axis is dead here;
 *    only the DEFINITION IDENTITY moved it.
 *  - func_290F50 PROTOTYPE PARAMETER ORDER (float param moved to position
 *    1/3/4/5 with the ABI held fixed, and the void* moved last): five arms,
 *    four of them the same 61eb0bd9 object.  [[mwcc-prototype-param-order]]
 *    is SPENT on this unit.
 *  - `*(volatile f32 *)&sy` moves the object (595d2714) but not the length.
 *  - `s32 id` + an explicit `& 0xFFFF` at the call is TWO words short.
 */
#include "types.h"

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
} Box;

typedef struct Wk {
    u8  pad00[0x12];
    s16 f12;
} Wk;

extern f32   D_0047D240;   /* gp - 0x7F30 */
extern f32   D_0047D288;   /* gp - 0x7EE8 */
extern void *D_004846E8;   /* gp - 0xA88  */
extern void *D_00484710;   /* gp - 0xA60  */

extern Box *func_28FE10(void *w, u16 id, s32 n);
extern void func_2905B0(void *w, u16 id, f32 r, f32 g, f32 b, f32 a);
extern void func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 t);
extern void func_291110(void *w, u16 id, s32 a, s32 b);
extern void func_2911A0(void *w, u16 id, u16 a);
extern s32  normal_TransMenuCanWarp_5185a0(void);
extern s32  normal_TransMenuIsHunterUnlocked_5185e0(void);

s32 normal_TransMenuTopCursorMoveCb_514bb0(Wk *a)
{
    Box *p;
    Box *q;
    s32  i;
    u16  id;
    u16  id2;
    s32  off2;
    f32  sum;
    f32  sy;
    f32  sc;

    for (i = 0; i < 4; i++) {
        id = i + 0x753B;
        p = func_28FE10(D_004846E8, id, 0);
        if (a->f12 == i) {
            p->f0C = p->f0E = 0;
            p->f04 = p->f06 = 0;
            sy = 43.0f;
            sc = 192.0f;
            func_2911A0(D_004846E8, 0x753A, id);
            func_291110(D_004846E8, 0x753A, 1, 1);
        } else {
            p->f04 = 0x76;
            p->f06 = 0x1B;
            p->f0C = p->f0E = 4;
            sy = 33.0f;
            sc = 224.0f;
        }
        func_290F50(D_004846E8, id, (s32)sy, i * 0x26 + 0x4F, 0, D_0047D240);
        id = i + 0x7536;
        off2 = i * 0x26 + 0x52;
        sum = 3.0f + sy;
        func_290F50(D_004846E8, id, (s32)sum, off2, 0, D_0047D240);
        q = func_28FE10(D_004846E8, i + 0x754F, 0);
        if (q != 0) {
            q->f08 = (s32)sc;
            if (i == 1) {
                if (normal_TransMenuCanWarp_5185a0() != 0) {
                    func_2905B0(D_00484710, 0x7540, 1.0f, 1.0f, 1.0f, 1.0f);
                    q->f0A = 0x32;
                    q->f0C = q->f0E = 0x1F;
                } else {
                    func_2905B0(D_00484710, 0x7540, D_0047D288, D_0047D288, D_0047D288, 1.0f);
                    q->f08 = 0x90;
                    q->f0A = 0x26;
                    q->f0C = q->f0E = 0x20;
                }
            } else if (i == 2) {
                if (normal_TransMenuIsHunterUnlocked_5185e0() != 0) {
                    q->f0A = 0x52;
                    q->f0C = q->f0E = 0x1F;
                } else {
                    q->f08 = 0x90;
                    q->f0A = 0x26;
                    q->f0C = q->f0E = 0x20;
                }
            }
        }
    }
    return 1;
}
