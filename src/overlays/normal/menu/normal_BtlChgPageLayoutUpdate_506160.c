#include "types.h"
/* normal 0x00506160 -- fetch-then-use guard, twin of 0x00506120. */
extern void *normal_UiPageGetLayout_289b60(void);
extern void  func_2913A0(void *w);

s32 normal_BtlChgPageLayoutUpdate_506160(void)
{
    void *w = normal_UiPageGetLayout_289b60();
    if (w == 0) {
        return 0;
    }
    func_2913A0(w);
    return 1;
}
