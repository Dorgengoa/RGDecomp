/* title.bin overlay, 0x004E9EC0 -- the entry slot, and it is PADDING: sixteen
 * nops, no prologue, no jr $31.  Nothing in the overlay branches here; MWo3
 * dispatches through the export table, not this address.
 *
 * No ordinary C function can produce this -- mwcc emits an epilogue for any
 * function body, and an empty body is `jr $31 / nop` (measured).  An `asm`
 * function is the one construct that emits its instructions VERBATIM with no
 * compiler frame, the same mechanism the main image already ships for the VU0
 * macro-mode units.  Sixteen literal nops survive -O4 unchanged (measured
 * 2026-08-25: .text is exactly 0x40 bytes of 0x00000000).
 *
 * This is a transcription of padding, not a recovered function, and it is
 * counted as such: it closes the 107th of 107 sized symbols.
 */

asm void title_entry(void)
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
