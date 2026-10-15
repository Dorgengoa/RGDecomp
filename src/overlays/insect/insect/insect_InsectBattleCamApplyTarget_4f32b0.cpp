#include "types.h"
/* insect 0x00004F32B0 -- C++ virtual dispatch, vptr at +0xC0, slot 0xB4 =
 * virtual #43 (8 + 4*43).  [[jalr-is-cpp-virtual]] */

class VE {
public:
    u8 pad000[0xC0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32();
    virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38();
    virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42();
    virtual void s43(f32 *v);           /* slot 0xB4 */
};

struct S {
    u8  pad000[0xB0];
    f32 f0B0[4];
    u8  pad0C0[0x874 - 0xC0];
    VE *f874;
};

extern "C" void insect_InsectBattleCamApplyTarget_4f32b0(S *s, f32 *v)
{
    f32 t[4];
    s32 i;

    if (s->f874 != 0) {
        for (i = 0; i < 4; i++) {
            t[i] = s->f0B0[i] + v[i];
        }
        s->f874->s43(t);
    }
}
