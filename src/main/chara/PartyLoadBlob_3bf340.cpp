#pragma divbyzerocheck on
#include "types.h"
#undef NULL
#define NULL 0
class Self { public:
virtual s32 offset();
virtual void v12();
virtual s32 size();
u8 pad[0x164];s32 p168,p16c,p170,p174,p178,p17c;
};
class Lookup { public:
virtual void v8();
virtual void v12();
virtual void v16();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v32();
virtual void v36();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v52();
virtual void v56();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v72();
virtual void v76();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v92();
virtual void v96();
virtual void v100();
virtual void v104();
virtual void v108();
virtual s32 get(s32);
};
extern "C" {

extern s32 GroupTableFindEntry_415e00(s32 arg0, s64 arg1, s64 arg2);
extern void memcpy(void *arg0, void *arg1, s32 arg2);
extern void *D_00483894;

s32 PartyLoadBlob_3bf340(Self *arg0, void *arg1, s32 arg2)
{
    s16 temp_4_5;
s32 temp_16;
    s32 temp_21;
    s32 temp_22;
    s32 temp_23;
    s32 var_17;
    void **temp_4;
    void **temp_4_2;
    void **temp_4_3;
    void **temp_4_4;
    void **temp_4_6;
    void *vtbl;
    void *tbl34;

    if(arg1==0 || arg2<=0)return 0;
    {
        {
            temp_16 = arg0->p168;
temp_21 = arg0->p170;
            temp_22 = arg0->p174;
            temp_23 = arg0->p17c;
            var_17=((Self *)arg0)->size();
            if(arg2<var_17)var_17=arg2;
            memcpy((u8 *)arg0 + ((Self *)arg0)->offset(), arg1, var_17);
            arg0->p168 = temp_16;
            arg0->p174 = temp_22;
            arg0->p170 = temp_21;
            arg0->p17c = temp_23;
            tbl34 = *(void **)((u8 *)D_00483894 + 0x34);
            temp_4 = *(void ***)((u8 *)(*(void **)((u8 *)D_00483894+0x34)) + 0x14);
            vtbl = *temp_4;
            *(s32 *)((u8 *)arg0 + 0x14) = ((Lookup *)temp_4)->get(*(s16 *)((u8 *)arg0+0x4));
            temp_4_2 = *(void ***)((u8 *)(*(void **)((u8 *)D_00483894+0x34)) + 0x8);
            vtbl = *temp_4_2;
            *(s32 *)((u8 *)arg0 + 0x18) = ((Lookup *)temp_4_2)->get(*(s16 *)((u8 *)arg0+0x6));
            temp_4_3 = *(void ***)((u8 *)(*(void **)((u8 *)D_00483894+0x34)) + 0xC);
            vtbl = *temp_4_3;
            *(s32 *)((u8 *)arg0 + 0x1C) = ((Lookup *)temp_4_3)->get(*(s16 *)((u8 *)arg0+0x8));
            temp_4_4 = *(void ***)((u8 *)(*(void **)((u8 *)D_00483894+0x34)) + 0x8);
            vtbl = *temp_4_4;
            *(s32 *)((u8 *)arg0 + 0x20) = ((Lookup *)temp_4_4)->get(*(s16 *)((u8 *)arg0+0xA));
            temp_4_5 = *(s16 *)((u8 *)arg0 + 0xC);
            *(s32 *)((u8 *)arg0 + 0x24) = GroupTableFindEntry_415e00(*(s32 *)((u8 *)(*(void **)((u8 *)D_00483894+0x34))+0x14), (s64)(s16)(temp_4_5 / 100), (s64)(s16)temp_4_5);
            temp_4_6 = *(void ***)((u8 *)(*(void **)((u8 *)D_00483894+0x34)) + 0x18);
            vtbl = *temp_4_6;
            *(s32 *)((u8 *)arg0 + 0x28) = ((Lookup *)temp_4_6)->get(*(s32 *)((u8 *)arg0+0x10));
            return var_17;
        }
        return 0;
    }
    return 0;
}

}
