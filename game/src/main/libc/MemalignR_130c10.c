#include "types.h"

extern void MallocR_1310d0(void);
extern void MallocLock_131c20(void);
extern void UModDi3_13a430(void);
extern void FreeR_12f9f8(void);
extern void MallocUnlock_131ca0(void);

asm void MemalignR_130c10(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sltiu      $2, $16, 0x11;
    sd         $20, 0x20($29);
    sd         $17, 0x8($29);
    daddu      $5, $6, $0;
    sd         $18, 0x10($29);
    daddu      $20, $4, $0;
    sd         $19, 0x18($29);
    beqz       $2, L00130C60;
    sd        $31, 0x28($29);
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $31, 0x28($29);
    j          MallocR_1310d0;
    addiu     $29, $29, 0x30;
  L00130C60:
    addiu      $5, $5, 0x13;
    sltiu      $2, $16, 0x10;
    addiu      $3, $0, 0x10;
    sltiu      $4, $5, 0x1F;
    bnez       $4, L00130C88;
    movn      $16, $3, $2;
    addiu      $2, $0, -0x10;
    b          L00130C8C;
    and       $19, $5, $2;
    nop;
  L00130C88:
    addiu      $19, $0, 0x10;
  L00130C8C:
    addu       $5, $19, $16;
    daddu      $4, $20, $0;
    jal        MallocR_1310d0;
    addiu     $5, $5, 0x10;
    daddu      $17, $2, $0;
    beql       $17, $0, L00130DBC;
    ld        $16, 0x0($29);
    daddu      $4, $20, $0;
    jal        MallocLock_131c20;
    addiu     $18, $17, -0x8;
    dsll32     $5, $16, 0;
    dsrl32     $5, $5, 0;
    jal        UModDi3_13a430;
    daddu     $4, $17, $0;
    beqz       $2, L00130D38;
    addu      $7, $17, $16;
    negu       $2, $16;
    addiu      $7, $7, -0x1;
    lw         $6, 0x4($18);
    and        $7, $7, $2;
    addiu      $3, $0, -0x4;
    addiu      $7, $7, -0x8;
    and        $6, $6, $3;
    subu       $2, $7, $18;
    daddu      $5, $17, $0;
    slti       $2, $2, 0x10;
    daddu      $4, $20, $0;
    mult       $3, $2, $16;
    addu       $7, $3, $7;
    subu       $8, $7, $18;
    subu       $6, $6, $8;
    ori        $3, $6, 0x1;
    addu       $6, $7, $6;
    sw         $3, 0x4($7);
    lw         $2, 0x4($6);
    ori        $2, $2, 0x1;
    sw         $2, 0x4($6);
    lw         $3, 0x4($18);
    andi       $3, $3, 0x1;
    or         $3, $3, $8;
    sw         $3, 0x4($18);
    jal        FreeR_12f9f8;
    daddu     $18, $7, $0;
  L00130D38:
    lw         $2, 0x4($18);
    addiu      $3, $0, -0x4;
    and        $2, $2, $3;
    sltu       $4, $2, $19;
    beql       $4, $0, L00130D68;
    subu      $2, $2, $19;
    subu       $2, $19, $2;
    dsll32     $2, $2, 0;
    dsrl32     $2, $2, 0;
    b          L00130D70;
    dsubu     $4, $0, $2;
    nop;
  L00130D68:
    dsll32     $2, $2, 0;
    dsrl32     $4, $2, 0;
  L00130D70:
    slti       $2, $4, 0x10;
    bnez       $2, L00130DAC;
    addiu     $2, $0, 0x1;
    addu       $6, $18, $19;
    or         $2, $4, $2;
    daddu      $4, $20, $0;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    addiu      $5, $6, 0x8;
    sw         $2, 0x4($6);
    lw         $3, 0x4($18);
    andi       $3, $3, 0x1;
    or         $3, $3, $19;
    jal        FreeR_12f9f8;
    sw        $3, 0x4($18);
  L00130DAC:
    jal        MallocUnlock_131ca0;
    daddu     $4, $20, $0;
    addiu      $2, $18, 0x8;
    ld         $16, 0x0($29);
  L00130DBC:
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $31, 0x28($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
