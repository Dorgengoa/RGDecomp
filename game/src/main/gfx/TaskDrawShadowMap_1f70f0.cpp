/* rgp:protos */
#line 1
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

typedef struct {
    f32 a;
    s32 b;
    s32 c;
    f32 d;
    V4 v1;
    V4 v2;
    u8 rest[0x90];
} Parm;

struct CBase { u8 pad[0x1B0]; };
struct EBase { u8 pad[0x68]; };
class CObj : public CBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f17() { VCM0(void, 0x4C); }
};

class EObj : public EBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f16(void * a0, s32 a1) { return VCM(s32, (void *, void *, s32), 0x48, a0, a1); }
    void f17(void * a0, s32 a1) { VCM(void, (void *, void *, s32), 0x4C, a0, a1); }
};

extern "C" {
void ShadowMapBlur_145b60(s32);
void ShadowMapRender_146680(s32, Parm *);
void DrawListAddLightPacket_146b00(s32);
void ShadowMapBuildProjMaterialMaybe_146b90(s32, Parm *);
void FrameGetWorldPos_148f30(s32, V4 *);
s32 ModelGetRootFrame_1511a0(CObj *);
void ShadowMapDescInit_156a00(Parm *);
s32 NameTableFindByName_159fb0(s32, void *, s32);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
s32 ObjRecGetFlags_1c3d90(s32, s32, s32);
s32 ObjRecHasFlags6_1c3eb0(s32, s32, s32);
CObj *ObjRecGetLiveObject_1c4a90(s32, s32);
void VecCopy_1cbe30(V4 *, V4 *);
s32 MapFindBlockOrAreaAtPos_1e39a0(s32, V4 *, f32);
EObj *MapDataGetModel_1e7810(s32);
s32 GetCurrentScene_1f5be0(void);
void *GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
s32 ObjGetNthAttachPointPosSafe_23b0c0(CObj *, s32, s32, V4 *);
extern u8 D_0045BCB8[];
extern u8 D_0045BCD0[];
extern f32 D_0047D7D8;
extern s32 D_00481A78;
void TaskDrawShadowMap_1f70f0(void);
}

void TaskDrawShadowMap_1f70f0(void)
{
    Parm pr __attribute__((aligned(16)));
    V4 pos __attribute__((aligned(16)));
    u8 buf[0x800] __attribute__((aligned(16)));
    s32 m;
    s32 w;
    s32 ctx;
    s32 st;
    s32 i;
    CObj *c;
    s32 h;
    EObj *e;
    s32 n;

    if (D_00481A78 > 0) {
        return;
    }
    m = GetCurrentScene_1f5be0();
    w = GetMapMgr_201a90();
    GetGameData_1fede0();
    ctx = GetDrawCtx_15de80();
    st = GetDrawCtxNameTable_15de40();
    DrawListAddTexLoad_1418c0(ctx, 0x321, 1.0f);
    ShadowMapDescInit_156a00(&pr);
    i = 0;
    do {
        if (((unsigned char)ObjRecHasFlags6_1c3eb0(m, 1, i)) != 0 && !(ObjRecGetFlags_1c3d90(m, 1, i) & 0x20) && (ObjRecGetFlags_1c3d90(m, 1, i) & 0x40)) {
            c = ObjRecGetLiveObject_1c4a90(m, i);
            if (c != 0) {
                if (ObjGetNthAttachPointPosSafe_23b0c0(c, 1, 0, &pos) == 0) {
                    FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(c), &pos);
                }
                h = MapFindBlockOrAreaAtPos_1e39a0(w, &pos, 0.0f);
                if (h != 0) {
                    e = MapDataGetModel_1e7810(h);
                    if (e != 0) {
                        VecCopy_1cbe30(&pr.v1, &pos);
                        pr.v1.y += 20.0f;
                        pr.d = 440.0f;
                        VecCopy_1cbe30(&pr.v2, &pos);
                        pr.v2.y += 800.0f;
                        pr.b = NameTableFindByName_159fb0(st, D_0045BCB8, -1);
                        pr.c = NameTableFindByName_159fb0(st, D_0045BCD0, -1);
                        pr.a = D_0047D7D8;
                        ShadowMapRender_146680(ctx, &pr);
                        c->f17();
                        n = 0;
                        n += e->f16(buf, 0x200);
                        ShadowMapBlur_145b60(ctx);
                        ShadowMapBuildProjMaterialMaybe_146b90(ctx, &pr);
                        e->f17(buf, n);
                        DrawListAddLightPacket_146b00(ctx);
                    }
                }
            }
        }
        i++;
    } while (i < 0xE0);
}
