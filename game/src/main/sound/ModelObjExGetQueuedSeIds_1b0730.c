/* rgp:protos */
#define RGP_SELF_ModelObjExGetQueuedSeIds_1b0730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S {
    u8 pad554[0x554];
    s32 f554;
    s32 arr558[1];
} S;

s32 ModelObjExGetQueuedSeIds_1b0730(S *self, s32 *dst, s32 count)
{
    s32 n;
    s32 i;
    n = self->f554;
    if (count < n) {
        n = count;
    }
    for (i = 0; i < n; i++) {
        dst[i] = self->arr558[i];
    }
    return n;
}
