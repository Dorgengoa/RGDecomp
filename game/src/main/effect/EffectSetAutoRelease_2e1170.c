/* rgp:protos */
#define RGP_SELF_EffectSetAutoRelease_2e1170 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct A2e1170 { s16 unk0; u8 pad2[6]; s32 unk8; s32 unkC; } A2e1170;
extern void EffInstSetAutoDestroy_1a0dd0(s32, s32, s32, void *);
/*rgp*/

s32 EffectSetAutoRelease_2e1170(s32 arg0, A2e1170 *arg1, s32 arg2) {
u8 *temp_7_2;
s32 temp_7;
s32 t;
switch (arg1->unk0) {
        default:
            goto gpt_return;
        case 1:
            temp_7 = arg1->unk8;
            if ((temp_7 < 0) || (temp_7 >= 0x30)) return 1;
            temp_7_2 = (u8 *)((temp_7 * 0x70) - (-arg0));
            if (*(s32 *)(temp_7_2 + 0x1D0) != 1) {
                return 2;
            }
            if (*(s32 *)(temp_7_2 + 0x174) < 0) {
                return 3;
            }
            t = !(*(volatile s32 *)&arg1->unkC != 0);
            if (t) { return 4; }
            if (arg2 != 0) {
                EffInstSetAutoDestroy_1a0dd0(arg0 + 0x58, arg1->unkC, arg2, temp_7_2);
            }
            break;
        case 2:
        case 3:
            if (arg2 != 0) {
                EffectEntriesSetAutoRelease_2de500(arg0 + 0x1674, arg1, (int)arg2);
            }
            break;
    }
    goto gpt_return;

gpt_return: return 0;
}
