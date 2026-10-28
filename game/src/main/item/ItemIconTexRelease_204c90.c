/* rgp:protos */
#define RGP_SELF_ItemIconTexRelease_204c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*//*rgp*//*rgp*/extern u8 D_004BBCE0[];extern s32 D_0044B710[][2];
s32 ItemIconTexRelease_204c90(s16 a,s16 b){s32 p=GetDrawCtxNameTable_15de40();if(!p)return 1;if(a<0 || b<0)return 2;MemStackReset_14d830(D_004BBCE0);NameTableRemoveByName_158c40(p,D_0044B710[a][b],0x32c);return 0;}
