#include "types.h"
#undef NULL
#define NULL 0
class Obj { public:
VC_VPTR_MEMBER;









void destroy() { VCM0(void, 0x30); }

















































void update(s32 a0) { VCM(void, (void *, s32), 0xF8, a0); }
};
struct Bits {u8 b0:1;u8 b1:1;};
struct Self {u8 pad[0x168];s32 list;};
extern "C" {

extern void PoolFreeElem_36a8e0(s32 arg0, s32 arg1);
extern void *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern void InvFreeCategory8Items_3c8d70(void *arg0);
extern s32 D_00465B50[16];
extern void *D_00483890;

s32 InvBroadcastPhase_3c02b0(Self *arg0, s32 arg1)
{
    s32 temp_16;
    s32 var_17;
    s32 var_17_2;
    void *temp_2;
    void *temp_2_2;
    void *vtbl;

    if (D_00483890 == NULL) {
        return 0;
    }
    if (!((Bits *)((u8 *)(*(void **)((u8 *)D_00483890 + 0x20)) + 0x24C))->b0) return 0;
    {
        if(arg0->list==0)return 0;
        {
            temp_16 = D_00465B50[0];
            var_17 = 0;
            while (var_17 < temp_16) {
                temp_2 = PoolGetUsedElem_36acb0(arg0->list, var_17);
                vtbl = *(void **)((u8 *)temp_2 + 0x0);
                if ((temp_2 != NULL) && (!(((Bits *)((u8 *)temp_2+0xA))->b1))) {
                    ((Obj *)temp_2)->update(arg1);
                }
                var_17 += 1;
            }
            InvFreeCategory8Items_3c8d70(arg0);
            if (arg0->list != 0) {
                var_17_2 = 0;
                while (var_17_2 < temp_16) {
                    temp_2_2 = PoolGetUsedElem_36acb0(arg0->list, var_17_2);
                    if ((temp_2_2 != NULL) && (((Bits *)((u8 *)temp_2_2+0xA))->b1)) {
                        vtbl = *(void **)((u8 *)temp_2_2 + 0x0);
                        ((Obj *)temp_2_2)->destroy();
                        PoolFreeElem_36a8e0(arg0->list, var_17_2);
                    }
                    var_17_2 += 1;
                }
            }
            return 1;
        }
        return 0;
    }
    return 0;
}

}
