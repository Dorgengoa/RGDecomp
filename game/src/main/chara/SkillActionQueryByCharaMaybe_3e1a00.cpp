#include "types.h"

struct E3e1a00 { s16 unk0; u8 pad2[0xD]; u8 unkF; u8 pad10[0x2C]; s16 unk3C; u8 pad3E[0xA]; };
struct O3e1a00 { u8 cnt; u8 found : 1; u8 all : 1; };

extern "C" {
extern E3e1a00 D_004E9770[2];

bool SkillActionQueryByCharaMaybe_3e1a00(s32 arg0, O3e1a00 *arg1)
{
    bool found = false;
    s32 cnt = 0;
    bool all = true;
    E3e1a00 *e = D_004E9770;
    s32 i;

    for (i = 0; i < 2; i++, e++) {
        if (e->unk0 >= 0) {
            cnt++;
            if (e->unk3C == arg0) {
                found = true;
                break;
            }
        }
        if (!(e->unkF & 1)) {
            all = false;
        }
    }
    if (arg1 != 0) {
        arg1->found = found;
        arg1->cnt = cnt;
        arg1->all = all;
    }
    return found;
}
}
