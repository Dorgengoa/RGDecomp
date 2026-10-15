#pragma opt_propagation off
#include "types.h"
struct Obj{u8 pad[0x20];u8 *base;s32 length; s32 offset;};
extern u8 *AlignUpAdd_42e4b0(u8 *,s32,s32);
extern u8 *PtrAdd_42e4d0(u8 *,s32);
u8 *BumpArenaAlloc_42e300(s32 size,struct Obj *o,s32 align){
 u8 *end,*next,*result;
 if(o==0)return 0;
 result=0;
 if(o->base!=0){
  s32 count=align;
  result=AlignUpAdd_42e4b0(o->base,o->offset,count);
  {s32 length=o->length;end=PtrAdd_42e4d0(o->base,length);}
  next=AlignUpAdd_42e4b0(result,size,count);
  if(end<next)result=0;
  else o->offset=next-o->base;
 }
 return result;
}
