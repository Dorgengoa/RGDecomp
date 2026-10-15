#include "types.h"

/* MSL C++ library: virtual-base "this"-adjustor thunk for basic_ostream<wchar_t>'s
 * destructor, the dtor slot of the basic_ios-in-basic_wostream vtable D_0046FDFC.
 * Entered with `this` = the basic_wios virtual base (+8); it adds the vbase's
 * +0x48 offset word, subtracts 8 and tail-jumps to ~basic_wostream
 * (WostreamDtor_103510).  mwcc emits such a thunk (@8@72@__dt__14basic_wostreamFv) with
 * the class vtable, in the TU that defines the class's key function (first
 * non-inline virtual), so key_fn below exists only to make this TU the vtable's
 * home; the dtor itself is only declared.  config/objfix.txt drops key_fn's
 * .text (dropfn) and the .vtables (retail vtables are data2c units), renames the
 * thunk to WostreamVirtualDtorThunk_106810 (globalized) and the dtor to WostreamDtor_103510
 * (libdeasm 106810 / 1067f0 NOTES). */
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

struct basic_wostream : virtual basic_wios {  /* vbptr +0, vptr +4, vbase +8 */
    virtual void key_fn();
    virtual ~basic_wostream();
};

void basic_wostream::key_fn()
{
}
