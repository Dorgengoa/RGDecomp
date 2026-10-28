#include "types.h"

extern void sceGszbufaddr(void);

asm void sceGsSetDefDrawEnv(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sll        $6, $6, 16;
    sd         $18, 0x20($29);
    sll        $5, $5, 16;
    sra        $18, $6, 16;
    sd         $20, 0x40($29);
    addiu      $2, $18, 0x3F;
    sra        $20, $5, 16;
    sra        $2, $2, 6;
    andi       $3, $20, 0xF;
    andi       $2, $2, 0x3F;
    sd         $16, 0x0($29);
    dsll       $3, $3, 24;
    dsll       $2, $2, 16;
    daddu      $16, $4, $0;
    or         $2, $2, $3;
    sd         $21, 0x50($29);
    sll        $7, $7, 16;
    sd         $19, 0x30($29);
    sll        $8, $8, 16;
    sd         $17, 0x10($29);
    sll        $9, $9, 16;
    sd         $31, 0x60($29);
    addiu      $3, $0, 0x4C;
    addiu      $4, $0, 0x4E;
    sra        $17, $7, 16;
    sra        $21, $8, 16;
    sra        $19, $9, 16;
    sd         $3, 0x8($16);
    sd         $2, 0x0($16);
    bnez       $21, L0010897C;
    sd        $4, 0x18($16);
    daddu      $4, $20, $0;
    daddu      $5, $18, $0;
    jal        sceGszbufaddr;
    daddu     $6, $17, $0;
    dsll32     $2, $2, 16;
    andi       $3, $19, 0xF;
    dsra32     $2, $2, 16;
    dsll       $3, $3, 24;
    or         $2, $2, $3;
    ori        $4, $0, 0x8000;
    dsll       $4, $4, 17;
    b          L001089A0;
    or        $2, $2, $4;
  L0010897C:
    daddu      $4, $20, $0;
    daddu      $5, $18, $0;
    jal        sceGszbufaddr;
    daddu     $6, $17, $0;
    dsll32     $2, $2, 16;
    andi       $3, $19, 0xF;
    dsra32     $2, $2, 16;
    dsll       $3, $3, 24;
    or         $2, $2, $3;
  L001089A0:
    sd         $2, 0x10($16);
    sra        $2, $17, 1;
    sra        $3, $18, 1;
    dsll32     $2, $2, 16;
    addiu      $4, $0, 0x800;
    dsll32     $3, $3, 16;
    dsra32     $2, $2, 16;
    dsra32     $3, $3, 16;
    dsubu      $2, $4, $2;
    dsubu      $4, $4, $3;
    dsll32     $2, $2, 4;
    addiu      $6, $18, -0x1;
    addiu      $5, $17, -0x1;
    dsll       $4, $4, 4;
    ld         $3, 0x40($16);
    ld         $7, 0x50($16);
    dsll32     $5, $5, 16;
    or         $4, $4, $2;
    dsll       $6, $6, 16;
    addiu      $11, $0, 0x1;
    or         $6, $6, $5;
    addiu      $2, $0, 0x18;
    or         $3, $3, $11;
    or         $7, $7, $11;
    addiu      $5, $0, 0x40;
    addiu      $8, $0, 0x1A;
    addiu      $9, $0, 0x46;
    addiu      $10, $0, 0x45;
    sd         $2, 0x28($16);
    sd         $4, 0x20($16);
    andi       $2, $20, 0x2;
    sd         $5, 0x38($16);
    sd         $6, 0x30($16);
    sd         $8, 0x48($16);
    sd         $3, 0x40($16);
    sd         $9, 0x58($16);
    sd         $7, 0x50($16);
    beqz       $2, L00108A48;
    sd        $10, 0x68($16);
    ld         $2, 0x60($16);
    b          L00108A54;
    or        $2, $2, $11;
  L00108A48:
    ld         $2, 0x60($16);
    addiu      $3, $0, -0x2;
    and        $2, $2, $3;
  L00108A54:
    sd         $2, 0x60($16);
    addiu      $2, $0, 0x47;
    beqz       $21, L00108A78;
    sd        $2, 0x78($16);
    andi       $2, $21, 0x3;
    lui        $3, (0x10000 >> 16);
    dsll       $2, $2, 17;
    b          L00108A7C;
    or        $2, $2, $3;
  L00108A78:
    lui        $2, (0x30000 >> 16);
  L00108A7C:
    sd         $2, 0x70($16);
    sync;
    ld         $31, 0x60($29);
    addiu      $2, $0, 0x8;
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}

