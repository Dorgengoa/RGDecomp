#include "types.h"

/* MSL C++ library: virtual-base "this"-adjustor thunk for basic_istream<wchar_t>'s
 * destructor, the dtor slot of the basic_wios-in-basic_wistream vtable.
 * Entered with `this` = the basic_wios virtual base (+0x18); it adds the vbase's
 * +0x48 offset word, subtracts 0x18 and tail-jumps to ~basic_wistream
 * (WistreamDtor_1035b0).  mwcc emits such a thunk (@24@72@__dt__14basic_wistreamFv) with
 * the class vtable, in the TU that defines the class's key function (first
 * non-inline virtual), so key_fn below exists only to make this TU the vtable's
 * home; the dtor itself is only declared.  config/objfix.txt drops key_fn's
 * .text (dropfn) and the .vtables (retail vtables are data2c units), renames the
 * thunk to WistreamVirtualDtorThunk_106820 (globalized) and the dtor to WistreamDtor_1035b0
 * (libdeasm 106820 / 106800 / 1067f0 NOTES). */
#pragma cplusplus on

struct ios_base {
    virtual ~ios_base();
    s32 state_[15];
};

struct basic_wios : ios_base {
    virtual ~basic_wios();
    void *tie_;         /* +0x40 */
    s16 fill_;          /* +0x44; the vbase offset word follows at +0x48 */
};

struct basic_wistream : virtual basic_wios {  /* vbptr +0, gcount +8, vptr +0x10, vbase +0x18 */
    s64 gcount_;        /* +0x08 */
    virtual void key_fn();
    virtual ~basic_wistream();
    s32 pad_;           /* +0x14: after the vptr (+0x10), puts the vbase at +0x18 */
};

void basic_wistream::key_fn()
{
}
