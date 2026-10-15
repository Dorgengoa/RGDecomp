#pragma divbyzerocheck on
#include "types.h"
/* normal 0x0051A9D0 -- the shop price/quantity caption: formats a two-field
 * number into a 0x20-byte stack buffer, hands it to the 0x75D8 widget and
 * turns the widget on.  `v == -1` is the "no item" case: the widget is turned
 * OFF and the function returns 0.
 *
 * Three `div`s, two `break 0,7` pairs: retail was built with
 * `#pragma divbyzerocheck on`, and the pair is emitted for `/` but NOT for
 * `%` -- the `div/mfhi` at 0x0051AA28 has no check because it is the modulo
 * of the SAME divisor mwcc has already proved non-zero at 0x0051AA14. */

extern void *D_00484710;          /* gp - 0xA60 */
extern const char D_00526830[];

extern void func_1343B8(void *dst, const char *fmt, ...);
extern void func_290AC0(void *w, u16 id, const void *s);
extern void func_291110(void *w, u16 id, s32 a, s32 b);

extern s32 normal_TransWarpPreviewTexSet_51a9d0(s32 v);

s32 normal_TransWarpPreviewTexSet_51a9d0(s32 v)
{
    char buf[0x20];

    if (v == -1) {
        func_291110(D_00484710, 0x75D8, 0, 1);
        return 0;
    }
    func_1343B8(buf, D_00526830, v / 100, (v / 10) % 10);
    func_290AC0(D_00484710, 0x75D8, buf);
    func_291110(D_00484710, 0x75D8, 1, 1);
    return 1;
}
