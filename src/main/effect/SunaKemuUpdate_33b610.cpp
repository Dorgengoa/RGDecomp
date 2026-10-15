#include "types.h"

class Camera {
public:
    u8 pad000[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void notify(void *arg);
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

extern f32 D_0047D404;
extern f32 D_0047D7F8;
extern const f32 D_0047D5D0 __attribute__((section(".sdata")));

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
