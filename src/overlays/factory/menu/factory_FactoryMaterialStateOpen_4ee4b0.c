#include "types.h"

typedef struct Meta { u8 pad00[0x14]; s16 f14; s16 f16; } Meta;
typedef struct Win  { u8 pad00[0x20]; void *f20; } Win;

typedef struct Root {
    u8    pad00[0x40];
    void *f40;
    void *f44;
    void *f48;
} Root;

extern Root *D_00484A58;
extern f32   D_0047D278;

extern void  factory_FactoryMenuCaptionSlideIn_4eb220(void);
extern void  factory_FactoryMenuCaptionSetRow_4eb270(s32 i);
extern void  factory_FactoryMaterialTabHighlight_4f3740(Root *r);
extern void  factory_FactoryMaterialShowCellInfo_4f38f0(Root *r);
extern void  factory_FactoryMaterialFrameInit_4f3d80(Root *r);
extern void  factory_FactoryMaterialLayout_4f3e00(Root *r);
extern void  factory_FactoryMaterialCursorReset_4f3fa0(Root *r);
extern void  func_28D580(void *w, s32 a, s32 b, s32 c, s32 d, s32 e);
extern Meta *func_28EA40(void *w, s32 id);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern Win  *func_290460(void *w, s32 id);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void  func_290F50(void *w, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void  func_290F60(void *w, s32 id, s32 x, s32 y);

s32 factory_FactoryMaterialStateOpen_4ee4b0(s32 a, s32 b)
{
    Meta *m;
    Win  *q;

    if (b != 0) {
        func_290010(D_00484A58->f40, 0xC, 1, -1);
        factory_FactoryMenuCaptionSetRow_4eb270(4);
        factory_FactoryMenuCaptionSlideIn_4eb220();
        func_290010(D_00484A58->f40, 0xB0, 1, -1);
        func_290010(D_00484A58->f40, 0x6D, 0, -1);
        func_290010(D_00484A58->f40, 0x77, 0, -1);
        func_290010(D_00484A58->f40, 0x67, 0, -1);
        factory_FactoryMaterialCursorReset_4f3fa0(D_00484A58);
        q = func_290460(D_00484A58->f40, 0x5D);
        if (q != 0) {
            if (q->f20 != 0) {
                func_28D580(q->f20, 0, 0, 0x193, 0x96, 0);
            }
        }
        func_290F60(D_00484A58->f40, 0xB0, 0x200, 0xAF);
        func_290F50(D_00484A58->f40, 0xB0, 0x2F, 0xAF, 0, D_0047D278);
        func_290690(D_00484A58->f40, 0xB0, 1.0f, 0.125f, 0.0f);
        m = func_28EA40(D_00484A58->f44, 0x891C);
        m->f16 = 0;
        m->f14 = 0;
        factory_FactoryMaterialTabHighlight_4f3740(D_00484A58);
        factory_FactoryMaterialFrameInit_4f3d80(D_00484A58);
        factory_FactoryMaterialLayout_4f3e00(D_00484A58);
        factory_FactoryMaterialShowCellInfo_4f38f0(D_00484A58);
    }
    func_28EDE0(D_00484A58->f48, 0x8980, 0);
    return 1;
}
