/* rgp:protos */
#define RGP_SELF_AiCmdObjMotionNameIs_2c9820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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
    a = ((s32)ObjRecGetLiveObject_1c4a90((*(s32 *)D_004DB920), *(s32 *)D_004DB928));
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
