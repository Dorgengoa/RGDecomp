#include "types.h"

/* Static-destructor thunk: the last reference drops the module's globals.
   The four `jalr $25` sites are C++ virtual destructor calls -- vptr offset
   read straight off `lw $25,K($obj)`, slot 0x8 = virtual #0. */

class VE_FUN_00103420_A {
public:
    u8 pad000[0x10];
    virtual void *dt(s16);
};

class VE_FUN_00103420_B {
public:
    u8 pad000[0x4];
    virtual void *dt(s16);
};

extern "C" {
extern struct { s32 v; u8 pad004[0xC]; } D_004853E0;
extern u8 D_00485580[];
extern u8 D_004855F0[];
extern u8 D_004856B0[];
extern u8 D_00485650[];
extern void WOstreamFlush_104320(void *);
extern void OperatorDelete_100840(void *);
}

extern "C" void *WIosBaseInitDtor_103420(void *o, s16 flag)
{
    if (o != 0) {
        D_004853E0.v -= 1;
        if (D_004853E0.v == 0) {
            WOstreamFlush_104320(D_004855F0);
            WOstreamFlush_104320(D_004856B0);
            WOstreamFlush_104320(D_00485650);
            ((VE_FUN_00103420_A *)D_00485580)->dt(-1);
            ((VE_FUN_00103420_B *)D_004855F0)->dt(-1);
            ((VE_FUN_00103420_B *)D_004856B0)->dt(-1);
            ((VE_FUN_00103420_B *)D_00485650)->dt(-1);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
