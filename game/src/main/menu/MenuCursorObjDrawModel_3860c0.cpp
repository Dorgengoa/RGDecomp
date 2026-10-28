#include "types.h"
extern "C" {
typedef struct { u8 pad[0x4DC]; s32 unk4DC; } S4DC_3860c0;

extern s32 DrawListAddTexLoad_1418c0(s32 arg0, s32 arg1, f32 arg2);
extern s32 GetDrawCtx_15de80(void);

class VC_0 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    void f(f32 x0) { VCM(void, (void *, f32), 0x18, x0); }
};
class VC_1 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    void f() { VCM0(void, 0x24); }
};
void MenuCursorObjDrawModel_3860c0(void *arg0)
{
    S4DC_3860c0 *temp_16;
    void *vtbl;

    if ((*(s32 *)((u8 *)arg0 + 0x0) != 0) && (*(s32 *)((u8 *)arg0 + 0x8) != 0)) {
        temp_16 = *(S4DC_3860c0 **)((u8 *)arg0 + 0x4);
        if (temp_16 != NULL) {
            if (temp_16->unk4DC > 0) {
                s32 t = GetDrawCtx_15de80();
                DrawListAddTexLoad_1418c0(t, temp_16->unk4DC, 1.0f);
            }
                    ((VC_0 *)(temp_16))->f(1.0f);
            ((VC_1 *)(temp_16))->f();
        }
    }
}

}
