/* rgp:protos */
#define RGP_SELF_insect_ModelObjExCtor_4f78f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F78F0 -- 356 bytes, 89 instructions, 7 calls, 2 conditional
 * branches, br/ins 0.022.  From x_band.py's branch-light band.
 *
 * A constructor.  The two vptr writes at +0x1B0 (0x470ED0 then 0x470FB0, the
 * base-then-derived pair) and the four three-store groups at +0x570/578/580/588
 * are raw stores through `volatile` members, which is overlay-c-pipeline's
 * recipe: a real C++ constructor would emit OUR vtable into the object's
 * .rodata, and without `volatile` mwcc deletes every store but the last as
 * dead.  Each group is base vptr, derived vptr, the +4 field, final vptr --
 * exactly the order the listing has.
 *
 * `lui $r, 0x48` + `addiu $r, $r, -0x2Fxx` is a %hi/%lo SYMBOL pair, not an
 * integer constant: 0x47D110's low half is negative so %hi carries.  Written as
 * an integer mwcc emits one shared `lui 0x47` and six `ori`s -- five words
 * short and the wrong mnemonic.  The eight addresses are main-image vtables,
 * declared as unsized externs so they can never be small data.
 *
 * `lui $2, 0x3F80` + `sw` (not `mtc1`/`swc1`) is how mwcc stores a float
 * constant whose low half is zero, so +0x508 is an `f32` assigned 1.0f.
 *
 * The two `insect_ModelAttachSlotCtor_4f7ad0` loops have TWO walking pointers, not one:
 * retail keeps $18 and $17 and computes `o + 0x248` INSIDE the first loop as
 * its bound, then starts the second loop from the same register -- the two
 * `(u8 *)o + 0x248` expressions are ONE CSE and mwcc materialises it at the
 * earlier, in-loop site.  One shared variable is a callee-saved register and
 * two words short; a `for` adds an entry `b` at each loop, so both are
 * `do`/`while`.
 */

typedef struct Vsub {
    volatile u8 *vptr;              /* +0x00 */
    s32          f04;               /* +0x04 */
} Vsub;

typedef struct Ins {
    u8           pad000[0x1B0];
    volatile u8 *f1B0;              /* +0x01B0 */
    u8           pad1B4[0x4F0 - 0x1B4];
    s32          f4F0;              /* +0x04F0 */
    u8           pad4F4[0x4F8 - 0x4F4];
    s32          f4F8;              /* +0x04F8 */
    s32          f4FC;              /* +0x04FC */
    s32          f500;              /* +0x0500 */
    s32          f504;              /* +0x0504 */
    f32          f508;              /* +0x0508 */
    s32          f50C;              /* +0x050C */
    s32          f510;              /* +0x0510 */
    s32          f514;              /* +0x0514 */
    s32          f518;              /* +0x0518 */
    u8           pad51C[0x548 - 0x51C];
    s32          f548;              /* +0x0548 */
    s32          f54C;              /* +0x054C */
    s32          f550;              /* +0x0550 */
    u8           pad554[0x570 - 0x554];
    Vsub         f570[4];           /* +0x0570 */
} Ins;

extern u8 D_00470ED0[];
extern u8 D_00470FB0[];
extern u8 D_0047D070[];
extern u8 D_0047D090[];
extern u8 D_0047D0B0[];
extern u8 D_0047D0D0[];
extern u8 D_0047D0F0[];
extern u8 D_0047D110[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(u8 *p, s32 v, s32 n);
/*rgp*/

Ins *insect_ModelObjExCtor_4f78f0(Ins *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    u8 *p;
    u8 *q;

    insect_ModelObjBaseCtor_4f7af0((void *)o, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    p = (u8 *)o + 0x228;
    o->f1B0 = D_00470ED0;
    do {
        insect_ModelAttachSlotCtor_4f7ad0(p);
        p += 8;
    } while (p < (u8 *)o + 0x248);
    q = (u8 *)o + 0x248;
    do {
        insect_ModelAttachSlotCtor_4f7ad0(q);
        q += 8;
    } while (q < (u8 *)o + 0x268);
    insect_ModelCtor_4f7a80((u8 *)o + 0x270, 0, 0, 0);
    insect_ModelObjShadowFrameMapCtor_4f7a60((u8 *)o + 0x430);
    o->f1B0 = D_00470FB0;
    memset((u8 *)o + 0x4F0, 0, 0x2C);
    o->f4F0 = -1;
    o->f4FC = -1;
    o->f500 = -1;
    o->f4F8 = 1;
    o->f504 = 1;
    o->f508 = 1.0f;
    o->f50C = 0;
    o->f510 = -1;
    o->f514 = 0;
    o->f518 = 0;
    o->f548 = 0;
    o->f54C = 0;
    o->f550 = 0;
    MotionEventListClear_1b4aa0((u8 *)o + 0x568);
    o->f570[0].vptr = D_0047D110;
    o->f570[0].vptr = D_0047D0F0;
    o->f570[0].f04 = 0;
    o->f570[0].vptr = D_0047D0D0;
    o->f570[1].vptr = D_0047D110;
    o->f570[1].vptr = D_0047D0F0;
    o->f570[1].f04 = 0;
    o->f570[1].vptr = D_0047D0B0;
    o->f570[2].vptr = D_0047D110;
    o->f570[2].vptr = D_0047D0F0;
    o->f570[2].f04 = 0;
    o->f570[2].vptr = D_0047D090;
    o->f570[3].vptr = D_0047D110;
    o->f570[3].vptr = D_0047D0F0;
    o->f570[3].f04 = 0;
    o->f570[3].vptr = D_0047D070;
    return o;
}
