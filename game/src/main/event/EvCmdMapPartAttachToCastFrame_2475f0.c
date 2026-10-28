/* rgp:protos */
#define RGP_SELF_Clear 1
#define RGP_SELF_EvCmdMapPartAttachToCastFrame_2475f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} V;

typedef struct {
    u8 pad0[0x34];
    s32 w34;
    s32 w38;
} R;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 *gEventContext;

static inline void Clear(V *v)
{
    u8 *b = (u8 *)v;
    u32 n = 0x10;
    if (b != NULL) {
        do {
            *b = 0;
            n--;
            b++;
        } while (n != 0);
    }
}

s32 EvCmdMapPartAttachToCastFrame_2475f0(s64 *arg0)
{
    s32 type;
    s32 obj;
    s32 w;
    V v60 __attribute__((aligned(16)));
    V v50 __attribute__((aligned(16)));
    s32 a;
    s32 y;
    s32 z;
    R *r;
    s32 ctx;
    s32 x;

    ctx = gEventContext[1] + 0x60;
    obj = ((s32)GetMapMgr_201a90());
    type = *(s32 *)arg0;
    if (type == 2) {
        a = ScriptGetCodeAddr_249050(arg0++);
        r = ((R *)MapFindObjInAreaByName_1e4470(obj, a, ScriptGetCodeAddr_249050(arg0++)));
    } else if (type == 0) {
        a = ScriptGetInt_2490f0(arg0++);
        r = ((R *)MapFindObjInAreaById_1e44b0(obj, a, ScriptGetCodeAddr_249050(arg0++)));
    } else {
        return 0;
    }
    if (r == NULL) {
        return 0;
    }
    x = EventCastFindKeyByName_24bb50(ctx, ScriptGetCodeAddr_249050(arg0++));
    y = ScriptGetCodeAddr_249050(arg0);
    z = ((s32)ObjRecGetLiveObject_1c4a90(gEventContext[0], EventCastGetObjId_24c160(ctx, x, 0)));
    if (z == 0) {
        return 0;
    }
    w = ((s32)ModelGetFrame_1511f0(z, ModelFindFrameIndexByName_151220(z, y)));
    if (w == 0) {
        return 0;
    }
    Clear(&v60);
    v60.x = 0;
    v60.y = 0;
    v60.z = 0;
    NodeSetTranslation_1866b0(r, &v60);
    Clear(&v50);
    v50.x = 0;
    v50.y = 0;
    v50.z = 0;
    NodeSetRotation_186620(r, &v50);
    r->w38 = w;
    r->w34 = 0;
    return 1;
}
