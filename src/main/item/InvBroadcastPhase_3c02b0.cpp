#include "types.h"
#undef NULL
#define NULL 0
class Obj { public:
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
virtual void destroy();
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
virtual void v112();
virtual void v116();
virtual void v120();
virtual void v124();
virtual void v128();
virtual void v132();
virtual void v136();
virtual void v140();
virtual void v144();
virtual void v148();
virtual void v152();
virtual void v156();
virtual void v160();
virtual void v164();
virtual void v168();
virtual void v172();
virtual void v176();
virtual void v180();
virtual void v184();
virtual void v188();
virtual void v192();
virtual void v196();
virtual void v200();
virtual void v204();
virtual void v208();
virtual void v212();
virtual void v216();
virtual void v220();
virtual void v224();
virtual void v228();
virtual void v232();
virtual void v236();
virtual void v240();
virtual void v244();
virtual void update(s32);
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
