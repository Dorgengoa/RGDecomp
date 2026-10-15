#include "types.h"
/* normal 0x004FC1E0 -- lays out the item-count widget: positions widget 0x50
 * from the 0x55FA record's own geometry, then wires two icons and shows 0x49.
 * $4 is unused; the guard is on the SECOND parameter.  0x40C00000 is 6.0f. */

typedef struct Rec {
    u8  pad000[4];
    s16 f004;
    s16 f006;
    u8  pad008[2];
    s16 f00A;
    u8  pad00C[0x14 - 0xC];
    s16 f014;
    s16 f016;
    u8  pad018[2];
    s16 f01A;
} Rec;

extern void *D_004844A0;          /* gp - 0xCD0 */
extern void *D_00484454;          /* gp - 0xD1C */
extern f32   D_004844B8;          /* gp - 0xCB8 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_00481BBC;          /* gp - 0x35B4 */
extern void *D_00484498;          /* gp - 0xCD8 */
extern const u8 D_005278E0[];

extern Rec  *func_28EA40(void *a, s32 id);
extern void  normal_BtlChgPageWeaponConfirmLayout_504030(void *a, s16 n);
extern void  func_28EA90(void *a, s32 id, s32 c);
extern f32   func_128FD0(f32 x);
extern void  func_290F60(void *a, s32 id, s32 c, s32 d);
extern void  func_28F930(void *a, s32 id, s32 c, s32 d);
extern const void *func_28AA30(void *a, s32 id);
extern void  func_28F510(void *a, s32 id, const void *c, s32 d);
extern void  func_291110(void *a, s32 id, s32 c, s32 d);
extern void  func_28D820(const void *a, s32 b);
extern void  func_28EDE0(void *a, s32 id, s32 c);

s32 normal_BtlChgMenuWeaponConfirmOpenState_4fc1e0(void *unused, s32 show)
{
    Rec *r;
    Rec *q;
    f32  t;

    if (show != 0) {
        r = func_28EA40(D_004844A0, 0x55F4);
        normal_BtlChgPageWeaponConfirmLayout_504030(D_00484454,
                            (s16)(r->f014 + r->f016 * 8 + r->f01A * 8));
        func_28EA90(D_004844A0, 0x55FA, 0);
        q = func_28EA40(D_004844A0, 0x55FA);
        q->f014 = 0;
        /* The PRODUCT must be its own statement or mwcc contracts the whole
         * expression into adda.s/madd.s; retail keeps mul.s and add.s.
         * Splitting the sum or the (f32) conversion instead does NOT work --
         * measured, twelve spellings. */
        t = 6.0f * func_128FD0(D_004844B8);
        func_290F60(D_0048449C, 0x50,
                    (s32)(t + (f32)(q->f004 + 0x52 + q->f014 * 0x50)),
                    q->f006 + 0x88 + q->f016 * q->f00A);
        func_28F930(D_0048449C, 0x4A, 0x4C, 0);
        func_28F930(D_0048449C, 0x4A, 0x18, 1);
        func_28F510(D_0048449C, 0x4B, func_28AA30(D_00481BBC, 0x52), 3);
        func_28F510(D_0048449C, 0x4B, func_28AA30(D_00481BBC, 0x53), 4);
        func_291110(D_0048449C, 0x49, 1, 1);
        func_290F60(D_0048449C, 0x49, 0x60, 0x82);
    }
    func_28D820(D_005278E0, 0x28);
    func_28EDE0(D_00484498, 0x5610, 0);
    return 1;
}
