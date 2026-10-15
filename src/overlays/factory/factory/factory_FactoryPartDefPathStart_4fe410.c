#include "types.h"

/* factory.bin overlay, 0x004FE410 -- bounds-check a slot index against the
 * part table and forward the slot's record to the writer.
 * 100 bytes, 25 instructions, 3 conditional branches, 1 call.
 *
 * * One of a four-member family found by ranking the OPEN population against
 * ITSELF: `004FE3A0` (0.929) forwards the record's `+6`
 * sub-record rather than the record itself, and `004FE600`/`004FE7C0` take the table as a parameter over a
 * 0x8- and a 0x6-byte stride.
 *
 * * The bound test is spelled `o->f64 <= i`, NOT `i >= o->f64`.  Both emit
 * `slt $1, $8, $2` + `bnel`, and only the "or-equal with the BOUND on the
 * left" token puts it in `$at` -- [[at-compare-class]]'s if/else row 2, on one
 * of the 37 inverted factory sites the recorded census had already flagged in
 * this exact function.
 *
 * ** The two index guards are ONE `if` with a short-circuit `||`.  Written as
 * two separate `if`s the negative test becomes a `bgezl` branch-AROUND and the
 * `return 0` needs its own block -- 8 bad words at the RIGHT LENGTH; the `||`
 * lets mwcc fold the first arm into `bltzl` + `daddu $2, $0, $0` in the delay
 * slot and share one `return 0` block with the second, exactly as the same
 * join does in `factory_FactoryGridRowFromZ_503f00`.
 *
 * * The call INSERTS an argument at position three, so `$7` takes the old `$6`
 * and `$8` the old `$7`; that shift is why `$9` is saved in the very first
 * delay slot.
 */

typedef struct Rec {
    u8 pad00[0x14];
} Rec;                                          /* 0x14 */

typedef struct Obj {
    u8   pad00[0x60];
    Rec *f60;
    s32  f64;
} Obj;

extern s32 factory_FactoryGridRotatePoint_4fe820(Obj *o, s32 a, Rec *p, s32 b, s32 c);

s32 factory_FactoryPartDefPathStart_4fe410(Obj *o, s32 a, s32 b, s32 c, s32 i)
{
    Rec *base;

    base = o->f60;
    if (base == 0) {
        return 0;
    }
    if (i < 0 || o->f64 <= i) {
        return 0;
    }
    return factory_FactoryGridRotatePoint_4fe820(o, a, &base[i], b, c);
}
