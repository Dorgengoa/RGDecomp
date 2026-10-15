#include "types.h"

/* MSL C++ library: basic_ostream<wchar_t>::basic_ostream(basic_streambuf<wchar_t> *sb)
 *   wide twin of OstreamCtor_104270: hidden s16 flag (a1) = "construct the virtual base": if set,
 *   vbptr(+0) = this+8 and the basic_ios<wchar_t> virtual base gets its ios_base / basic_ios
 *   vtables; then wostream vptr(+4), the vbase's wostream vtable and its +0x48 offset word,
 *   basic_ios::init(sb) (IosInit_102a50), tie = 0, fill = L' '.
 * Built as a REAL C++ constructor with exceptions on: only the EH vbase-cleanup action that
 * is conditional on the hidden flag keeps the flag live in $s0 (`move $s0,$a1`) as retail
 * does (libdeasm 103f50 / 104270 NOTES).  config/objfix.txt renames the mangled ctor to
 * WostreamCtor_1044e0, the vtables to retail D_0046FDA0 / D_0046FDD8 / D_0046FDF0 (+0xC = D_0046FDFC),
 * init to IosInit_102a50 and the basic_ios<wchar_t> dtor to WiosDtor_103650, and drops
 * .exceptix/.exception (retail carries no EH table for this ctor). */
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

struct basic_wostream : virtual basic_wios {
    basic_wostream(void *sb);
    virtual ~basic_wostream();
};

basic_wostream::basic_wostream(void *sb)
{
    basic_wios &ios = *this;    /* reference: no null check, one vbptr load */

    ios.init(sb);
    ios.tie_ = 0;
    ios.fill_ = ' ';
}
