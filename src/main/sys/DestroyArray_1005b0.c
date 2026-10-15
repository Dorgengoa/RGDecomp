#include "types.h"

/* MW C++ runtime __destroy_arr (NMWException.cp): destroy n objects of `size`
 * bytes at `block`, last to first, via dtor(obj, -1).
 * Built with `-O4,p` (optimize for speed; config/toolchain.txt row): the runtime
 * library TU was compiled for speed, which leaves the extra `nop` after the loop. */
void DestroyArray_1005b0(char *block, void (*dtor)(void *, s32), u32 size, u32 n)
{
    char *p;

    for (p = block + size * n; n > 0; n--) {
        p -= size;
        dtor(p, -1);
    }
}
