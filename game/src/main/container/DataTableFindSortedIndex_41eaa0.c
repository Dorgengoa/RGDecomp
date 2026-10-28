/* rgp:protos */
#define RGP_SELF_DataTableFindSortedIndex_41eaa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
s32 DataTableFindSortedIndex_41eaa0(u8 *self,s32 id){
s32 count;
s16 v;
u8 *p;
s32 i;
s32 result;
if(id<0)return -1;
 p=*(u8 **)(self+0x8C);
 if(p==0)return -1;
 count=*(s16 *)(self+0x7C);
 result=-1;
 for(i=0;i<count;i++,p+=0x14){
  v=*(s16 *)(p+2);
  if(v==id){result=i;break;}
  if(v > id)break;
 }
 return result;
}
