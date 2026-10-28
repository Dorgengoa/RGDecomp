#include "types.h"

extern void InitSys_120918(void);
extern void FlushCache(s32 mode);
extern void Main_15e700(void *, s32);
extern void Exit_12f4e0(void *);

/* THE image entry point (per the lane header note: real work, not just
   padding, so treat it as a genuine hand-written function -- naked
   `asm void`, lever 6). Clears all GPRs/FPRs, sets FP round mode, BSS-
   clears three regions with byte/quad loops, two syscalls (0x3C/0x3D --
   likely SetupThread/ExecThread-class), then tail-jumps into
   Exit_12f4e0 via `j` and never returns (no `jr $31` anywhere in the
   whole function). D_00481080/D_00485170/D_00485280 and
   `CrtRootExitThread_100220`'s own address hardcoded per lever 5 -- `CrtRootExitThread_100220`
   itself is the still-unregistered unit parked earlier; only its ADDRESS
   is used here (as a `sce_exit`-style callback pointer), so it does not
   need to resolve to anything for this unit's byte match. */

asm void entry(void)
{
    .set noreorder;
    padduw $1, $0, $0;
    padduw $2, $0, $0;
    padduw $3, $0, $0;
    padduw $4, $0, $0;
    padduw $5, $0, $0;
    padduw $6, $0, $0;
    padduw $7, $0, $0;
    padduw $8, $0, $0;
    padduw $9, $0, $0;
    padduw $10, $0, $0;
    padduw $11, $0, $0;
    padduw $12, $0, $0;
    padduw $13, $0, $0;
    padduw $14, $0, $0;
    padduw $15, $0, $0;
    padduw $16, $0, $0;
    padduw $17, $0, $0;
    padduw $18, $0, $0;
    padduw $19, $0, $0;
    padduw $20, $0, $0;
    padduw $21, $0, $0;
    padduw $22, $0, $0;
    padduw $23, $0, $0;
    padduw $24, $0, $0;
    padduw $25, $0, $0;
    padduw $28, $0, $0;
    padduw $29, $0, $0;
    padduw $30, $0, $0;
    padduw $31, $0, $0;
    mthi   $0;
    mthi1  $0;
    mtlo   $0;
    mtlo1  $0;
    mtsah  $0, 0x0;
    mtc1   $0, $f0;
    mtc1   $0, $f1;
    mtc1   $0, $f2;
    mtc1   $0, $f3;
    mtc1   $0, $f4;
    mtc1   $0, $f5;
    mtc1   $0, $f6;
    mtc1   $0, $f7;
    mtc1   $0, $f8;
    mtc1   $0, $f9;
    mtc1   $0, $f10;
    mtc1   $0, $f11;
    mtc1   $0, $f12;
    mtc1   $0, $f13;
    mtc1   $0, $f14;
    mtc1   $0, $f15;
    mtc1   $0, $f16;
    mtc1   $0, $f17;
    mtc1   $0, $f18;
    mtc1   $0, $f19;
    mtc1   $0, $f20;
    mtc1   $0, $f21;
    mtc1   $0, $f22;
    mtc1   $0, $f23;
    mtc1   $0, $f24;
    mtc1   $0, $f25;
    mtc1   $0, $f26;
    mtc1   $0, $f27;
    mtc1   $0, $f28;
    mtc1   $0, $f29;
    mtc1   $0, $f30;
    mtc1   $0, $f31;
    adda.s $f0, $f1;
    sync.p;
    ctc1   $0, $31;
    lui    $2, 0x48;
    lui    $3, 0x53;
    addiu  $2, $2, 0x1080;
    addiu  $3, $3, -0x7E00;
func_0010012C:
    andi   $4, $2, 0xF;
    beqz   $4, L0010014C;
    nop;
    sb     $0, 0x0($2);
    addiu  $2, $2, 0x1;
    nop;
    j      func_0010012C;
    nop;
L0010014C:
    lui    $4, (0xFFFFFFF0 >> 16);
    ori    $4, $4, (0xFFFFFFF0 & 0xFFFF);
    and    $4, $3, $4;
func_00100158:
    beq    $2, $4, func_00100178;
    nop;
    sq     $0, 0x0($2);
    addiu  $2, $2, 0x10;
    nop;
    nop;
    j      func_00100158;
    nop;
func_00100178:
    beq    $2, $3, L00100198;
    nop;
    sb     $0, 0x0($2);
    addiu  $2, $2, 0x1;
    nop;
    nop;
    j      func_00100178;
    nop;
L00100198:
    lui    $4, 0x48;
    lui    $5, 0x1FD;
    lui    $6, 0x3;
    lui    $7, 0x48;
    lui    $8, 0x10;
    addiu  $4, $4, 0x5170;
    addiu  $5, $5, (0x1FD0000 & 0xFFFF);
    addiu  $6, $6, (0x30000 & 0xFFFF);
    addiu  $7, $7, 0x5280;
    addiu  $8, $8, 0x220;
    or     $28, $4, $0;
    addiu  $3, $0, 0x3C;
    syscall 0;
    or     $29, $2, $0;
    lui    $4, 0x53;
    lui    $5, (0x0 >> 16);
    addiu  $4, $4, -0x7E00;
    addiu  $5, $5, -0x1;
    addiu  $3, $0, 0x3D;
    syscall 0;
    jal    InitSys_120918;
    nop;
    jal    FlushCache;
    or     $4, $0, $0;
    ei;
    lui    $2, 0x48;
    addiu  $2, $2, 0x5280;
    lw     $4, 0x0($2);
    jal    Main_15e700;
    addiu  $5, $2, 0x4;
    j      Exit_12f4e0;
    or     $4, $2, $0;
}
