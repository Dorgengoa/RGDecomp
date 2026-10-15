#include "types.h"

typedef struct {
    u8 pad0[0xA60];
    s32 unkA60;
} Ctx;

typedef struct {
    s32 unk0;
    Ctx *unk4;
} EventCtx;

extern s32 ScriptGetInt_2490f0(s32);
extern EventCtx *gEventContext;

s32 EvCmdEventPlayerSetSkippable_2448c0(s64 *arg0, s32 arg1)
{
    Ctx *ctx;
    s32 a;
    s32 b;

    ctx = gEventContext->unk4;
    if (arg1 == 1) {
        if (ScriptGetInt_2490f0((s32)arg0++) != 0) {
            ctx->unkA60 &= ~1;
        } else {
            ctx->unkA60 |= 1;
        }
    }
    if (arg1 >= 2) {
        a = ScriptGetInt_2490f0((s32)arg0++);
        b = ScriptGetInt_2490f0((s32)arg0++);
        switch (a) {
        case 0:
            if (b != 0) {
                ctx->unkA60 &= ~1;
            } else {
                ctx->unkA60 |= 1;
            }
            break;
        case 1:
            if (b != 0) {
                ctx->unkA60 |= 2;
            } else {
                ctx->unkA60 &= ~2;
            }
            break;
        }
    }
    return 1;
}
