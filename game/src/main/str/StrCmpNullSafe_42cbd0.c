/* rgp:protos */
#define RGP_SELF_StrCmpNullSafe_42cbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 StrCmpNullSafe_42cbd0(const s8 *a, const s8 *b)
{
    if (a == 0) {
        goto none;
    }
    if (b != 0) {
        goto ok;
    }
none:
    return 0;
ok:
    while (*a == *b) {
        if (*a == 0) return 0;
        a++;
        b++;
    }
    return (u8)*a - (u8)*b;
}
