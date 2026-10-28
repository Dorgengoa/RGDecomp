/* rgp:protos */
#line 1
#pragma opt_propagation off
#include "types.h"

extern "C" {
extern void *IterNext_370040(void *arg0);
extern void IterInit_370170(void *, s32, int, int);
}

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s16 x) { return VCM(s32, (void *, s16), 0x70, x); }
};

typedef struct {
    u8 pad0[0x12];
    s16 unkA;
    u8 padC[0x18 - 0x14];
    s32 *unk14;
} Node;

extern "C" {
s32 WorldSubsysLinkIds_3fc450(s32 arg0, void *arg1, int rgp_a2, int rgp_a3)
{
    s32 *var_18;
    Node *temp_2;
    s32 var_17;
    s32 var_5;
    Node *nd;
    u8 sp58[0x8];

    if (arg1 == NULL) {
        return 0;
    }
    var_5 = arg0;
    if (arg0 != 0) {
        var_5 += 0x88;
    }
    IterInit_370170(sp58, var_5, (int)rgp_a2, (int)rgp_a3);
    while ((nd = (Node *)IterNext_370040(sp58)), (temp_2 = nd) != NULL) {
        var_18 = temp_2->unk14;
        if (1) {
            for (var_17 = 0; var_17 < temp_2->unkA; var_17++) {
                *var_18 = (*(VObj **)((u8 *)*(void **)((u8 *)arg1 + 0x5C) + 0x8))->f(*(s16 *)var_18);
                var_18++;
            }
        }
    }
    return 1;
}
}
