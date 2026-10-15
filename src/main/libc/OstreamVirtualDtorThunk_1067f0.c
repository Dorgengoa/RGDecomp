#include "types.h"

/* MSL C++ library: virtual-base "this"-adjustor thunk for basic_ostream<char>'s
 * destructor, the dtor slot of the basic_ios-in-basic_ostream vtable D_0046FECC
 * (offset -8).  Entered with `this` = the basic_ios virtual base; it adds the
 * vbase's +0x48 offset word, subtracts 8 and tail-jumps to ~basic_ostream
 * (OstreamDtor_102fd0).  mwcc emits such a thunk (@8@72@__dt__13basic_ostreamFv) with
 * the class vtable, in the TU that defines the class's key function (first
 * non-inline virtual), so key_fn below exists only to make this TU the vtable's
 * home; the dtor itself is only declared.  config/objfix.txt drops key_fn's
 * .text (dropfn) and the .vtables (retail D_0046FEC0/D_0046FECC are data2c
 * units), renames the thunk to OstreamVirtualDtorThunk_1067f0 (globalized) and the dtor to
 * OstreamDtor_102fd0 (libdeasm 1067f0 NOTES). */
#pragma cplusplus on

struct ios_base {
    virtual ~ios_base();
    s32 state_[15];
};

struct basic_ios : ios_base {
    virtual ~basic_ios();
    void *tie_;         /* +0x40 */
    char fill_;         /* +0x44; the vbase offset word follows at +0x48 */
};

struct basic_ostream : virtual basic_ios {  /* vbptr +0, vptr +4, vbase +8 */
    virtual void key_fn();
    virtual ~basic_ostream();
};

void basic_ostream::key_fn()
{
}
