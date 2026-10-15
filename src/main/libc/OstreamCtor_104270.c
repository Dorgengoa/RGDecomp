#include "types.h"

/* MSL C++ library: basic_ostream<char>::basic_ostream(basic_streambuf<char> *sb)
 *   hidden s16 flag (a1) = "construct the virtual base": if set, vbptr(+0) = this+8 and the
 *   basic_ios virtual base gets its ios_base / basic_ios vtables; then ostream vptr(+4),
 *   the vbase's ostream vtable and its +0x48 offset word, basic_ios::init(sb) (IosInit_102a50),
 *   tie = 0, fill = ' '.
 * Built as a REAL C++ constructor with exceptions on: only the EH vbase-cleanup action that
 * is conditional on the hidden flag keeps the flag live in $s0 (`move $s0,$a1`) as retail
 * does (libdeasm 103f50 NOTES).  config/objfix.txt renames the mangled ctor to OstreamCtor_104270,
 * the vtables to retail D_0046FDA0 / D_0046FEA8 / D_0046FEC0 (+0xC = D_0046FECC), init to
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

struct basic_ostream : virtual basic_ios {
    basic_ostream(void *sb);
    virtual ~basic_ostream();
};

basic_ostream::basic_ostream(void *sb)
{
    basic_ios &ios = *this;     /* reference: no null check, one vbptr load */

    ios.init(sb);
    ios.tie_ = 0;
    ios.fill_ = ' ';
}
