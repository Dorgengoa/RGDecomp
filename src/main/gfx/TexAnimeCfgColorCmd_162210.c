#include "types.h"

struct S8 { s32 a; s32 b; };

extern s32 VariantGetInt_15f780(struct S8 *);

extern u8 D_00495EA4[16];
extern u8 D_00495EA5[16];
extern u8 D_00495EA6[16];
extern u8 D_00495EA7[16];

s32 TexAnimeCfgColorCmd_162210(struct S8 *p0, s32 p1)
{
    if (p1 > 0) {
        D_00495EA4[0] = VariantGetInt_15f780(p0++);
    }
    if (p1 > 1) {
        D_00495EA5[0] = VariantGetInt_15f780(p0++);
    }
    if (p1 > 2) {
        D_00495EA6[0] = VariantGetInt_15f780(p0++);
    }
    if (p1 > 3) {
        D_00495EA7[0] = VariantGetInt_15f780(p0);
    }
    return 1;
}
