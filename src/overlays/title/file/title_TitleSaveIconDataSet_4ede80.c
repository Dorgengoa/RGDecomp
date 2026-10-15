#include "types.h"

/* title.bin overlay, 0x004EDE80 -- guarded call, %hi/%lo address of an
 * overlay-local object as the first argument (hence `const`).
 */

extern const u8 D_004F1900;
extern void func_1319A8(void *dst, void *src, s32 n);

void title_TitleSaveIconDataSet_4ede80(void *p)
{
    if (p != 0) {
        func_1319A8((void *)&D_004F1900, p, 0x78);
    }
}
