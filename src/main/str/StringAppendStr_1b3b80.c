#include "types.h"

typedef struct Str_FUN_001b3b80 {
    u8  flag : 1;
    u8  len : 7;
    u8  pad001[3];
    s32 f4;
} Str_FUN_001b3b80;

extern s32 StringReplaceWithStr_1a7820(Str_FUN_001b3b80 *, s32, s32, s32);

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
