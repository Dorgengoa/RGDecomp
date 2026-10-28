/* rgp:protos */
#define RGP_SELF_StringAssignChar_1b3b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str_FUN_001b3b30 {
    u8 isLong : 1;
    u8 len : 7;
    u8 buf[3];
    s32 f04;
    u8 *f08;
} Str_FUN_001b3b30;

Str_FUN_001b3b30 *StringAssignChar_1b3b30(Str_FUN_001b3b30 *s, u8 c)
{
    u8 *p;

    if ((*(s32 *)s & 1) != 0) {
        p = s->f08;
        s->f04 = 1;
    } else {
        s->len = 1;
        p = s->buf;
    }
    p[0] = c;
    p[1] = 0;
    return s;
}
