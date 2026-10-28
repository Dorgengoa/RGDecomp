#include "types.h"

class Camera {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void notify(void *arg) { VCM(void, (void *, void *), 0xA8, arg); }
};

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    s16 unk10;
    u8 pad12[2];
} Entry; /* size 0x14 */

typedef struct {
    u8 pad00[0x18];
    Entry entries[10];
    f32 unkE0;
} Obj;

extern "C" void *GetCurrentScene_1f5be0(void);
extern "C" void *ObjRecGetLiveObject_1c3bc0(void *table, s32 id);
extern "C" f32 RandRangeFloat_1ca5d0(f32 max);

extern "C" f32 D_0047D404;
extern "C" f32 D_0047D7F8;
extern "C" f32 D_0047D5D0 __attribute__((section(".sdata")));

extern "C" void SunaKemuUpdate_33b610(Obj *self)
{
    void *mgr;
    Camera *camera;
    Entry *e;
    s32 i;

    f32 zz;

    zz = 0.0f;
    if (self->unkE0 == zz) {
        return;
    }

    mgr = GetCurrentScene_1f5be0();
    if (mgr == NULL) {
        return;
    }

    camera = (Camera *)ObjRecGetLiveObject_1c3bc0(mgr, *(s32 *)((u8 *)mgr + 0x4344));
    if (camera == NULL) {
        return;
    }

    camera->notify(self);

    e = self->entries;
    for (i = 0; i < 10; i++, e++) {
        if (e->unk10 <= 0) {
            continue;
        }
        e->unk0C -= e->unk08;
        if (e->unk0C <= -200.0f) {
            e->unk10 = 0;
        }
    }

    e = self->entries;
    for (i = 0; i < 10; i++, e++) {
        if (e->unk10 > 0) {
            continue;
        }
        e->unk00 = RandRangeFloat_1ca5d0(D_0047D404) - D_0047D7F8;
        e->unk04 = 200.0f;
        e->unk10 = 0xF0;
        e->unk08 = 20.0f * (RandRangeFloat_1ca5d0(D_0047D5D0) + (*(f32 *)&D_0047D5D0));
        e->unk0C = 100.0f + RandRangeFloat_1ca5d0(200.0f);
        return;
    }
}
