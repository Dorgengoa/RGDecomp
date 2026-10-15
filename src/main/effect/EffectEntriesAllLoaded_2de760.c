#include "types.h"

/* The two `== 0` arms are ONE guard in retail, not two: retail's first test is
   an annulled `beql` straight to the epilogue and there is no second exit
   block at all. Folding them into a single `||` closes it --
   [[levers.d/mwcc-branch-likely-duplication]] factory-s41 fix 3. The nested
   `!= 0` / `continue` spelling is the SAME object. Measured INERT before this:
   `break` vs `return 0` on either or both arms (all four combos, 7 bad each);
   `goto` to a shared zero-return is one word SHORT; dropping the `result`
   local for literal returns is 25 bad. */

u16 EffectEntriesAllLoaded_2de760(s32 arg0) {
    s32 var_7;
    u8 *temp_6;
    u16 result = 1;
    for (var_7 = 0; var_7 < 0x30; var_7++) {
        temp_6 = (u8 *)arg0 + var_7 * 0xE0 + 0xC;
        if (temp_6 == NULL) { continue; }
        if (*(s16 *)(temp_6 + 2) == -1) { continue; }
        if (*(s16 *)(temp_6 + 0xA) == 0 || *(s16 *)(temp_6 + 0xC) == 0) { result = 0; break; }
    }
    return result;
}
