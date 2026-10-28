/* rgp:protos */
#define RGP_SELF_PartySetLeaderId_3c27c0 1
#define RGP_SELF_find 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj003c27c0 {
    u8 pad0[0x18C];
    s16 unk18C;
    s16 unk18E;
    s16 arr190[0x20];
} Obj003c27c0;

static inline s32 find(Obj003c27c0 *arg0, s32 val)
{
    s32 i;
    s16 count;

    if (val < 0) {
        return -1;
    }
    count = arg0->unk18C;
    for (i = 0; i < count; i++) {
        if (arg0->arr190[i] == val) {
            return i;
        }
    }
    return -1;
}

s32 PartySetLeaderId_3c27c0(Obj003c27c0 *arg0, s32 val)
{
    s32 i;

    i = find(arg0, val);
    if (i >= 0) {
        arg0->unk18E = val;
        return 1;
    }
    return 0;
}
