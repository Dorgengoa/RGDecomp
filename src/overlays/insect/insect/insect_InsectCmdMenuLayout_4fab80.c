#include "types.h"
/* insect 0x004FAB80 -- 680 bytes, 170 instructions.
 *
 * Lays out the three sub-widgets of a panel.  Both dispatches are `beql`
 * INTO their arms, so both are `switch`es and the source case order is the
 * compare chain reversed: (3, 2) for the swap and (3, 2, 0) for the x
 * placement -- which is also the order of the arms' block addresses
 * (0x4FAD4C < 0x4FAD58 < 0x4FAD64). */

typedef struct Obj {
    u8  pad0000[0x878];
    s32 f878;                       /* +0x878 */
    u8  pad087C[0x502C - 0x87C];
    u8  f502C[1];                   /* +0x502C */
    u8  pad502D[0x5054 - 0x502D];
    u8  f5054[1];                   /* +0x5054 */
    u8  pad5055[0x506C - 0x5055];
    u8  f506C[1];                   /* +0x506C */
    u8  pad506D[0x5DA0 - 0x506D];
    s32 f5DA0;                      /* +0x5DA0 */
    s32 f5DA4;                      /* +0x5DA4 */
    u8  pad5DA8[0x5EF1 - 0x5DA8];
    u8  f5EF1;                      /* +0x5EF1 */
} Obj;

extern s32  insect_InsectCmdMenuCount_4efc10(void *p);
extern s32  insect_InsectMsgTextWidth_512ab0(void *p, s32 a, s32 b);
extern void func_28F510(s32 h, s32 id, s32 a, s32 b);
extern s32  func_290460(s32 h, s32 id);
extern void func_290690(s32 h, s32 id, f32 a, f32 b, f32 c);
extern void func_2907A0(s32 h, s32 id, f32 a);
extern void func_290F60(s32 h, s32 id, s32 x, s32 y);
extern void func_392250(void *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, u8 g);
extern void func_3934D0(void *p, s32 a, s32 b, s32 c, s32 d, u8 e);
extern void func_393960(void *p, s32 a, s32 b);
extern void func_393AC0(void *p, s32 a, s32 b, s32 c, s32 d);

void insect_InsectCmdMenuLayout_4fab80(Obj *o, s32 mode, s32 f2, s32 f3)
{
    s32 i;
    s32 pos;
    s32 off;
    s32 dx;
    s32 dy;

    for (i = 0; i < 7; i++) {
        func_28F510(o->f878, 0x7561, 0, i);
    }
    func_393960(o->f5054, func_290460(o->f878, 0x7562), 6);
    func_392250(o->f5054, func_290460(o->f878, 0x7560),
                func_290460(o->f878, 0x7562), func_290460(o->f878, 0x7561),
                insect_InsectCmdMenuCount_4efc10(o->f502C), 1, -1, o->f5EF1);
    func_3934D0(o->f5054, func_290460(o->f878, 0x7563), 0x70, 0x20, 5,
                o->f5EF1);
    pos = 0x74;
    off = 0;
    if (f3 != 0) {
        pos = insect_InsectMsgTextWidth_512ab0(o->f506C, f3, 2) + 0x10;
        if (mode != 0) {
            if (o->f5EF1 == 1) {
                switch (mode) {
                case 2:
                    mode = 3;
                    break;
                case 3:
                    mode = 2;
                    break;
                }
            }
        }
        if (mode == 2) {
            off = pos - 0x74;
        }
        if (pos < 0x75) {
            off = 0;
            pos = 0x74;
        }
    }
    if (f2 != 0) {
        func_393AC0(o->f5054, func_290460(o->f878, 0x7564), pos, 0x24, mode);
    }
    dy = (o->f5DA4 / 2) - 0x32;
    switch (mode) {
    case 3:
        dx = 0x28;
        break;
    case 2:
        dx = (o->f5DA0 - pos) - 0x28;
        break;
    case 0:
        dx = (o->f5DA0 - 0x60) / 2;
        break;
    }
    func_290F60(o->f878, 0x7560, off, 0x24);
    func_290F60(o->f878, 0x7564, dx, dy);
    func_2907A0(o->f878, 0x755F, 0.0f);
    func_290690(o->f878, 0x755F, 1.0f, 0.125f, -1.0f);
    func_290690(o->f878, 0x7565, 1.0f, 0.125f, -1.0f);
}
