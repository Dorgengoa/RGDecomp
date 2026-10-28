/* rgp:protos */
#define RGP_SELF_MapAreaRequestPac_1dd090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void strcpy(void *, void *);
extern void Sprintf_1343b8(void *, void *, s32, s32, void *);
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045B388[];
extern u8 D_0045B390[];

s32 MapAreaRequestPac_1dd090(s32 p0, s32 p1, s32 p2)
{
    u128 vC0[2];
    u128 v40[8];

    LoadHandleResetThunk_1ccc10((int)p0);
    if (p1 == 0) {
        goto fail;
    }
    if (p2 != 0) {
        goto ok;
    }
fail:
    return 0;
ok:
    strcpy(vC0, D_0045B388);
    Sprintf_1343b8(v40, D_0045B390, p1, p2, vC0);
    LoadHandleRequestFile_1ccbb0(p0, v40);
    return 1;
}
