#include "types.h"
/* normal 0x0051D030 */

extern u8 D_004DB150[];

extern void func_26F620(u8 *p, s32 a, s32 b, s32 c, s32 d);
extern void func_26F600(void);
extern void func_13F730(void *p, s32 a);
extern void func_13EC80(void *p, s32 a, u64 v);
extern void func_13F5B0(void *p);
extern s32  func_15DE80(void);
extern s32  func_1451E0(s32 t);
extern s32  func_1451D0(s32 t);

s32 normal_TransWarpListClipDrawCb_51d030(void *p, s32 b, s32 c, s32 d, s32 e)
{
    u8 *q;
    s32 t;
    s32 h;
    s32 w;

    q = D_004DB150;
    if (e != 0) {
        if (q != 0) {
            func_26F620(q, 0, 0x200, 0x127, 0x1AC);
        }
        if (p != 0) {
            func_13F730(p, 6);
            func_13EC80(p, 0x40, ((u64)0x1AC0127 << 32) | 0x2000000);
            func_13F5B0(p);
        }
    } else {
        if (q != 0) {
            func_26F600();
        }
        t = func_15DE80();
        h = func_1451E0(t);
        w = func_1451D0(t);
        if (p != 0) {
            func_13F730(p, 6);
            func_13EC80(p, 0x40, ((u64)(h - 1) << 16) | ((u64)(w - 1) << 48));
            func_13F5B0(p);
        }
    }
    return 1;
}
