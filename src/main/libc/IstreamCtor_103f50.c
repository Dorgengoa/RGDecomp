#include "types.h"

/* MSL C++ library: basic_istream<char>::basic_istream(basic_streambuf<char> *sb)
 *   hidden s16 flag (a1) = "construct the virtual base": if set, vbptr(+0) = this+0x18 and the
 *   basic_ios virtual base gets its ios_base / basic_ios vtables; then istream vptr(+0x10),
 *   the vbase's istream vtable and its +0x48 offset word, gcount = 0, basic_ios::init(sb)
 *   (IosInit_102a50), tie = 0, fill = ' '.
 * Built as a REAL C++ constructor with exceptions on: only the EH vbase-cleanup action that
 * is conditional on the hidden flag keeps the flag live in $s0 (`move $s0,$a1`) as retail
 * does (libdeasm 103f50 NOTES).  config/objfix.txt renames the mangled ctor to IstreamCtor_103f50,
 * the vtables to retail D_0046FDA0 / D_0046FEA8 / D_0046FE90 (+0xC = D_0046FE9C), init to
 * IosInit_102a50 and the basic_ios dtor to IosDtor_103700, and drops .exceptix/.exception
 * (retail carries no EH table for this ctor). */
#pragma cplusplus on
#pragma exceptions on

struct ios_base {
    virtual ~ios_base();
    s32 state_[15];
};

struct basic_ios : ios_base {
    basic_ios() {}
    virtual ~basic_ios();
    void init(void *sb);
    void *tie_;         /* +0x40 */
    char fill_;         /* +0x44 */
};

struct basic_istream : virtual basic_ios {
    s64 gcount_;        /* +0x08 */
    basic_istream(void *sb);
    virtual ~basic_istream();
    s32 pad_;           /* +0x14: after the vptr (+0x10), puts the vbase at +0x18 */
};

basic_istream::basic_istream(void *sb) : gcount_(0)
{
    basic_ios &ios = *this;     /* reference: no null check, one vbptr load */

    ios.init(sb);
    ios.tie_ = 0;
    ios.fill_ = ' ';
}
