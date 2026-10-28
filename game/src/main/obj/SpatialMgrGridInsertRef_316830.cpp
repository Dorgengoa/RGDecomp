/* rgp:protos */
#line 1
#include "types.h"

struct Obj316;

class VE316 {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v25(s32 a0) { VCM(void, (void *, s32), 0x6C, a0); }
};

struct Obj316 { VE316 *unk0; s32 unk4; };

extern "C" Obj316 * SpatialGridInsert_3163f0(void *, int);

extern "C" void SpatialMgrGridInsertRef_316830(void *arg0, s32 arg1, Obj316 **arg2) {
    s32 var_3;
    Obj316 *temp_2;
    Obj316 *temp_4;
    Obj316 *temp_4_2;
    VE316 *temp_4_3;
    Obj316 *temp_4_4;

    temp_2 = SpatialGridInsert_3163f0((void *)arg0, (int)arg1);
    if (temp_2 == NULL) {
        return;
    }
    temp_2->unk4 = arg1;
    if ((void *)temp_2 == (void *)arg2) {
        return;
    }
    temp_4 = (Obj316 *)temp_2->unk0;
    if (((temp_4 != NULL) ^ 1) != 0) {
        goto rest;
    }
    if (temp_4 != NULL) {
        temp_4->unk4 = temp_4->unk4 - 1;
    }
    temp_4_2 = (Obj316 *)temp_2->unk0;
    var_3 = (temp_4_2 != NULL) ? temp_4_2->unk4 : 0;
    if ((var_3 == 0) && (temp_4_2 != NULL)) {
        temp_4_3 = temp_4_2->unk0;
        if (temp_4_3 != NULL) {
            temp_4_3->v25(-1);
        }
        ((Obj316 *)temp_2->unk0)->unk4 = 0;
        temp_2->unk0 = (VE316 *)NULL;
    }
    temp_2->unk0 = (VE316 *)NULL;
rest:
    temp_4_4 = *arg2;
    temp_2->unk0 = (VE316 *)temp_4_4;
    if (temp_4_4 != NULL) {
        temp_4_4->unk4 = temp_4_4->unk4 + 1;
    }
}
