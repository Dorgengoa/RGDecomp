#pragma opt_propagation off
#include "types.h"

struct Ios {
    u8 pad0[0x20];
    s32 rdbuf;
    u8 pad24[0x16];
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
s32 strlen(const char *);
void OstreamFlush_1040b0(Ostream *);
void OstreamSentryCtor_106230(Sentry *, Ostream *);
void Abort_12de80();
void Fprintf_12f9a0(s32, s32 *);
Iter NumPutPadOutput_1a4610(s32, Ios *, s8, s32, s32, const char *, s32);
s32 IosFail_1a1f40(Ios *);
void *IosGetFlags_1a1f30(Ios *);
s32 IosFlagsAnd_1a1f10(void *, s32);
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

extern "C" Ostream *OstreamWriteCStr_1a1dd0(Ostream *os, const char *str)
{
    Sentry s;
    bool failed;
    Ios *ios;
    s32 len;

    OstreamSentryCtor_106230(&s, os);
    if (s.ok) {
        len = strlen(str);
        ios = os->ios;
        {
            s32 r = ios->rdbuf;
            s8 f = ios->fill;
            s.w8 = r;
            failed = NumPutPadOutput_1a4610(r, ios, f, 0, 0, str, len).failed();
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
