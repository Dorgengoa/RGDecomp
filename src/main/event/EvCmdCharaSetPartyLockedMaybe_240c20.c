#include "types.h"

struct Ctx240c20 { u8 pad0[0x14]; s32 f14; };
struct E240c20 { s32 a; s32 b; };
struct Obj240c20 { u8 pad0[0x234]; u8 flag : 1; u8 rest : 7; };

extern struct Ctx240c20 *GetGameData_1fede0(void);
extern s32 ScriptGetInt_2490f0(void *p);
extern struct Obj240c20 *CharaMgrPoolFindById_3a8c60(s32 a, s32 b);

s32 EvCmdCharaSetPartyLockedMaybe_240c20(struct E240c20 *p, s32 kind)
{
    struct Ctx240c20 *ctx;
    struct Obj240c20 *obj;

    if (kind != 2) {
        return 0;
    }
    ctx = GetGameData_1fede0();
    obj = CharaMgrPoolFindById_3a8c60(ctx->f14, ScriptGetInt_2490f0(p++));
    if (obj == 0) {
        return 0;
    }
    obj->flag = ScriptGetInt_2490f0(p) != 0;
    return 1;
}
