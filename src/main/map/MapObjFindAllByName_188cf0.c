#include "types.h"

extern s32 strcmp(const char *, const char *);

typedef struct S188cf0 {
    u8 pad0[0x504];
    s32 bound;
    void **arr;
} S188cf0;

s32 MapObjFindAllByName_188cf0(S188cf0 *self, char *needle, void **out, s32 max)
{
    s32 bound = self->bound;
    void **arr = self->arr;
    s32 j = 0;
    s32 i;
    void *rec;

    for (i = 0; i < bound; i++) {
        rec = arr[i];
        if (rec == 0) {
            continue;
        }
        if (strcmp(needle, *(char **)((u8 *)rec + 0x8C)) != 0) {
            continue;
        }
        out[j] = rec;
        j++;
        if (j < max) {
            continue;
        }
        return j;
    }
    return j;
}
