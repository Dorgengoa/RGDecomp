#include "types.h"

/* factory.bin overlay, 0x004F2A70 -- open the parts sub-menu, once.
 *
 * ★ `sh $6, 0x14($2)` and the following `mult $2, $6, $4` share `$6`: retail
 * FORWARDS the value just stored into `rec->f14` rather than re-loading it, so
 * the multiply's left operand is the field, not a literal 1 -- the recorded
 * store-then-read shape.
 * ★ `o->f78 = 2;` written BEFORE `func_207DF0()` is what puts the `sb` in that
 * call's delay slot.
 */

typedef struct Rec {
    s16 f00;
    u8  pad02[0x2];
    s16 f04;
    s16 f06;
    s16 f08;
    u8  pad0A[0xA];
    s16 f14;
    u8  pad16[0x2];
    s16 f18;
} Rec;

typedef struct Page {
    u8    pad00[0x1E];
    u8    f1E;
    u8    pad1F[0x21];
    void *f40;
    void *f44;
    u8    pad48[0x30];
    u8    f78;
} Page;

extern void *D_004807EC;                        /* _gp - 0x4984 */

extern void  factory_FactoryMaterialClearConfirmLayout_4f2170(void);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern Rec  *func_28FE10(void *w, s32 id, s32 a);
extern void  func_28FCD0(void *w, s32 id, s32 a, s32 b);
extern Rec  *func_28EA40(void *ctx, s32 id);
extern void  func_290F60(void *w, s32 id, s32 a, s32 b);
extern void  func_28EA90(void *ctx, s32 id, s32 a);
extern void *func_207DF0(void);
extern void  func_1B9520(void *p, s32 a, s32 b, f32 v);

void factory_FactoryMaterialClearConfirmOpen_4f2a70(Page *o)
{
    Rec *row;
    Rec *rec;

    if (o->f78 == 0) {
        factory_FactoryMaterialClearConfirmLayout_4f2170();
        func_290010(o->f40, 0x64, 0, -1);
        func_290010(o->f40, 0x63, 0, -1);
        func_290010(o->f40, 0x68, 0, -1);
        func_290010(o->f40, 0x6A, 1, -1);
        func_290010(D_004807EC, 0x97, 1, -1);
        func_290690(o->f40, 0x6A, 1.0f, 0.125f, -1.0f);
        func_290690(D_004807EC, 0x97, 1.0f, 0.125f, -1.0f);
        row = func_28FE10(o->f40, 0x75, 0);
        func_28FCD0(o->f40, 0x75, row->f00 + 2 + row->f18, 3);
        rec = func_28EA40(o->f44, 0x893A);
        rec->f14 = 1;
        func_290F60(D_004807EC, 0x97, rec->f04 + rec->f14 * rec->f08, rec->f06);
        o->f1E = 1;
        func_28EA90(o->f44, 0x893A, 0);
        o->f78 = 2;
        func_1B9520(func_207DF0(), 5, 0, 1.0f);
    }
}
