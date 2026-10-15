/* `opt_rebuildlogicals off`: without it mwcc rebuilds the guarded flag
   assignment into a computed boolean (slt/sltu) and loses retail's
   branchy `flag = 0 / flag = 1` form. Measured on ModelMeshUpdateBoundsMaybe_150170: 8 other
   opt_* pragmas and volatile/s32 on the flag are all ONE object. */
#pragma opt_rebuildlogicals off
#include "types.h"

/* Returns a 16-byte {s64,s32} record through the hidden sret pointer in $4;
   arg2 is a 16-byte struct passed BY VALUE (the address arrives in $6 and the
   callee copies it - that is the ld/ld/sd/sd prologue).
   The double `andi 0xFF` says the flag parameter is u8 and the masked value is
   narrowed again.  Real DATA MEMBERS (not `*(s32*)((u8*)o + K)`) are what stop
   mwcc CSEing `o + 0x1C` into its own callee-saved register.
   The vptr is at offset 0 (V_vtable), slot 0x34 = the 12th declared virtual
   (slot = 8 + 4*N). */

class Obj {
public:
    virtual void vs0();
    virtual void vs1();
    virtual void vs2();
    virtual void vs3();
    virtual void vs4();
    virtual void vs5();
    virtual void vs6();
    virtual void vs7();
    virtual void vs8();
    virtual void vs9();
    virtual void vs10();
    virtual s32 f34(s32);
    /* 0x04 */ s32 m04;
    /* 0x08 */ s32 m08;
    /* 0x0C */ s32 m0C;
    /* 0x10 */ u32 m10;
    /* 0x14 */ u32 m14;
    /* 0x18 */ s32 m18;
    /* 0x1C */ s32 m1C;
    /* 0x20 */ u8  pad20[0x44];
    /* 0xXX */ u8  mFLAG;
};

typedef struct { s64 lo; s64 hi; } Val16;
typedef struct { s64 a; s32 b; } Ret;

extern "C" s32 Fseek_12fe60(s32, s64, s32);

extern "C" void WFilebufSeekpos_105140(Ret *out, Obj *o, Val16 v, u8 flags)
{
    bool busy;   /* M1: bool was NOT in the nine measured width arms */

    if (o->m1C == 0 || (u8)(flags & 0x18) == 0) {
        out->a = -1;
        out->b = 0;
        return;
    }

    busy = false;
    if (o->m14 > o->m10 && o->f34(-1) == -1) {
        busy = true;
    }
    if (busy) {
        out->a = -1;
        out->b = 0;
        return;
    }

    if (Fseek_12fe60(o->m1C, v.lo, 0) != 0) {
        out->a = -1;
        out->b = 0;
        return;
    }

    o->m04 = 0;
    o->m08 = 0;
    o->m0C = 0;
    o->m14 = 0;
    o->m10 = 0;
    o->m18 = 0;
    o->mFLAG = 0;
    out->a = v.lo;
    out->b = (s32)v.hi;
}
