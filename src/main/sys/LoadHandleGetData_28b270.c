#include "types.h"

extern s32   LoadHandleIsReady_28b200(void *a);
extern void *GetLoaderMgr_1f59d0(void);
extern s32   LoaderGetData_1cd490(void *h, s32 v, s32 *out);

s32 LoadHandleGetData_28b270(s32 *a, s32 *out)
{
    void *h;

    if (out != 0) {
        *out = 0;
    }
    if (LoadHandleIsReady_28b200(a) == 0) {
        return 0;
    }
    h = GetLoaderMgr_1f59d0();
    if (h == 0) {
        return 0;
    }
    return LoaderGetData_1cd490(h, *a, out);
}
