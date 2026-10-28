/* rgp:protos */
#define RGP_SELF_SoundBankPartRelease_1ba620 1
#include "port/game_protos.h"
#line 1
#pragma opt_dead_assignments off
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0049EB10[][0x1E0];

typedef struct {
    u8 pad0[0x4];
    s32 unk4;
    s32 unk8;
    u8 padC[0x4];
    s32 unk10;
    u8 pad14[0xc];
    s32 unk20;
    u8 pad24[0x4];
    s32 *unk28;
    s32 *unk2C;
} T1ba620_arg1;

void SoundBankPartRelease_1ba620(s32 arg0, T1ba620_arg1 *arg1, s32 arg2)
{
    s32 i;
    s32 *p;

    if (arg0 < 0 || arg0 > 0x10) {
        p = NULL;
    } else {
        p = (s32 *)D_0049EB10[arg0];
    }
    if (p != NULL) {
        if (arg1->unk10 >= 0) {
            SoundSendCmd_1b6cc0(0x17, 1, arg1->unk10);
            arg1->unk10 = -1;
        }
        if (arg1->unk4 != 0) {
            IopHeapFreeLocked_1c2290(arg1->unk4);
            arg1->unk4 = 0;
        }
        if (arg2 == 0 && arg1->unk28 != 0 && arg1->unk20 > 0) {
            for (i = 0; i < arg1->unk20; i++) {
                if (arg1->unk2C[i] >= 0) {
                    SoundSendCmd_1b6cc0(0x15, 1, arg1->unk2C[i]);
                }
                if (arg1->unk28[i] != 0) {
                    IopHeapFreeLocked_1c2290(arg1->unk28[i]);
                    arg1->unk28[i] = 0;
                }
            }
        }
        if (arg1->unk8 != 0) {
            if (*p != 0) {
                BlockHeapFree_1c2370(*p, arg1->unk8);
            }
            arg1->unk8 = 0;
        }
    }
}
