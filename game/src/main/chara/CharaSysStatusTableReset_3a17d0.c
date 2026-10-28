/* rgp:protos */
#define RGP_SELF_CharaSysStatusTableReset_3a17d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 b0;
    u8 b1;
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 pad : 5;
    u8 b3;
    s32 w4;
} E3a17;

typedef struct {
    u8 flag;
    u8 pad[3];
    E3a17 e[32];
} T3a17;

s32 CharaSysStatusTableReset_3a17d0(u8 *arg0)
{
    E3a17 *cur;
    s32 i;
    s32 z;

    if (*(T3a17 **)(arg0 + 0xB94) == NULL) {
        return 0;
    }

    (*(T3a17 **)(arg0 + 0xB94))->flag = 1;
    i = 0;
    cur = (*(T3a17 **)(arg0 + 0xB94))->e;
    do {
        cur->b0 = 0;
        i += 1;
        cur->b1 = 0;
        cur->f0 = 0;
        cur->f1 = 0;
        cur->f2 = 0;
        cur->w4 = 0;
        cur++;
    } while (i < 0x20);
    return 1;
}
