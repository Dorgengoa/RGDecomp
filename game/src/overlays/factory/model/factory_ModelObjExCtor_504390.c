/* rgp:protos */
#define RGP_SELF_factory_ModelObjExCtor_504390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504390 -- 356 B / 89 words.  The big constructor:
 * chain up through 0x00504590, two four-element sub-object loops, two more
 * sub-object constructors, a 0x2C clear plus its field defaults, and finally
 * four 8-byte table slots each written three times.
 *
 * * The two loops have NO entry guard -- body first, test at the bottom -- so
 *   they are DO-WHILE, not `for`.  MEASURED (round trip 1, build/obj-fy06):
 *   the `for` spelling is the same function plus mwcc's two entry branches,
 *   0x170 instead of 0x164 -- one extra word on the first loop, two on the
 *   second (its guard needs the limit materialised in the delay slot).
 *   The second loop's induction variable IS the first one's limit register, so
 *   the two limits are the SAME expression `p->a248`.
 * * The store block at 0x4F0 is written in retail's order, not ascending:
 *   0x4F0, 0x4FC, 0x500, 0x4F8, 0x504, 0x508, 0x50C, 0x510, 0x514, 0x518,
 *   0x548, 0x54C, 0x550 ([[factory-list-ranking]]: a store block's order is
 *   SOURCE order even when it looks wrong).
 * * 0x508 takes `lui $2,0x3F80 / sw` -- an integer lui with no addiu, which is
 *   how mwcc stores a float constant whose low half is zero.
 * * The 0x570/0x578/0x580/0x588 slots are each stored THREE times with three
 *   different table addresses and a zero into +4 between the second and the
 *   third.  That is a constructor chain, one layer per store; the first two
 *   are dead by any dataflow reading and retail keeps them.
 */

typedef struct Elem8 { u8 d[8]; } Elem8;

typedef struct Slot390 {
    void *t;      /* +0 */
    s32   x;      /* +4 */
} Slot390;

typedef struct Fac390 {
    u8       pad000[0x1B0];
    void    *t1B0;                    /* 0x1B0 */
    u8       pad1B4[0x228 - 0x1B4];
    Elem8    a228[4];                 /* 0x228 */
    Elem8    a248[4];                 /* 0x248 */
    u8       pad268[0x270 - 0x268];
    u8       f270[0x430 - 0x270];     /* 0x270 */
    u8       f430[0x4F0 - 0x430];     /* 0x430 */
    s32      f4F0;                    /* 0x4F0 */
    s32      f4F4;
    s32      f4F8;
    s32      f4FC;
    s32      f500;
    s32      f504;
    f32      f508;
    s32      f50C;
    s32      f510;
    s32      f514;
    s32      f518;
    u8       pad51C[0x548 - 0x51C];
    s32      f548;                    /* 0x548 */
    s32      f54C;
    s32      f550;
    u8       pad554[0x568 - 0x554];
    u8       f568[8];                 /* 0x568 */
    Slot390  s570[4];                 /* 0x570 */
} Fac390;

extern u8 D_00470ED0[];
extern u8 D_00470FB0[];
extern u8 D_0047CE40[];
extern u8 D_0047CE20[];
extern u8 D_0047CE00[];
extern u8 D_0047CDE0[];
extern u8 D_0047CDC0[];
extern u8 D_0047CDA0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  memset(void *p, s32 v, s32 n);
/*rgp*/

Fac390 *factory_ModelObjExCtor_504390(Fac390 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    Elem8 *e;

    factory_ModelObjBaseCtor_504590(p, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    p->t1B0 = D_00470ED0;

    e = p->a228;
    do {
        factory_ModelAttachSlotCtor_504570(e);
        e++;
    } while (e < p->a248);

    e = p->a248;
    do {
        factory_ModelAttachSlotCtor_504570(e);
        e++;
    } while (e < &p->a248[4]);

    factory_ModelCtor_504520(p->f270, 0, 0, 0);
    factory_ModelObjShadowFrameMapCtor_504500(p->f430);

    p->t1B0 = D_00470FB0;
    memset(&p->f4F0, 0, 0x2C);

    p->f4F0 = -1;
    p->f4FC = -1;
    p->f500 = -1;
    p->f4F8 = 1;
    p->f504 = 1;
    p->f508 = 1.0f;
    p->f50C = 0;
    p->f510 = -1;
    p->f514 = 0;
    p->f518 = 0;
    p->f548 = 0;
    p->f54C = 0;
    p->f550 = 0;

    MotionEventListClear_1b4aa0(p->f568);

    p->s570[0].t = D_0047CE40;
    p->s570[0].t = D_0047CE20;
    p->s570[0].x = 0;
    p->s570[0].t = D_0047CE00;

    p->s570[1].t = D_0047CE40;
    p->s570[1].t = D_0047CE20;
    p->s570[1].x = 0;
    p->s570[1].t = D_0047CDE0;

    p->s570[2].t = D_0047CE40;
    p->s570[2].t = D_0047CE20;
    p->s570[2].x = 0;
    p->s570[2].t = D_0047CDC0;

    p->s570[3].t = D_0047CE40;
    p->s570[3].t = D_0047CE20;
    p->s570[3].x = 0;
    p->s570[3].t = D_0047CDA0;

    return p;
}
