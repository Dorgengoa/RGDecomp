#include "types.h"

typedef struct Obj002301a0 {
    u8 pad0[0x18];
    s32 arr[6];
    u8 pad1[0x60 - 0x18 - 6 * 4];
    u16 flags;
} Obj002301a0;

void CharaEffEntrySetWorkInt_2301a0(Obj002301a0 *arg0, s32 arg1, s32 arg2)
{
    if (arg1 < 0 || arg1 >= 6) {
        return;
    }
    arg0->flags = (u16)(arg0->flags | 0x10);
    arg0->arr[arg1] = arg2;
}
