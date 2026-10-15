#include "types.h"

/* insmenu 0x004EA110 (156 bytes) -- tint rows 0..n-1 of a widget, the rows past
 * `m` one shade lighter than the rest.
 *
 * ★ The loop compare lands in $at (`slt $1, $17, $16`), which the recorded
 * compare-class rule attributes to the relational operator TOKEN rather than to
 * register pressure. */

extern const u8 D_004FA180[];

extern void func_290A40(const void *a, s32 id, u32 rgba, s32 row);

void insmenu_InsectVsListSetRowColors_4ea110(s32 id, s32 n, s32 m)
{
    s32 i;

    for (i = 0; i < n; i++) {
        if (i <= m) {
            func_290A40(D_004FA180, id, 0xFF303030, i);
        } else {
            func_290A40(D_004FA180, id, 0xFF202020, i);
        }
    }
}
