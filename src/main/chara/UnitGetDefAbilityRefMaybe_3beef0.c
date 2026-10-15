#include "types.h"

typedef struct {
    u8 pad0[0x78];
    s16 unk78;
    s32 unk7C;
} Inner003BEEF0;

typedef struct {
    u8 pad0[0x234];
    Inner003BEEF0 *unk234;
} S003BEEF0;

s32 UnitGetDefAbilityRefMaybe_3beef0(S003BEEF0 *arg0, s32 arg1)
{
    Inner003BEEF0 *temp_4;

    if (arg1 >= 0) {
        temp_4 = arg0->unk234;
        if (arg1 < temp_4->unk78) {
            return temp_4->unk7C + (arg1 * 4);
        }
    }
    return 0;
}
