#include "types.h"

struct B1C47E0 { u8 pad[0x1B0]; };

struct Rec1C47E0 : public B1C47E0 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11(f32 a, void *b);
};

struct P1C47E0 {
    u8 pad[0x4360];
    f32 f4360;
    u8 pad2[0xC];
    s32 f4370;
};

extern "C" Rec1C47E0 *ObjRecGetLiveObject_1c4a90(P1C47E0 *);

extern "C" void SceneObjApplyWind_1c47e0(P1C47E0 *p)
{
    Rec1C47E0 *r;

    r = ObjRecGetLiveObject_1c4a90(p);
    if (r != 0) {
        r->v11(p->f4360, &p->f4370);
    }
}
