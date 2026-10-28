/* rgp:protos */
#define RGP_SELF_DataTableCmdTableParams_3f9660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8  pad000[0x94];
    f32 m94;
    f32 m98;
    f32 m9C;
    f32 mA0;
    f32 mA4;
    f32 mA8;
    f32 mAC[3];
    f32 mB8;
    f32 mBC;
    f32 mC0;
    s16 mC4;
    s16 mC6;
    s16 mC8;
    u8  mCA[3];
    u8  mCD;
    u8  mCE;
    u8  mCF;
    u8  mD0;
} Pool;

extern Pool *D_004830F8;
extern f32 D_0045B078;
/*rgp*/
/*rgp*/

s32 DataTableCmdTableParams_3f9660(R8 *a)
{
    Pool *p = D_004830F8;
    s32 i;
    f32 v;
    f32 x;

    p->m94 = VariantGetFloat_15f740(a++);
    p->m98 = VariantGetFloat_15f740(a++);
    p->m9C = VariantGetFloat_15f740(a++);
    p->mA0 = VariantGetFloat_15f740(a++);
    p->mA4 = VariantGetFloat_15f740(a++);
    for (i = 0; i < 3; i++) p->mAC[i] = VariantGetFloat_15f740(a++);
    p->mB8 = VariantGetFloat_15f740(a++);
    p->mC0 = VariantGetFloat_15f740(a++);
    for (i = 0; i < 3; i++) p->mCA[i] = VariantGetInt_15f780(a++);
    p->mA8 = VariantGetFloat_15f740(a++);
    x = VariantGetFloat_15f740(a++);
    v = (s32)(x * D_0045B078);
    p->mC4 = v;
    p->mCD = VariantGetInt_15f780(a++);
    p->mCE = VariantGetInt_15f780(a++);
    p->mCF = VariantGetInt_15f780(a++);
    p->mD0 = (s32)(10.0f * VariantGetFloat_15f740(a++));
    p->mC6 = (s32)(10.0f * VariantGetFloat_15f740(a++));
    p->mC8 = (s32)(10.0f * VariantGetFloat_15f740(a++));
    p->mBC = VariantGetFloat_15f740(a);
    return 1;
}
