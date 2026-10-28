#include "types.h"

typedef struct SubCED50 {
    u8 pad00[0xC];
    s32 unkC;
} SubCED50;

typedef struct Obj003CED50 {
    u8 pad00[0x18];
    SubCED50 *unk18;
} Obj003CED50;

class Base003ced50 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void unk10C(f32 x) { VCM(void, (void *, f32), 0x10C, x); }
};

extern "C" Base003ced50 *InsectRecSlotGetItem_3cfb30(void *arg0, s32 arg1);

extern "C" s32 InsectRecSlotsTick_3ced50(Obj003CED50 *arg0, f32 fparg0)
{
    SubCED50 *sub;
    Base003ced50 *obj;
    s32 i;

    sub = arg0->unk18;
    if (sub == NULL) {
        return 0;
    }
    if (sub->unkC == 0) {
        return 0;
    }
    i = 0;
    do {
        obj = InsectRecSlotGetItem_3cfb30(arg0, i);
        if (obj != NULL) {
            obj->unk10C(fparg0);
        }
        i += 1;
    } while (i < 5);
    return 1;
}
