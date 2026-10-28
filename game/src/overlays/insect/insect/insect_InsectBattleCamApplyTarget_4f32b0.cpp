#include "types.h"
/* insect 0x00004F32B0 -- C++ virtual dispatch, vptr at +0xC0, slot 0xB4 =
 * virtual #43 (8 + 4*43).  [[jalr-is-cpp-virtual]] */

class VE {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;  
      
      
      
      
      
      
      
      
      
      void s32() { VCM0(void, 0x88); }
      
      
      
    
    void s43(f32 *v) { VCM(void, (void *, f32 *), 0xB4, v); }           /* slot 0xB4 */
};

struct S {
    u8  pad000[0xB0];
    f32 f0B0[4];
    u8  pad0C0[0x874 - 0xC0];
    VE *f874;
};

extern "C" void insect_InsectBattleCamApplyTarget_4f32b0(S *s, f32 *v)
{
    f32 t[4] __attribute__((aligned(16)));
    s32 i;

    if (s->f874 != 0) {
        for (i = 0; i < 4; i++) {
            t[i] = s->f0B0[i] + v[i];
        }
        s->f874->s43(t);
    }
}
