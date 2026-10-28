/* rgp:protos */
#define RGP_SELF_XformPairComposeOffset_19a010 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/* Neighbour family of the already-matched src/accessors/FUN_0019a1?0.c:
   VecAdd_13be20/bd40 are (dst, a, b) vector ops, MatFromSRTVu0_13bc90 is a 4-arg
   matrix build, MtxMul_13d240 is (dst, src, mtx).
   Stack locals are allocated in REVERSE declaration order, so the 64-byte
   matrix (sp+0x80, the top of the local area) is declared FIRST. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void XformPairComposeOffset_19a010(u8 *p, u8 *d, u8 *s)
{
    Mtx4 m __attribute__((aligned(16)));
    Vec4 t __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));

    VecAdd_13be20(&c, (Vec4 *)(p + 0x10), (Vec4 *)(p + 0x60));
    VecAdd_13be20(&b, (Vec4 *)(p + 0x20), (Vec4 *)(p + 0x70));
    VecMul_13bd40(&a, (Vec4 *)(p + 0x30), (Vec4 *)(p + 0x80));
    MatFromSRTVu0_13bc90(&m, &a, &b, &c);
    VecMul_13bd40(&t, (Vec4 *)(p + 0x40), (Vec4 *)(p + 0x90));
    MtxMul_13d240(d, s, &m);
    VecMul_13bd40((Vec4 *)(d + 0x40), (Vec4 *)(s + 0x40), &t);
}
