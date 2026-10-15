#include "types.h"

extern struct Big9D43C { s32 v; s32 pad[3]; } D_0049D43C;
extern struct Big9D440 { s32 v; s32 pad[3]; } D_0049D440;
extern s32 VariantGetInt_15f780(void);

s32 InfoCfgOutlineLevelCmd_1ab1e0(void)
{
    D_0049D43C.v = 1;
    D_0049D440.v = VariantGetInt_15f780();
    return 1;
}
