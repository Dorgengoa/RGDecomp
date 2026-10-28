/* rgp:protos */
#define RGP_SELF_title_TitleMovieSetVolume_4f05d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F05D0 -- guarded call, always returns 0.
 *
 * `beql` with the epilogue restore in its delay slot: the CALL is the inline
 * arm, so guard on the call rather than writing an early return.
 */

extern void *D_00484290;
/*rgp*/

s32 title_TitleMovieSetVolume_4f05d0(float rgp_f0)
{
    void *p;

    p = D_00484290;
    if (p != 0) {
        AudioDecSetInputVolumeF_1d52e0((float)rgp_f0);
    }
    return 0;
}
