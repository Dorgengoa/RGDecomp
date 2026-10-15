#include "types.h"

typedef struct Ent {
    s16   f00;
    s32   f04;
    s32   f08;
    s32   f0C;
    s32   f10;
    void *f14;
    s8    f18;
    u8    pad19[7];
    f32   f20;
    f32   f24;
    f32   f28;
    s32   f2C;
} Ent;

typedef struct Wk {
    u8  pad00[0x12];
    s16 f12;
    u8  pad14[2];
    s16 f16;
} Wk;

typedef struct Pl {
    u8    pad000[0x510];
    void *f510;
    void *f514;
} Pl;

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

extern f32   D_0047D9DC;   /* gp - 0x7794 */
extern void *D_00484710;   /* gp - 0xA60  */
extern void *D_00484848;   /* gp - 0x928  */
extern Ent  *D_00484870;   /* gp - 0x900  */

extern void *func_134950(void *p, void *q);
extern void *func_1DFEF0(void *p);
extern void *func_1E4910(void *p, void *q, s32 n);
extern void *func_1E49B0(void *p, void *q, s32 *out);
extern void  func_1E7740(void *p, Vec *v);
extern void *func_1E7BF0(s32 n);
extern void  func_1FEDE0(void);
extern Pl   *func_201A70(void);
extern void *func_201A90(void);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);
extern void  func_321EA0(Pl *p, void *q);
extern void *func_324A40(void *p);
extern void  func_324A70(void *p, void *q, f32 *v);
extern void  func_324BB0(void *p, Vec *v);
extern void  func_329EF0(void *p, f32 t);
extern void *func_32A8F0(void *p);

void normal_TransWarpMinimapFocus_51a7a0(Wk *a)
{
    s32   n;
    Vec   v;
    Pl   *pl;
    void *p2;
    void *r;
    void *h;
    void *o;
    s32   i;

    if (a != 0) {
        func_1FEDE0();
        i = a->f12 + a->f16;
        if (D_00484870[i].f00 == 3) {
            pl = func_201A70();
            if (pl != 0) {
                h = D_00484870[i].f14;
                p2 = func_201A90();
                if (p2 != 0) {
                    n = 0;
                    r = func_1E49B0(p2, h, &n);
                    if (n != 0) {
                        func_321EA0(pl, func_1E7BF0(n));
                        h = pl->f514;
                        if (h == 0) {
                            h = pl->f510;
                        }
                        if (r != 0) {
                            func_324A70(h, func_1DFEF0(r), &D_00484870[i].f20);
                            func_1E7740(func_1E4910(p2, func_324A40(h), 0), &v);
                            func_324BB0(h, &v);
                            if (D_00484848 != 0) {
                                o = func_32A8F0(h);
                                if (o != 0) {
                                    if (func_134950(D_00484848, (void *)((u8 *)o + 0x54)) != 0) {
                                        func_290690(D_00484710, 0x75D1, 0.0f, D_0047D9DC, -1.0f);
                                    } else {
                                        func_290690(D_00484710, 0x75D1, 1.0f, D_0047D9DC, -1.0f);
                                        func_291110(D_00484710, 0x75D1, 1, 1);
                                    }
                                }
                            }
                        }
                        if (h == pl->f510) {
                            func_329EF0(h, 15.0f);
                        }
                    }
                }
            }
        }
    }
}
