/* rgp:protos */
#define RGP_SELF_ActCfgTableGetColPrmValue_223460 1
#define RGP_SELF_s_find 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* ActCfgTableFindColPrmByName_222b40's body INLINED (three distinct `$17 = 0` materialisations =
   the helper's three `return 0`s) followed by an id fetch.  Written as a
   `static inline` helper - mwcc's C mode honours static inline. */

/*rgp*/
/*rgp*/
/*rgp*/

static inline s32 s_find(s32 arg0, s32 arg1)
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
        if (((unsigned char)StrEqualNonNull_1ca6c0(arg1, ActInfoColPrmGetName_230910(p))) != 0) {
            return p;
        }
    }
    return 0;
}

s32 ActCfgTableGetColPrmValue_223460(s32 arg0, s32 arg1)
{
    s32 p;

    p = s_find(arg0, arg1);
    if (p != 0) {
        return ActInfoColPrmGetValue_230900(p);
    }
    return -1;
}
