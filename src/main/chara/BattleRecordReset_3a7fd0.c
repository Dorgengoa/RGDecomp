#include "types.h"

typedef struct S003a7fd0 {
    u16 unk0;
    s32 unk4;
    s16 unk8;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    s64 unk10;
    s64 unk18;
    s64 unk20;
    s32 unk28;
    u8 arr[2][0x14];
    s16 unk54;
    s16 unk56;
    s16 unk58;
    s16 unk5A;
    s16 unk5C;
    u8 unk5E;
} S003a7fd0;

extern void BattleRecordStatsReset_3a7fb0(void *arg0);

void BattleRecordReset_3a7fd0(S003a7fd0 *arg0)
{
    u8 *p;
    s32 i;

    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 2;
    arg0->b0 = 0;
    arg0->b1 = 0;
    arg0->b2 = 0;
    arg0->b3 = 0;
    arg0->b4 = 0;
    arg0->unk10 = 0;
    arg0->unk18 = 0;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    p = (u8 *)arg0 + 0x2C;
    i = 0;
    do {
        BattleRecordStatsReset_3a7fb0(p);
        i += 1;
        p += 0x14;
    } while (i < 2);
    arg0->unk54 = 0;
    arg0->unk56 = 0;
    arg0->unk58 = 0;
    arg0->unk5A = 0;
    arg0->unk5C = 0;
    arg0->unk5E = 0;
}
