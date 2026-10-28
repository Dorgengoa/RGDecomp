#ifndef EEKERNEL_H
#define EEKERNEL_H

/* SDK kernel macros, modelled on Sony's eekernel.h.
 * Permitted by the user ruling of 2026-10-04 ("spirit of a full decomp"):
 * privileged/barrier tails that were Sony SDK header macros in the original
 * source may be written as the SDK macro from this header ONLY.
 * No other asm may be added here (no VU0 ops, no hand-scheduled code).
 *
 * ExitHandler(): interrupt-handler exit, `sync.l; ei` (retail words
 * 0x0000000F 0x42000038; mwcc assembles sync.l as plain `sync`, stype 0).
 */

#define ExitHandler() __asm__ volatile("sync.l; ei")

#endif /* EEKERNEL_H */
