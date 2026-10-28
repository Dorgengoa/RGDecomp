/* rgp:protos */
#define RGP_SELF_MapDataGetSoundEnvPresetId_1e5340 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*//*rgp*//*rgp*//*rgp*//*rgp*/
s32 MapDataGetSoundEnvPresetId_1e5340(s32 ctx,u8*p){s32 mode;void*q;if(!p)return-1;mode=((signed char)MapDataGetType_1e7c00(p));switch(mode){case 2:return ((short)MapAreaGetSoundEnvPresetId_1dcea0(p));case 4:if(*(s32*)(p+0x2c)&8)return ((short)MapBlockGetSoundEnvPresetId_1e0090(p));q=MapFindAreaSlotById_1e4cb0(ctx,((short)MapDataGetParentId_1e7bb0(p)));return q?((short)MapAreaGetSoundEnvPresetId_1dcea0(q)):-1;default:return-1;}}
