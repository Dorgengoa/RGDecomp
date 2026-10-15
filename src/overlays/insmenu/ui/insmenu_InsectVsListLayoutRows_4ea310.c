#include "types.h"

/* insmenu 0x004EA310 (256 bytes) -- lay the item rows out down the panel, then
 * size and select the list.
 *
 * ★ `dsll32 $16, $7, 16 / dsra32 $16, $16, 16` on an incoming parameter is an
 * s32 argument with an explicit `(s16)` cast; a plain s16 parameter emits
 * nothing at all.
 * ★ The `mult` in the latch's likely delay slot is the body's first
 * computation, so `pitch * i` is written inline in the call's argument. */

extern const u8 D_004FA180[];

extern void func_28FD10(const void *a, s32 id, s32 c, s32 y, s32 row);
extern void func_28F8F0(const void *a, s32 id, s32 c, s32 row);
extern void func_28F670(const void *a, s32 id, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void func_28FCD0(const void *a, s32 id, s32 c, s32 n);

void insmenu_InsectVsListLayoutRows_4ea310(s32 id, s32 n, s32 lit, s32 pitch)
{
    s32 i;
    s16 step;

    step = (s16)pitch;
    for (i = 0; i < n; i++) {
        func_28FD10(D_004FA180, id, 0xA, step * i + 9, i);
        if (i < lit) {
            func_28F8F0(D_004FA180, id, 0x58, i);
        } else {
            func_28F8F0(D_004FA180, id, 0x6C, i);
        }
    }
    func_28F670(D_004FA180, id, 0x14, 0x14, 0x14, 0x14, 0);
    func_28FCD0(D_004FA180, id, -1, n);
}
