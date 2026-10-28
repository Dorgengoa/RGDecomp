/* rgp:protos */
#define RGP_SELF_StringAppendStr_1b3b80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str_FUN_001b3b80 {
    u8  flag : 1;
    u8  len : 7;
    u8  pad001[3];
    s32 f4;
} Str_FUN_001b3b80;

/*rgp*/

s32 StringAppendStr_1b3b80(Str_FUN_001b3b80 *s, s32 a)
{
    s32 n;

    if (*(s32 *)s & 1) {
        n = s->f4;
    } else {
        n = s->len;
    }
    return StringReplaceWithStr_1a7820(s, n, 0, a);
}
