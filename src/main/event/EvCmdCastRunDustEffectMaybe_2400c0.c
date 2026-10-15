#include "types.h"
#pragma opt_propagation off

typedef unsigned __int128 u128;

typedef union {
    u128 q;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } f;
} Vec;

typedef struct {
    Vec lo;
    Vec hi;
} Box;

typedef struct {
    u8 pad0[0x42];
    s16 type;
    u8 pad44[0x60 - 0x44];
} Hit;

typedef struct {
    u8 data[0x20];
} Snd;

extern void FrameGetWorldPos_148f30(s32, Vec *);
extern s32 ModelGetRootFrame_1511a0(s32);
extern s32 ModelGetFrame_1511f0(s32, s32);
extern s32 ModelFindFrameIndexByName_151220(s32, s32);
extern s32 MeshRaycastWrapper_16f610(Hit *, s32, Vec *, Vec *, Vec *, s32, s32);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 MapEvCollectCollPolysMaybe_1ff270(Hit *, s32, Box *, s32);
extern s32 ScriptGetCodeAddr_249050(s32);
extern s32 EventCastFindKeyByName_24bb50(s32, s32);
extern s32 EventCastGetObjId_24c160(s32, s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetId_2e0100(s32, Snd *, s32);
extern void EffectSetPos_2e0bb0(s32, Snd *, Vec *);
extern void EffectCreateByName_2e1020(Snd *, s32, char *, s32);
extern char *strcpy(char *, const char *);
extern f32 D_0045B080[];
extern char D_0045E998[];
extern char D_0045E9A0[];
extern s32 *gEventContext;

static inline void clear(char *p, s32 n) {
    if (p != NULL) {
        do {
            *p++ = 0;
        } while (--n != 0);
    }
}

s32 EvCmdCastRunDustEffectMaybe_2400c0(s64 *arg0, s32 arg1) {
    Vec pos;
    Hit hits[0x100];
    Box box;
    Vec c;
    Vec b;
    Vec a;
    char name[0x20];
    Snd snd;
    s32 base;
    s32 id;
    s32 obj;
    s32 r;
    f32 d;
    s32 n;
    s32 idx;
    s32 h;

    if (arg1 <= 0) {
        return 0;
    }
    id = ScriptGetCodeAddr_249050((s32)arg0++);
    base = gEventContext[1] + 0x60;
    id = EventCastGetObjId_24c160(base, EventCastFindKeyByName_24bb50(base, id));
    obj = ObjRecGetLiveObject_1c4a90(gEventContext[0], id);
    if (obj == 0) {
        return 0;
    }
    if (arg1 >= 2) {
        r = ModelGetFrame_1511f0(obj, ModelFindFrameIndexByName_151220(obj, ScriptGetCodeAddr_249050((s32)arg0)));
        if (r == 0) {
            return 0;
        }
        FrameGetWorldPos_148f30(r, &pos);
    } else {
        r = ModelGetRootFrame_1511a0(obj);
        if (r == 0) {
            return 0;
        }
        FrameGetWorldPos_148f30(r, &pos);
    }
    box.hi.q = pos.q;
    box.lo.q = pos.q;
    { f32 t = D_0045B080[0]; d = 2.0f * t; }
    box.hi.f.w = 1.0f;
    box.lo.f.w = 1.0f;
    box.hi.f.x -= d;
    box.hi.f.y -= d;
    box.hi.f.z -= d;
    box.lo.f.x += d;
    box.lo.f.y += d;
    box.lo.f.z += d;
    n = MapEvCollectCollPolysMaybe_1ff270(hits, 0x100, &box, -1);
    c.q = pos.q;
    b.q = pos.q;
    c.f.y += d;
    b.f.y -= d;
    idx = MeshRaycastWrapper_16f610(hits, n, &c, &b, &a, 1, 0);
    if (idx < 0) {
        return 0;
    }
    clear(name, 0x20);
    switch (hits[idx].type) {
    case 14:
    case 17:
        strcpy(name, D_0045E998);
        break;
    case 22:
    case 16:
    case 1:
        strcpy(name, D_0045E9A0);
        break;
    }
    if (name[0] != 0) {
        h = GetEffectMgr_2d9040();
        EffectCreateByName_2e1020(&snd, h, name, -1);
        EffectSetId_2e0100(h, &snd, id);
        EffectSetPos_2e0bb0(h, &snd, &pos);
    }
    return 1;
}
