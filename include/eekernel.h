#ifndef EEKERNEL_H
#define EEKERNEL_H

/* SDK kernel macros, modelled on Sony's eekernel.h.
 * Permitted by the user ruling of 2026-10-04 ("spirit of a full decomp"):
 * privileged/barrier tails that were Sony SDK header macros in the original
 * source may be written as the SDK macro from this header ONLY.
 * User exception 2026-10-14: narrow CP0 Wired read/write, CP0 TLB register
 * writes, sync.p and tlbwi macros are also permitted. Keep all surrounding
 * validation, arithmetic and control flow in C; use the shortest privileged
 * spans. Evidence: build/libdeasm/446470/NOTES.md.
 * User exception 2026-10-14: standalone sync via SyncLoad is permitted.
 * User exception 2026-10-14: GetGlobalPointer may retain the original gp read.
 * No other asm may be added here (no VU0 ops, no hand-scheduled C logic).
 *
 * ExitHandler(): interrupt-handler exit, `sync.l; ei` (retail words
 * 0x0000000F 0x42000038; mwcc assembles sync.l as plain `sync`, stype 0).
 */

/* Standalone load barrier approved 2026-10-14; same original sync opcode.
 * C-emitter and matching evidence: build/libdeasm/4473a0d/NOTES.md. */
#ifdef __MWERKS__
#define SyncLoad() asm volatile { sync }
#else
#define SyncLoad() __asm__ volatile("sync")
#endif

/* Original gp read approved 2026-10-14; output register is compiler allocated.
 * Exact scheduling evidence: build/libdeasm/447588j/NOTES.md. */
#define GetGlobalPointer(value) __asm__ volatile("daddu %0,$28,$0" : "=r" (value))

#define ExitHandler() __asm__ volatile("sync.l; ei")

/* Narrow CP0/TLB operations approved 2026-10-14.
 * No C emitter: build/libdeasm/446470/NOTES.md. Arithmetic stays in C.
 * GCC register operands let the compiler allocate all general registers. */
#define GetWired(value) __asm__ volatile("mfc0 %0,$6" : "=r" (value))
#define SetWired(value) __asm__ volatile("mtc0 %0,$6" : : "r" (value))
#define SetTLBIndex(value) __asm__ volatile("mtc0 %0,$0" : : "r" (value))
#define SetTLBPageMask(value) __asm__ volatile("mtc0 %0,$5" : : "r" (value))
#define SetTLBEntryHi(value) __asm__ volatile("mtc0 %0,$10" : : "r" (value))
#define SetTLBEntryLo0(value) __asm__ volatile("mtc0 %0,$2" : : "r" (value))
#define SetTLBEntryLo1(value) __asm__ volatile("mtc0 %0,$3" : : "r" (value))
#define SyncPipeline() __asm__ volatile("sync.p" : : : "memory")
#define WriteTLBIndexed() __asm__ volatile("tlbwi" : : : "memory")

/* Contiguous privileged-only TLB write spans; same approval/evidence above.
 * Clear accepts literal zero operands; Write preserves register operands. */
#define ClearTLBEntry(index, hi) __asm__ volatile("mtc0 %0,$0; mtc0 $0,$5; mtc0 %1,$10; mtc0 $0,$2; mtc0 $0,$3; sync.p; tlbwi; sync.p" : : "r" (index), "r" (hi) : "memory")
#define WriteTLBEntry(index, mask, hi, lo0, lo1) __asm__ volatile("mtc0 %0,$0; mtc0 %1,$5; mtc0 %2,$10; mtc0 %3,$2; mtc0 %4,$3; sync.p; tlbwi; sync.p" : : "r" (index), "r" (mask), "r" (hi), "r" (lo0), "r" (lo1) : "memory")

/* TLB fields after a separate SetTLBIndex; privileged operations only.
 * Matching lifetime evidence: build/libdeasm/446470d/NOTES.md. */
#define WriteTLBFields(mask,hi,lo0,lo1) __asm__ volatile("mtc0 %0,$5; mtc0 %1,$10; mtc0 %2,$2; mtc0 %3,$3; sync.p; tlbwi; sync.p" : : "r" (mask), "r" (hi), "r" (lo0), "r" (lo1) : "memory")

#endif /* EEKERNEL_H */
