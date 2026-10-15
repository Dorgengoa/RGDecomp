#include "types.h"

typedef struct Obj003c1e70 {
    u8 pad0[0x18C];
    s16 unk18C;
    s16 pad18E;
    s16 arr190[0x20];
} Obj003c1e70;

inline s32 find(Obj003c1e70 *arg0, s32 val)
{
    s32 j;

    if (val < 0) {
        return -1;
    }
    for (j = 0; j < arg0->unk18C; j++) {
        if (arg0->arr190[j] == val) {
            return j;
        }
    }
    return -1;
}

s32 PartyHasMember_3c1e70(Obj003c1e70 *arg0, s32 val)
{
    s32 i;

    i = find(arg0, val);
    return i >= 0;
}
