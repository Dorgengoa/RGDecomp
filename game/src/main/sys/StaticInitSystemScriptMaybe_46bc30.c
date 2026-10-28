/* rgp:protos */
#define RGP_SELF_IosBaseInitDtor_102ee0 1
#define RGP_SELF_StaticInitSystemScriptMaybe_46bc30 1
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
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482150;
extern s32 D_0048215C;
extern s32 D_00482160;
extern s32 D_0048216C;
extern u8 D_004D77B0[];
extern u8 D_004D7810[];
extern u8 D_004D7830[];
extern u8 D_004D7C40[];
extern u8 D_004D7C8C[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitSystemScriptMaybe_46bc30(void)
{
    IosBaseInitCtor_102bd0(&D_0048215C);
    RegisterGlobalObject_100dc0(&D_0048215C, IosBaseInitDtor_102ee0, &D_00482150);
    WIosBaseInitCtor_103110(&D_0048216C);
    RegisterGlobalObject_100dc0(&D_0048216C, WIosBaseInitDtor_103420, &D_00482160);
    MemStackCtor_14e030(D_004D77B0);
    LetterboxReset_278390(D_004D7810);
    EventIconTableReset_278b40(D_004D7830);
    InteractRecResetMaybe_3ee600(D_004D7C40);
    ExecInfoInit_3a7940(D_004D7C8C);
}
