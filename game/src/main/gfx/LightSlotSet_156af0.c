/* rgp:protos */
#define RGP_SELF_LightSlotSet_156af0 1
#define RGP_SELF_slotOf 1
#include "port/game_protos.h"
#line 1
#include "vec.h"

/* Write two rows and a scalar into one of four 0x30-byte slots at +0xE0.

   The accessor is INLINED: retail's `daddu $4, $0, $0` twice and the
   `addiu $4, $3, 0xE0` all land in $a0 and are then tested once with `beqz`,
   which is a returned pointer flowing into an `if`, not two separate exits.
   `static inline` in mwcc's C mode is what reproduces that. */

typedef struct Slot30 {
    Vec4 a;            /* +0x00 */
    Vec4 b;            /* +0x10 */
    f32 t;             /* +0x20 */
} Slot30;

typedef struct OwnerE0a {
    u8 pad000[0xE0];
    Slot30 rec[1];     /* +0xE0 */
} OwnerE0a;

static inline Slot30 *slotOf(OwnerE0a *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 4;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index];
}

void LightSlotSet_156af0(OwnerE0a *o, s32 index, const Vec4 *a, const Vec4 *b, f32 t)
{
    Slot30 *slot;

    slot = slotOf(o, index);
    if (slot != 0) {
        slot->a = *a;
        slot->b = *b;
        slot->t = t;
    }
}
