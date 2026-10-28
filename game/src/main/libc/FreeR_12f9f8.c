#include "types.h"

extern void MallocLock_131c20(void);
extern void MallocTrim_12fcf0(void);
extern void MallocUnlock_131ca0(void);

asm void FreeR_12f9f8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sd         $17, 0x8($29);
    daddu      $17, $4, $0;
    beqz       $16, L0012FCD8;
    sd        $31, 0x10($29);
    jal        MallocLock_131c20;
    nop;
    addiu      $9, $16, -0x8;
    lw         $6, 0x4($9);
    addiu      $2, $0, -0x2;
    lui        $12, 0x45;
    addiu      $4, $0, -0x4;
    and        $8, $6, $2;
    addiu      $10, $12, -0x6798;
    addu       $5, $9, $8;
    lw         $3, 0x8($10);
    lw         $2, 0x4($5);
    bne        $5, $3, L0012FAC0;
    and       $4, $2, $4;
    andi       $2, $6, 0x1;
    bnez       $2, L0012FA74;
    addu      $8, $8, $4;
    lw         $3, 0x0($9);
    subu       $9, $9, $3;
    addu       $8, $8, $3;
    lw         $7, 0xC($9);
    lw         $6, 0x8($9);
    sw         $7, 0xC($6);
    sw         $6, 0x8($7);
  L0012FA74:
    ori        $3, $8, 0x1;
    sw         $9, 0x8($10);
    sw         $3, 0x4($9);
    lui        $4, 0x45;
    dsll32     $2, $8, 0;
    ld         $3, -0x6390($4);
    dsrl32     $2, $2, 0;
    sltu       $2, $2, $3;
    bnez       $2, L0012FAAC;
    daddu     $4, $17, $0;
    lui        $2, 0x45;
    jal        MallocTrim_12fcf0;
    lw        $5, -0x6388($2);
    daddu      $4, $17, $0;
  L0012FAAC:
    ld         $17, 0x8($29);
    ld         $16, 0x0($29);
    ld         $31, 0x10($29);
    j          MallocUnlock_131ca0;
    addiu     $29, $29, 0x20;
  L0012FAC0:
    andi       $2, $6, 0x1;
    sw         $4, 0x4($5);
    bnez       $2, L0012FB04;
    daddu     $11, $0, $0;
    lw         $3, 0x0($9);
    addiu      $2, $10, 0x8;
    subu       $9, $9, $3;
    addu       $8, $8, $3;
    lw         $3, 0x8($9);
    bnel       $3, $2, L0012FAF8;
    lw        $7, 0xC($9);
    b          L0012FB04;
    addiu     $11, $0, 0x1;
    nop;
  L0012FAF8:
    daddu      $6, $3, $0;
    sw         $7, 0xC($6);
    sw         $6, 0x8($7);
  L0012FB04:
    addu       $3, $5, $4;
    lw         $2, 0x4($3);
    andi       $2, $2, 0x1;
    bnez       $2, L0012FB68;
    ori       $2, $8, 0x1;
    bnez       $11, L0012FB50;
    addu      $8, $8, $4;
    lui        $2, 0x45;
    lw         $3, 0x8($5);
    addiu      $2, $2, -0x6788;
    addiu      $2, $2, -0x8;
    bnel       $3, $2, L0012FB58;
    lw        $7, 0xC($5);
    sw         $9, 0xC($3);
    addiu      $11, $0, 0x1;
    sw         $9, 0x8($3);
    sw         $3, 0x8($9);
    b          L0012FB64;
    sw        $3, 0xC($9);
  L0012FB50:
    lw         $3, 0x8($5);
    lw         $7, 0xC($5);
  L0012FB58:
    daddu      $6, $3, $0;
    sw         $7, 0xC($6);
    sw         $6, 0x8($7);
  L0012FB64:
    ori        $2, $8, 0x1;
  L0012FB68:
    addu       $3, $9, $8;
    sw         $2, 0x4($9);
    bnez       $11, L0012FCC0;
    sw        $8, 0x0($3);
    sltiu      $2, $8, 0x200;
    beql       $2, $0, L0012FBC8;
    srl       $3, $8, 9;
    srl        $5, $8, 3;
    addiu      $4, $12, -0x6798;
    sll        $3, $5, 3;
    srl        $5, $5, 2;
    addiu      $2, $0, 0x1;
    addu       $7, $3, $4;
    dsllv      $2, $2, $5;
    lw         $3, 0x4($4);
    lw         $6, 0x8($7);
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    or         $3, $3, $2;
    sw         $7, 0xC($9);
    sw         $6, 0x8($9);
    b          L0012FCB8;
    sw        $3, 0x4($4);
    nop;
  L0012FBC8:
    beqz       $3, L0012FC30;
    srl       $5, $8, 3;
    sltiu      $2, $3, 0x5;
    beqz       $2, L0012FBE8;
    sltiu     $2, $3, 0x15;
    srl        $2, $8, 6;
    b          L0012FC30;
    addiu     $5, $2, 0x38;
  L0012FBE8:
    bnez       $2, L0012FC30;
    addiu     $5, $3, 0x5B;
    sltiu      $2, $3, 0x55;
    beqz       $2, L0012FC08;
    sltiu     $2, $3, 0x155;
    srl        $2, $8, 12;
    b          L0012FC30;
    addiu     $5, $2, 0x6E;
  L0012FC08:
    beqz       $2, L0012FC20;
    sltiu     $2, $3, 0x555;
    srl        $2, $8, 15;
    b          L0012FC30;
    addiu     $5, $2, 0x77;
    nop;
  L0012FC20:
    beql       $2, $0, L0012FC30;
    addiu     $5, $0, 0x7E;
    srl        $2, $8, 18;
    addiu      $5, $2, 0x7C;
  L0012FC30:
    lui        $2, 0x45;
    sll        $3, $5, 3;
    addiu      $2, $2, -0x6790;
    addiu      $10, $2, -0x8;
    addu       $7, $3, $10;
    lw         $6, 0x8($7);
    bnel       $6, $7, L0012FC80;
    lw        $2, 0x4($6);
    addiu      $4, $5, 0x3;
    slti       $3, $5, 0x0;
    movn       $5, $4, $3;
    lw         $3, 0x4($10);
    addiu      $2, $0, 0x1;
    sra        $4, $5, 2;
    dsllv      $2, $2, $4;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    or         $3, $3, $2;
    b          L0012FCB0;
    sw        $3, 0x4($10);
  L0012FC80:
    b          L0012FC94;
    addiu     $3, $0, -0x4;
  L0012FC88:
    beql       $6, $7, L0012FCB0;
    lw        $7, 0xC($6);
    lw         $2, 0x4($6);
  L0012FC94:
    and        $2, $2, $3;
    sltu       $2, $8, $2;
    nop;
    nop;
    bnel       $2, $0, L0012FC88;
    lw        $6, 0x8($6);
    lw         $7, 0xC($6);
  L0012FCB0:
    sw         $7, 0xC($9);
    sw         $6, 0x8($9);
  L0012FCB8:
    sw         $9, 0x8($7);
    sw         $9, 0xC($6);
  L0012FCC0:
    daddu      $4, $17, $0;
    ld         $17, 0x8($29);
    ld         $16, 0x0($29);
    ld         $31, 0x10($29);
    j          MallocUnlock_131ca0;
    addiu     $29, $29, 0x20;
  L0012FCD8:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
