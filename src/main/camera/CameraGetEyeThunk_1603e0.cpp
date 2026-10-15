#include "types.h"

/* CameraGetEyeThunk_1603e0 -- ONE 52-byte symbol spanning THREE entry points.
 *   0x001603E0  4 w: virtual tail call, vptr at 0xC0, slot 0xA0 (index 38)
 *   0x001603F0  4 w: virtual tail call, vptr at 0xC0, slot 0x9C (index 37)
 *   0x00160400  5 w: tail call VecSub_13be40(b, &a[0x50], &a[0x60])
 */

struct VC0B { unsigned char pad[0xC0]; };
class VC0 : public VC0B {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
};

extern "C" void VecSub_13be40(void *, void *, void *);

extern "C" void CameraGetEyeThunk_1603e0(VC0 *o) { o->v38(); }

extern "C" void func_001603E0_e1(VC0 *o) { o->v37(); }

extern "C" void func_001603E0_e2(unsigned char *a, void *b)
{
    VecSub_13be40(b, a + 0x50, a + 0x60);
}
