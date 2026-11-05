/* rg-override: replaces game/src/main/map/MapAreaModelDrawObjListLitMaybe_188120.cpp sha256 3d6dafb5ccb5d8d1508923626c840f5a1cb0083aee30e3516afff9c97b6b0cc6
 * why: draw-path random numbers (docs/WIDESCREEN.md "Draw-path random numbers", lane randdraw): an object drawn only because of the port's wider planes (and its children) draws with the private stream; the helpers are in the ViewSetPerspective_1564a0 override; no effect at 4:3 / 16:9 (no retail-plane set) */
#include "types.h"

/* jalr $25: the vptr lands at +0x68 of the element, so the class carries
   0x68 bytes before its first virtual.  Slot = 8 + 4*index. */
struct E {
    u8  pad000[0x32];
    s16 m32;
    u8  pad034[0x68 - 0x34];
    VC_VPTR_MEMBER;
    
    
    
    
    void v5(f32 f) { VCM(void, (void *, f32), 0x1C, f); }
    
    
    void v8() { VCM0(void, 0x28); }
};

struct Self {
    u8   pad000[0x52C];
    s32  m52C;
    E  **m530;
};

extern "C" void NodeObjIsInView_194200(E *e);

extern "C" s32 rg_cull_draw_begin(void *obj);
extern "C" void rg_cull_draw_end(s32 tok);

extern "C" void MapAreaModelDrawObjListLitMaybe_188120(Self *self)
{
    s32 tok;
    E  **arr;
    s32  n;
    s32  i;
    E   *e;

    arr = self->m530;
    n = self->m52C;
    for (i = 0; i < n; i++) {
        e = arr[i];
        if (e == 0) {
            continue;
        }
        if (e->m32 == 0) {
            continue;
        }
        NodeObjIsInView_194200(e);
        tok = rg_cull_draw_begin(e);
        e->v5(1.0f);
        e->v8();
        rg_cull_draw_end(tok);
    }
}
