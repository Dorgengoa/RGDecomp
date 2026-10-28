/* rgp:protos */
#define RGP_SELF_NpcObjTableCollectIds_2fb3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct ElemFB3B0 {
    u16 unk0;
    u8 pad2[0xC4 - 0x2];
    s16 unkC4;
} ElemFB3B0;

typedef struct Obj002fb3b0 {
    u8 pad0[0x4];
    s32 unk4;
    u8 pad8[0xC - 0x8];
    ElemFB3B0 *unkC;
    u8 pad10[0x20C - 0x10];
    s16 unk20C;
} Obj002fb3b0;

s32 NpcObjTableCollectIds_2fb3b0(Obj002fb3b0 *arg0, s32 *out)
{
    ElemFB3B0 **arr;
    ElemFB3B0 *elem;
    s32 i;
    s32 count;

    if (arg0->unk4 == 0) {
        return 0;
    }
    count = 0;
    arr = (ElemFB3B0 **)&arg0->unkC;
    i = 0;
    while (i < arg0->unk20C) {
        elem = *arr;
        if (elem->unk0 & 1) {
            if (elem->unkC4 != -1) {
                *out = elem->unkC4;
                count++;
                out++;
            }
        }
        i++;
        arr++;
    }
    return count;
}
