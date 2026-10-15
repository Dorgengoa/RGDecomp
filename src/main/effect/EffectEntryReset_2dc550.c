#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 padC[0xE - 0xC];
    s16 unkE;
    u8 pad10[0x1A - 0x10];
    s16 unk1A;
    s16 unk1C;
    u8 padA4[0xA4 - 0x1E];
    s32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s16 unkB4;
    s16 unkB6;
    u8 padBA[0xBA - 0xB8];
    s16 unkBA;
    u8 padDC[0xDC - 0xBC];
    u16 unkDC;
} Obj002DC550;

extern void memset(void *dst, s32 fill, s32 len);

void EffectEntryReset_2dc550(Obj002DC550 *arg0) {
    arg0->unkA4 = 0;
    arg0->unkA8 = 0;
    arg0->unkB4 = 0;
    arg0->unkB6 = 0;
    arg0->unkB0 = -1;
    memset((u8 *)arg0 + 0xC, 0, 0x98);
    memset((u8 *)arg0 + 0xBC, 0, 0x20);
    arg0->unkE = -1;
    arg0->unkAC = 0;
    arg0->unk1A = -1;
    arg0->unk1C = -1;
    arg0->unkDC = 0xFFFF;
    arg0->unkBA = 0;
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
}
