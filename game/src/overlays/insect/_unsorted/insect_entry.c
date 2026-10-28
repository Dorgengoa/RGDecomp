/* insect.bin overlay, 0x004E9EC0 -- the entry slot, and it is PADDING: sixteen
 * nops, no prologue, no jr $31, no gp setup.  0x004E9E80 (the MWo3 load
 * address) + 0x40 header = 0x004E9EC0, so this is simply the first text word
 * after the overlay header.  Byte-identical to title/insmenu's equivalents.
 *
 * No ordinary C function can produce this -- mwcc emits an epilogue for any
 * function body and an empty body is `jr $31 / nop`.  An `asm` function is the
 * one construct that emits its instructions verbatim with no compiler frame.
 *
 * THIS IS A TRANSCRIPTION, not compiled C.  Count it as a transcription line
 * item, never as part of insect's compiled-C count.
 */

asm void insect_entry(void)
{
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
    nop;
}
