/* rgp:protos */
#define RGP_SELF_AmixerCfgTrackNumCmd_170030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj {
    s32 m08;
    void *m0C;
};

extern struct Obj *D_00481188 __attribute__((section(".sdata")));
extern void *D_0048118C __attribute__((section(".sdata")));
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AmixerCfgTrackNumCmd_170030(void *rgp_a0)
{
    s32 n;
    struct Obj *o;
    void *pool;
    void *p;
    void *r;

    n = VariantGetInt_15f780((void *)rgp_a0);
    pool = D_0048118C;
    o = D_00481188;
    if (n > 0) {
        p = MemStackNew_14e1b0(n * 20 + 0x10, pool);
        r = ConstructNewArray_100710(p, (void *)AmixerTrackCtor_1700b0, 0, 0x14, n);
        o->m0C = r;
        if (r != 0) {
            o->m08 = n;
        }
    }
    return 1;
}
