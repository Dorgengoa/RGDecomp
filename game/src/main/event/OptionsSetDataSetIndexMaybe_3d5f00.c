/* rgp:protos */
#define RGP_SELF_OptionsSetDataSetIndexMaybe_3d5f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern s32 D_004659A8[0x100];
/*rgp*/
void OptionsSetDataSetIndexMaybe_3d5f00(u8 *self,s32 id){
    if(id<0 || id>=D_004659A8[0]) *(s16 *)(self+0x2E)=((unsigned char)StateGetRequiredDisc_3d5ed0());
    else *(s16 *)(self+0x2E)=id;
}
