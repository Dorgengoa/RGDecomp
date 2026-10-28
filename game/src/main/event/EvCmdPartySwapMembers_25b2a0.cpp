#include "types.h"

struct Ctx0240b10 { u8 pad0[0x14]; s32 f14; s32 f18; };
struct E0240b10 { s32 a; s32 b; };

extern "C" {
extern Ctx0240b10 *GetGameData_1fede0(void);
extern s32 ScriptGetInt_26a2a0(void *p);
extern s32 CharaMgrPoolFindById_3a8c60(s32 a, s32 b);
extern bool CharaIsInReserve_3ae0e0(s32 a);
extern void CharaSetFlag234Bit2Related_3ae370(s32 a, s32 b);
extern void PartySwapMembers_3c0ad0(s32 a, s32 b, s32 c, s32 d, s32 e);
}

extern "C" s32 EvCmdPartySwapMembers_25b2a0(E0240b10 *p, s32 kind)
{
    Ctx0240b10 *ctx;
    s32 a;
    s32 b;
    s32 x;
    s32 y;
    bool f;

    if (kind != 2) {
        return 0;
    }
    ctx = GetGameData_1fede0();
    a = ScriptGetInt_26a2a0(p++);
    b = ScriptGetInt_26a2a0(p);
    x = CharaMgrPoolFindById_3a8c60(ctx->f14, a);
    if (x == 0) {
        return 0;
    }
    y = CharaMgrPoolFindById_3a8c60(ctx->f14, b);
    if (y == 0) {
        return 0;
    }
    f = CharaIsInReserve_3ae0e0(x);
    if (f != CharaIsInReserve_3ae0e0(y)) {
        CharaSetFlag234Bit2Related_3ae370(x, 0);
        CharaSetFlag234Bit2Related_3ae370(y, 0);
    }
    PartySwapMembers_3c0ad0(ctx->f18, a, b, 1, 0);
    return 1;
}
