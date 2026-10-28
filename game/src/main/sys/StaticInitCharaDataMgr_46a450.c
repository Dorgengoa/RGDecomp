/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitCharaDataMgr_46a450 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481938;
extern s32 D_00481944;
extern s32 D_00481948;
extern s32 D_00481954;
extern u8 D_004B3910[];
extern u8 D_004B4120[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitCharaDataMgr_46a450(void)
{
    s32 l5;
    s32 l6;

    IosBaseInitCtor_102bd0(&D_00481944);
    RegisterGlobalObject_100dc0(&D_00481944, IosBaseInitDtor_102ee0, &D_00481938);
    WIosBaseInitCtor_103110(&D_00481954);
    RegisterGlobalObject_100dc0(&D_00481954, WIosBaseInitDtor_103420, &D_00481948);
    IdSlotTableInit_1efa30(D_004B3910);
    l6 = 0;
    do {
        *(u8 *)((u8 *)D_004B4120 + (l6 << 8)) = 0;
        *(s32 *)((u8 *)D_004B4120 + (l6 << 2) + 0x1000) = -1;
        l5 = ((l6 + 1) < 0x10);
        l6 = (l6 + 1);
    } while (l5 != 0);
}
