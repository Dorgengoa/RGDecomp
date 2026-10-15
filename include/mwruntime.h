#ifndef MWRUNTIME_H
#define MWRUNTIME_H

/* mwruntime.h -- Metrowerks C++ runtime routines, modelled on MW's own
 * runtime sources (ptmf.c ships these as hand-written asm).
 *
 * Permitted by the user ruling of 2026-10-12 (build/libdeasm/BRIEF.md):
 * ONLY MW runtime routines with a PROVEN missing C emitter (two failed
 * de-asm lanes with proof NOTES). One macro per routine, named after the
 * MW routine, citing the unemittable ops and the proof NOTES paths.
 *
 * Users:
 *   __PTMF_SCALL   PtmfScall_100e70 (__ptmf_scall)
 *   __TRANSFER_CONTROL   EhRestoreContextAndJump_102550 (TransferControl)
 *   __THROW   ThrowException_1025c0 (__throw)
 */

/* __PTMF_SCALL(): __ptmf_scall, pointer-to-member-function call thunk.
 * Input PTMF* in $t9 (compiler-emitted runtime call); this += p->delta;
 * f = p->func; if (p->vtoff >= 0) f = *(*(this + f) + vtoff); jr f with
 * a1..a3 still live. Unemittable: $at as a data register (lw $1), MIPS-I
 * load-delay nops, input in the volatile non-argument register $t9, and the
 * tail jump through $t9 (mwcc colours an indirect tail call to v0).
 * Proof: build/libdeasm/100e70/NOTES.md, build/libdeasm/100e70b/NOTES.md,
 * build/libdeasm/100e70c/NOTES.md (no C function form drops `jr ra; nop`). */
#define __PTMF_SCALL() \
        .set noreorder; \
        lw $1, 0x0($25); \
        lw $24, 0x4($25); \
        lw $25, 0x8($25); \
        bltz $24, ptmf_scall_jr; \
        addu $4, $4, $1; \
        addu $25, $4, $25; \
        lw $25, 0x0($25); \
        nop; \
        addu $25, $25, $24; \
        lw $25, 0x0($25); \
        nop; \
    ptmf_scall_jr: \
        jr $25; \
        nop

/* __TRANSFER_CONTROL(): MW C++ exception runtime "jump to catch handler"
 * (ExceptionPPC.cp TransferControl shape; tail-called by EhThrowHandler_101050).
 * $a0 = ThrowContext*, $a2 = handler PC. Restores the catch frame's
 * callee-saved state from the context -- lq $16-$23,$30, lwc1 $f20-$f31 --
 * then $sp = context->SP - context->framesize and `jr $a2`.
 * Unemittable: writes to nonvolatile GPR/FPRs that must SURVIVE the
 * function (mwcc saves/restores every bound r16../f20.. it writes, under
 * every pragma incl. interrupt/tailcall/optimization_level 0 and every mwcc
 * build), any write to $sp (r29 binding rejected, "sp" spelling rejected;
 * __alloca = fp frame + subu + restore), trapping `sub`, no inline
 * setjmp/longjmp or catch-dispatch intrinsic, and a C function always
 * appends `jr $ra; nop` (build/libdeasm/100e70c/NOTES.md).
 * Proof: build/libdeasm/102550/NOTES.md, build/libdeasm/102550b/NOTES.md. */
#define __TRANSFER_CONTROL() \
        lq    $16, 0x120($4); \
        lwc1  $f20, 0x288($4); \
        lq    $17, 0x130($4); \
        lwc1  $f21, 0x28C($4); \
        lq    $18, 0x140($4); \
        lwc1  $f22, 0x290($4); \
        lq    $19, 0x150($4); \
        lwc1  $f23, 0x294($4); \
        lq    $20, 0x160($4); \
        lwc1  $f24, 0x298($4); \
        lq    $21, 0x170($4); \
        lwc1  $f25, 0x29C($4); \
        lq    $22, 0x180($4); \
        lwc1  $f26, 0x2A0($4); \
        lq    $23, 0x190($4); \
        lwc1  $f27, 0x2A4($4); \
        lq    $30, 0x200($4); \
        lwc1  $f28, 0x2A8($4); \
        lwc1  $f29, 0x2AC($4); \
        lw    $29, 0x1C($4); \
        lwc1  $f30, 0x2B0($4); \
        lw    $2, 0x224($4); \
        lwc1  $f31, 0x2B4($4); \
        jr    $6; \
        sub   $29, $29, $2

/* __THROW(): MW C++ runtime __throw(throwtype, location, dtor) (ExceptionPPC.cp
 * shape; MW ships it as an `asm` function with fralloc). Captures the thrower's
 * state into a ThrowContext at the new $sp: entry $sp (paddub copy taken BEFORE
 * the frame is allocated) -> SP/FP, sq $16-$23,$30 -> GPR[], swc1 $f20-$f31 ->
 * FPR[], $ra -> returnaddr, a0-a2 -> throwtype/location/dtor, then
 * jal EhThrowHandler_101050 (__ThrowHandler) which never returns: no epilogue.
 * Unemittable: mwcc caps register bindings at 2 GPR / 3 FPR per TU in every
 * build, C and C++ TUs alike, not liftable by vu0_max_used_nvreg /
 * vu0_register_number (9 + 12 needed); r29/r31 bindings rejected (no
 * $sp-before-frame or $ra read; no __builtin_return_address/frame_address);
 * no sq/paddub intrinsic (__I_* ops take C values only); noreturn
 * attribute/infinite loop still emit an epilogue/loop; a bound callee-saved
 * read adds prologue save + epilogue restore.
 * Proof: build/libdeasm/1025c0/NOTES.md, build/libdeasm/1025c0b/NOTES.md. */
#define __THROW() \
        .set noreorder; \
        paddub $2, $29, $0; \
        addiu  $29, $29, -0x2C0; \
        sq     $16, 0x120($29); \
        sq     $17, 0x130($29); \
        sq     $18, 0x140($29); \
        sq     $19, 0x150($29); \
        sq     $20, 0x160($29); \
        sq     $21, 0x170($29); \
        sq     $22, 0x180($29); \
        sq     $23, 0x190($29); \
        sq     $30, 0x200($29); \
        swc1   $f20, 0x288($29); \
        swc1   $f21, 0x28C($29); \
        swc1   $f22, 0x290($29); \
        swc1   $f23, 0x294($29); \
        swc1   $f24, 0x298($29); \
        swc1   $f25, 0x29C($29); \
        swc1   $f26, 0x2A0($29); \
        swc1   $f27, 0x2A4($29); \
        swc1   $f28, 0x2A8($29); \
        swc1   $f29, 0x2AC($29); \
        swc1   $f30, 0x2B0($29); \
        swc1   $f31, 0x2B4($29); \
        sw     $2, 0x14($29); \
        sw     $2, 0x1C($29); \
        sw     $31, 0x10($29); \
        sw     $4, 0x0($29); \
        sw     $5, 0x4($29); \
        paddub $4, $29, $0; \
        jal    EhThrowHandler_101050; \
        sw     $6, 0x8($29); \
        nop

#endif /* MWRUNTIME_H */
