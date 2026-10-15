#include "types.h"
/* normal 0x004F9AE0 -- open the 0x7F widget.  _gp = 0x00485170, so -0x35B4
 * is D_00481BBC (a pointer, 4 bytes, so it stays in small data).  $4 is never
 * reloaded for the first func_291110 call: it is still the incoming a0. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3A2 - 0x37A];
    s16 f3A2;
    u8  pad3A4[0x3D8 - 0x3A4];
    s16 f3D8;
    u8  pad3DA[0x4A0 - 0x3DA];
    s16 f4A0;
} Obj;

extern void  func_291110(Obj *a, u16 id, s32 c, s32 d);
extern void  func_290F60(Obj *a, u16 id, s32 c, s32 d);
extern void  func_2907A0(Obj *a, u16 id, f32 t);
extern void *func_28AA30(void *bank, s32 k);
extern void  func_28F510(Obj *a, u16 id, void *q, s32 k);
extern void  func_28FCD0(Obj *a, u16 id, s32 c, s32 d);
extern void *D_00481BBC;                                /* _gp - 0x35B4 */

void normal_FieldHudWidget7FOpen_4f9ae0(Obj *p, s32 sel)
{
    if (p->f378 == 0) {
        return;
    }
    if (p->f3A2 != 0) {
        return;
    }
    if (p->f3D8 != 0) {
        func_291110(p, 0x7F, 0, 1);
        return;
    }
    func_291110(p, 0x7F, 1, 1);
    if (sel != 0) {
        func_28F510(p, 0x7F, func_28AA30(D_00481BBC, 0), 0);
        func_28FCD0(p, 0x7F, 3, 0);
    } else {
        func_28F510(p, 0x7F, func_28AA30(D_00481BBC, 1), 0);
        func_28FCD0(p, 0x7F, -1, 0);
    }
    func_290F60(p, 0x7F, 0x10, 0x14A);
    func_2907A0(p, 0x7F, 1.0f);
    p->f4A0 = 1;
}
