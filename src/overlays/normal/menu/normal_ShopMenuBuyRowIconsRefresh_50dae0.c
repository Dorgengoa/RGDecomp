#include "types.h"

typedef struct DAE0M {
    u8   pad00[0x10];
    s16 *f10;
} DAE0M;

typedef struct DAE0P {
    DAE0M *f00;
} DAE0P;

extern DAE0P *D_00527D30[];
extern s16    D_00526520[][2];

extern void *D_004845C8;          /* gp - 0xBA8 */

extern void *func_1FEDE0(void);
extern void  func_28FCD0(void *w, u16 id, s32 a, s32 b);
extern s32   func_3E97C0(void *ctx, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern s32   func_3CE690(DAE0P *p);
extern void  func_28F970(void *w, u16 id, s32 a, s32 b, s32 c);
extern s32   func_3CE8E0(DAE0P *p);

s32 normal_ShopMenuBuyRowIconsRefresh_50dae0(s32 a, s32 b)
{
    DAE0P **tbl;
    void   *ctx;
    DAE0M  *o;
    s32     i;
    DAE0P  *p;
    s32     r;

    ctx = func_1FEDE0();
    tbl = &D_00527D30[a];
    for (i = 0; i < 8; i++) {
        p = tbl[i];
        if (p == NULL) {
            return 0;
        }
        o = p->f00;
        if (o == NULL) {
            return 0;
        }
        func_28FCD0(D_004845C8, 0x22, 0x25, i);
        if (func_3E97C0(ctx, o->f10[0], -1, 0, 1, 1, 0) > 0) {
            if (b != 0) {
                if (func_3CE690(p) == 0) {
                    func_28F970(D_004845C8, 0x22, 0xA6, 0x42, i);
                    continue;
                }
            }
        }
        r = func_3CE8E0(p);
        func_28F970(D_004845C8, 0x22, D_00526520[r][0], D_00526520[r][1], i);
    }
    return 1;
}
