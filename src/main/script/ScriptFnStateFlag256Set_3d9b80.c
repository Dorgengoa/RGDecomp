#include "types.h"

typedef struct H_003d9b80 {
    u8 pad000[0x10];
    void *f10;
} H_003d9b80;

extern H_003d9b80 *D_00483960;
extern s32 D_00483964;

extern s32 VariantGetS8_36fe50(void);
extern void StateFlag256Set_3cc4c0(void *a, s32 b, s32 c);

void ScriptFnStateFlag256Set_3d9b80(void *a0, s32 *a1)
{
    if (a0 == 0 || a1 == 0) {
        return;
    }
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    StateFlag256Set_3cc4c0(D_00483960->f10, *a1, VariantGetS8_36fe50() != 0);
}
