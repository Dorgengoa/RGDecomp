/* rgp:protos */
#line 1
#pragma divbyzerocheck on
#include "types.h"
#undef NULL
#define NULL 0
class Self { public:
VC_VPTR_MEMBER; s32 offset() { return VCM0(s32, 0x8); }

s32 size(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
u8 pad[0x164];s32 p168,p16c,p170,p174,p178,p17c;
};
class Lookup { public:
VC_VPTR_MEMBER;

























s32 get(s32 a0) { return VCM(s32, (void *, s32), 0x70, a0); }
};
extern "C" {

extern s32 GroupTableFindEntry_415e00(s32, int, int, int);
extern void memcpy(void *arg0, void *arg1, s32 arg2);
extern void *D_00483894;

s32 PartyLoadBlob_3bf340(Self *arg0, void *arg1, s32 arg2, int rgp_a3)
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
            var_17=((Self *)arg0)->size((int)(long)(arg1), (int)(long)(arg2), (int)(long)(rgp_a3));
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
            *(s32 *)((u8 *)arg0 + 0x24) = GroupTableFindEntry_415e00(*(s32 *)((u8 *)(*(void **)((u8 *)D_00483894+0x34))+0x14), (int)((s64)(s16)(temp_4_5 / 100)), (int)((s64)(s16)temp_4_5), 0);
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
