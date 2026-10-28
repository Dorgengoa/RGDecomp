/* rgp:protos */
#define RGP_SELF_EvCmdCastNodeShow_2464a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg { s32 a; s32 b; } Arg;
typedef struct Ctx { s32 m0; s32 m4; } Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Ctx *gEventContext;

s32 EvCmdCastNodeShow_2464a0(Arg *p)
{
    s32 obj;
    u8 *r;
    s8 v;
    s32 base;

    if (p->a == 2) {
        base = gEventContext->m4 + 0x60;
        obj = ((s32)ObjRecGetLiveObject_1c4a90(gEventContext->m0, EventCastGetObjId_24c160(base, EventCastFindKeyByName_24bb50(base, ScriptGetCodeAddr_249050(p++)), 0)));
        if (obj == 0) {
            return 0;
        }
        r = ((u8 *)ModelGetFrame_1511f0(obj, ModelFindFrameIndexByName_151220(obj, ScriptGetCodeAddr_249050(p++))));
        if (r == 0) {
            return 0;
        }
        if (ScriptGetInt_2490f0(p) != 0) {
            v = 1;
        } else {
            v = 2;
        }
        r[0x24] = v;
    } else if (p->a == 0) {
        obj = ((s32)ObjRecGetLiveObject_1c4a90(gEventContext->m0, ScriptGetInt_2490f0(p++)));
        if (obj == 0) {
            return 0;
        }
        r = ((u8 *)ModelGetFrame_1511f0(obj, ModelFindFrameIndexByName_151220(obj, ScriptGetCodeAddr_249050(p++))));
        if (r == 0) {
            return 0;
        }
        if (ScriptGetInt_2490f0(p) == 0) {
            v = 2;
        } else {
            v = 1;
        }
        r[0x24] = v;
    }
    return 1;
}
