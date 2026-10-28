/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
class VC_DC_14 {
public:
    u8 pad[0xDC];
    VC_VPTR_MEMBER;
    
    
    s32 f() { return VCM0(s32, 0x14); }
};
extern "C" {

extern s32 NodeObjFindChildByName_195040(void *arg0, s32 arg1);
extern void *TargetRefGetMapObj_2e7050(s32 arg0);
extern void EvObjResolveTarget_2f9a60(void *, int);
extern s32 EvMapObjGetMode_366b80(void *arg0);
extern s32 EvMapObjGetModelName_366ba0(void *arg0);
extern s32 EvMapObjGetModel_366bb0(void *arg0);
extern void EvMapObjNodeBindFrame_3672d0(s32 arg0, s32 arg1);

s32 EvMapObjResolveTarget_3656c0(void *arg0, int rgp_a1)
{
    s32 var_19;
    s32 var_18;
    s32 var_2;
    void *temp_2;
    void *vtbl;

    EvObjResolveTarget_2f9a60((void *)arg0, (int)rgp_a1);
    *(s32 *)((u8 *)arg0 + 0x220) = 0;
    temp_2 = TargetRefGetMapObj_2e7050((s32)((u8 *)arg0 + 0xA0));
    if (temp_2 != NULL) {
        *(s32 *)((u8 *)arg0 + 0x220) = NodeObjFindChildByName_195040(temp_2, EvMapObjGetModelName_366ba0(arg0));
    }
    var_19 = *(s32*)((u8 *)arg0 + 0x2F4);
    var_18 = 0;
    while (var_18 < *(s16*)((u8 *)arg0 + 0x2FC)) {
        EvMapObjNodeBindFrame_3672d0(var_19, EvMapObjGetModel_366bb0(arg0));
        var_18 += 1;
        var_19 += 0x150;
    }
    if (!(((VC_DC_14 *)arg0)->f() & 0xFF)) {
        var_2 = *(s32 *)((u8 *)arg0 + 0xD0) & 0xFDFFFFFF;
    } else {
        var_2 = *(s32 *)((u8 *)arg0 + 0xD0) | 0x02000000;
    }
    *(s32 *)((u8 *)arg0 + 0xD0) = var_2;
    if ((((short)EvMapObjGetMode_366b80(arg0)) == 0) && (temp_2 != NULL)) {
        *(s16 *)((u8 *)temp_2 + 0x32) = 0;
        *(s32 *)((u8 *)temp_2 + 0x3C) = *(s32 *)((u8 *)temp_2 + 0x3C) | 1;
    }
    return 1;
}
}
