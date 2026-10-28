/* rgp:protos */
#define RGP_SELF_ModelDetachRootFrames_151460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { s32 x0; s32 x4; u8 pad[0xFC]; s32 x104; u8 pad2[4]; s32 x10C; s32 *x110; } S;
typedef struct T { u8 pad[4]; s32 x4; u8 pad2[0x20]; s8 x28; } T;
/*rgp*/

void ModelDetachRootFrames_151460(S *a)
{
    s32 i;
    T *t;

    a->x4 = 0;
    if (a->x110 == NULL || a->x0 == 0) {
        return;
    }
    for (i = 0; i < a->x10C; i++) {
        t = ((T *)ArrayGetChecked_152fd0(a->x104, a->x110[i]));
        if (t != NULL && t->x28 != 0) {
            t->x4 = 0;
        }
    }
}
