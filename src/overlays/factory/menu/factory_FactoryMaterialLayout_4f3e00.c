#include "types.h"

/* factory.bin overlay, 0x004F3E00 -- build the two-choice confirm bar.
 *
 * ★ `bgez $2 / sra $3, $2, 1 / addiu $2, $2, 1 / sra $3, $2, 1` is the signed
 * `/ 2` bias sequence and nothing else -- m2c writes it out longhand, but a
 * plain division compiles to exactly these four instructions.
 */

typedef struct Page {
    u8    pad00[0x40];
    void *f40;
    u8    pad44[0x34];
    u8    f78;
} Page;

extern void *D_00484A70;                        /* _gp - 0x700 */

extern void factory_FactoryMaterialClearConfirmLayout_4f2170(Page *o);
extern void factory_FactoryMaterialReqListLayout_4f2d50(Page *o);
extern void func_290010(void *w, s32 id, s32 a, s32 b);
extern void func_290BD0(void *w, s32 id, s32 a, s32 b, s32 c, s32 d);
extern s32  func_28AA30(void *ctx, s32 id);
extern void func_28F510(void *w, s32 id, s32 p, s32 a);
extern void func_2907A0(void *w, s32 id, f32 v);
extern s32  func_28F400(void *w, s32 id, s32 a);
extern void func_28F590(void *w, s32 id, s32 a, s32 b);

void factory_FactoryMaterialLayout_4f3e00(Page *o)
{
    func_290010(o->f40, 0x68, 0, -1);
    func_290BD0(o->f40, 0x65, 0x200, 1, 0, 0);
    func_290BD0(o->f40, 0x65, 0x200, 1, 1, 0);
    func_28F510(o->f40, 0x65, func_28AA30(D_00484A70, 0x18), 0);
    func_28F510(o->f40, 0x65, func_28AA30(D_00484A70, 0xE6), 1);
    func_290010(o->f40, 0x69, 1, -1);
    func_2907A0(o->f40, 0x69, 0.0f);
    func_290BD0(o->f40, 0x69, 0x200, 1, 0, 0);
    func_28F510(o->f40, 0x69, func_28AA30(D_00484A70, 0xDC), 0);
    func_28F590(o->f40, 0x69, 0x100 - func_28F400(o->f40, 0x69, 0) / 2, 0);
    factory_FactoryMaterialClearConfirmLayout_4f2170(o);
    factory_FactoryMaterialReqListLayout_4f2d50(o);
    o->f78 = 0;
}
