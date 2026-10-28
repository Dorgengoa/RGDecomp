/* rgp:protos */
#define RGP_SELF_SphereModelLoad_313c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Three call results held in callee-saved regs ($19,$18,$17 = declaration
   order descending) plus a fourth ($16).  Stack locals go in REVERSE
   declaration order (last-declared gets the LOWEST address): `tag` at 0x5C is
   declared first, the 12-byte `rec` at 0x50 second. */

extern u8 D_00462340[];
extern u8 D_004E7BE0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct Rec00313c60 {
    s32 m00;
    s32 m04;
    s32 m08;
} Rec00313c60;

void SphereModelLoad_313c60(void)
{
    s32 tag;
    Rec00313c60 rec __attribute__((aligned(16)));
    void *a;
    void *b;
    void *c;
    void *d;

    a = GetSystemMemStack_202600();
    b = GetDrawCtx_15de80();
    c = GetReadBuffHeap_2025e0();
    if (c == 0) {
        return;
    }
    d = MemStackHeapAlloc_14db10(c, 2, 0, 0x40);
    if (d == 0) {
        return;
    }
    MemStackAlign64_14d8e0(c);
    if (ResidentFileReadLocalizedMaybe_1c2860(D_00462340, d, &tag) != 0) {
        rec.m00 = 0;
        ModelResRelocate_14bfd0(&rec, d);
        ModelBuildFrames_1506c0(D_004E7BE0, &rec, b, a);
    }
    MemStackReturnToOwnerMaybe_14dad0(c);
    MemStackHeapFree_14dcb0(c, d);
}
