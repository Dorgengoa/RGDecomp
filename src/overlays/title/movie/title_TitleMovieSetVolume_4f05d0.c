#include "types.h"

/* title.bin overlay, 0x004F05D0 -- guarded call, always returns 0.
 *
 * `beql` with the epilogue restore in its delay slot: the CALL is the inline
 * arm, so guard on the call rather than writing an early return.
 */

extern void *D_00484290;
extern void func_1D52E0(void *o);

s32 title_TitleMovieSetVolume_4f05d0(void)
{
    void *p;

    p = D_00484290;
    if (p != 0) {
        func_1D52E0(p);
    }
    return 0;
}
