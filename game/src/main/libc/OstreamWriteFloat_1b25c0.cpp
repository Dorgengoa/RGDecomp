/* PARKED at triage (0 round trips): m2c's draft references `sp54` and
 * `sp51` that are never declared/assigned anywhere in the function body --
 * they must alias the declared `sp5C`/`sp58`/`sp50` locals at different
 * offsets/widths that m2c failed to unify. Needs a raw-asm trace of the
 * stack frame before it's worth compiling. Deferred to preserve lane
 * throughput. See asm/matchings/main/OstreamWriteFloat_1b25c0.s. */
/* s49m: 5 */
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
Iter NumPutDoubleThunk_1b2840(Iter, Ios *, s8, double);
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

extern "C" Ostream *OstreamWriteFloat_1b25c0(Ostream *os, f32 n)
{
    Sentry s __attribute__((aligned(16)));
    bool failed;
    s8 fill;
    Ios *ios;

    OstreamSentryCtor_106230(&s, os);
    if (s.ok) {
        ios = os->ios;
        {
            s32 r = ios->rdbuf;
            fill = ios->fill;
            s.w8 = r;
            failed = NumPutDoubleThunk_1b2840(*(Iter *)&s.w8, ios, fill, n).failed();
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
