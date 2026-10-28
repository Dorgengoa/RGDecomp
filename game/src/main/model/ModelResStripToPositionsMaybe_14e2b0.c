/* rgp:protos */
#define RGP_SELF_ModelResStripToPositionsMaybe_14e2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 ModelResGetMeshInfo_14c440(void *, s32, s32);
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x40];
    s32 m40;
    s32 m44;
    u8 pad048[0x9];
    u8 m51;
};

struct Obj1 {
    u8 pad000[0x8];
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
};

void ModelResStripToPositionsMaybe_14e2b0(s32 p0)
{
    u128 v40[2];
    s32 r0;
    s32 l1;
    struct Obj0 *r2;
    s32 r3;
    struct Obj1 *r4;

    if (p0 != 0) {
        r0 = ModelResGetMaterialCount_14c640(p0);
        l1 = 0;
        while (l1 < r0) {
            r2 = ArrayGetChecked_14c5e0(p0, l1);
            if (r2 != 0) {
                r2->m44 = 0;
                r2->m40 = 4;
                r2->m51 = 1;
            }
            l1 = (l1 + 1);
        }
        r3 = ModelResGetMeshInfo_14c440(v40, p0, 0);
        r4 = ModelResGetVertexBufMaybe_14ce60(v40);
        if (r4 == 0) {
            return;
        }
        r4->m0C = 0;
        r4->m08 = 0;
        r4->m14 = 0;
        r4->m10 = 0;
        r4->m1C = 0;
        r4->m18 = 0;
        return;
    }
}
