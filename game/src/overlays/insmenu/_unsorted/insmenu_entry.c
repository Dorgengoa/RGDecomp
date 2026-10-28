/* insmenu.bin overlay, 0x004E9EC0 -- the entry slot, and it is PADDING:
 * sixteen nops, no prologue, no jr $31, no gp setup, no ctor-table walk.
 * INSMENU.BIN[0x40:0x80] is 64 zero bytes; 0x004E9E80 (the MWo3 load address)
 * + 0x40 header = 0x004E9EC0, so this is simply the first text word after the
 * overlay header.  The listing is byte-identical to title/normal/factory/
 * insect's equivalents.
 *
 * No ordinary C function can produce this -- mwcc emits an epilogue for any
 * function body and an empty body is `jr $31 / nop`.  An `asm` function is the
 * one construct that emits its instructions verbatim with no compiler frame.
 *
 * THIS IS A TRANSCRIPTION, not compiled C.  It makes the image byte-identical
 * and it closes a sized symbol, but it must be counted as a transcription line
 * item and never folded into insmenu's compiled-C count.  Title's overlay had
 * to retract a "100% compiled C" claim for exactly this reason.
 */

asm void insmenu_entry(void)
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
