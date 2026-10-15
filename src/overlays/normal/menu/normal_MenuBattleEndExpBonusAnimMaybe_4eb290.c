#include "types.h"
/* normal 0x004EB290 -- widget 0x11's two phases: phase 1 ramps 0xA0 toward
 * 0x9C and pushes the integer via func_290F60; phase 2 reads the current
 * scale back with func_2904B0 and drives the two transform setters. */

typedef struct Eb2Obj {
    u8  pad000[0x14];
    u8  f014[0x9C - 0x14];
    f32 f09C;
    f32 f0A0;
    f32 f0A4;
    s16 f0A8;
} Eb2Obj;

extern void  func_290F60(void *w, u16 id, s32 a, s32 b);
extern f32  *func_2904B0(void *w, u16 id);
extern void  func_2904E0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern void  func_2905B0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d);

void normal_MenuBattleEndExpBonusAnimMaybe_4eb290(Eb2Obj *p)
{
    f32 v;

    if (p->f0A8 == 1) {
        if (p->f0A0 == p->f09C) {
            return;
        }
        p->f0A0 = p->f0A0 + p->f0A4;
        p->f0A4 = p->f0A4 + 1.2f;
        if (p->f0A0 >= p->f09C) {
            p->f0A0 = p->f09C;
            p->f0A4 = 0.0f;
            p->f0A8 = 2;
        }
        func_290F60(p->f014, 0x11, 0, (s32)p->f0A0);
    } else if (p->f0A8 == 2) {
        v = *func_2904B0(p->f014, 0x11);
        if (v <= 1.0f) {
            func_2905B0(p->f014, 0x11, 1.0f, 1.0f, 1.0f, -1.0f);
            func_2904E0(p->f014, 0x11, 1.7f, 1.7f, 1.7f, -1.0f, 0.075f);
        } else if (v >= 1.7f) {
            func_2905B0(p->f014, 0x11, 1.7f, 1.7f, 1.7f, -1.0f);
            func_2904E0(p->f014, 0x11, 1.0f, 1.0f, 1.0f, -1.0f, -0.045f);
        }
    }
}
