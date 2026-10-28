/* rg-override: replaces game/src/main/libc/OstreamWriteBool_1b2710.cpp sha256 23912f0309aa9be6a620354cfcff4488fa5265bb65048b6130332df71ee4c666
 * why: the MWCC view `Iter NumPutBool_1b2860(Iter, Ios *, s8, s32)` returns the iterator
 *      through a hidden pointer in $a0 (retail: `addiu $4, $29, 0x3C`, result read back from
 *      sp+0x3C), so the definition NumPutBool_1b2860(s32 out, s32 it, A2 *, s32 fill, s32 v)
 *      takes 5 arguments; on i686 the 4-argument call lost the value (the callee read a
 *      stale stack word for `v`) and passed the stream buffer as the out pointer.  Fix: the
 *      explicit out pointer (protos `manual-decl` count 4 vs 5, ret Iter vs int;
 *      tools/bringup/protos_deficits.py, BRINGUP-HISTORY 2026-10-25 (sweep)). */
#pragma opt_propagation off
#include "types.h"

struct Ios {
    u8 pad0[0x20];
    s32 rdbuf;
    u8 pad24[0x14];
    u16 flags;
    u8 state;
    u8 except;
    u8 pad3C[8];
    s8 fill;
};

struct Ostream {
    Ios *ios;
};

struct Iter {
    s32 sb;
    bool failed() { return sb == 0; }
};

struct Sentry {
    u8 ok;
    u8 b;
    u8 pad[2];
    Ostream *os;
    s32 w8;
};


struct Exc {
    u8 pad[0xC];
    s32 xC;
};

extern "C" {
void OstreamFlush_1040b0(Ostream *);
void OstreamSentryCtor_106230(Sentry *, Ostream *);
void Abort_12de80();
void Fprintf_12f9a0(s32, s32 *);
int NumPutBool_1b2860(Iter *, s32, Ios *, s32, s32); /* rg-override: explicit out pointer */
}
extern "C" Exc *D_00449858[];
extern "C" s32 D_004556F0[];

static inline void Clear(Ios *ios, u64 st)
{
    u8 e;

    ios->state = st;
    if (ios->rdbuf == 0) {
        ios->state |= 1;
    }
    e = ios->except;
    if ((u8)(ios->state & e)) {
        Fprintf_12f9a0(D_00449858[0]->xC, D_004556F0);
        Abort_12de80();
    }
}

static inline void SetState(Ios *ios, u64 st)
{
    u8 s;
    u64 t;

    t = ios->state;
    s = st;
    Clear(ios, t | s);
}

extern "C" Ostream *OstreamWriteBool_1b2710(Ostream *os, s32 n)
{
    Sentry s __attribute__((aligned(16)));
    bool failed;
    Ios *ios;

    OstreamSentryCtor_106230(&s, os);
    if (s.ok) {
        ios = os->ios;
        {
            s32 r = ios->rdbuf;
            s8 f = ios->fill;
            s.w8 = r;
            { /* rg-override: the out pointer retail passed in $a0 */
                Iter res;
                NumPutBool_1b2860(&res, s.w8, ios, f, n);
                failed = res.failed();
            }
        }
        if (failed) {
            SetState(os->ios, 5);
        }
    }
    if ((u8)(s.os->ios->state & 5) == 0 && (u16)(s.os->ios->flags & 0x2000) != 0 && s.b == 0) {
        OstreamFlush_1040b0(s.os);
    }
    return os;
}
