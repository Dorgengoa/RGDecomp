#include "types.h"
#pragma optimization_level 3

extern void memset(void *, s32, s32);
extern const s32 D_00465D80[];

typedef struct {
    u8 a[0xD];
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 arr[6];
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 pad19;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    u8 f0 : 1;
    u8 f1 : 1;
    u8 fr : 6;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    s32 unk24;
} S4325;

void InsectTeamMemberInit_4325b0(S4325 *arg0)
{
    s32 i;
    s32 z;

    memset(arg0, 0, 0xD);
    arg0->unkD = 0;
    arg0->unkE = 0;
    arg0->unkF = 0;
    i = 0;
    do {
        arg0->arr[i] = 0;
        i++;
    } while (i < 6);
    arg0->unk16 = 2;
    z = 0;
    arg0->unk17 = D_00465D80[0];
    arg0->unk18 = 0;
    arg0->unk1A = 0;
    arg0->unk1C = 0;
    arg0->unk1E = 0;
    arg0->f0 = z;
    arg0->f1 = z;
    arg0->unk21 = 0;
    arg0->unk22 = 0;
    arg0->unk23 = 0;
    arg0->unk24 = 0;
}
