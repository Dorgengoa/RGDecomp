#include "types.h"

typedef struct Ent {
    u8 b0;
    u8 pad1[3];
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    u8 b14;
    u8 b15;
    u8 b16;
    u8 b17;
    s32 x18;
    s32 x1C;
    s32 x20;
} Ent;

typedef struct Tbl {
    s32 n;
    u8 pad4[4];
    Ent ents[16];
    s32 order[16];
} Tbl;

void ConstructArray_100620(void *, void *, s32, s32, s32);
void BlockHeapReset_1c2770(void *);
extern Tbl D_0049E880;
extern u8 D_0049E884[0x10];
extern u8 D_0049EB10[];
extern u8 D_004A0910[];
extern u8 D_004A1B90[];
extern u8 D_004A1BC0[];
extern void BlockHeapCtor_1bbf50();
extern void SoundVoiceTableCtor_1bbf80();
extern void SoundBankCtor_1bc000();

void StaticInitSoundSpuMaybe_4696f0(void) {
    s32 i;
    Ent *e;

    D_0049E880.n = 0x40;
    D_0049E884[0] = 0;
    i = 0;
    do {
        e = &D_0049E880.ents[i];
        e->b0 = 0;
        e->x4 = 0;
        e->x8 = 0;
        e->x18 = 0;
        e->xC = 0;
        e->x10 = -1;
        e->b14 = 0;
        e->b15 = 0;
        e->b16 = 0;
        e->b17 = 0;
        e->x1C = -1;
        e->x20 = -1;
        D_0049E880.order[i] = i;
        i++;
    } while (i < 16);
    ConstructArray_100620(D_0049EB10, SoundBankCtor_1bc000, 0, 0x1E0, 0x10);
    ConstructArray_100620(D_004A0910, SoundVoiceTableCtor_1bbf80, 0, 0x90, 0x20);
    BlockHeapReset_1c2770(D_004A1B90);
    ConstructArray_100620(D_004A1BC0, BlockHeapCtor_1bbf50, 0, 0x28, 0x10);
}
