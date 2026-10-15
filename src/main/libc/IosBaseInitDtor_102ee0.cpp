#include "types.h"

/* Static-destructor thunk: the last reference drops the module's globals.
   The four `jalr $25` sites are C++ virtual destructor calls -- vptr offset
   read straight off `lw $25,K($obj)`, slot 0x8 = virtual #0. */

class VE_FUN_00102ee0_A {
public:
    u8 pad000[0x10];
    virtual void *dt(s16);
};

class VE_FUN_00102ee0_B {
public:
    u8 pad000[0x4];
    virtual void *dt(s16);
};

extern "C" {
extern struct { s32 v; u8 pad004[0xC]; } D_004853D8;
extern u8 D_004853F0[];
extern u8 D_00485460[];
extern u8 D_00485520[];
extern u8 D_004854C0[];
extern void OstreamFlush_1040b0(void *);
extern void OperatorDelete_100840(void *);
}

extern "C" void *IosBaseInitDtor_102ee0(void *o, s16 flag)
{
    if (o != 0) {
        D_004853D8.v -= 1;
        if (D_004853D8.v == 0) {
            OstreamFlush_1040b0(D_00485460);
            OstreamFlush_1040b0(D_00485520);
            OstreamFlush_1040b0(D_004854C0);
            ((VE_FUN_00102ee0_A *)D_004853F0)->dt(-1);
            ((VE_FUN_00102ee0_B *)D_00485460)->dt(-1);
            ((VE_FUN_00102ee0_B *)D_00485520)->dt(-1);
            ((VE_FUN_00102ee0_B *)D_004854C0)->dt(-1);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
