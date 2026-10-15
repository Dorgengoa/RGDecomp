#include "types.h"

typedef struct {
    u8 pad0[0x64];
    s16 unk64;
} Elem001ED7D0;

typedef struct {
    u8 pad0[0xF94];
    s32 unkF94;
} Obj001ED7D0;

extern void MemStackHeapReinit_14de90(s32);
extern void CharaDataRecRelease_1ee190(Elem001ED7D0 *, s16);

void CharaDataReleaseHeapRecs_1ed7d0(Obj001ED7D0 *arg0) {
    s16 temp_5;
    s32 i;
    Elem001ED7D0 *e;
    s32 temp_4_2;

    i = 0;
    do {
        e = (Elem001ED7D0 *)((u8 *)arg0 + (i * 0x74));
        temp_5 = e->unk64;
        if (temp_5 == 1) {
            CharaDataRecRelease_1ee190(e, temp_5);
        }
        i += 1;
    } while (i < 0x20);
    temp_4_2 = arg0->unkF94;
    if (temp_4_2 != 0) {
        MemStackHeapReinit_14de90(temp_4_2);
    }
}
