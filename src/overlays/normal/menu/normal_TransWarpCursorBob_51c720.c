#include "types.h"
/* normal 0x0051C720 -- places the two 0x75DD/0x75DE panels.  Parameter two
 * ($5) leaves NO trace; its presence is inferred from the register map
 * ($4->$20, $6->$19, $7->$18, $8->$21), i.e. five EABI integer slots.
 * Both float products are NAMED locals -- that is what keeps retail's separate
 * `mul.s`/`add.s` pair and the plain `cvt.w.s` truncation.
 * `bgez / sra ..,1` around `addiu $2,$rX,1` is a signed divide by 2. */

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8  pad08[0x8];
    s16 f10;
    s16 f12;
} Box;

extern f32   D_0047D3B8;          /* gp - 0x7DB8 */
extern f32   D_0047D3F8;          /* gp - 0x7D78 */
extern f32   D_0048487C;          /* gp - 0x8F4  */
extern f32   D_00484880;          /* gp - 0x8F0  */
extern void *D_00484710;          /* gp - 0xA60  */

extern void *func_15DE80(void);
extern s32   func_1451E0(void *h);
extern s32   func_1451D0(void *h);
extern void  func_28B630(f32 *p, f32 v);
extern f32   func_128FD0(f32 v);
extern void  func_290F60(void *p, u16 id, s32 x, s32 y);
extern void  func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);

s32 normal_TransWarpCursorBob_51c720(Box *p, s32 unused, s32 cx, s32 cy, s32 mode)
{
    void *h;
    s32   w;
    s32   ht;
    f32   t;
    f32   m;
    s32   x;
    s32   y;

    h = func_15DE80();
    w = func_1451E0(h);
    ht = func_1451D0(h);
    func_28B630(&D_0048487C, D_0047D3B8);
    t = func_128FD0(D_0048487C);
    m = 8.0f * t;
    x = (s32)((f32)cx + (m + (f32)(p->f00 + p->f10 * p->f04)));
    y = cy + (p->f02 + p->f12 * p->f06);
    func_28B630(&D_00484880, D_0047D3F8);
    t = func_128FD0(D_00484880);
    m = 6.0f * t;
    w = (s32)((f32)(w / 2 + 8) + m);
    ht = (s32)((f32)(ht / 2 + 7) + m);
    if (mode != 0) {
        func_290F60(D_00484710, 0x75DD, x, y);
        func_290F60(D_00484710, 0x75DE, w, ht);
    } else {
        func_290F50(D_00484710, 0x75DD, x, y, 0, 0.25f);
        func_290F50(D_00484710, 0x75DE, w, ht, 0, 0.25f);
    }
    return 1;
}
