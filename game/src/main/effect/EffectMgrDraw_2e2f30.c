/* rgp:protos */
#define RGP_SELF_EffectMgrDraw_2e2f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern void *memset(void *,s32,u32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D288;
void EffectMgrDraw_2e2f30(u8 *o) {
 s32 b6c,b68,b64,b60; s32 range[2]; s32 id,i,end;
 if(*(s16 *)(o+0x4078)) {
 id=GetDrawCtx_15de80();memset(range,0,8);EffTableBuildIndexMaybe_1a04d0(o+0x58,range);
 end=range[1];i=range[0];
 while(i<=end) {
 DrawListGetStats_148940(id,&b6c,&b68,&b64,&b60);
 if(!((f32)b68<D_0047D288*(f32)b60))break;
 DrawListAddTexLoad_1418c0(id,i,1.0f);EffTableDrawTexBucket_1a0290(o+0x58,i,D_0047D288);i++;
 }
 EffTableFreeIndex_1a0470(o+0x58);EffectEntriesDraw_2deac0(o+0x1674);
 }
}
