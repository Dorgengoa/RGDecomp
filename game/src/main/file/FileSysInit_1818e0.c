/* rgp:protos */
#define RGP_SELF_FileSysInit_1818e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern s32 CreateSema(void*);extern void DeleteSema(s32);/*rgp*/extern s32 D_0047E028,D_0047E02C,D_0048120C;
s32 FileSysInit_1818e0(void){s32 data[8] __attribute__((aligned(16)));s32 id;if(D_0048120C)return 0;data[2]=1;data[1]=1;data[5]=0;D_0047E02C=CreateSema(data);id=CreateSema(data);D_0047E028=id;if(id<0 || D_0047E02C<0){if(id>=0)DeleteSema(id);if(D_0047E02C>=0)DeleteSema(D_0047E02C);return 0;}FileAliasTableSet_1816a0(0,0);D_0048120C=1;return 1;}
