/* PORT REPLACEMENT for include/eekernel.h (decomp d784320c+): the SDK kernel
 * macros the de-asm'd interrupt handlers end with.  include/ is searched
 * ahead of game/include (docs/PORT-HEADERS.md), so this shadows the decomp's
 * `#define ExitHandler() __asm__ volatile("sync.l; ei")`.
 *
 * ExitHandler(): `sync.l; ei` -> EIntr() (src/sce/kernel: sets the handler's
 * EIE copy, docs/KERNEL.md), what the former overrides of
 * GfxVblankStartHandler_15df20 / Vif1IntcHandler_15e170 /
 * SoundVblankIntrHandler_1bd6f0 / Movie*Handler did by hand. */
#ifndef EEKERNEL_H
#define EEKERNEL_H

#ifdef __cplusplus
extern "C" {
#endif
int EIntr(void);
#ifdef __cplusplus
}
#endif

#define ExitHandler() ((void)EIntr())

#endif /* EEKERNEL_H */
