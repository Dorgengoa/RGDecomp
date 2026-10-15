#include "types.h"

typedef struct S002d6220 {
    f32 v[0x12][4];
    s16 unk120;
    s16 unk122;
    u8 pad124[4];
    s32 unk128;
    s32 unk12C;
    u8 pad130[0x16];
    s16 unk146;
} S002d6220;

extern s32 GetGameMode_1f59c0(s16);
extern void MovingLineReset_2d5f30(S002d6220 *);
extern void sceVu0CopyVector(void *, void *);

void MovingLineUpdate_2d6220(S002d6220 *arg0)
{
    s32 i;

    if (arg0->unk120 == 0) {
        return;
    }
    if (arg0->unk146 == 10 && GetGameMode_1f59c0(arg0->unk146) != 10) {
        MovingLineReset_2d5f30(arg0);
    }
    i = 1;
    if (arg0->unk120 == 1) {
        if (arg0->unk122 == 0) {
            for (; i < arg0->unk12C; i++) {
                sceVu0CopyVector(arg0->v[i - 1], arg0->v[i]);
            }
            if (--arg0->unk12C <= 0) {
                arg0->unk120 = 0;
            }
        }
        arg0->unk122 = 0;
    }
    if (arg0->unk120 == 3) {
        for (i = 1; i < arg0->unk128; i++) {
            sceVu0CopyVector(arg0->v[i - 1], arg0->v[i]);
        }
        if (--arg0->unk12C <= 0) {
            arg0->unk120 = 0;
        }
    }
}
