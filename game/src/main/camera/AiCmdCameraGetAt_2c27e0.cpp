#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  vptr at +0xC0, slot byte offset = 8 + 4*N. */

struct Vec4 { f32 x, y, z, w; };

class Camera {
    u8 pad000[0xC0];
public:
    /* +0x08 */ VC_VPTR_MEMBER;
    /* +0x0C */ 
    /* +0x10 */ 
    /* +0x14 */ 
    /* +0x18 */ 
    /* +0x1C */ 
    /* +0x20 */ 
    /* +0x24 */ 
    /* +0x28 */ 
    /* +0x2C */ 
    /* +0x30 */ 
    /* +0x34 */ 
    /* +0x38 */ 
    /* +0x3C */ 
    /* +0x40 */ 
    /* +0x44 */ 
    /* +0x48 */ 
    /* +0x4C */ 
    /* +0x50 */ 
    /* +0x54 */ 
    /* +0x58 */ 
    /* +0x5C */ 
    /* +0x60 */ 
    /* +0x64 */ 
    /* +0x68 */ 
    /* +0x6C */ 
    /* +0x70 */ 
    /* +0x74 */ 
    /* +0x78 */ 
    /* +0x7C */ 
    /* +0x80 */ 
    /* +0x84 */ 
    /* +0x88 */ 
    /* +0x8C */ 
    /* +0x90 */ 
    /* +0x94 */ 
    /* +0x98 */ 
    /* +0x9C */ 
    /* +0xA0 */ 
    /* +0xA4 */ 
    /* +0xA8 */ void target(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA8, a0); }
};

struct World {
    u8  pad0000[0x4344];
    s32 m4344;
};

extern "C" World *GetCurrentScene_1f5be0(void);
extern "C" Camera *ObjRecGetLiveObject_1c3bc0(World *w, s32 scene);
extern "C" void ScriptSlotStoreVec3_2cc8a0(void *self, Vec4 *v);

extern "C" s32 AiCmdCameraGetAt_2c27e0(void *self, s32 kind)
{
    World *w;
    Camera *cam;
    Vec4 buf __attribute__((aligned(16)));

    if (kind != 3) {
        return 0;
    }
    w = GetCurrentScene_1f5be0();
    if (w == NULL) {
        return 0;
    }
    cam = ObjRecGetLiveObject_1c3bc0(w, w->m4344);
    if (cam == NULL) {
        return 0;
    }
    cam->target(&buf);
    ScriptSlotStoreVec3_2cc8a0(self, &buf);
    return 1;
}
