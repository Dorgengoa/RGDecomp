/* rgp:protos */
#define RGP_SELF_GameReqListRemoveById_20a010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3_20a010;

typedef struct {
    s32 id;
    s32 val;
    V3_20a010 v;
} E_20a010;

typedef struct {
    E_20a010 *arr;
    s16 count;
} L_20a010;

void GameReqListRemoveById_20a010(L_20a010 *self, s32 arg1)
{
    s32 keep;
    s32 i;
    E_20a010 *arr;
    E_20a010 *src;
    E_20a010 *dst;

    if (self->arr == NULL || self->count <= 0) {
        return;
    }
    keep = 0;
    for (i = 0; i < self->count; i++) {
        arr = self->arr;
        src = &arr[i];
        if (arg1 != *(volatile s32 *)&src->id) {
            dst = &arr[keep];
            keep++;
            dst->id = src->id;
            dst->val = src->val;
            dst->v = src->v;
        }
    }
    self->count = keep;
}
