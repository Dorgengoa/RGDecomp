#include "types.h"

extern s32 ModelObjGetMotionName_1add90(s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern s32 ScriptSlotGetCodeAddr_2cc980(s32);
extern s32 strcmp(const char *, const char *);
extern u8 D_004DB920[0x400];
extern u8 D_004DB928[0x400];

s32 AiCmdObjMotionNameIs_2c9820(s64 *arg0)
{
    s32 flag;
    s32 a;
    s32 b;
    s32 c;

    flag = 0;
    a = ObjRecGetLiveObject_1c4a90((*(s32 *)D_004DB920), *(s32 *)D_004DB928);
    if (a == 0) {
        return 0;
    }
    b = ModelObjGetMotionName_1add90(a);
    c = ScriptSlotGetCodeAddr_2cc980((s32)arg0++);
    if (b != 0 && strcmp((const char *)b, (const char *)c) == 0) {
        flag = 1;
    }
    ScriptSlotStoreIntRef_2cc900((s32)arg0, flag);
    return 1;
}
