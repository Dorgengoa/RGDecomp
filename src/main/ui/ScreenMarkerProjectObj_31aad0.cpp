#pragma opt_propagation off
#include "types.h"

struct Vec4 {
    f32 x, y, z, w;
};

struct Base {
    u8 pad[0xC0];
};

struct Cam : public Base {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void GetMat(Vec4 *);
};

struct Self {
    u8 pad[0x144];
    f32 x144;
};

struct Pos {
    u8 pad[0x38];
    f32 x, y, z;
};

struct Hit {
    u8 pad[0x10];
    f32 x10;
};

extern "C" {
u8 *GetDrawCtx_15de80(void);
s32 DrawEnvGetWidth_1451e0(u8 *);
s32 DrawEnvGetHeight_1451d0(u8 *);
u8 *GetCurrentScene_1f5be0(void);
u8 *ObjRecGetLiveObject_1c4a90(u8 *, s32);
u8 *GetNpcObjTable_312860(void);
Pos *NpcObjFindDefById_2fb490(u8 *, s32);
Cam *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
u8 *ModelGetRootFrame_1511a0(u8 *);
void FrameGetWorldPos_148f30(u8 *, Vec4 *);
f32 ModelObjGetScaledHeight_23b110(u8 *);
Hit *ObjGetNthAttachPointPos_1ade20(u8 *, s32, s32, Vec4 *);
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
f32 ScreenMarkerGetNearDist_31ae20(Self *);
f32 ScreenMarkerGetFarDist_31ae40(Self *);
void ProjectToScreenOffset_15d160(s32 *, Vec4 *);
void ScreenMarkerSetFlagById_31a900(Self *, s32, s32);
extern f32 D_0045B080[];
extern f32 D_0047D82C;
extern f32 D_0047F2C0;
extern f32 D_0047F2C4;
extern f32 D_0047F2C8;
extern f32 D_0047F2CC;
}

extern "C" s32 ScreenMarkerProjectObj_31aad0(Self *self, s32 id) {
    Vec4 c;
    s32 b[4];
    Vec4 a;
    Vec4 v;
    u8 *h;
    s32 w;
    s32 ht;
    u8 *world;
    u8 *obj;
    Pos *pos;
    Cam *cam;
    Hit *hit;
    f32 f;
    f32 dist;
    f32 lo;
    f32 ratio;
    s32 r;

    h = GetDrawCtx_15de80();
    w = DrawEnvGetWidth_1451e0(h);
    ht = DrawEnvGetHeight_1451d0(h);
    world = GetCurrentScene_1f5be0();
    obj = ObjRecGetLiveObject_1c4a90(world, id);
    if (obj == 0) {
        return 0;
    }
    pos = NpcObjFindDefById_2fb490(GetNpcObjTable_312860(), id);
    cam = ObjRecGetLiveObject_1c3bc0(world, *(s32 *)(world + 0x4344));
    if (cam == 0) {
        return 0;
    }
    cam->GetMat(&a);
    if (obj != 0) {
        FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(obj), &c);
        f = ModelObjGetScaledHeight_23b110(obj);
        hit = ObjGetNthAttachPointPos_1ade20(obj, 0x96, 0, &c);
        if (hit != 0) {
            { f32 x = hit->x10; f32 j = D_0045B080[0]; c.y = c.y + x * (D_0047D82C * j); }
        } else {
            c.y = c.y + f;
        }
    }
    { Vec4 *pv = &v; pv->x = D_0047F2C0; pv->y = D_0047F2C4; pv->z = D_0047F2C8; pv->w = D_0047F2CC; }
    v.x = c.x;
    v.y = c.y;
    v.z = c.z;
    if (pos != 0) {
        v.x = pos->x;
        v.y = pos->y;
        v.z = pos->z;
    }
    dist = VecDistance_13d3d0(&a, &v);
    lo = ScreenMarkerGetNearDist_31ae20(self);
    if (!(dist <= ScreenMarkerGetFarDist_31ae40(self)) || dist < lo) {
        return 0;
    }
    {
    ratio = dist / self->x144;
    if ((id >= 0 && id < 12) || (id >= 0x80 && id < 0x9C)) {
        c.y = c.y + 5.0f;
    } else if (id >= 0xC0 && id < 0xE0) {
        c.y = c.y + 2.0f * ratio;
    }
    ProjectToScreenOffset_15d160(b, &c);
    b[0] /= 16;
    b[1] /= 16;
    b[2] /= 16;
    if (b[2] < 0) {
        ScreenMarkerSetFlagById_31a900(self, 0, id);
        return 0;
    }
    if (b[0] < 0 || b[1] < 0 || b[0] > w || b[1] > ht) {
        return 0;
    }
    return 1;
    }
}
