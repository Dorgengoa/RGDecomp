/* rgp:protos */
#define RGP_SELF_title_TitleSaveIconDataSet_4ede80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EDE80 -- guarded call, %hi/%lo address of an
 * overlay-local object as the first argument (hence `const`).
 */

extern u8 title_D_004F1900;
extern void memcpy(void *dst, void *src, s32 n);

void title_TitleSaveIconDataSet_4ede80(void *p)
{
    if (p != 0) {
        memcpy((void *)&title_D_004F1900, p, 0x78);
    }
}
