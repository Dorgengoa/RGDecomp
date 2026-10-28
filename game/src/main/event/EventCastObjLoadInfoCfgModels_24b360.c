/* rgp:protos */
#define RGP_SELF_EventCastObjLoadInfoCfgModels_24b360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 x0;
    char *name;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 pad1C[4];
    u8 *p2C;
    s32 n30;
    s32 pad34;
    u8 *p38;
    s32 n3C;
    u8 buf40[0x20];
    u8 buf60[0x20];
    s32 pad80[2];
} Req;

extern void Sprintf_1343b8(char *, const char *, ...);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);
extern char *strcpy(char *, const char *);
/*rgp*/
extern char D_0045EB20[];
extern char D_0045EB70[];
extern char D_0045EB78[];

s32 EventCastObjLoadInfoCfgModels_24b360(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    char buf[0x20] __attribute__((aligned(16)));
    char name[0x20] __attribute__((aligned(16)));
    Req req __attribute__((aligned(16)));
    s32 id;
    s32 v;
    u8 *obj;
    s32 h;
    u8 *g;

    id = EventCastGetObjId_24c160(arg0, arg3, (int)arg2);
    g = ((u8 *)GetDrawCtxNameTable_15de40());
    if ((obj = ((u8 *)ObjRecGetLiveObject_1c4a90(arg1, id))) == NULL) {
        return 0;
    }
    if ((h = ((s32)RecStackGetSlot_1c4330(arg1, arg2))) == 0) {
        return 0;
    }
    MemStackAlign64_14d8e0(h);
    v = *(s32 *)(obj + 0x4DC);
    if (v < 0) {
        v = ((s32)ObjRecDefaultTexGroupMaybe_250440(id));
    }
    Sprintf_1343b8(buf, D_0045EB70, id);
    if (id >= 0x40 && id < 0x80) {
        strcpy((char *)(g + 0x1E4), buf);
    }
    if (arg6 == 0) {
        Sprintf_1343b8(name, D_0045EB20);
    } else {
        Sprintf_1343b8(name, D_0045EB78, arg6);
    }
    memset(&req, 0, sizeof(req));
    req.p2C = req.buf40;
    req.n30 = 8;
    req.n3C = 8;
    req.p38 = req.buf60;
    req.name = name;
    req.x18 = 1;
    req.x0 = arg5;
    req.x14 = v;
    req.x8 = h;
    req.xC = h;
    req.x10 = h;
    InfoCfgParseModelsThunk_1abfe0(obj, &req);
    if (id >= 0x40 && id < 0x80) {
        *(g + 0x1E4) = 0;
    }
    return 1;
}
