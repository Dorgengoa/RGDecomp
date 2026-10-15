#include "types.h"
struct Obj {u8 pad[0x38];s16 count;u8 pad3A[2];s32 entries[4];};
s32 ExecEffInfoListAdd_3a6cc0(struct Obj *self,s32 value){
 s32 i;
 if(value==0)return 0;
 i=self->count;
 if(i<4){self->count=i+1;self->entries[i]=value;}
 return 1;
}
