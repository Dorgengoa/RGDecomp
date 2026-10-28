/* rgp:protos */
#define RGP_SELF_ScriptFnPlaceUnitByEncounterSlotMaybe_3d7da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 *D_00483960;
/*rgp*/
extern s32 D_00483964;

void ScriptFnPlaceUnitByEncounterSlotMaybe_3d7da0(s32 a,s32 b,s32 n,s32 args){
    s64 id;
    f32 x,y,z,t;
    u8 *entry;
    s32 ctx;
    s32 obj;
    if(a==0)return;
    VariantSetS32_36f040(a,0,1);
    if(D_00483960==NULL || D_00483964==0)return;
    if(args==0 || n<5)return;
    id=(s64)(s16)VariantGetS16_36fcc0(args);
    x=VariantGetFloat_36f7a0(args+0x38);
    y=VariantGetFloat_36f7a0(args+0x70);
    z=VariantGetFloat_36f7a0(args+0xA8);
    t=VariantGetFloat_36f7a0(args+0xE0);
    entry=((u8 *)ObjMgrFindByEncounterSlotIdMaybe_3bb0c0(*(s32 *)(D_00483960+0x1C), (int)(id)));
    if(entry==NULL)return;
    ctx=((s32)GetActionMgr_1fdb50());
    if(ctx==0)return;
    obj=((s32)ActionMgrFindById_233b50(ctx,*(s32 *)(entry+0xC)));
    if(obj==0)return;
    CharaSetPosXYZ_2139e0(obj,x,y,z);
    CharaSetYaw_2138f0(obj,t);
    VariantSetS32_36f040(a,1,1);
}
