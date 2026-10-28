/* rgp:protos */
#define RGP_SELF_ScriptFnInvAddItem_3d9a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00483960;
extern s32 D_00483964;

/*rgp*/
/*rgp*/
void ScriptFnInvAddItem_3d9a80(s32 a,s32 b,s32 n,s32 args){
    s64 id;
    void *p;
    if(a==0)return;
    VariantSetS32_36f040(a,0,1);
    if(D_00483960==NULL || D_00483964==0)return;
    if(args==0 || n<=0)return;
    id=(s64)(s16)VariantGetS16_36fcc0(args);
    p=InvAddItemCoreMaybe_3c6540(*(s32 *)((u8 *)D_00483960+0x18), (int)(id), 0, 1, -1, 0, 0);
    if(p!=NULL)return;
    p=InvAddItemCoreMaybe_3c6540(*(s32 *)((u8 *)D_00483960+0x18), (int)(id), 9, 1, -1, 0, 0);
    if(p!=NULL)StateFlagSet_3ccb70(*(s32 *)((u8 *)D_00483960+0x10),0x7F8,1,1);
}
