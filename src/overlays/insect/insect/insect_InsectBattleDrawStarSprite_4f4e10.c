#include "types.h"
/* insect 0x004F4E10 -- 456 bytes, 114 instructions.
 * Draws the 0x100-wide box centred on the point func_15D160 resolves. */

typedef struct Obj {
    u8  pad00[0xD4];
    s32 fD4;                        /* +0xD4 */
} Obj;

typedef struct Vec {
    s32 x;
    s32 y;
    s32 z;
} Vec;

extern void func_13EC00(void *b, s32 k);
extern void func_13ED60(void *b, s32 k, s32 m);
extern void func_13EE40(void *b, s32 r, s32 g, s32 bl, s32 al);
extern void func_13EF10(void *b, s32 x, s32 y, s32 z);
extern void func_13F5B0(void *b);
extern void func_13F730(void *b, s32 k);
extern s32 func_15D160(Vec *v, s32 c);
extern s32 func_15D4A0(f32 *p);

void insect_InsectBattleDrawStarSprite_4f4e10(Obj *a, void *b, s32 c)
{
    Vec v;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 z;

    if (func_15D160(&v, c) != 0) {
        func_13F730(b, 6);
        func_13EC00(b, a->fD4);
        z = v.z;
        x0 = v.x - 0x80;
        x1 = v.x + 0x80;
        y0 = v.y - 0x80;
        y1 = v.y + 0x80;
        {
            f32 p[4] = {0};
            p[0] = (f32)x0;
            p[2] = (f32)v.z;
            p[1] = (f32)y0;
            {
                f32 q[4] = {0};
                q[0] = (f32)x1;
                q[2] = (f32)v.z;
                q[1] = (f32)y1;
                if (func_15D4A0(p) == 0 || func_15D4A0(q) == 0) {
                    return;
                }
                                func_13EE40(b, 0x80, 0x80, 0x80, 0x80);
                                func_13ED60(b, 0x41, 1);
                                func_13EF10(b, x0, y0, z);
                                func_13ED60(b, 0x7F, 0x3E);
                                func_13EF10(b, x1, y1, z);
                                func_13F5B0(b);
            }
        }
    }
}
