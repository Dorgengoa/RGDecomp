#pragma opt_propagation off
#include "types.h"

typedef struct {
    u8 pad[0x7C];
} E7C;

extern void CharaEffEntrySetPos_2300b0(E7C *arg0, f32 *arg1);
extern f32 ScriptArgGetFloat_23fbc0(u8 *arg0);
extern f32 D_0047E7B0;
extern f32 D_0047E7B4;
extern f32 D_0047E7B8;
extern f32 D_0047E7BC;
extern E7C *D_004BCE60[];
extern s16 D_004BCE8C[];

s32 CharaEffEntrySetPosCmd_23d9c0(u8 *arg0, s32 arg1)
{
    f32 v[4];
    f32 *qv = v;
    E7C *p;
    E7C *base;

    if (arg1 != 3) {
        return 0;
    }
    if (D_004BCE60[0] == NULL || D_004BCE8C[0] >= 0x80) {
        return 1;
    }
    qv[0] = D_0047E7B0;
    p = &D_004BCE60[0][D_004BCE8C[0]];
    qv[1] = D_0047E7B4;
    qv[2] = D_0047E7B8;
    qv[3] = D_0047E7BC;
    v[0] = ScriptArgGetFloat_23fbc0(arg0);
    v[1] = ScriptArgGetFloat_23fbc0(arg0 + 8);
    v[2] = ScriptArgGetFloat_23fbc0(arg0 + 0x10);
    CharaEffEntrySetPos_2300b0(p, v);
    return 1;
}
