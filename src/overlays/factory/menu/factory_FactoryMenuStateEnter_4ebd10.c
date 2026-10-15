#include "types.h"

typedef struct Scene {
    u8    pad00[0x64];
    void *f64;
    u8    pad68[0x4];
    void *f6C;
} Scene;

extern s32    D_00480828;                       /* _gp - 0x4948 */
extern u8     D_00480800;                       /* _gp - 0x4970 */
extern Scene *D_00484A44;                       /* _gp - 0x72C  */
extern s32    D_00484A8C;                       /* _gp - 0x6E4  */
extern s32    D_00484A90;                       /* _gp - 0x6E0  */
extern u8     D_00484A94;                       /* _gp - 0x6DC  */
extern f32    D_0047D510;                       /* _gp - 0x7C60 */
extern f32    D_0047D520;                       /* _gp - 0x7C50 */

typedef struct Owner {
    u8    pad00[0x8];
    void *f8;
} Owner;

extern Owner *func_1FEDE0(void);
extern s32    func_3EEF10(void *p);
extern void   func_290F60(void *w, s32 id, s32 a, s32 b);
extern void   func_290F50(void *w, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void   func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void   func_2910A0(void *w, s32 id, s32 *a, s32 *b);
extern void   func_28EDE0(void *w, s32 id, s32 a);
extern void   factory_FactoryMenuReset_4f10f0(Scene *s);
extern void   factory_FactoryMenuRowsSlideIn_4eb3c0(void);

s32 factory_FactoryMenuStateEnter_4ebd10(s32 unused, s32 start)
{
    s32 x;
    s32 y;
    Owner *o;

    if (start != 0) {
        D_00480828 = -1;
        D_00480800 = 1;
    }
    o = func_1FEDE0();
    if (o == 0) {
        return 1;
    }
    switch (D_00480828) {
    case -1:
        if (func_3EEF10(o->f8) != 0) {
            func_290F60(D_00484A44->f64, 1, -0x30, -0xF);
            func_290F50(D_00484A44->f64, 1, -1, -1, 0, D_0047D510);
            func_290690(D_00484A44->f64, 1, 1.0f, D_0047D520, 0.0f);
            factory_FactoryMenuReset_4f10f0(D_00484A44);
            D_00480828 = 0;
            D_00484A94 = 0;
            D_00484A8C = 0;
            D_00484A90 = 0;
        }
        break;
    case 0:
        func_2910A0(D_00484A44->f64, 1, &x, &y);
        if (x == -1 && y == -1) {
            factory_FactoryMenuRowsSlideIn_4eb3c0();
            D_00480828 = 1;
        }
        /* fallthrough */
    case 1:
        func_2910A0(D_00484A44->f64, 0xA, &x, &y);
        if (x == 0 && y == 0) {
            func_28EDE0(D_00484A44->f6C, 0x88CC, 0);
            D_00480828 = -1;
        }
        break;
    }
    return 1;
}
