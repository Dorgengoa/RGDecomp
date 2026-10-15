#include "types.h"
extern "C" {

extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void ModelSetScale_150ff0(void *, void *);
extern void ModelSetRot_151080(void *, void *);
extern void ModelSetPos_151110(void *, void *);
extern s32 GetDrawCtx_15de80(void);
extern f32 AngleWrap_1cbf30(f32);
extern void *GetCursorObj_1fdb20(void);
extern void *InsectCageMgrFindSlotById_39b0c0(void *, s32);
extern void *InsectCageSlotGetModel_39b470(void *);
extern void InsectCageSlotDraw_39b490(void *, s32);

extern f32 D_0047D858;
extern f32 D_0047FF90;
extern f32 D_0047FF94;
extern f32 D_0047FF98;
extern f32 D_0047FF9C;

}

class VC_0 {
public:
    u8 pad[0x1B0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void f(f32 x0);
    virtual void d5();
    virtual void d6();
    virtual void g();
};

struct V4 { f32 x, y, z, w; };

struct Sub { u8 pad[0x30]; };

typedef struct {
    Sub sub[3];
    u8 pad90[0x40];
    f32 xD0;
    f32 xD4;
    f32 xD8;
    u8 padDC[0x14];
    s32 xF0;
    s32 xF4;
} T;

extern "C" void InsectCageMgrDraw_39a420(T *arg0, s32 arg1) {
    V4 sp60;
    V4 sp50;
    V4 sp40;
    s32 i;
    void *h;
    void *p;
    s32 ctx;
    VC_0 *obj;
    f32 r;
    u8 *q;
    u32 n;
    f32 x, y, z;

    for (i = 0; i < 3; i++) {
        InsectCageSlotDraw_39b490(&arg0->sub[i], arg1);
    }
    h = InsectCageMgrFindSlotById_39b0c0(arg0, arg0->xF0);
    if (h == NULL) return;
    p = InsectCageSlotGetModel_39b470(h);
    if (p == NULL) return;
    if (*(f32 *)((u8 *)p + 0x448) < 0.5f) return;
    ctx = GetDrawCtx_15de80();
    obj = (VC_0 *)GetCursorObj_1fdb20();
    z = arg0->xD8;
    y = 7.0f + arg0->xD4;
    x = arg0->xD0;
    { f32 *pf = (f32 *)&sp60; pf[0] = D_0047FF90; pf[1] = D_0047FF94; pf[2] = D_0047FF98; pf[3] = D_0047FF9C; }
    sp60.x = x;
    sp60.y = y;
    sp60.z = z;
    ModelSetPos_151110(obj, &sp60);
    r = AngleWrap_1cbf30(D_0047D858 * (f32)arg0->xF4 / 45.0f);
    q = (u8 *)&sp50;
    n = 16;
    if (q != NULL) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    sp50.y = r;
    sp50.x = 0.0f;
    sp50.z = 0.0f;
    ModelSetRot_151080(obj, &sp50);
    q = (u8 *)&sp40;
    n = 16;
    if (q != NULL) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    sp40.x = 1.0f;
    sp40.y = 1.0f;
    sp40.z = 1.0f;
    ModelSetScale_150ff0(obj, &sp40);
    DrawListAddTexLoad_1418c0(ctx, *(s32 *)((u8 *)obj + 0x4DC), 1.0f);
    obj->f(1.0f);
    obj->g();
}
