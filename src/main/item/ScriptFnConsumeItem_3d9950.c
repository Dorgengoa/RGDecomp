#include "types.h"

extern void VariantSetS32_36f040(s32, s32, s32);
extern s64 VariantGetS16_36fcc0(s32);
extern void *CharaMgrPoolFindByDataId_3a8a70(s32, s64, s32, s32, s32, s32, s32);
extern s32 PartyMoveToReserve_3c19b0(s32, s32, s32, s32);
extern void *D_00483960;
extern s32 D_00483964;

extern u8 *InvFindByUniqueId_3c85d0(s32,s64,s32,s32);
extern u8 *InvFindInCategoryRange_3c8370(s32,s64,s32,s32,s32,s32);
extern void ItemConsume_3d41b0(u8 *,s32,s32);
void ScriptFnConsumeItem_3d9950(s32 a,s32 b,s32 n,s32 args){
 s64 id,which;
 u8 *p;
 if(a==0)return;
 VariantSetS32_36f040(a,0,1);
 if(D_00483960==NULL || D_00483964==0)return;
 if(args==0 || n<=0)return;
 id=(s64)(s16)VariantGetS16_36fcc0(args);
 which=-1;
 if(n>=2)which=(s64)(s16)VariantGetS16_36fcc0(args+0x38);
 if(which>0){
  p=InvFindByUniqueId_3c85d0(*(s32 *)((u8 *)D_00483960+0x18),which,0,0);
  if(p!=NULL && id!=**(s16 **)(p+0x10))p=NULL;
 }else p=InvFindInCategoryRange_3c8370(*(s32 *)((u8 *)D_00483960+0x18),id,0,-1,0,0);
 if(p!=NULL)ItemConsume_3d41b0(p,1,1);
}
