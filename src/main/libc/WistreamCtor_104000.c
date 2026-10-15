#include "types.h"

/* MSL C++ library: basic_istream<wchar_t>::basic_istream(basic_streambuf<wchar_t> *sb)
 *   wide twin of IstreamCtor_103f50: hidden s16 flag (a1) = "construct the virtual base": if set,
 *   vbptr(+0) = this+0x18 and the basic_ios<wchar_t> virtual base gets its ios_base /
 *   basic_ios vtables; then wistream vptr(+0x10), the vbase's wistream vtable and its +0x48
 *   offset word, gcount = 0, basic_ios::init(sb) (IosInit_102a50), tie = 0, fill = L' '.
 * Built as a REAL C++ constructor with exceptions on: only the EH vbase-cleanup action that
 * is conditional on the hidden flag keeps the flag live in $s0 (`move $s0,$a1`) as retail
 * does (libdeasm 103f50 / 104000 NOTES).  config/objfix.txt renames the mangled ctor to
 * WistreamCtor_104000, the vtables to retail D_0046FDA0 / D_0046FDD8 / D_0046FDC0 (+0xC = D_0046FDCC),
 * init to IosInit_102a50 and the basic_ios dtor to WiosDtor_103650, and drops .exceptix/.exception
 * (retail carries no EH table for this ctor). */
#pragma cplusplus on
#pragma exceptions on

struct ios_base {
    virtual ~ios_base();
    s32 state_[15];
};

struct basic_wios : ios_base {
    basic_wios() {}
    virtual ~basic_wios();
    void init(void *sb);
    void *tie_;         /* +0x40 */
    s16 fill_;          /* +0x44 */
};

struct basic_wistream : virtual basic_wios {
    s64 gcount_;        /* +0x08 */
    basic_wistream(void *sb);
    virtual ~basic_wistream();
    s32 pad_;           /* +0x14: after the vptr (+0x10), puts the vbase at +0x18 */
};

basic_wistream::basic_wistream(void *sb) : gcount_(0)
{
    basic_wios &ios = *this;    /* reference: no null check, one vbptr load */

    ios.init(sb);
    ios.tie_ = 0;
    ios.fill_ = ' ';
}
