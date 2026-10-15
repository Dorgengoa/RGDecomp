#include "types.h"
extern s32 LoaderCountQueued_1cd620(void*);extern s32 LoaderQueueFindUnitById_1cdc70(void*,s32,void*,s32);
s32 LoaderGetStatus_1cd4f0(u8*p,s32 index){if(index<0)return-1;if(LoaderCountQueued_1cd620(p)<=0)return-1;if(LoaderQueueFindUnitById_1cdc70(p,index,p+0x20,0))return 0;if(LoaderQueueFindUnitById_1cdc70(p,index,p+0x28,0))return 0;if(!LoaderQueueFindUnitById_1cdc70(p,index,p+0x30,0))return-1;return 1;}
