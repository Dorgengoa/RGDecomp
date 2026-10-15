#include "types.h"
extern void EffDefDestroy_1a0a90(void*,s32);
void EffTableDestroyAll_1a0240(u8*p){volatile struct{u8 pad[8];s32 value;void*node;}it;
 for(;;){void*node=*(void**)(p+0xe0);s32 value;it.node=node;if(node==p+0xd8)break;value=*(s32*)((u8*)node+0x18);it.value=value;EffDefDestroy_1a0a90(p,value);}}
