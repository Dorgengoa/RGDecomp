#include "types.h"

typedef struct Head {
    u8    pad00[0x8];
    s16   f08;
    u8    pad0A[0x36];
    void *f40;
    void *f44;
    void *f48;
    u8    pad4C[0x2C];
    u8    f78;
} Head;

extern Head *D_00484A58;                        /* _gp - 0x718 */
extern f32   D_0047D4FC;                        /* _gp - 0x7C74 */

extern void  func_28EC60(void *h);
extern void  factory_FactoryMaterialFrameScroll_4f3a40(Head *h);
extern f32  *func_2904B0(void *h, s32 id);
extern f32   func_290770(void *h, s32 id);
extern void  func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern void  func_28EDE0(void *h, s32 id, s32 a);
extern void  func_28EA90(void *h, s32 id, s32 a);
extern void  func_2907A0(void *h, s32 id, f32 a);

s32 factory_FactoryMaterialQtyClose_4ed580(void)
{
    void *h;

    h = D_00484A58->f40;
    if (h == 0) {
        return 0;
    }
    func_28EC60(D_00484A58->f44);
    factory_FactoryMaterialFrameScroll_4f3a40(D_00484A58);
    if (*func_2904B0(h, 0x79) <= 1.0f) {
        if (func_290770(h, 0x77) >= 1.0f) {
            func_290690(h, 0x77, 0.0f, D_0047D4FC, -1.0f);
        }
    }
    if (func_290770(h, 0x77) <= 0.0f) {
        if (D_00484A58->f08 > 0) {
            D_00484A58->f78 = 1;
            func_28EDE0(D_00484A58->f48, 0x8980, 0);
            func_28EA90(D_00484A58->f44, 0x894E, 0);
            func_2907A0(D_00484A58->f40, 0xB0, 0.0f);
            func_2907A0(D_00484A58->f40, 0x69, 1.0f);
        } else {
            func_28EDE0(D_00484A58->f48, 0x8980, 0);
        }
    }
    return 1;
}
