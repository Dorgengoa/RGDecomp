#include "types.h"

/* MSL C++ library: basic_ostream<char>::flush()
 *   sentry s(*this) (OstreamSentryCtor_106230; {ok, b1, os} at fp+0x78), s.b1 = 1;
 *   if (rdbuf()) { try { if (rdbuf()->pubsync() == -1) failed } catch (...) { setstate(badbit),
 *   rethrow if exceptions() & badbit }; if (failed) setstate(badbit) -> inline basic_ios::clear:
 *   throw ios_base::failure("ios_base failure in clear") (D_004556F0) }; then the inlined
 *   ~sentry tail: if (good-ish && (flags() & unitbuf) && !s.b1) flush(s.os) (recursive).
 * Built as C++ with exceptions on (try/catch = fp frame, sp save fp+0x64, CatchInfo fp+0x50);
 * the ~RcPtr() declaration gives the EH cleanup that homes &failure/&msg in $s2/$s0 as retail.
 * `#pragma opt_dead_assignments off` gives retail's `and $v0,$v0,$v1` operand order in clear().
 * The sentry tail is written out (no ~Sentry) so no weak out-of-line dtors are emitted.
 * config/objfix.txt: drop .exceptix/.exception (retail has no EH table), redirect the throw
 * type string to D_00455A60, rename __vt__7Failure -> D_0046FDB0, __dt__7FailureFv ->
 * IosBaseFailureDtor_1028f0, __dt__5RcPtrFv -> SharedArrayPtrDtor_102ab0, __dt__9ExceptionFv -> ExceptionDtor_1008a0.
 * Same object at -O4 and -O4,p (no toolchain row).  libdeasm 1040b0. */

#pragma cplusplus on
#pragma exceptions on
#pragma opt_dead_assignments off

extern "C" void SharedArrayPtrCtor_102b30(void *rc, void *p);
extern "C" void *OperatorNewArray_100900(u32 n);
extern "C" u32 strlen(const char *);
extern "C" char *strcpy(char *, const char *);
extern "C" char D_004556F0[];

struct RcPtr {
    char *ptr;
    s32 *count;
    RcPtr(char *p) { SharedArrayPtrCtor_102b30(this, p); }
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

struct Streambuf {
    virtual ~Streambuf();
    virtual void setbuf();
    virtual void seekoff();
    virtual void seekpos();
    virtual s32 sync();
};

struct Ios {
    void *vt;
    s32 pad04[7];
    Streambuf *sb_;     /* +0x20 */
    s32 pad24[5];
    u16 flags_;         /* +0x38 */
    u8 state_;          /* +0x3A */
    u8 except_;         /* +0x3B */
    u8 rdstate() { return state_; }
    u8 exceptions() { return except_; }
    u16 flags() { return flags_; }
};

struct Ostream {
    Ios *vb;
};

extern "C" void OstreamSentryCtor_106230(void *s, Ostream *os);
extern "C" Ostream *OstreamFlush_1040b0(Ostream *self);

struct Sentry {
    u8 ok_;
    u8 b1_;
    Ostream *os_;
    Sentry(Ostream *os) { OstreamSentryCtor_106230(this, os); }
};

extern "C" Ostream *OstreamFlush_1040b0(Ostream *self)
{
    Sentry s(self);

    s.b1_ = 1;
    if (self->vb->sb_) {
        bool failed = false;
        try {
            if (self->vb->sb_->sync() == -1) failed = true;
        } catch (...) {
            self->vb->state_ |= 1;
            if (self->vb->except_ & 1) throw;
        }
        if (failed) {
            Ios *ios = self->vb;
            ios->state_ |= 1;
            if (!ios->sb_) ios->state_ |= 1;
            if ((u8)(ios->rdstate() & ios->exceptions())) throw Failure(D_004556F0);
        }
    }
    {
        Ios *ios = s.os_->vb;
        if (!(u8)(ios->rdstate() & 5) && (u16)(ios->flags() & 0x2000) && !s.b1_) OstreamFlush_1040b0(s.os_);
    }
    return self;
}
