/* rgp:hwaccess */ #include "port/hwaccess.h"
/* rgp:hwaccess */ extern unsigned char D_00527020[];
#line 1
/* rgp:protos */
#define RGP_SELF_FieldHudInitOnce_204120 1
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
/*rgp*/

extern s32 D_00481C5C;
extern u8 D_004BBC80[];
extern u8 D_004BC250[];
extern u8 D_00527020[];

void FieldHudInitOnce_204120(void)
{
    if (D_00481C5C == 0) {
        func_4F6F50(D_00527020);
        func_4F6F00(D_00527020);
        func_4F19E0(D_00527020);
        func_506DC0(D_004BC250, D_004BBC80);
        func_506D80(D_004BC250);
        func_506B70(D_004BC250, 0x59D9);
        func_506C10(D_004BC250);
        func_509040(1, 0);
        func_4FAAC0(D_004BBC80);
        D_00481C5C = 1;
    }
    (*(s8 *)((unsigned char *)D_00527020 + 0x3AE)) = 1;
}
