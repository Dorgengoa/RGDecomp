#include "types.h"
#pragma optimization_level 3

/* PARK: RIGHT LENGTH (59 words), 17 bad, two named residues left.
   (1) mwcc TAIL-MERGES the inner `sp3C = NULL;` with the outer one; retail
       emits the store THREE times (annulled copy + inner + outer).  Nested
       ifs, `&&`, and a `*(s32 *)&sp3C = 0;` spelling are one object.
   (2) `temp_3_2 >= 0x7531` puts the slti in $v1 and costs a nop;
       `> 0x7530` puts it in $at and sinks the store into the delay slot
       (retail) but then the unit is one word SHORT because of (1).
   The `((sp3C != NULL) ^ 1) == 0` bool materialisation and the C++ virtual
   call are both confirmed correct here. */

struct Obj3147;

class VE3147 {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v25(s32 a0) { VCM(void, (void *, s32), 0x6C, a0); }
};

struct Obj3147 { VE3147 *unk0; s32 unk4; };
struct S3147 { Obj3147 *unk0; s32 unk4; };

extern "C" s32 HandleRegistryInsert_314f80(s32, Obj3147 **, s32);

extern "C" s32 HandleRegistryRegister_3147e0(S3147 *arg0, Obj3147 **__restrict arg1) {
    s32 arg_h2;

    Obj3147 *sp3C;
    s32 temp_16;
    s32 temp_2;
    s32 temp_3_2;
    s32 var_2;
    VE3147 *temp_4;

    sp3C = *arg1;
    if (sp3C != NULL) {
        sp3C->unk4 = sp3C->unk4 + 1;
    }
    arg_h2 = arg0->unk4;
    temp_16 = HandleRegistryInsert_314f80((s32)arg0->unk0, &sp3C, arg_h2) & 0xFF;
    if (((sp3C != NULL) ^ 1) == 0) {
        if (sp3C != NULL) {
            sp3C->unk4 = sp3C->unk4 - 1;
        }
        var_2 = (sp3C != NULL) ? sp3C->unk4 : 0;
        if ((var_2 == 0) && (sp3C != NULL)) {
            temp_4 = sp3C->unk0;
            if (temp_4 != NULL) {
                temp_4->v25(-1);
            }
            sp3C->unk4 = 0;
            sp3C = (Obj3147 *)NULL;
        }
        sp3C = (Obj3147 *)NULL;
    }
    if (temp_16 == 0) {
        return -1;
    }
    temp_2 = arg0->unk4;
    temp_3_2 = temp_2 + 1;
    arg0->unk4 = temp_3_2;
    if (temp_3_2 > 0x7530) {
        arg0->unk4 = 0;
    }
    return temp_2;
}
