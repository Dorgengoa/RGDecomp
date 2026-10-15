#include "types.h"
#pragma optimization_level 3

struct Vec4 { f32 x, y, z, w; };
struct Mtx { f32 m[4][4]; };
struct Obj {
    u8 pad00[0x26];
    s16 m26;
    u8 pad28[2];
    s16 m2A;
    u8 pad2C[8];
    s16 m34;
    u8 pad36[2];
    f32 m38[4];
    f32 m48[4];
    f32 m58;
    f32 m5C;
    f32 m60;
    u8 pad64[0xC];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 brest : 6;
};
struct Part { u8 pad00[0x24]; u8 m24; u8 pad25[9]; s16 m2E; };
struct Base1B0 { u8 pad[0x1B0]; };
struct Ctl : Base1B0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7();
    u8 pad1B4[0x448 - 0x1B4];
    f32 m448;
    u8 pad44C[4];
    s32 m450;
};
struct Src { u8 pad00[0x28]; Ctl *m28; u8 pad2C[0xC]; s32 m38; u8 pad3C[4]; Part *m40[3]; };
struct Res { u8 pad00[4]; Src *m4; u8 pad08[4]; s16 mC; };

extern "C" {
Res *TreasureBoxResolveRec_33b180();
s32 GetDrawCtx_15de80();
void ModelSetPos_151110(Ctl *, Obj *);
void ModelSetRot_151080(Ctl *, void *);
void FrameSetRot_14a390(s32, Vec4 *);
void Character2LightBlendSetTarget_1aebe0(Ctl *, s32, Mtx *, Mtx *, Vec4 *, Vec4 *, s32);
}

extern "C" s32 TreasureBoxDraw_339540(Obj *obj, f32 scale)
{
    Part *arr[3];
    Vec4 v100;
    Mtx mC0;
    Mtx m80;
    Vec4 v70;
    Vec4 v60;
    Res *r;
    Src *src;
    s32 kind;
    s32 s2;
    Ctl *ctl;
    s32 i;
    Part *p;
    u8 flag;
    Mtx *pm;
    Vec4 *pv;
    s32 id;
    u8 *z;
    u32 n;

    r = TreasureBoxResolveRec_33b180();
    if (r == 0) {
        return 0;
    }
    if (!obj->b0 && obj->m26 == 0) {
        return 0;
    }
    src = r->m4;
    kind = r->mC;
    if (src == 0) {
        return 0;
    }
    ctl = src->m28;
    if (ctl == 0) {
        return 0;
    }
    s2 = src->m38;
    { z = (u8 *)(arr); n = 12; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); } }
    for (i = 0; i < 3; i++) {
        arr[i] = src->m40[i];
    }
    if (!obj->b1) {
        obj->m2A = 150;
    }
    if (GetDrawCtx_15de80() == 0) {
        return 0;
    }
    ModelSetPos_151110(ctl, obj);
    ModelSetRot_151080(ctl, (u8 *)obj + 0x10);
    if (s2 != 0) {
        { z = (u8 *)(&v100); n = 16; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); } }
        v100.x = obj->m5C;
        FrameSetRot_14a390(s2, &v100);
    }
    ctl->m448 = obj->m58 * scale;
    for (i = 0; i < 3; i++) {
        p = arr[i];
        if (p != 0) {
            flag = 0;
            switch (i) {
            case 0:
                if (kind == 1 || kind == 11) {
                    flag = 1;
                }
                break;
            case 1:
                if (kind == 2) {
                    flag = (u8)1;
                }
                break;
            case 2:
                if (kind == 3) {
                    flag = 1;
                }
                break;
            }
            if (flag && !(obj->m60 <= 0.0f)) {
                p->m24 = 1;
                p->m2E = (s32)(16384.0f * obj->m60);
            } else {
                p->m24 = 0;
            }
        }
    }
    ctl->m450 = 0;
    if (obj->m34 >= 0) {
        id = obj->m34 + 100;
        { z = (u8 *)(&mC0); n = 0x40; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); } }
        { z = (u8 *)(&m80); n = 0x40; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); } }
        { z = (u8 *)(&v70); n = 0x10; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); } }
        { z = (u8 *)(&v60); n = 0x10; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); } }
        mC0.m[0][0] = obj->m38[0];
        { f32 *q = (f32 *)((u32)&mC0);
        q[1] = obj->m38[1];
        q[2] = obj->m38[2];
        q[3] = obj->m38[3]; }
        v70.x = obj->m48[0];
        { f32 *r = (f32 *)((u32)&v70);
        r[1] = obj->m48[1];
        r[2] = obj->m48[2];
        r[3] = obj->m48[3]; }
        Character2LightBlendSetTarget_1aebe0(ctl, id, &mC0, &m80, &v70, &v60, 0);
    }
    ctl->v7();
    return 0;
}
