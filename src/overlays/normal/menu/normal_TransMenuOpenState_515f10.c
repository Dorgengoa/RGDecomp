#include "types.h"
/* normal 0x00515F10 -- the 0x7534 widget-group open/refresh entry.  224
 * instructions, frame -0x60.
 *
 * Signature: the caller normal_TransMenuQuickOpenState_515da0 passes its OWN $a0 straight through
 * and sets $a1 = 1, and the body never reads $a0, so this is a two-parameter
 * function with a pass-through first parameter.
 *
 * gp data: _gp = 0x00485170.  -0xA88 = D_004846E8 (the widget world),
 * -0xA60 = D_00484710, -0xA70 = D_00484700, -0xA40 = D_00484730,
 * -0xA20 = D_00484750, -0x9F4 = D_0048477C.
 * gp floats: -0x7850 = D_0047D920, -0x7BA0 = D_0047D5D0, -0x7748 = D_0047DA28,
 * -0x7EE8 = D_0047D288. */

typedef struct Wid { u8 pad00[8]; s16 f08; s16 f0A; s16 f0C; s16 f0E; } Wid;
typedef struct Sub { u8 pad000[0x1A4]; u8 f1A4; } Sub;
typedef struct Sys { u8 pad00[8]; void *f08; u8 pad0C[0xC]; Sub *f18; } Sys;
typedef struct Blk { void *f00; u8 pad04[0xC]; } Blk;
typedef struct It  { u8 pad00[8]; } It;

extern void *D_004846E8;            /* _gp - 0xA88 */
extern void *D_00484710;            /* _gp - 0xA60 */
extern u8    D_00484700[8];         /* _gp - 0xA70 */
extern u8    D_00484730;            /* _gp - 0xA40 */
extern s16   D_00484750;            /* _gp - 0xA20 */
extern u8    D_0048477C;            /* _gp - 0x9F4 */
extern f32   D_0047D920;            /* _gp - 0x7850 */
extern f32   D_0047D5D0;            /* _gp - 0x7BA0 */
extern f32   D_0047DA28;            /* _gp - 0x7748 */
extern f32   D_0047D288;            /* _gp - 0x7EE8 */
extern u8    D_00477600[];

extern void  func_291110(void *w, u16 id, s32 a, s32 b);
extern void  func_290F60(void *w, u16 id, s32 a, s32 b);
extern void  func_2905B0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d);
extern void  func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 t);
extern void  func_290690(void *w, u16 id, f32 a, f32 b, f32 c);
extern void  func_2910A0(void *w, u16 id, s32 *a, s32 *b);
extern Wid  *func_28FE10(void *w, u16 id, s32 c);
extern Sys  *func_1FEDE0(void);
extern s32   func_1FEDF0(void);
extern void  func_3F0960(s32 a, s32 b);
extern s32   func_3EEF10(void *p);
extern void  func_3FCF00(Blk *q, Sys *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void  func_370170(It *it, Blk *q);
extern s32   func_370040(It *it);
extern void  func_28EDE0(void *p, s32 a, s32 b);
extern s32   normal_TransMenuCanWarp_5185a0(void);
extern s32   normal_TransMenuIsHunterUnlocked_5185e0(void);

s32 normal_TransMenuOpenState_515f10(s32 a0, s32 go)
{
    s32  x;
    s32  y;
    It   it;
    Blk  blk;
    Sys *sys;
    Wid *p;
    s32  i;
    s32  k;
    s32  t;
    s32  t2;
    u16  id;

    if (go != 0) {
        func_291110(D_004846E8, 0x7534, 1, 1);
        func_290F60(D_004846E8, 0x7535, 5, 5);
        func_2905B0(D_004846E8, 0x7535, 0.0f, 0.0f, 0.0f, D_0047D920);
        func_290F60(D_004846E8, 0x7534, -0x30, -0xF);
        func_290F50(D_004846E8, 0x7534, 0, 0, 0, D_0047D5D0);
        func_290690(D_004846E8, 0x7534, 1.0f, D_0047DA28, 0.0f);
        func_290F60(D_004846E8, 0x7553, -0x32, 0);
        for (i = 0; i < 4; i++) {
            t = i * 0x26 + 0x4F;
            func_290F60(D_004846E8, i + 0x753B, -0x4A, t);
            id = i + 0x7536;
            func_290F60(D_004846E8, id, -0x47, t + 3);
            func_2905B0(D_004846E8, id, 0.0f, 0.0f, 0.0f, D_0047D920);
        }
        for (i = 0; i < 4; i++) {
            t2 = i * 32 + 0x12;
            p = func_28FE10(D_004846E8, i + 0x754F, 0);
            if (p != 0) {
                p->f0A = t2;
                p->f08 = 0xE0;
                if (i == 1) {
                    if (normal_TransMenuCanWarp_5185a0() != 0) {
                        func_2905B0(D_00484710, 0x7540, 1.0f, 1.0f, 1.0f, 1.0f);
                        p->f0A = 0x32;
                        p->f0C = p->f0E = 0x1F;
                    } else {
                        func_2905B0(D_00484710, 0x7540, D_0047D288, D_0047D288,
                                    D_0047D288, 1.0f);
                        p->f08 = 0x90;
                        p->f0A = 0x26;
                        p->f0C = p->f0E = 0x20;
                    }
                } else if (i == 2) {
                    if (normal_TransMenuIsHunterUnlocked_5185e0() != 0) {
                        p->f0A = 0x52;
                        p->f0C = p->f0E = 0x1F;
                    } else {
                        p->f08 = 0x90;
                        p->f0A = 0x26;
                        p->f0C = p->f0E = 0x20;
                    }
                }
            }
        }
        k = func_1FEDE0()->f18->f1A4 & 1;
        D_0048477C = 0;
        D_00484730 = (u8)(k != 0);
        func_3F0960(func_1FEDF0(), 2);
    }

    func_2910A0(D_004846E8, 0x7534, &x, &y);
    sys = func_1FEDE0();
    if (x == 0 && y == 0 && D_00484750 != 0 && func_3EEF10(sys->f08) != 0) {
        blk.f00 = D_00477600;
        func_3FCF00(&blk, sys, 1, 1, 0, 0, 1, 0);
        func_370170(&it, &blk);
        k = 0;
        while (func_370040(&it) != 0) {
            k++;
        }
        if (k > 0) {
            D_0048477C = 1;
        }
        func_28EDE0(D_00484700, 3, 1);
    }
    return 1;
}
