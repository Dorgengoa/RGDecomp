/* rgp:protos */
#define RGP_SELF_InsectCageMenuItemCellCb_38f4f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483310;
extern u8 D_004DB430[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
    s16 m12;
};

s32 InsectCageMenuItemCellCb_38f4f0(struct Obj0 *p0)
{
    s16 t0;
    s16 t1;
    s32 t2;
    s32 r1;
    s32 r2;

    t0 = p0->m10;
    t1 = p0->m12;
    UiSelFrameSetGridCell_28db00(D_004DB430, 0x78, t0, t1, 0x62, 0x49);
    t2 = D_00483310;
    r1 = ((s32)InsectCageMenuItemCellSetupMaybe_38f810(p0, t2));
    r2 = ItemInsectUseClassMaybe_390b20(r1);
    return 1;
}
