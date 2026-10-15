#include "types.h"
/* normal 0x004F1940 -- sibling of normal_FieldHudRadarShow_4f19e0 for the same widget id. */
typedef struct Obj { u8 pad000[0x430]; s8 f430; } Obj;

extern f32  D_0047DB7C;
extern f32  D_0047DD14;
extern f32  D_0047DD18;
extern void func_2907A0(Obj *p, u16 id, f32 x);
extern void func_290690(Obj *p, u16 id, f32 x, f32 y, f32 z);
extern void func_290F50(Obj *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void normal_FieldHudAllySuggestCancel_4eec90(Obj *p);

void normal_FieldHudRadarSlideOut_4f1940(Obj *p)
{
    func_2907A0(p, 0x25, 1.0f);
    func_290690(p, 0x25, D_0047DB7C, -1.0f, -1.0f);
    func_290F50(p, 0x25, 0x258, 0x140, 0, D_0047DD14);
    func_290690(p, 0x54, 0.0f, D_0047DD18, -1.0f);
    normal_FieldHudAllySuggestCancel_4eec90(p);
    p->f430 = 1;
}
