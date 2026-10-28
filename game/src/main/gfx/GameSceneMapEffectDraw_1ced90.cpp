/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_loop_invariants off

class ActorBase {
public:
    u8 pad0[0x68];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void Draw(s32 a0) { VCM(void, (void *, s32), 0x38, a0); }
    void Post() { VCM0(void, 0x3C); }
};

class Actor : public ActorBase {
public:
    u8 pad6c[0x167C - 0x6C];
    s32 f167C;
};

struct Rect {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
};

struct View {
    u8 pad[0x70];
};

extern "C" {
void GfxBlitTexRectPixelsAt_141810(void *, View *, Rect *, s32, s32, s32);
void DrawListAddTexLoad_1418c0(void *, s32, f32);
void DrawEnvGetFrameTexDesc_144cc0(void *, View *);
s32 DrawEnvGetHeight_1451d0(void *);
s32 DrawEnvGetWidth_1451e0(void *);
s32 NameTableFindByName_159fb0(void *, s8 *, s32);
void NameTableNodeCtor_15ae50(View *);
void *GetDrawCtxNameTable_15de40(void);
void *GetDrawCtx_15de80(void);
void ParticleSwirlSetTex_17da90(void *, s32);
s32 ObjRecCollectLiveObjects_1c5150(u8 *, Actor **, s32);
f32 GameSceneGetTimeStep_1ceba0(u8 *);
}
extern "C" s8 D_0045B0B0[0x10];

extern "C" void GameSceneMapEffectDraw_1ced90(u8 *obj, s32 arg1)
{
    Actor *list[20];
    View view __attribute__((aligned(16)));
    Rect rect __attribute__((aligned(16)));
    void *g;
    void *tex;
    s32 n;
    s32 i;
    s32 t;

    g = GetDrawCtx_15de80();
    tex = GetDrawCtxNameTable_15de40();
    n = ObjRecCollectLiveObjects_1c5150(obj, list, 20);
    DrawListAddTexLoad_1418c0(g, arg1, GameSceneGetTimeStep_1ceba0(obj));
    for (i = 0; i < n; i++) {
        Actor **pp = &list[i];
        if (*pp != 0) {
            (*pp)->f167C = (s32)(obj + 0x59E0);
            (*pp)->Draw(arg1);
            (*pp)->f167C = 0;
        }
    }
    t = NameTableFindByName_159fb0(tex, D_0045B0B0, arg1);
    ParticleSwirlSetTex_17da90(obj + 0x59E0, t);
    NameTableNodeCtor_15ae50(&view);
    DrawEnvGetFrameTexDesc_144cc0(g, &view);
    {
        s32 w = DrawEnvGetHeight_1451d0(g) - 1;
        s32 h = DrawEnvGetWidth_1451e0(g) - 1;
        rect.x = 0;
        rect.y = 0;
        rect.w = w;
        rect.h = h;
    }
    GfxBlitTexRectPixelsAt_141810(g, &view, &rect, t, 0, 0);
    for (i = 0; i < n; i++) {
        Actor **pp = &list[i];
        if (*pp != 0) {
            (*pp)->f167C = (s32)(obj + 0x59E0);
            (*pp)->Post();
            (*pp)->f167C = 0;
        }
    }
}
