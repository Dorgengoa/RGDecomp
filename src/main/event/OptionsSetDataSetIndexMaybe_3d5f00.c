#include "types.h"
extern s32 D_004659A8[0x100];
extern s32 StateGetRequiredDisc_3d5ed0(void *);
void OptionsSetDataSetIndexMaybe_3d5f00(u8 *self,s32 id){
    if(id<0 || id>=D_004659A8[0]) *(s16 *)(self+0x2E)=StateGetRequiredDisc_3d5ed0(self);
    else *(s16 *)(self+0x2E)=id;
}
