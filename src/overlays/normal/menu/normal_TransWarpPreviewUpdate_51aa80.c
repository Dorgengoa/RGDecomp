#pragma divbyzerocheck on
#include "types.h"
/* normal 0x0051AA80 -- the shop slot's per-frame refresh.  D_00484870 is the
 * 0xC00 shop work buffer (allocated in normal_TransWarpListAlloc_51a9a0) read as an array
 * of 0x30-byte slots; `i*0x30` is strength-reduced once into $16 and reused,
 * while the gp POINTER is reloaded at every use because the calls clobber it.
 *
 * `%` emits a bare `div`, `/` emits the `bnez`/`break 0,7` pair -- the two
 * modulos by 0x64 and 0xA are unchecked, the `/ 3` at 0x0051AB10 is checked. */

typedef struct Slot {
    s16   f00;
    u8    pad02[0x10 - 0x02];
    s32   f10;
    u8    pad14[0x20 - 0x14];
    s32   f20;
    u8    pad24[0x30 - 0x24];
} Slot;                                     /* 0x30 */

typedef struct W   { s16 f00; u8 pad02[0x08 - 0x02]; s16 f08; s16 f0A; } W;
typedef struct Vw  { u8 pad00[0x30]; s16 f30; } Vw;
typedef struct Root{ u8 pad00[0x18]; Vw *f18; } Root;
typedef struct Cam { u8 pad000[0x510]; void *f510; void *f514; } Cam;

extern Slot *D_00484870;          /* gp - 0x900 */
extern void *D_00484710;          /* gp - 0xA60 */

extern s32   normal_TransWarpPreviewTexSet_51a9d0(s32 v);
extern W    *func_28FE10(void *w, u16 id, s32 n);
extern Root *func_1FEDE0(void);
extern void *func_201A90(void);
extern void  func_1E49B0(void *a, s16 b, s32 *c);
extern void *func_1DCB50(s32 a);
extern Cam  *func_201A70(void);
extern void  func_324530(void *a, void *b, s32 c, s32 d);

extern s32 normal_TransWarpPreviewUpdate_51aa80(s32 i);

s32 normal_TransWarpPreviewUpdate_51aa80(s32 i)
{
    Root *r;
    Cam  *c;
    W    *w;
    void *p;
    void *a;
    void *b;
    s32   v;
    s32   h;

    normal_TransWarpPreviewTexSet_51a9d0(D_00484870[i].f10);
    w = func_28FE10(D_00484710, 0x75D8, 0);
    if (w == 0) {
        return 0;
    }
    w->f00 = 5;
    v = D_00484870[i].f10 % 100;
    if (v >= 10) {
        v = v % 10;
    }
    w->f08 = (v % 3) * 84;
    w->f0A = (v / 3) * 74;
    if (D_00484870[i].f00 == 3) {
        r = func_1FEDE0();
        p = func_201A90();
        if (p != 0) {
            h = 0;
            func_1E49B0(p, r->f18->f30, &h);
            if (h != 0) {
                a = func_1DCB50(h);
                b = 0;
                c = func_201A70();
                if (c != 0) {
                    a = c->f510;
                    b = c->f514;
                }
                if (a != 0) {
                    func_324530(a, &D_00484870[i].f20, 0xF, 0);
                }
                if (b != 0) {
                    func_324530(b, &D_00484870[i].f20, 0xF, 0);
                }
            }
        }
    }
    return 1;
}
