#include "types.h"
/* normal 0x004FD760 -- re-open the 0x55F3 record's frame.  The negative row
 * offset is `n * -50` (mwcc builds it out of shifts), the 0x25 slot uses the
 * CONTRACTED adda.s/madd.s form so the product must NOT be named here, and
 * only the SECOND out-parameter pair of func_2910A0 is written. */

typedef struct Rec {
    u8  pad00[8];
    s16 f08;
    s16 f0A;
    u8  pad0C[0x14 - 0xC];
    s16 f14;
    s16 f16;
    u8  pad18[2];
    s16 f1A;
} Rec;

typedef struct Node { u8 pad00[0x20]; s16 f20; } Node;
typedef struct Widget { u8 pad00[0x20]; Node *f20; } Widget;

extern void    *D_0048449C;       /* gp - 0xCD4  */
extern void    *D_004844A0;       /* gp - 0xCD0  */
extern void    *D_00484498;       /* gp - 0xCD8  */
extern s16      D_004844A8;       /* gp - 0xCC8  */
extern s16      D_004844AA;       /* gp - 0xCC6  */
extern s16      D_004844AC;       /* gp - 0xCC4  */
extern f32      D_004844B0;       /* gp - 0xCC0  */
extern s32      D_00480500;       /* gp - 0x4C70 */
extern s32      D_00480504;       /* gp - 0x4C6C */
extern s32      D_00480508;       /* gp - 0x4C68 */
extern const u8 D_005278E0[];

extern void    func_291110(void *p, s32 id, s32 c, s32 d);
extern Widget *func_290460(void *p, s32 id);
extern Rec    *func_28EA40(void *p, s32 id);
extern void    func_2910A0(void *p, s32 id, s32 *outX, s32 *outY);
extern void    func_290F60(void *p, s32 id, s32 c, s32 d);
extern void    func_28DB40(const void *p, s32 a, s32 b, s32 c, s32 d, s32 e,
                           s32 f, s32 g);
extern void    func_28EDE0(void *p, s32 id, s32 a);

s32 normal_BtlChgMenuItemTargetCancelState_4fd760(void *unused, s32 show)
{
    Widget *w;
    Rec    *r;
    s32     n;
    s32     x;
    s32     y;

    if (show != 0) {
        func_291110(D_0048449C, 0x2A, 0, 1);
        func_291110(D_0048449C, 0x43, 0, 1);
    }
    w = func_290460(D_0048449C, 0x2A);
    if (w != NULL) {
        if (w->f20 != NULL) {
            w->f20->f20 = -1;
        }
    }
    r = func_28EA40(D_004844A0, 0x55F3);
    r->f14 = D_004844A8;
    r->f16 = D_004844AA;
    n = D_004844AC;
    r->f1A = n;
    if (n < 0) {
        n = 0;
    }
    func_2910A0(D_0048449C, 0x26, &x, &y);
    n = n * -50;
    func_290F60(D_0048449C, 0x26, 0x1A, n + 0x1D);
    func_290F60(D_0048449C, 0x27, 0x3C, n + 0x37);
    func_290F60(D_0048449C, 0x23, 0, 0);
    func_290F60(D_0048449C, 0x25, 0x183,
                (s32)(30.0f + (f32)r->f1A * D_004844B0));
    func_28DB40(D_005278E0, 0x28, r->f14 * r->f08 + 0x19,
                r->f16 * r->f0A + 0x17, 0x2A, 0x30, 0x2B, 0xD1);
    D_00480500 = r->f14;
    D_00480504 = r->f16;
    D_00480508 = r->f1A;
    func_28EDE0(D_00484498, 0x55FA, 0);
    return 1;
}
