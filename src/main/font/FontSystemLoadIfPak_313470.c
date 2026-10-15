#include "types.h"

/* `sltu $2,$0,$2` before the test: the call's result is NORMALISED to 0/1
   into a temporary first (a bare `if (f())` emits only `beq $2,$0`).
   The `b <epilogue>` after the tail call is the explicit `return` INSIDE the
   guarded block -- without it the block falls through and the unit is one
   word short. */

extern s32 MesFontPakRead_2703f0(void);
extern s32 FontSystemLoad_3133c0(void *a, void *b, void *c);

s32 FontSystemLoadIfPak_313470(void *a, void *b, void *c)
{
    s32 ok;

    if (b == 0) {
        return 0;
    }
    ok = (MesFontPakRead_2703f0() != 0);
    if (ok != 0) {
        return FontSystemLoad_3133c0(a, b, c);
    }
    return 0;
}
