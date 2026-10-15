#include "types.h"

typedef struct Ctx {
    u8    pad00[0x8];
    s16   f8;
    u8    padA[0x36];
    void *f40;
    void *f44;
    void *f48;
} Ctx;

typedef struct View {
    u8  pad00[0x8];
    s16 f8;
    u8  pad0A[0x6];
    s16 f10;
} View;

typedef struct Glyph {
    u8  pad00[0xC];
    s16 f0C;
} Glyph;

typedef struct Msg {
    s32   f0;
    u8    pad04[0x10];
    void *f14;
    s32   f18;
} Msg;

extern Ctx *D_00484A58;                         /* _gp - 0x718  */
extern f32  D_0047D35C;                         /* _gp - 0x7E14 */
extern f32  D_0047D4F8;                         /* _gp - 0x7C78 */
extern const u8 D_004B2570[];

extern void   func_28EA90(void *w, s32 id, s32 a);
extern Glyph *func_28EA40(void *w, s32 id);
extern s32    func_28E170(void *w, const u8 *p, s32 a, s32 b);
extern View  *func_28EC60(void *w);
extern s32    func_1839F0(const u8 *p, s32 mask);
extern void   func_289EF0(s32 a);
extern void   func_291250(void *w, s32 id, s32 a, s64 b);
extern s32    func_28EF00(void *w, s32 id, s32 a);
extern void   func_2905B0(void *w, s32 id, f32 a, f32 b, f32 c, f32 d);
extern void   func_2904E0(void *w, s32 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern void   func_28EDE0(void *w, s32 id, s32 a);
extern Msg   *func_367EC0(void);
extern void   factory_FactoryMaterialQtyPreset_4f2bf0(Ctx *c);
extern s32    factory_FactoryMaterialCellItemCount_4f3370(Ctx *c);
extern void  *factory_FactoryMaterialGetCellItem_4f3290(Ctx *c);

s32 factory_FactoryMaterialQtyTick_4ed320(s32 unused, s32 start)
{
    Glyph *g;
    View  *vw;
    Msg   *m;
    void  *h;
    s32    base;
    s32    v;
    s32    lim;
    s32    r;
    s32    n;

    if (start != 0) {
        func_28EA90(D_00484A58->f44, 0x8930, 0);
        g = func_28EA40(D_00484A58->f44, 0x8930);
        factory_FactoryMaterialQtyPreset_4f2bf0(D_00484A58);
        g->f0C = factory_FactoryMaterialCellItemCount_4f3370(D_00484A58);
    }
    vw = func_28EC60(D_00484A58->f44);
    base = vw->f10;
    r = func_28E170(D_00484A58->f44, D_004B2570, 1, 0);
    v = vw->f10;
    if (v == base) {
        lim = vw->f8;
        if (func_1839F0(D_004B2570, 0x1000) != 0) {
            v += 0xA;
        } else if (func_1839F0(D_004B2570, 0x4000) != 0) {
            v -= 0xA;
        }
        if (v < 0) {
            v = 0;
        } else if (lim < v) {
            v = lim;
        }
        vw->f10 = v;
    }
    if (v != base) {
        func_289EF0(4);
        func_291250(D_00484A58->f40, 0x79, 0, v);
    }
    if (r == 1) {
        n = func_28EF00(D_00484A58->f40, 0x79, 0);
        if (n > 0) {
            func_289EF0(5);
            func_2905B0(D_00484A58->f40, 0x79, D_0047D35C, D_0047D35C, D_0047D35C,
                        -1.0f);
            func_2904E0(D_00484A58->f40, 0x79, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D4F8);
            D_00484A58->f8 = n;
            func_28EDE0(D_00484A58->f48, 0x89B2, 0);
            h = factory_FactoryMaterialGetCellItem_4f3290(D_00484A58);
            if (h != 0) {
                m = func_367EC0();
                m->f0 = 0xB;
                m->f14 = h;
                m->f18 = n;
            }
        } else {
            func_289EF0(6);
        }
    } else if (r == 2) {
        func_289EF0(6);
        D_00484A58->f8 = -1;
        func_28EDE0(D_00484A58->f48, 0x89B2, 0);
    }
    return 1;
}
