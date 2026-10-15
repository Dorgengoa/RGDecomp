#include "types.h"
#undef NULL
#define NULL 0

class O {
public:
    u8 pad[0x190];
    virtual void v0();
    virtual void v1();
    virtual void f10();
    virtual void f14(s32, u8 *, s32);
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
    virtual s32 f60();
    virtual s16 f64();
};

typedef struct Node {
    struct Node *next;
    u8 pad4[0xC];
    O *obj;
} Node;

extern "C" {
extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetFrameMask_13e420(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void DrawListEndPrim_141a20(s32);
extern s32 DrawListBeginPrim_141b00(s32);
extern void DrawListGetStats_148940(s32, s32 *, s32 *, s32 *, s32 *);
extern s32 NameTableFindByName_159fb0(s32, u8 *, s32);
extern s32 GetDrawCtxNameTable_15de40();
extern s32 GetDrawCtx_15de80(s32);
extern f32 D_0047D288;
}

static inline O **next(u8 *a)
{
    Node *c;
    Node *nx;
    O **e;

    c = *(Node **)(a + 4);
    if (c == NULL) {
        e = NULL;
    } else {
        e = &c->obj;
        nx = c->next;
        *(Node **)(a + 4) = nx;
        if (nx == NULL) {
            *(s32 *)(a + 8) = 1;
        }
    }
    return e;
}

extern "C" void EffectEntryDrawNodes_2da850(u8 *a)
{
    s32 n;
    Node *p;
    s32 h;
    s32 r20;
    s32 r19;
    s16 mode;
    O **e;
    s32 x6C;
    s32 x68;
    s32 x64;
    s32 x60;

    if (*(s16 *)(a + 0xBA) & 2) {
        return;
    }
    p = *(Node **)a;
    if (p == NULL) {
        n = 0;
    } else {
        n = 1;
        for (p = p->next; p != NULL; p = p->next) {
            n++;
        }
    }
    if (n <= 0) {
        return;
    }
    h = GetDrawCtx_15de80(n);
    DrawListAddTexLoad_1418c0(h, *(s16 *)(a + 0x14), 1.0f);
    if (*(Node **)(a + 4) == NULL) {
        *(Node **)(a + 4) = *(Node **)a;
        *(s32 *)(a + 8) = 0;
    }
    mode = *(s16 *)(a + 0xC);
    if (mode == 0) {
        for (;;) {
            e = next(a);
            if (e == NULL) {
                break;
            }
            DrawListGetStats_148940(h, &x6C, &x68, &x64, &x60);
            if (!((f32)x68 < D_0047D288 * (f32)x60)) {
                break;
            }
            if (*e != NULL) {
                (*e)->f10();
            }
        }
    } else if (mode == 1) {
        r20 = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), a + 0x5E, *(s16 *)(a + 0x14));
        if (*(s32 *)(a + 0x94) & 2) {
            return;
        }
        for (;;) {
            e = next(a);
            if (e == NULL) {
                break;
            }
            DrawListGetStats_148940(h, &x6C, &x68, &x64, &x60);
            if (!((f32)x68 < D_0047D288 * (f32)x60)) {
                break;
            }
            if (*e != NULL && !(*(s32 *)(a + 0x94) & 0x10) && (*e)->f60() != 0 && (*e)->f64() > 0) {
                r19 = DrawListBeginPrim_141b00(h);
                if (*(s32 *)(a + 0x94) & 4) {
                    GsPktSetAlphaBlend_13e500(r19, 0);
                } else {
                    GsPktSetAlphaBlend_13e500(r19, 1);
                    GsPktSetBlendMode_13e4f0(r19, *(s32 *)(a + 0x98));
                    GsPktEnableAlphaTest_13e4d0(r19, 0);
                }
                if (*(s32 *)(a + 0x94) & 8) {
                    GsPktSetZWriteMask_13e430(r19, 0);
                } else {
                    GsPktSetZWriteMask_13e430(r19, 1);
                }
                GsPktSetZWriteMask_13e430(r19, 1);
                GsPktSetFrameMask_13e420(r19, 1);
                GsPktSetTexFilter_13e3d0(r19, 1);
                GsPktSetTextured_13e400(r19, 1);
                if (*(s32 *)(a + 0x94) & 8) {
                    GsPktEnableZTest_13e460(r19, 0);
                } else {
                    GsPktEnableZTest_13e460(r19, 1);
                }
                (*e)->f14(r19, a + 0xC, r20);
                GsPktClose_13f5b0(r19);
                DrawListEndPrim_141a20(h);
            }
        }
    }
    *(Node **)(a + 4) = NULL;
    *(s32 *)(a + 8) = 0;
}
