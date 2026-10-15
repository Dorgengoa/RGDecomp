#include "types.h"

extern void SlotGetInt_15f720(void *);
extern u8 VariantGetInt_15f780(void *);
extern void TexAnimKeyInit_164080(u8 *);
extern s32 D_00481148;
extern s32 D_0048114C;
extern u8 D_00495E70[0x20];
extern s16 D_00495E9E[0x10];

s32 TexAnimeCfgTexAnimeDataCmd_162690(void *arg0) {
    void *old;

    D_00481148 = -1;
    TexAnimKeyInit_164080(D_00495E70);
    old = arg0;
    arg0 = (u8 *)arg0 + 8;
    D_00495E70[0] = VariantGetInt_15f780(old);
    SlotGetInt_15f720(arg0);
    D_00495E9E[0] = (s16)D_0048114C;
    return 1;
}
