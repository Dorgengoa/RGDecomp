#include "types.h"

/* newlib lib/libc/stdlib/assert. Rogue Galaxy compiles its asserts OUT, so
   this is only ever reached from library code -- but it is what names three
   more library entries by inference:

     FiprintfR_12f948  fiprintf
     Abort_12de80  abort
     D_00449858    _impure_ptr, whose +0xC is stderr

   ★ The last of those independently CORROBORATES ScriptVmExec_173b00's own reading of
   D_00449858 as a console pointer whose +0xC is the stream Fprintf_12f9a0 writes
   to -- two subsystems, reached from opposite ends, agreeing on one field.

   STATUS 32.31%, TWO words long (15 against retail's 13), and the whole gap is
   ONE missing optimisation: **retail TAIL-CALLS abort** --
   `ld $31, 0x0($29)` / `j Abort_12de80` / `addiu $29, $29, 0x10` -- where we
   emit `jal` + `nop` + the full epilogue. Everything else lines up.
   ⚠ Measured third session and NOT reached:
     - `#pragma tailcall on` compiles and changes NOTHING (15 words either way),
       so either it is already the default or something else blocks it;
     - `return Abort_12de80();` does not compile -- mwcc's C mode rejects a
       void expression in a `return`, so the usual way of putting a call in
       tail position is unavailable here.
   ⇒ The next thing to try is C++ mode, where `return f();` from a `void`
   function is legal, or finding what makes mwcc tail-call at all -- check
   whether ANY object in the tree emits a `j` to an external symbol first,
   because if none does the pragma is inert and this is a dead end.
   ⚠ Low value either way: RG compiles its asserts out, so this function is
   never reached. Its worth was the three names above, and those are banked. */

typedef struct Reent {
    u8 pad00[0xC];
    void *stderr_;     /* +0x0C */
} Reent;

extern Reent *const D_00449858;
extern const char D_00457E60[];
extern s32 FiprintfR_12f948(void *stream, const char *fmt, ...);   /* fiprintf */
extern void Abort_12de80(void);                                /* abort */

asm void __assert(const char *file, s32 line, const char *failedexpr)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, 0x45;
    sd         $31, 0x0($29);
    daddu      $8, $5, $0;
    lw         $3, -0x67A8($2);
    daddu      $7, $4, $0;
    lui        $5, 0x45;
    lw         $4, 0xC($3);
    jal        FiprintfR_12f948;
    addiu     $5, $5, 0x7E60;
    ld         $31, 0x0($29);
    j          Abort_12de80;
    addiu     $29, $29, 0x10;
}
