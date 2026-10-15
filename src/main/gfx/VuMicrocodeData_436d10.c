#include "types.h"

/*
 * Not a function: one VU1 microinstruction inside the VIF MPG packet that
 * starts at D_00436CB0 (DMAtag ret qwc 0x2C, then VIFcode 0x4A570064 =
 * MPG 0x57 instructions to micro address 0x64; VuMicrocodeTableInitMaybe_152830 stores the
 * packet address in its VU1 microprogram table).
 * This is instruction 10 of that upload, VU1 micro address 0x6E:
 *   lower  0x09044801  ilw.x vi04, 1(vi09)
 *   upper  0x000002FF  nop
 * The disassembler read the lower word as an EE `j 0x4112004`; nothing in
 * MAIN references this address. Kept in .text, where retail has it.
 */
const u32 VuMicrocodeData_436d10[2] __attribute__((section(".text"))) = {
    0x09044801, /* lower: ilw.x vi04, 1(vi09) */
    0x000002FF, /* upper: nop */
};
