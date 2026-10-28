/* rgp:protos */
#define RGP_SELF_StrNotEqual_1f5300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 StrNotEqual_1f5300(s8 *a, s8 *b)
{
    while (*a != 0) {
        if (*a != *b) {
            return 1;
        }
        a++;
        b++;
    }
    return *b != 0;
}
