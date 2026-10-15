#include "types.h"
#pragma optimize_for_size on

typedef struct {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 f;
    u8 g;
    u8 h;
    u8 i;
    u8 pad[3];
} E_1b5a90;

typedef struct {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0xC];
    s32 unk28;
    s32 unk2C;
    E_1b5a90 e[8];
} S_1b5a90;

extern u8 SoundNextVoiceId_1b81a0(void);

void SoundSeqPlayerInit_1b5a90(S_1b5a90 *arg0) {
    s32 i;
    E_1b5a90 *p;

    arg0->unk10 = 0;
    arg0->unk14 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk18 = 0x7F;
    arg0->unk28 = 0;
    arg0->unk2C = 8;
    for (i = 0; i < arg0->unk2C; i++) {
        arg0->e[i].a = 0x7F;
        arg0->e[i].b = 0x7F;
        arg0->e[i].c = 0;
        arg0->e[i].d = 0x40;
        arg0->e[i].e = 0;
        arg0->e[i].f = 0x40;
        arg0->e[i].g = 0;
        arg0->e[i].h = 0;
        arg0->e[i].i = 0;
        arg0->e[i].g = SoundNextVoiceId_1b81a0();
    }
}
