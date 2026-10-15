#include "types.h"

/* factory.bin overlay, 0x004FCC50 -- the "can the parts dialog open" test:
 * refuse when it is already open or when a job is running, otherwise arm the
 * sound cue and say yes.  104 bytes, 26 instructions, 2 branches, 3 calls.
 *
 * * Both guards are the INVERTED early return of the `004ED6D0` seed: retail
 *   branches INTO the continuation (`beqz`) and lets the failure FALL THROUGH
 *   to `b <epilogue>` with `daddu $2, $0, $0` in the slot, so the source is
 *   `if (<cond>) { return 0; }`.
 * * `lw $2, 0x0($2)` in `func_367EC0`'s delay slot means the result is
 *   dereferenced INLINE -- naming it would spend a register.
 * * `func_1B9520(void *s, f32 g, s32 a, s32 b)` is the merged spelling from
 *   the byte-identical `factory_FactoryBlueprintConfirm_4fb840`; the float rides `$f12` from a
 *   separate FP argument file, which is why `a1`/`a2` still carry 6 and 0.
 * * The `func_207DF0()` result feeds `$4` straight from `$2`, so the call is
 *   NESTED, not parked in a local as in `004FB840`.
 */

typedef struct Job {
    s32 f00;
} Job;

typedef struct Dlg {
    u8 pad00[0x64];
    u8 f64;
} Dlg;

extern void  func_1B9520(void *s, f32 g, s32 a, s32 b);
extern void *func_207DF0(void);
extern Job  *func_367EC0(void);

s32 factory_FactoryRemoveWaitRequest_4fcc50(Dlg *o)
{
    if (o->f64 != 0) {
        return 0;
    }
    if (func_367EC0()->f00 != 0) {
        return 0;
    }
    func_1B9520(func_207DF0(), 1.0f, 6, 0);
    return 1;
}
