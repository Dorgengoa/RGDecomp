/* rgp:protos */
#define RGP_SELF_CharaTableFindStepByName_225320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Name lookup over the 0x44-stride table at +0x2C (count s16 at +0x30).
   The first character is compared inline before the tail compare call.
   `bnez $2` branches PAST the `return p`, so the fall-through is the
   if body. */

/*rgp*/

s32 CharaTableFindStepByName_225320(s32 arg0, s8 *arg1)
{
    s32 p;
    s32 i;
    s8 *s;

    if (arg1 == 0) {
        return 0;
    }
    p = *(s32 *)(arg0 + 0x2C);
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < *(s16 *)(arg0 + 0x30); i++, p += 0x44) {
        s = *(s8 **)p;
        if (*arg1 == *s) {
            if (StrNotEqual_1f5300(s + 1, arg1 + 1) == 0) {
                return p;
            }
        }
    }
    return 0;
}
