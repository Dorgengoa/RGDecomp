/* rgp:protos */
#define RGP_SELF_ActCfgTableDtor_234550 1
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitActCfgTables_46b6c0 1
#define RGP_SELF_WIosBaseInitDtor_103420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481E50;
extern s32 D_00481E5C;
extern s32 D_00481E60;
extern s32 D_00481E6C;
extern s32 D_00481EE0;
extern u8 D_004BCDB0[];
extern u8 D_004BCDE0[];
extern u8 D_004BCE20[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];
extern u8 ActCfgTableDtor_234550[];

void StaticInitActCfgTables_46b6c0(void)
{
    IosBaseInitCtor_102bd0(&D_00481E5C);
    RegisterGlobalObject_100dc0(&D_00481E5C, IosBaseInitDtor_102ee0, &D_00481E50);
    WIosBaseInitCtor_103110(&D_00481E6C);
    RegisterGlobalObject_100dc0(&D_00481E6C, WIosBaseInitDtor_103420, &D_00481E60);
    CharaNormalTableCtor_225ac0(D_004BCDB0);
    CharaTableCtor_225790(D_004BCDE0);
    ActCfgTableCtor_225250(D_004BCE20);
    RegisterGlobalObject_100dc0(D_004BCE20, ActCfgTableDtor_234550, &D_00481EE0);
}
