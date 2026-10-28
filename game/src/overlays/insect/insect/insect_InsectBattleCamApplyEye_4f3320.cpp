#include "types.h"
/* insect 0x00004F3320 -- C++ virtual dispatch, vptr at +0xC0, slot 0xB0 =
 * virtual #42 (8 + 4*42).  [[jalr-is-cpp-virtual]] */

class VE {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;  
      
      
      
      
      
      
      
      
      
      void s32() { VCM0(void, 0x88); }
      
      
      
    void s42(f32 *v) { VCM(void, (void *, f32 *), 0xB0, v); }           /* slot 0xB0 */
};

struct S {
    u8  pad000[0xA0];
    f32 f0A0[4];
    u8  pad0B0[0x874 - 0xB0];
    VE *f874;
};

extern "C" void insect_InsectBattleCamApplyEye_4f3320(S *s, f32 *v)
{
    f32 t[4] __attribute__((aligned(16)));
    s32 i;

    if (s->f874 != 0) {
        for (i = 0; i < 4; i++) {
            t[i] = s->f0A0[i] + v[i];
        }
        s->f874->s42(t);
    }
}
