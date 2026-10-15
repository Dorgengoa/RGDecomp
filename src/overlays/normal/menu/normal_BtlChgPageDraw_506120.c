#include "types.h"
/* normal 0x00506120 -- fetch-then-use guard, twin of 0x00506160. */
extern void *normal_UiPageGetLayout_289b60(void);
extern void  func_291910(void *w);

s32 normal_BtlChgPageDraw_506120(void)
{
    void *w = normal_UiPageGetLayout_289b60();
    if (w == 0) {
        return 0;
    }
    func_291910(w);
    return 1;
}
