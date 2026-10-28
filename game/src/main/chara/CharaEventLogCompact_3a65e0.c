/* rgp:protos */
#define RGP_SELF_CharaEventLogCompact_3a65e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
typedef struct E { u8 d[6]; u8 used : 1; u8 f6 : 7; u8 x7; } E;
typedef struct O { u8 pad[0x42]; s16 n; u8 pad44[2]; E e[1]; } O;
extern s32 memcpy(void *, void *, s32);

s32 CharaEventLogCompact_3a65e0(O *arg0)
{
    s32 cnt;
    E *p;
    E *dst;
    s32 i;
    s32 n;

    if (arg0->n <= 0) {
        return 0;
    }
    cnt = 0;
    p = arg0->e;
    dst = NULL;
    i = 0;
    for (; i < (n = arg0->n); i++, p++) {
        if (p->used) {
            if (dst == NULL) {
                dst = p;
            }
            cnt++;
        } else if (dst != NULL) {
            memcpy(dst, p, 8);
            p->used = 1;
            dst++;
            if (!dst->used) {
                dst = NULL;
            }
        }
    }
    arg0->n = n - (s16)cnt;
    return 1;
}
