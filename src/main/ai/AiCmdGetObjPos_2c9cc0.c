#include "types.h"
#pragma opt_propagation off

typedef struct V4 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) V4;

typedef struct Obj {
    u8 pad0[0x180];
    V4 v180;
} Obj;

typedef struct Cfg {
    u8 pad0[0x18];
    s16 *x18;
} Cfg;

typedef struct Sub {
    u8 pad0[0x238];
    Cfg *x238;
} Sub;

typedef struct Glob {
    u8 pad0[0x20];
    Sub *x20;
} Glob;

extern void FrameGetWorldPos_148f30(s32, V4 *);
extern s32 ModelGetRootFrame_1511a0(Obj *);
extern s32 ModelGetFrame_1511f0(Obj *, s32);
extern s32 *ObjFindNthAttachPoint_1addc0(Obj *, s32, s32);
extern Obj *ObjRecGetLiveObject_1c4a90(s32, s32);
extern Glob *GetGameData_1fede0(void);
extern s32 IsInBattle_288420(void);
extern void ScriptSlotStoreVec3_2cc8a0(s32, V4 *);
extern s32 ScriptSlotGetInt_2cc9c0(void);
extern f32 D_0047EDE0;
extern f32 D_0047EDE4;
extern f32 D_0047EDE8;
extern f32 D_0047EDEC;
extern s32 D_004DB920[4];

s32 AiCmdGetObjPos_2c9cc0(s32 arg0, s32 arg1)
{
    V4 v;
    s32 n;
    Obj *o;
    s32 h;
    Cfg *c;
    s16 *id;
    s32 *r;
    s32 t;
    s32 mgr;
    V4 *pv;

    if (arg1 != 4) {
        return 0;
    }
    arg0 += 8;
    n = ScriptSlotGetInt_2cc9c0();
    { f32 *pa = (f32 *)&v; pa[0] = D_0047EDE0; pa[1] = D_0047EDE4; pa[2] = D_0047EDE8; pa[3] = D_0047EDEC; }
    mgr = D_004DB920[0];
    if (n < 0) {
        ScriptSlotStoreVec3_2cc8a0(arg0, &v);
        return 1;
    }
    o = ObjRecGetLiveObject_1c4a90(mgr, n);
    if (o == NULL) {
        ScriptSlotStoreVec3_2cc8a0(arg0, &v);
        return 1;
    }
    h = ModelGetRootFrame_1511a0(o);
    if (IsInBattle_288420() != 0 && n >= 0x81 && n < 0x87) {
        c = GetGameData_1fede0()->x20->x238;
        if (c != NULL) {
            id = c->x18;
        } else {
            id = NULL;
        }
        if (id != NULL && *id == 0x40A) {
            r = ObjFindNthAttachPoint_1addc0(o, 0x82, 0);
            if (r != NULL) {
                t = ModelGetFrame_1511f0(o, *r);
                if (t != 0) {
                    h = t;
                }
            }
        }
    }
    if (h != 0) {
        FrameGetWorldPos_148f30(h, &v);
    } else {
        v = o->v180;
    }
    ScriptSlotStoreVec3_2cc8a0(arg0, &v);
    return 1;
}
