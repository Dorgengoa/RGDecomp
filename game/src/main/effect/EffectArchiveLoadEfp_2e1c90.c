/* rgp:protos */
#define RGP_SELF_EffectArchiveLoadEfp_2e1c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S002e1c90 {
    s16 unk0;
    s16 pad2;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S002e1c90;

/*rgp*/
/*rgp*/
extern char *strcat(char *arg0, const char *arg1);
extern char *strcpy(char *arg0, const char *arg1);
extern char D_004617B0[];

void EffectArchiveLoadEfp_2e1c90(S002e1c90 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, char *arg6, s32 arg7)
{
    s32 spBC;
    char sp80[0x3C] __attribute__((aligned(16)));
    s32 t;

    t = *(s32 *)(sp80 + 0x2C);
    if (arg5 == 0 || arg6 == 0) {
        arg0->unk0 = 1;
        arg0->unk4 = -1;
        arg0->unk8 = 0;
        arg0->unkC = t;
        return;
    }
    {
        strcpy(sp80, arg6);
        strcat(sp80, D_004617B0);
        ({ __typeof__(((s32)ArchiveGetFileByPath_1c2800(arg5, sp80, &spBC))) rgp_ao0 = ((s32)ArchiveGetFileByPath_1c2800(arg5, sp80, &spBC)); EffectResLoadEfp_2e1d70(arg0, arg1, arg2, arg3, arg4, rgp_ao0, spBC, arg7); });
    }
}
