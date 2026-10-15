#include "types.h"

/* factory.bin overlay, 0x004F6D10 -- allocate one trail point: ask the pool for
 * a slot at (x, y, z), copy the template over it and, when asked to, write the
 * position back.  176 bytes, 44 instructions, 3 conditional branches, 2 calls.
 *
 * * `dsll32 $16, $2, 16 / dsra32 $16, $16, 16` on a CALL RESULT is an `s32`
 * local plus an explicit `(s16)` cast, the 16-bit reading of
 * [[normal-s16-cast-sign-extension]]; the SECOND pair before the return is the
 * same cast spelled again on the way out, which is why an `s16` local -- which
 * would already be extended -- is the wrong declaration.
 *
 * * The index scales by 20: `sll 2 / addu / sll 2` is `(i * 4 + i) * 4`, so
 * `f78` is a pointer to a 0x14-byte record and the site is `&o->f78[i]`.
 *
 * * `o->f7C` is read BEFORE `$18` is overwritten with the element pointer --
 * one register serves as `o` and then as `p`, which only works because `o` is
 * dead after the two loads.
 */

typedef struct Pt3 {
    f32 f00;
    f32 f04;
    f32 f08;
    u8  pad0C[0x8];
} Pt3;                                          /* 0x14 */

typedef struct Trail {
    u8    pad00[0x78];
    Pt3  *f78;
    void *f7C;
} Trail;

extern s32  factory_FactoryMarkerFindFree_4f6280(Trail *o, f32 x, f32 y, f32 z);
extern void func_1319A8(void *dst, const void *src, s32 n);

s32 factory_FactoryMarkerAddFromSavedSlot_4f6d10(Trail *o, s32 set, f32 x, f32 y, f32 z)
{
    s32  i;
    Pt3 *p;

    i = (s16)factory_FactoryMarkerFindFree_4f6280(o, x, y, z);
    if (i < 0) {
        return -1;
    }
    p = &o->f78[i];
    func_1319A8(p, o->f7C, 0x14);
    if (set != 0) {
        p->f00 = x;
        p->f04 = y;
        p->f08 = z;
    }
    return (s16)i;
}
