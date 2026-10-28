/* rgp:protos */
#define RGP_SELF_DrawListGetCurBufHeader_1427c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_FUN_001427c0 {
    s32 n;
    u8 pad004[4];
    s32 a[1];
} S_FUN_001427c0;

s32 DrawListGetCurBufHeader_1427c0(S_FUN_001427c0 *p)
{
    return p->a[p->n];
}
