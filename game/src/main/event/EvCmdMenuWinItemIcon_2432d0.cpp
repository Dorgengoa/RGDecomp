#pragma opt_propagation off
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} Vec4;

typedef struct {
    u8 pad0[0x10];
    s16 a;
    s16 b;
    s16 c;
    s16 d;
} Info;

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * v70(s32 a0) { return VCM(u8 *, (void *, s32), 0x70, a0); }
};

extern "C" {
s32 NameTableFindByName_159fb0(s32, Info *, s32);
s32 GetDrawCtxNameTable_15de40(void);
u8 *GetWorldDataMgr_1fedf0(void);
s32 ScriptGetCodeAddr_249050(s32);
s32 ScriptGetInt_2490f0(s32);
void EventCastFindKeyByName_24bb50(u8 *, s32);
s32 MenuWinGet_2653e0(s32);
void MenuWinSetBlendMode_26c270(s32, s32);
void MenuWinSetUvRect_26c300(s32, s32, s32, s32, s32);
void MenuWinSetSize_26c320(s32, s32, s32);
void MenuWinSetColor_26c380(s32, Vec4 *);
void MenuWinSetPos_26c3b0(s32, Vec4 *);
void MenuWinSetTexFilter_26c3c0(s32, s32);
void MenuWinSetDrawLayer_26c3d0(s32, s32);
void MenuWinSetDrawMode_26c3e0(s32, s32);
void MenuWinSetTexName_26c410(s32, Info *, s32);
void UiGetWorkIconSprite_288a10(s32, s32 *);
extern f32 D_0047E850;
extern f32 D_0047E854;
extern f32 D_0047E858;
extern f32 D_0047E85C;
extern f32 D_0047E860;
extern f32 D_0047E864;
extern f32 D_0047E868;
extern f32 D_0047E86C;
extern u8 *gEventContext;
}

extern "C" s32 EvCmdMenuWinItemIcon_2432d0(s64 *arg0)
{
    struct { s32 n; Info info; } L;
    Vec4 pos __attribute__((aligned(16)));
    Vec4 col __attribute__((aligned(16)));
    s32 r;
    s32 id;
    s32 w;
    u8 *pl;
    u8 *q;
    u8 *e;
    u8 *t;
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    r = MenuWinGet_2653e0(ScriptGetInt_2490f0((s32)arg0++));
    if (r == 0) {
        return 0;
    }
    id = ScriptGetInt_2490f0((s32)arg0++);
    w = GetDrawCtxNameTable_15de40();
    pl = *(u8 **)(gEventContext + 4);
    q = pl + 0x60;
    EventCastFindKeyByName_24bb50(q, ScriptGetCodeAddr_249050((s32)arg0));
    e = ((VObj *)*(u8 **)(*(u8 **)(GetWorldDataMgr_1fedf0() + 0x40) + 8))->v70((s16)id);
    if (e == NULL) {
        return 0;
    }
    UiGetWorkIconSprite_288a10(*(s16 *)(e + 0x2C), &L.n);
    if (NameTableFindByName_159fb0(w, &L.info, L.n) == 0) {
        return 0;
    }
    {
        f32 *p = (f32 *)&pos;
        p[0] = D_0047E850;
        p[1] = D_0047E854;
        p[2] = D_0047E858;
        p[3] = D_0047E85C;
        p = (f32 *)&col;
        p[0] = D_0047E860;
        p[1] = D_0047E864;
        p[2] = D_0047E868;
        p[3] = D_0047E86C;
    }
    a = L.info.a;
    b = L.info.b;
    c = L.info.c;
    d = L.info.d;
    t = *(u8 **)(pl + 0x42C);
    if (t != NULL) {
        s32 x = *(s32 *)(t + 0x40);
        s32 y = *(s32 *)(t + 0x44);
        pos.x = (f32)(x - 0x1C);
        pos.y = (f32)(y + 0xA);
    }
    MenuWinSetDrawMode_26c3e0(r, 0);
    MenuWinSetBlendMode_26c270(r, 1);
    MenuWinSetPos_26c3b0(r, &pos);
    MenuWinSetColor_26c380(r, &col);
    MenuWinSetSize_26c320(r, 0x2A, 0x2A);
    MenuWinSetUvRect_26c300(r, a, b, c, d);
    MenuWinSetDrawLayer_26c3d0(r, 1);
    MenuWinSetTexFilter_26c3c0(r, 1);
    MenuWinSetTexName_26c410(r, &L.info, L.n);
    return 1;
}
