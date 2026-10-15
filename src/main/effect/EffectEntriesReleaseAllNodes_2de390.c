#include "types.h"

s32 StrEqualNonNull_1ca6c0(s32, u8 *);
u8 *GetGameData_1fede0();
s32 EffectEntryGetName_2d9540(u8 *);
s32 EffectEntryReleaseAllNodes_2da430(u8 *);
s32 CharaSysStatusClear_3a1510(s32, u8);
u8 *CharaSysStatusGet_3a1770(s32, s32, s32);
s32 StatusEntryIsRunning_3a6190(u8 *);
extern u8 D_00461740[0x400];

void EffectEntriesReleaseAllNodes_2de390(u8 *arg0)
{
    s32 i;
    s32 j;
    u8 *e;
    u8 *t;
    u8 *q;

    for (i = 0; i < 0x30; i++) {
        e = arg0 + i * 0xE0;
        if (*(s16 *)(e + 0xB4) == 3) {
            if (StrEqualNonNull_1ca6c0(EffectEntryGetName_2d9540(e), D_00461740) != 0) {
                t = GetGameData_1fede0();
                for (j = 0; j < 0x20; j++) {
                    q = CharaSysStatusGet_3a1770(*(s32 *)(t + 0x20), j, 0);
                    if (StatusEntryIsRunning_3a6190(q) != 0) {
                        CharaSysStatusClear_3a1510(*(s32 *)(t + 0x20), *q);
                    }
                }
            }
            EffectEntryReleaseAllNodes_2da430(e);
        }
    }
}
