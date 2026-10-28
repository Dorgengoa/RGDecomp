/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x004F3390 -- C++ virtual dispatch, vptr at +0xC0, slots 0xA4 and
 * 0xA8 = virtuals #39 and #40 (8 + 4*N).  [[jalr-is-cpp-virtual]]
 *
 * Same class as insect_InsectBattleCamApplyTarget_4f32b0 / insect_InsectBattleCamApplyEye_4f3320 (vptr 0xC0), and the
 * owning object is the same `S` whose f874 holds the VE pointer.
 */

class VE {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;  
      
      
      
      
      
      
      
      
      
      void s32() { VCM0(void, 0x88); }
      
      
    void s39(void *p) { VCM(void, (void *, void *), 0xA4, p); }          /* slot 0xA4 */
    void s40(f32 *v) { VCM(void, (void *, f32 *), 0xA8, v); }           /* slot 0xA8 */
};

struct P {
    u8  pad0000[0x4344];
    s32 f4344;
};

struct S {
    f32 f000[3];                        /* +0x00 */
    u8  pad00C[0x10 - 0x0C];
    f32 f010[3];                        /* +0x10 */
    u8  pad01C[0x20 - 0x1C];
    f32 f020[3];                        /* +0x20 */
    u8  pad02C[0x30 - 0x2C];
    f32 f030[3];                        /* +0x30 */
    u8  pad03C[0x40 - 0x3C];
    f32 f040[3];                        /* +0x40 */
    u8  pad04C[0x50 - 0x4C];
    f32 f050[3];                        /* +0x50 */
    u8  pad05C[0x80 - 0x5C];
    f32 f080[3];                        /* +0x80 */
    u8  pad08C[0x90 - 0x8C];
    f32 f090[3];                        /* +0x90 */
    u8  pad09C[0xA0 - 0x9C];
    f32 f0A0[4];                        /* +0xA0 */
    f32 f0B0[4];                        /* +0xB0 */
    u8  pad0C0[0x870 - 0xC0];
    P  *f870;
    VE *f874;
    u8  pad878[0x5D98 - 0x878];
    f32 f5D98;
};

extern "C" VE *ObjRecGetLiveObject_1c3bc0(P *p, s32 n);

extern "C" void insect_InsectBattleCamInit_4f3390(S *s)
{
    P *p;
    VE *e;
    s32 i;
    f32 t;
    f32 u;

    p = s->f870;
    if (p != 0) {
        s->f874 = ObjRecGetLiveObject_1c3bc0(p, p->f4344);
        e = s->f874;
        if (e != 0) {
            e->s39(s);
            s->f874->s40(s->f010);
            s->f000[0] = 0.0f;
            s->f000[1] = 30.0f;
            s->f000[2] = 35.0f;
            s->f010[0] = 0.0f;
            s->f010[1] = 25.0f;
            s->f010[2] = 0.0f;
            for (i = 0; i < 3; i++) {
                s->f040[i] = 0.0f;
                s->f050[i] = 0.0f;
                t = s->f000[i];
                s->f080[i] = t;
                s->f020[i] = t;
                u = s->f010[i];
                s->f090[i] = u;
                s->f030[i] = u;
            }
            s->f5D98 = 0.0f;
            for (i = 0; i < 4; i++) {
                s->f0A0[i] = 0.0f;
                s->f0B0[i] = 0.0f;
            }
        }
    }
}
