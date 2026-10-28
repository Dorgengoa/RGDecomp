/* rgp:protos */
#define RGP_SELF_StringAppendCStr_1a20e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str_FUN_001a20e0 {
    u8  flag : 1;
    u8  len : 7;
    u8  pad001[3];
    s32 f4;
} Str_FUN_001a20e0;

/*rgp*/

s32 StringAppendCStr_1a20e0(Str_FUN_001a20e0 *s, s32 a)
{
    s32 n;

    if (*(s32 *)s & 1) {
        n = s->f4;
    } else {
        n = s->len;
    }
    return ((s32)StringReplaceCStr_106f20(s, n, 0, a));
}
