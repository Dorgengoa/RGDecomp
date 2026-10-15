#include "types.h"

/*
 * Not a function: one VU1 microinstruction inside the VIF MPG packet that
 * starts at D_00436CB0 (DMAtag ret qwc 0x2C, then VIFcode 0x4A570064 =
 * MPG 0x57 instructions to micro address 0x64; VuMicrocodeTableInitMaybe_152830 stores the
 * packet address in its VU1 microprogram table).
 * This is instruction 8 of that upload, VU1 micro address 0x6C:
 *   lower  0x09070057  ilw.x vi07, 0x57(vi00)
 *   upper  0x000002FF  nop
 * The disassembler read the lower word as an EE `j 0x41C015C`; nothing in
 * MAIN references this address. Kept in .text, where retail has it.
 */
const u32 VuMicrocodeData_436d00[2] __attribute__((section(".text"))) = {
    0x09070057, /* lower: ilw.x vi07, 0x57(vi00) */
    0x000002FF, /* upper: nop */
};
