#include "types.h"

typedef struct {
    s32 a;
    s32 b;
} P8;

typedef struct {
    f32 x, y, z, w;
} V4;

typedef struct {
    u8 pad0[0x2C];
    s16 unk2C;
} Item;

class Tbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Item * v70(s16 a0) { return VCM(Item *, (void *, s16), 0x70, a0); }
};

typedef struct {
    u8 pad0[8];
    Tbl *unk8;
} Sub40;

typedef struct {
    u8 pad0[0x40];
    Sub40 *unk40;
} Glob;

typedef struct {
    u8 pad0[0x10];
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    u8 pad18[4];
} Info;

extern "C" {
extern s32 NameTableFindByName_159fb0(s32, Info *, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern Glob *GetWorldDataMgr_1fedf0(void);
extern void *MenuWinGet_2653e0(s32);
extern s32 ScriptGetInt_26a2a0(P8 *);
extern void MenuWinSetBlendMode_26c270(void *, s32);
extern void MenuWinSetUvRect_26c300(void *, s32, s32, s32, s32);
extern void MenuWinSetSize_26c320(void *, s32, s32);
extern void MenuWinSetColor_26c380(void *, V4 *);
extern void MenuWinSetPos_26c3b0(void *, V4 *);
extern void MenuWinSetTexFilter_26c3c0(void *, s32);
extern void MenuWinSetDrawLayer_26c3d0(void *, s32);
extern void MenuWinSetDrawMode_26c3e0(void *, s32);
extern void MenuWinSetTexName_26c410(void *, Info *, s32);
extern void UiGetWorkIconSprite_288a10(s32, s32 *);
extern f32 D_0047E940;
extern f32 D_0047E944;
extern f32 D_0047E948;
extern f32 D_0047E94C;
extern f32 D_0047E950;
extern f32 D_0047E954;
extern f32 D_0047E958;
extern f32 D_0047E95C;
}

extern "C" s32 EvCmdMenuWinItemIcon_264a30(P8 *p)
{
    struct {
        s32 n;
        Info info;
    } k;
    V4 v1 __attribute__((aligned(16)));
    V4 v2 __attribute__((aligned(16)));
    void *o;
    Item *it;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 id;

    o = MenuWinGet_2653e0(ScriptGetInt_26a2a0(p++));
    if (o == 0) {
        return 0;
    }
    id = ScriptGetInt_26a2a0(p);
    it = GetWorldDataMgr_1fedf0()->unk40->unk8->v70(id);
    if (it == 0) {
        return 0;
    }
    UiGetWorkIconSprite_288a10(it->unk2C, &k.n);
    if (NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), &k.info, k.n) == 0) {
        return 0;
    }
    a = k.info.a;
    b = k.info.b;
    c = k.info.c;
    d = k.info.d;
    { f32 *pa = (f32 *)&v1; pa[0] = D_0047E940; pa[1] = D_0047E944; pa[2] = D_0047E948; pa[3] = D_0047E94C; }
    { f32 *pb = (f32 *)&v2; pb[0] = D_0047E950; pb[1] = D_0047E954; pb[2] = D_0047E958; pb[3] = D_0047E95C; }
    MenuWinSetDrawMode_26c3e0(o, 0);
    MenuWinSetBlendMode_26c270(o, 1);
    MenuWinSetPos_26c3b0(o, &v1);
    MenuWinSetColor_26c380(o, &v2);
    MenuWinSetSize_26c320(o, 0x2A, 0x2A);
    MenuWinSetUvRect_26c300(o, a, b, c, d);
    MenuWinSetDrawLayer_26c3d0(o, 3);
    MenuWinSetTexFilter_26c3c0(o, 1);
    MenuWinSetTexName_26c410(o, &k.info, k.n);
    return 1;
}
