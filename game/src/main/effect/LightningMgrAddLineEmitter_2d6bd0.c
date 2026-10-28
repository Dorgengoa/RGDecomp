/* rgp:protos */
#define RGP_SELF_LightningMgrAddLineEmitter_2d6bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

typedef struct E002d6bd0 {
    f32 v0[4];
    f32 v1[4];
    s16 unk20;
    s16 pad22;
    f32 unk24;
    s16 unk28;
    s16 unk2A;
    s8 unk2C;
} E002d6bd0;

typedef struct S002d6bd0 {
    u8 pad0[0x10];
    E002d6bd0 e[16];
} S002d6bd0;

void LightningMgrAddLineEmitter_2d6bd0(S002d6bd0 *arg0, void *arg1, void *arg2, s16 arg3, s16 arg4, s8 arg5, f32 fparg0)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg0->e[i].unk2A == 0) {
            sceVu0CopyVector(arg0->e[i].v0, arg1);
            sceVu0CopyVector(arg0->e[i].v1, arg2);
            arg0->e[i].unk2A = 2;
            arg0->e[i].unk20 = arg4;
            arg0->e[i].unk24 = fparg0;
            arg0->e[i].unk28 = arg3;
            arg0->e[i].unk2C = arg5;
            return;
        }
    }
}
