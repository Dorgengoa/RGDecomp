#include "types.h"
/* normal 0x004F8F10 -- the party-formation object's per-frame HINT-TIMER
 * driver.  Eight independent widget channels (0x83, 0x86, 0x81, 0x82, 0x7F,
 * 0x87, 0x50) each run the same three-statement idiom:
 *
 *     if (counter != 0 || weight(id) >= 1.0f) { if (++counter >= LIMIT) fade(); }
 *     if (weight(id) <= 0.0f) counter = 0;
 *
 * `counter != 0 || weight >= 1.0f` is what produces the `bnel`/`bc1tl` pair:
 * the second operand's guard is branch-likely and its delay slot carries the
 * duplicated head load of the increment block (levers.d/mwcc-branch-likely-
 * duplication.md).  `++counter` on an s16 member is the dsll32/dsra32 16
 * widening pair, so the limit compare is on the INCREMENTED register and not
 * on a reload (levers.d/normal-s16-cast-sign-extension.md).
 *
 * The 0x3D8 / 0x3DA blocks are countdowns, not fades, and both write the
 * counter to 0 in the CALL's delay slot -- store first, then call.
 * `D_0047DA6C` is the shared gp fade-rate float that normal_FUN_004F9670
 * (our own callee) already names.
 */

typedef struct Ent { u8 pad000[0xA]; s16 f00A; } Ent;
typedef struct Handle { u8 pad000[0x20]; Ent *f020; } Handle;

typedef struct Obj {
    u8  pad000[0x37E];
    s16 f37E;                       /* +0x037E */
    u8  pad380[0x3A2 - 0x380];
    s16 f3A2;                       /* +0x03A2 */
    u8  pad3A4[0x3D8 - 0x3A4];
    s16 f3D8;                       /* +0x03D8 */
    s16 f3DA;                       /* +0x03DA */
    u8  pad3DC[0x49C - 0x3DC];
    s16 f49C;                       /* +0x049C */
    s16 f49E;                       /* +0x049E */
    s16 f4A0;                       /* +0x04A0 */
    s16 f4A2;                       /* +0x04A2 */
    s16 f4A4;                       /* +0x04A4 */
    s16 f4A6;                       /* +0x04A6 */
} Obj;

extern f32 D_0047DA6C;              /* gp - 0x7704 */

extern Handle *func_290460(void *p, u16 id);
extern void    func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern f32     func_290770(void *p, u16 id);
extern void    func_2907A0(void *p, u16 id, f32 v);

extern void normal_FieldHudWidget80LiftCloseMaybe_4f9670(Obj *p, s32 b);
extern void normal_FieldHudWidget80CarryCloseMaybe_4f9770(Obj *p);

void normal_FieldHudHintTimersUpdateMaybe_4f8f10(Obj *p)
{
    Handle *h;
    Ent *e;

    if (p->f49E != 0 || func_290770(p, 0x83) >= 1.0f) {
        if (++p->f49E >= 60) {
            func_290690(p, 0x83, 0.0f, D_0047DA6C, -1.0f);
        }
    }
    if (func_290770(p, 0x83) <= 0.0f) {
        p->f49E = 0;
    }

    if (p->f4A6 != 0 || func_290770(p, 0x86) >= 1.0f) {
        if (++p->f4A6 >= 60) {
            func_290690(p, 0x86, 0.0f, D_0047DA6C, -1.0f);
        }
    }
    if (func_290770(p, 0x86) <= 0.0f) {
        p->f4A6 = 0;
    }

    if (p->f49C != 0 || func_290770(p, 0x81) >= 1.0f) {
        if (++p->f49C >= 30) {
            func_290690(p, 0x81, 0.0f, D_0047DA6C, -1.0f);
        }
    }
    if (func_290770(p, 0x81) <= 0.0f) {
        p->f49C = 0;
    }

    if (p->f4A4 != 0 || func_290770(p, 0x82) >= 1.0f) {
        if (++p->f4A4 >= 30) {
            func_290690(p, 0x82, 0.0f, D_0047DA6C, -1.0f);
        }
    }
    if (func_290770(p, 0x82) <= 0.0f) {
        p->f4A4 = 0;
    }

    if (p->f3D8 != 0) {
        p->f3D8--;
        if (p->f3A2 != 0) {
            p->f3D8 = 0;
            normal_FieldHudWidget80CarryCloseMaybe_4f9770(p);
        }
        if (p->f3D8 <= 0) {
            p->f3D8 = 0;
            normal_FieldHudWidget80CarryCloseMaybe_4f9770(p);
        }
    }

    if (p->f3DA != 0) {
        p->f3DA--;
        if (p->f3A2 != 0) {
            p->f3DA = 0;
            normal_FieldHudWidget80LiftCloseMaybe_4f9670(p, 0);
        }
        if (p->f3DA <= 0) {
            p->f3DA = 0;
            normal_FieldHudWidget80LiftCloseMaybe_4f9670(p, 1);
        }
    }

    if (p->f3DA == 0 && func_290770(p, 0x80) <= 0.0f) {
        normal_FieldHudWidget80LiftCloseMaybe_4f9670(p, 0);
    }

    if (p->f4A0 != 0 || func_290770(p, 0x7F) >= 1.0f) {
        if (++p->f4A0 >= 30) {
            func_290690(p, 0x7F, 0.0f, D_0047DA6C, -1.0f);
        }
        if (p->f3A2 != 0) {
            func_2907A0(p, 0x7F, 0.0f);
        }
    }
    if (func_290770(p, 0x7F) <= 0.0f) {
        p->f4A0 = 0;
    }

    if (p->f4A2 != 0 || func_290770(p, 0x87) >= 1.0f) {
        if (++p->f4A2 >= 15) {
            h = func_290460(p, 0x8A);
            if (h == 0) {
                return;
            }
            e = h->f020;
            if (e == 0) {
                return;
            }
            if (e->f00A == 0x6E) {
                e->f00A = 0x8C;
            } else if (e->f00A == 0x8C) {
                e->f00A = 0x6E;
            }
            p->f4A2 = 1;
        }
    }
    if (func_290770(p, 0x87) <= 0.0f) {
        p->f4A2 = 0;
    }

    if (p->f37E != 0 || func_290770(p, 0x50) >= 1.0f) {
        if (++p->f37E >= 75) {
            func_290690(p, 0x50, 0.0f, D_0047DA6C, -1.0f);
            p->f37E = 1;
        }
    }
    if (func_290770(p, 0x50) <= 0.0f) {
        p->f37E = 0;
    }
}
