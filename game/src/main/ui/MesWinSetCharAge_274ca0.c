/* rgp:protos */
#define RGP_SELF_MesWinSetCharAge_274ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E {
    u8 f[8];
} E;

typedef struct T {
    u8 pad000[0xc8];
    E  arr[0x300];
} T;

void MesWinSetCharAge_274ca0(T *t, s32 i, u8 v)
{
    if (i < 0 || i >= 0x300) {
        return;
    }
    t->arr[i].f[2] = v;
}
