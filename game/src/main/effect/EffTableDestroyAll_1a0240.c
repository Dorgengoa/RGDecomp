/* rgp:protos */
#define RGP_SELF_EffTableDestroyAll_1a0240 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
void EffTableDestroyAll_1a0240(u8*p){volatile struct{u8 pad[8];s32 value;void*node;}it;
 for(;;){void*node=*(void**)(p+0xe0);s32 value;it.node=node;if(node==p+0xd8)break;value=*(s32*)((u8*)node+0x18);it.value=value;EffDefDestroy_1a0a90(p,value);}}
