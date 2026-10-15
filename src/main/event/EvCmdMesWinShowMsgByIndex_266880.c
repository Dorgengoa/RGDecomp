#include "types.h"
typedef struct { s32 a, b; } E8_266880;
extern s32 ScriptGetInt_26a2a0(E8_266880 *);
extern s32 MsgGetTextByIndex_279040(s32);
extern void ScriptArgInitInt_26a1b0(E8_266880 *, s32);
extern void ScriptArgInitCodeAddr_26a1a0(E8_266880 *, s32);
extern s32 EvCmdMesWinShowMsg_2668f0(E8_266880 *, s32);

s32 EvCmdMesWinShowMsgByIndex_266880(E8_266880 *p0)
{
    E8_266880 v[2];
    s32 a;
    s32 b;
    s32 c;

    a = ScriptGetInt_26a2a0(p0++);
    b = ScriptGetInt_26a2a0(p0);
    c = MsgGetTextByIndex_279040(b);
    ScriptArgInitInt_26a1b0(&v[0], a);
    ScriptArgInitCodeAddr_26a1a0(&v[1], c);
    return EvCmdMesWinShowMsg_2668f0(v, 2) != 0;
}
