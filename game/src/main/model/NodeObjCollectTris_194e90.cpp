/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_dead_assignments off
typedef struct SNode00194E90 SNode00194E90;
struct SNode00194E90 {
    SNode00194E90 *unk0;
    u8 pad4[0x10 - 4];
    SNode00194E90 *unk10;
    u8 pad14[0x34 - 0x14];
    void *unk34;
    s32 unk38;
};

class Obj00194E90 {
public:
    u8 pad0[0x68];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void v12(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x38, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 NodeObjBasicCollectTrisWorld_196d70(SNode00194E90 *, s32, s32, s32, s32);

extern "C" s32 NodeObjCollectTris_194e90(Obj00194E90 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_2;
    s32 var_20;
    s32 var_19;
    SNode00194E90 *var_18;
    SNode00194E90 *temp_16;
    s32 var_17;

    var_20 = arg2;
    var_19 = arg4;
    if (*(s16 *)((u8 *)arg0 + 0x32) == 0) {
        return 0;
    }
    var_18 = *(SNode00194E90 **)((u8 *)arg0 + 0x94);
    arg0->v12((int)(long)(arg1), (int)(long)(arg2), (int)(long)(arg3));
    var_17 = 0;
    while (var_18 != NULL) {
        temp_16 = var_18->unk10;
        if (temp_16 != NULL) {
            temp_16->unk34 = arg0;
            temp_16->unk38 = 0;
            temp_2 = NodeObjBasicCollectTrisWorld_196d70(temp_16, arg1, var_20, arg3, var_19);
            temp_16->unk34 = NULL;
            temp_16->unk38 = 0;
            var_20 += temp_2 * 0x60;
            var_19 -= temp_2;
            var_17 += temp_2;
            if (var_19 <= 0) {
                break;
            }
        }
        var_18 = var_18->unk0;
    }
    return var_17;
}
