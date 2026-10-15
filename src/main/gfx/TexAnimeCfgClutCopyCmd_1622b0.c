#include "types.h"

extern u8 VariantGetInt_15f780(void);
extern struct Big95E73 { u8 v; u8 pad[15]; } D_00495E73;

s32 TexAnimeCfgClutCopyCmd_1622b0(void)
{
    D_00495E73.v = VariantGetInt_15f780();
    return 1;
}
