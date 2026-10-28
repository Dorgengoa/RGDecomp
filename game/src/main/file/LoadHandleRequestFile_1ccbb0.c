/* rgp:protos */
#define RGP_SELF_LoadHandleRequestFile_1ccbb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s16 m00;
};

s16 LoadHandleRequestFile_1ccbb0(struct Obj0 *p0, s32 p1)
{
    s32 r1;
    s32 r2;

    LoadHandleReset_1ccc10(p0);
    r1 = ((s32)GetLoaderMgr_1f59d0());
    r2 = LoaderRequestFile_1cd870(r1, p1, 0);
    p0->m00 = r2;
    return r2;
}
