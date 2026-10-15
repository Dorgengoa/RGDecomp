#include "types.h"

/* factory.bin overlay, 0x004F6DD0 -- retire the whole trail: kill all six
 * widgets and wipe the six-record ring.  128 bytes, 32 instructions,
 * 2 branches, 2 calls.
 *
 * * Same container as `factory_FactoryMarkerAddFromSavedSlot_4f6d10` / `factory_FactoryMarkerRemoveSlot_4f6e50`: `f78`
 *   is a `Pt3 *` of 0x14-byte records and 0x78 == 6 * 0x14, which is what
 *   fixes the loop bound at 6.
 * * `slti $3, $16, 6` lands in a GENERAL register, so the compare is the
 *   non-strict `i < 6` form.
 * * The index arithmetic is emitted AFTER the `jal`, so the store is the
 *   SECOND statement of the body.
 * * `beql $4, $0` with `ld $31` in the likely slot is the tail-duplicated
 *   epilogue of an `if` WITH a body, not an early return.
 */

typedef struct Pt3 {
    f32 f00;
    f32 f04;
    f32 f08;
    u8  pad0C[0x2];
    u8  f0E;
    u8  f0F;
    u8  pad10[0x4];
} Pt3;                                          /* 0x14 */

typedef struct Trail {
    u8    pad00[0x78];
    Pt3  *f78;
    void *f7C;
    u8    pad80[0x4];
    void *f84;
} Trail;

extern void func_131B60(void *p, s32 v, s32 n);
extern void func_290010(void *w, u16 id, s32 a, s32 b);

void factory_FactoryMarkerClearAllSlots_4f6dd0(Trail *o)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        func_290010(o->f84, i + 0x98, 0, -1);
        o->f78[i].f0E = 0;
    }
    if (o->f78 != 0) {
        func_131B60(o->f78, 0, 0x78);
    }
}
