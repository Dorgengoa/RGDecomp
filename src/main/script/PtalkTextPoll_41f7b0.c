#include "types.h"

typedef struct S0041f7b0 {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
} S0041f7b0;

extern s32 LoaderGetData_1cd490(s32 arg0, s32 arg1, s32 *arg2);
extern s32 LoaderGetStatus_1cd4f0(s32 arg0, s32 arg1);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 PtalkTextCfgExec_41f6b0(S0041f7b0 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void PtalkTextRelease_41f8b0(S0041f7b0 *arg0);

s32 PtalkTextPoll_41f7b0(S0041f7b0 *arg0)
{
    s32 sp3C;
    s32 h;
    s32 r;
    s32 q;

    if (arg0->unk10 == 3) {
        return 3;
    }
    if (arg0->unk10 != 2) {
        return 1;
    }

    if (arg0->unk14 < 0) {
        arg0->unk10 = 1;
        return 1;
    }
    h = GetLoaderMgr_1f59d0();
    if (h == 0) {
        return 2;
    }
    r = LoaderGetStatus_1cd4f0(h, arg0->unk14);
    if (r == -1) {
        PtalkTextRelease_41f8b0(arg0);
        arg0->unk10 = 1;
        return 1;
    }
    if (r != 1) {
        return 2;
    }

    sp3C = 0;
    q = LoaderGetData_1cd490(h, arg0->unk14, &sp3C);
    if (PtalkTextCfgExec_41f6b0(arg0, q, sp3C, arg0->unk18) != 0) {
        arg0->unk10 = 3;
    } else {
        arg0->unk10 = 1;
    }

    PtalkTextRelease_41f8b0(arg0);
    return arg0->unk10;
}
