#include "types.h"
#include "vec.h"
extern "C" {

extern s32 PtmfTest_100eb0(void *);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void *GetWorldDataMgr_1fedf0(void);
extern void DrawBillboard32_2783c0(f32, f32, u128 *, f32, f32 *, f32, s32);
extern void UiGetWorkIconSprite_288a10(s16, s32 *);

extern f32 D_0047D7CC;
extern u8 D_0047E9D0;

class VC_0 {
public:
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
    virtual void * f(s16 x0);
};

struct Ent {
    u128 pos;
    u8 pad10[0x14];
    f32 scale;
    s32 id;
    s32 x2c;
    s32 x30;
    u8 pad34[0xC];
};

struct Mgr {
    Ent e[16];
    s32 x400;
    s32 active;
};

struct Info {
    u8 pad[0x10];
    s16 x;
    s16 y;
    u8 pad2[8];
};

void EventIconDrawAll_278790(Mgr *arg0) {
    u128 pos;
    f32 col[4];
    struct { s32 idx; Info info; } q;
    void *mgr;
    s32 ctx;
    s32 res;
    s32 i;
    Ent *e;
    f32 sx;
    f32 sy;
    f32 s;
    f32 s2;
    void *obj;
    s32 n;
    s32 *p;

    if (arg0->active != 0) {
        mgr = GetWorldDataMgr_1fedf0();
        ctx = GetDrawCtxNameTable_15de40();
        for (i = 0; i < 16; i++) {
            e = &arg0->e[i];
            p = &e->id;
            if ((*p >= 0) != 0 && e->x2c <= 0) {
                s = e->scale;
                sy = s;
                s = s2 = 10.0f * sy;
                res = 0;
                sy = sx = 40.0f;
                pos = e->pos;
                n = e->x30;
                if (n - 10 > 0) {
                    col[0] = 128.0f;
                    col[1] = 128.0f;
                    col[2] = 128.0f;
                    col[3] = 128.0f;
                } else {
                    col[0] = 128.0f;
                    col[1] = 128.0f;
                    col[2] = 128.0f;
                    col[3] = D_0047D7CC * (128.0f * (f32)n);
                }
                obj = ((VC_0 *)*(void **)(*(u8 **)((u8 *)mgr + 0x40) + 8))->f(*(s16 *)p);
                if (obj != NULL) {
                    UiGetWorkIconSprite_288a10(*(s16 *)((u8 *)obj + 0x2C), &q.idx);
                    res = NameTableFindByName_159fb0(ctx, &q.info, q.idx);
                    sx = q.info.x;
                    sy = q.info.y;
                }
                DrawBillboard32_2783c0(s - 0.5, s2 - 0.5, &pos, sx, col, sy, res);
            }
        }
        if (PtmfTest_100eb0(&D_0047E9D0) == 0) {
            arg0->active = 0;
        }
    }
}

}
