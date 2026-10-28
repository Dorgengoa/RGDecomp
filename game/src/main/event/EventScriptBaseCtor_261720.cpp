#include "types.h"

/* A constructor. Retail installs `&D_004714C0` at +0x58, calls ScriptVmCtor_176be0,
   then makes a VIRTUAL call through that same word and returns the receiver.
   All three are Metrowerks C++ shapes `EventCastLoadCfg_249b60.cpp` already
   documents: the vptr lands at +0x58 because the padding in front of it is
   declared first, +0x08 is the first slot a virtual can occupy, and a
   constructor returns `this`.

   ⚠ The class is REAL and the vptr store is EXPLICIT, and both halves are
   needed:
     - a plain `struct { void (*fn)(void *); } *vptr` field compiles the call
       to `lw v0 / lw v0 / jalr v0` and misses by three words. Only a virtual
       call gives retail's `lw t9 / lw t9 / jalr t9`.
     - the store cannot be an implicit one. Letting mwcc set the vptr means
       letting it emit its OWN vtable, which is a mangled symbol this image
       does not have and a `.data` section the link refuses. Writing through
       the cast names retail's table and emits nothing but the three words.
     - and it is declared as an INCOMPLETE ARRAY, not a pointer. `extern const
       void *D_004714C0` is a four-byte object, so mwcc reaches it through
       $gp in ONE instruction and the function comes out a word short; an
       array of unknown size cannot live in small data and gets retail's
       `lui %hi` / `addiu %lo` pair. This is the recorded `%gp_rel` vs
       `%hi`/`%lo` switch, and the lever here is the SIZE, not the `const`. */

class Obj00261720 {
    u8 pad00[0x58];
public:
    /* vtable +0x08, the first slot a virtual can occupy */
    VC_VPTR_MEMBER; void fn08() { VCM0(void, 0x8); }
};

extern "C" {
extern u8 D_004714C0[];
extern void ScriptVmCtor_176be0(Obj00261720 *self);
}

extern "C" Obj00261720 *EventScriptBaseCtor_261720(Obj00261720 *self)
{
    *(const u8 **)((u8 *)self + 0x58) = D_004714C0;
    ScriptVmCtor_176be0(self);
    self->fn08();
    return self;
}
