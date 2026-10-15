#include "types.h"

typedef struct {
    u8 pad0[0xA];
    u8 unkA;
    u8 padB[0x68 - 0xB];
} E;

typedef struct {
    u8 pad0[0x60];
    s16 unk60;
    u8 pad62[4];
    s16 unk66;
    E *unk68;
} A;

extern void CharaDataSubRecPollBuild_1ee730(E *);
extern void CharaDataSubRecPollLoads_1ee7e0(E *);

void CharaDataRecUpdate_1ee2a0(A *arg0)
{
    s32 n;
    s32 i;
    s32 j;
    s32 cnt;

    if (arg0->unk60 == 0) {
        return;
    }
    if (arg0->unk60 == 4) {
        return;
    }
    for (i = 0; i < (n = arg0->unk66); i++) {
        CharaDataSubRecPollLoads_1ee7e0(&arg0->unk68[i]);
        CharaDataSubRecPollBuild_1ee730(&arg0->unk68[i]);
    }
    if (arg0->unk60 != 2) {
        return;
    }
    cnt = 0;
    for (j = 0; j < n; j++) {
        switch (arg0->unk68[j].unkA) {
        case 2:
            break;
        case 1:
        case 3:
            cnt++;
            break;
        case 4:
            arg0->unk60 = 4;
            return;
        default:
            break;
        }
    }
    if (j == cnt) {
        arg0->unk60 = 3;
    }
}
