/* rgp:protos */
#define RGP_SELF_SoundStreamHandleAlloc_1bfba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimize_for_size on
typedef struct { u8 pad[0x82]; u16 id; } E;
typedef struct { u32 n; E e[8]; u16 ctr; } M;
void SoundStreamHandleAlloc_1bfba0(s16 *arg0, M *arg1)
{
    s32 idx;
    s32 i;
    u16 t;

    idx = -1;
    for (i = 0; i < arg1->n; i++) {
        if (arg1->e[i].id != 0) {
            continue;
        }
        idx = i;
        break;
    }
    if (idx < 0) {
        arg0[0] = 0;
        arg0[1] = 0;
        return;
    }
    t = arg1->ctr;
    arg1->ctr = t + 1;
    if (arg1->ctr == 0) {
        arg1->ctr = 1;
    }
    arg1->e[idx].id = t;
    arg0[0] = idx;
    arg0[1] = t;
}
