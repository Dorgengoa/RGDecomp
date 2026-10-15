#include "types.h"

/* MSL C++ library: basic_ostream<char>::sentry::sentry(basic_ostream &os), C-linkage form
 * (called by basic_ostream::flush OstreamFlush_1040b0; sentry {bool ok; bool b1; ostream *os}).
 *   ok = b1 = false; os_ = &os;
 *   try { if (good()) { if (tie()) tie()->flush(); }  if (good()) ok = true;
 *         else setstate(failbit) -> inline clear: rdbuf()==0 adds badbit, throw
 *         ios_base::failure("...") (D_004556F0) when (state & exceptions()) }
 *   catch (...) { if (!(state & failbit)) state |= badbit; if (state & exceptions()) throw; }
 * Built as C++ with exceptions on (try/catch = fp frame, CatchInfo fp+0x90, sp save fp+0xA4).
 * `#pragma inline_depth(8)` inlines the RcPtr ctor (SharedArrayPtrCtor_102b30 body, own try/catch) into
 * both throw sites as retail does.  setstate is written out (no clear() call: avoids an andi).
 * The catch test reads state through a const-reference accessor so it is not CSE'd with the
 * `|= badbit` load (retail reloads it); the rethrow test loads state into a local first.
 * config/objfix.txt: drop .exceptix/.exception (retail has no EH table), redirect the throw
 * type string to D_00455A60, rename __vt__7Failure -> D_0046FDB0, __dt__7FailureFv ->
 * IosBaseFailureDtor_1028f0 (+ RcPtr/exception dtors as in 1040b0).  libdeasm 106230. */

#pragma cplusplus on
#pragma exceptions on
#pragma opt_dead_assignments off
#pragma inline_depth(8)

extern "C" void *OperatorNewArray_100900(u32 n);
extern "C" void *OperatorNew_100990(u32 n);
extern "C" void OperatorDeleteArray_100820(void *p);
extern "C" u32 strlen(const char *);
extern "C" char *strcpy(char *, const char *);
extern "C" char D_004556F0[];

struct RcPtr {
    char *ptr;
    s32 *count;
    RcPtr(char *p) : ptr(p), count(0) {
        try {
            if (ptr) {
                s32 *c = (s32 *)OperatorNew_100990(4);
                if (c) *c = 1;
                count = c;
            }
        } catch (...) {
            OperatorDeleteArray_100820(ptr);
            throw;
        }
    }
    ~RcPtr();
};

struct String {
    RcPtr p_;
    String(const char *s) : p_((char *)OperatorNewArray_100900(strlen(s) + 1)) { strcpy(p_.ptr, s); }
    ~String();
};

struct Exception {
    Exception() {}
    virtual ~Exception();
};

struct Failure : Exception {
    String msg_;
    Failure(const char *s) : msg_(s) {}
    virtual ~Failure();
};

struct Ostream;

struct Ios {
    void *vt;
    s32 pad04[7];
    void *sb_;          /* +0x20 */
    s32 pad24[5];
    u16 flags_;         /* +0x38 */
    u8 state_;          /* +0x3A */
    u8 except_;         /* +0x3B */
    s32 pad3c;
    Ostream *tie_;      /* +0x40 */
    u8 rdstate() { return state_; }
    const u8 &rstate() const { return state_; }
    u8 exceptions() { return except_; }
    void setstate(u32 s) {
        state_ |= s;
        if (!sb_) state_ |= 1;
        if ((u8)(rdstate() & exceptions())) throw Failure(D_004556F0);
    }
};

struct Ostream {
    Ios *vb;
};

extern "C" Ostream *OstreamFlush_1040b0(Ostream *self);

struct Sentry {
    u8 ok_;
    u8 b1_;
    Ostream *os_;
};

extern "C" Sentry *OstreamSentryCtor_106230(Sentry *self, Ostream *os)
{
    self->ok_ = 0;
    self->b1_ = 0;
    self->os_ = os;
    try {
        if (!self->os_->vb->state_) {
            if (self->os_->vb->tie_) OstreamFlush_1040b0(self->os_->vb->tie_);
            if (!self->os_->vb->state_) self->ok_ = 1;
            else self->os_->vb->setstate(4);
        } else {
            self->os_->vb->setstate(4);
        }
    } catch (...) {
        {
            Ios *ios = self->os_->vb;
            if (!(u8)(ios->rstate() & 4)) ios->state_ |= 1;
        }
        {
            Ios *ios = self->os_->vb;
            u8 st = ios->state_;
            if ((u8)(ios->except_ & st)) throw;
        }
    }
    return self;
}
