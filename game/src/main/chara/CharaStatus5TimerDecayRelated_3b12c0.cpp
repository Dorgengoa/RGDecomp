/* MATCH (s41 agent36): store through `fp = &arr[i]`, `var_f1 = *fp; var_f1 -= ...`. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VTvar2 {
    u8 pad70[0x70];
    u8 *(*unk70)(void *, s32);
} VTvar2;

typedef struct Vtarg0 {
    u8 pad19C[0x19C];
    s32 (*unk19C)(void *, s32);
} Vtarg0;

extern u8 *D_0048381C;
extern u8 D_0045B078[0x400];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x19C, x0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * f(s32 x0) { return VCM(u8 *, (void *, s32), 0x70, x0); }
};
s32 CharaStatus5TimerDecayRelated_3b12c0(Vtarg0 **arg0) {
    f32 var_f1;
    s16 temp_4_2;
    VTvar2 **temp_4;
    u8 *var_2;
    u8 *base;
    u8 *p2;
    f32 *fp;
    f32 x;
    f32 d;
    f32 two;

    if (((VC_0 *)(arg0))->f(5) != 0) {
        p2 = *(u8 **)(D_0048381C + 0x58);
        temp_4 = *(VTvar2 ***)(p2 + 8);
        if (temp_4 != NULL) {
            var_2 = ((VC_1 *)(temp_4))->f(5);
        } else {
            var_2 = NULL;
        }
        if (var_2 != NULL) {
            temp_4_2 = *(s16 *)(var_2 + 0x3C);
            if (((s16 *)((u8 *)(u8 *)arg0 + 0x150))[temp_4_2] == 5) {
                fp = &((f32 *)((u8 *)arg0 + 0xD0))[temp_4_2];
                var_f1 = *fp;
                var_f1 -= 2.0f * (*(f32 *)D_0045B078);
                if (var_f1 < 1.0f) {
                    var_f1 = 1.0f;
                }
                *fp = var_f1;
            }
        }
    }
    return 1;
}

}
