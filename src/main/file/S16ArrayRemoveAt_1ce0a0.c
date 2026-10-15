#include "types.h"
#pragma opt_propagation off
typedef struct {
    s16 *arr;
    s16 pad4;
    s16 count;
} L;

void S16ArrayRemoveAt_1ce0a0(L *self, s32 idx)
{
    s32 i;

    if (self->arr == NULL || idx < 0 || self->count <= idx) return;
    for (i = idx + 1; i < self->count; i++) {
        self->arr[i - 1] = self->arr[i];
    }
    self->count--;
}
