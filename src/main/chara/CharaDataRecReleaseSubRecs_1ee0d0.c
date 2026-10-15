#include "types.h"

typedef struct Item1ee0d0 {
    u8 pad0[8];
    s16 unk8;
} Item1ee0d0;

typedef struct T1ee0d0 {
    u8 pad0[0x66];
    s16 unk66;
    Item1ee0d0 *unk68;
} T1ee0d0;

extern void CharaDataSubRecRelease_1ee6d0(Item1ee0d0 *);

void CharaDataRecReleaseSubRecs_1ee0d0(T1ee0d0 *arg0)
{
    Item1ee0d0 *item;
    s32 i;

    for (i = 0; i < arg0->unk66; i++) {
        item = (Item1ee0d0 *)((s32)arg0->unk68 + i * 0x68);
        if (item->unk8 != 0) {
            CharaDataSubRecRelease_1ee6d0(item);
        }
    }
    for (i = 0; i < arg0->unk66; i++) {
        item = (Item1ee0d0 *)((s32)arg0->unk68 + i * 0x68);
        if (item->unk8 == 0) {
            CharaDataSubRecRelease_1ee6d0(item);
        }
    }
}
