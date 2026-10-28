/* rgp:protos */
#define RGP_SELF_StringPopBack_1b3bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str_FUN_001b3bb0 {
    u8 isLong : 1;
    u8 len : 7;
    u8 buf[3];
    s32 f04;
    u8 *f08;
} Str_FUN_001b3bb0;

void StringPopBack_1b3bb0(Str_FUN_001b3bb0 *s)
{
    s32 n;
    u8 *buf;

    if ((*(s32 *)s & 1) == 0) {
        buf = s->buf;
        n = s->len - 1;
        buf += n;
        *buf = 0;
        s->len = n;
    } else {
        n = s->f04 - 1;
        s->f08[n] = 0;
        s->f04 = n;
    }
}
