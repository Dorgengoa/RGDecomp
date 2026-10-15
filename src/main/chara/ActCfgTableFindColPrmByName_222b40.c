#include "types.h"

/* Linear search of the 8-byte-stride table at +0x3C (count s16 at +0x6A)
   through the StrEqualNonNull_1ca6c0 predicate. */

extern s32 ActInfoColPrmGetName_230910(s32);
extern s32 StrEqualNonNull_1ca6c0(s32, s32);

s32 ActCfgTableFindColPrmByName_222b40(s32 arg0, s32 arg1)
{
    s32 p;
    s32 i;

    if (arg1 == 0) {
        return 0;
    }
    p = *(s32 *)(arg0 + 0x3C);
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < *(s16 *)(arg0 + 0x6A); i++, p += 8) {
        if (StrEqualNonNull_1ca6c0(arg1, ActInfoColPrmGetName_230910(p)) != 0) {
            return p;
        }
    }
    return 0;
}
