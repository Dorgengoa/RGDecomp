#include "types.h"
/* normal 0x004FFEE0 -- reload of the shop grid after the selection moved.
 * The 0x450 pair indexes the main-image 2D table D_0044B710; the 0x100-entry
 * scratch at gp-0xD18 is copied from the widget's +0x60 blob and every live
 * cell is stamped -0x80.  The trailing rows/cols come from a signed /8 with
 * the exact-multiple correction. */

typedef struct Glyph { u8 pad00[0x0E]; s16 f0E; u8 pad10[0x12 - 0x10]; s16 f12; } Glyph;
typedef struct Ref   { u8 pad00[0x60]; void *f60; } Ref;
typedef struct Ctx {
    u8  pad000[0x7A];
    s16 f07A;
    u8  pad07C[0x450 - 0x7C];
    s16 f450;
    s16 f452;
} Ctx;

extern s32   D_0044B710[][2];
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_004844A0;          /* gp - 0xCD0 */
extern Ctx  *D_00484454;          /* gp - 0xD1C */
extern s32  *D_00484458;          /* gp - 0xD18 */
extern f32   D_004844B4;          /* gp - 0xCBC */

extern void  *func_1FEDE0(void);
extern void   func_290AC0(void *w, u16 id, s32 s);
extern s32    func_28FE10(void *w, u16 id, s32 k);
extern void  *func_15DE40(void);
extern Ref   *func_159FB0(void *ctx, s32 name, s32 k);
extern void   func_1319A8(void *dst, const void *src, s32 n);
extern void   normal_BtlChgPageWeaponListBuild_504b50(Ctx *p, s32 a);
extern void   normal_BtlChgPageWeaponGridLayout_5047a0(Ctx *p, s32 id, s32 c, s32 d);
extern Glyph *func_28EA40(void *ctx, s32 id);
extern f32    normal_BtlChgMenuScrollBarLayout_5004b0(s32 a, s32 b, s32 c, s32 d, s32 e);

void normal_BtlChgMenuWeaponListRefresh_4ffee0(void)
{
    s16   *sel;
    Ref   *w;
    s32   *q;
    Glyph *g;
    s32    i;
    s32    n;
    s32    d;

    if (func_1FEDE0() == 0) {
        return;
    }
    sel = &D_00484454->f450;
    func_290AC0(D_0048449C, 0x26, D_0044B710[sel[0]][sel[1]]);
    func_290AC0(D_0048449C, 0x55, D_0044B710[sel[0]][sel[1]]);
    func_28FE10(D_0048449C, 0x26, 0);
    w = func_159FB0(func_15DE40(), D_0044B710[sel[0]][sel[1]], 0x32C);
    if (w != 0) {
        func_1319A8(D_00484458, w->f60, 0x400);
        q = D_00484458;
        for (i = 0; i < 0x100; i++) {
            if (q[0] != 0) {
                q[0] = -0x80;
            }
            q++;
        }
    }
    normal_BtlChgPageWeaponListBuild_504b50(D_00484454, sel[1]);
    normal_BtlChgPageWeaponGridLayout_5047a0(D_00484454, 0x26, D_00484454->f07A, 0);
    n = D_00484454->f07A;
    if (n < 0) {
        n = 0;
    }
    g = func_28EA40(D_004844A0, 0x55F4);
    d = n / 8;
    g->f12 = d;
    if (n % 8 == 0) {
        if (d != 0) {
            g->f12 = g->f12 - 1;
        }
    }
    D_004844B4 = normal_BtlChgMenuScrollBarLayout_5004b0(0x25, 0x5A, g->f0E + 1, g->f12 + 1, 0);
}
