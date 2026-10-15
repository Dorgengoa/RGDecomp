#include "types.h"

extern s32 ScriptGetCodeAddr_249050(s32 arg0);
extern s32 ScriptGetInt_2490f0(s32 arg0);
extern s32 EventCastFindKeyByName_24bb50(s32 arg0, s32 arg1);
extern s32 EventCastGetObjId_24c160(s32 arg0, s32 arg1);
extern s32 EventVoiceWithMessage_24ebf0(s32 arg0, s32 arg1, s32 arg2, s8 *arg3);
extern s32 strcmp(s8 *a, s8 *b);
extern void strcpy(s8 *dst, s8 *src);
extern s8 D_0044CE80[];
extern u8 D_0045EAD8[0x400];
extern s32 D_0047E7E8;
extern u8 *gEventContext;

s32 EvCmdVoiceWithMessage_245ce0(s64 *arg0, s32 arg1)
{
    u8 *ctx;
    s8 *src;
    s8 *dst;
    s32 s;
    s32 var_20;
    s32 base420;
    s32 name;
    s8 sp60[0x20];
    s32 base60;
    s32 n;

    ctx = *(u8 **)(gEventContext + 4);
    base420 = (s32)ctx + 0x420;
    base60 = (s32)ctx + 0x60;
    if ((*(s32 *)(ctx + 0x484) < 0) ^ 1) {
        return 1;
    }
    var_20 = EventCastGetObjId_24c160(base60, EventCastFindKeyByName_24bb50(base60, ScriptGetCodeAddr_249050((s32)arg0++)));
    name = ScriptGetInt_2490f0((s32)arg0++);
    src = D_0044CE80;
    dst = sp60;
    n = 0x10;
    do {
        n -= 1;
        dst[0] = src[0];
        dst[1] = src[1];
        src += 2;
        dst += 2;
    } while (n > 0);
    if (arg1 >= 3) {
        s = ScriptGetCodeAddr_249050((s32)arg0);
        if (strcmp((s8 *)s, (s8 *)D_0045EAD8) == 0) {
            sp60[0] = 0;
            var_20 = -1;
        } else {
            strcpy(sp60, (s8 *)s);
        }
    }
    D_0047E7E8 = EventVoiceWithMessage_24ebf0(base420, name, var_20, sp60);
    return 1;
}
