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
s32 IosFlagsAnd_1a1f10(s32, s32);
s32 IosGetFlags_1a1f30(Ios *);
s32 IosFail_1a1f40(Ios *);
Iter NumPutUnsigned_1a4290(s32, Ios *, s8, u64);
Iter NumPutSigned_1a4300(s32, Ios *, s8, s64);
}
extern Exc *D_00449858[];
extern s32 D_004556F0[];

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

static inline s32 Keep(s32 r)
{
    volatile s32 w;
    w = r;
    return r;
}

static inline bool Put2(s32 r, Ios *io, s8 fl, s64 n)
{
    return NumPutSigned_1a4300(Keep(r), io, fl, n).failed();
}

extern "C" Ostream *OstreamWriteInt_1a1f60(Ostream *os, s32 n)
{
    Sentry s;
    bool failed;
    Ios *ios;

    OstreamSentryCtor_106230(&s, os);
    if (s.ok) {
        u16 f;
        ios = os->ios;
        f = ios->flags & 0x4A;
        if (f == 0x40 || f == 8) {
            Ios *io2 = *(Ios *volatile *)&os->ios;
            s32 r = io2->rdbuf;
            s8 fl = io2->fill;
            failed = NumPutUnsigned_1a4290(Keep(r), io2, fl, (u32)n).failed();
        } else {
            s32 r = ios->rdbuf;
            s8 fl = ios->fill;
            failed = Put2(r, ios, fl, n);
        }
        if (failed) {
            SetState(os->ios, 5);
        }
    }
    if (IosFail_1a1f40(s.os->ios) == 0 && IosFlagsAnd_1a1f10(IosGetFlags_1a1f30(s.os->ios), 0x2000) != 0 && s.b == 0) {
        OstreamFlush_1040b0(s.os);
    }
    return os;
}
