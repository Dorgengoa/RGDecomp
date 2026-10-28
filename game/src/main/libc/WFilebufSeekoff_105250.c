#include "types.h"

extern void Fseek_12fe60(void);
extern void Ftell_130370(void);

asm void WFilebufSeekoff_105250(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $31, 0x60($29);
    sq         $21, 0x50($29);
    sq         $20, 0x40($29);
    daddu      $21, $4, $0;
    sq         $19, 0x30($29);
    daddu      $20, $5, $0;
    sq         $18, 0x20($29);
    daddu      $19, $6, $0;
    sq         $17, 0x10($29);
    daddu      $18, $7, $0;
    sq         $16, 0x0($29);
    lw         $3, 0x1C($5);
    beqz       $3, L00105294;
    daddu     $17, $8, $0;
    b          L001052A4;
    lw        $4, 0x14($20);
  L00105294:
    addiu      $3, $0, -0x1;
    sd         $3, 0x0($21);
    b          L001053B0;
    sw        $0, 0x8($21);
  L001052A4:
    lw         $3, 0x10($20);
    sltu       $1, $3, $4;
    beqz       $1, L001052D8;
    daddu     $16, $0, $0;
    lw         $25, 0x0($20);
    daddu      $4, $20, $0;
    lw         $25, 0x34($25);
    jalr $31, $25;
    addiu     $5, $0, -0x1;
    addiu      $3, $0, -0x1;
    bne        $2, $3, L001052D8;
    nop;
    daddiu     $16, $0, 0x1;
  L001052D8:
    beql       $16, $0, L001052F0;
    andi      $4, $18, 0xFF;
    addiu      $3, $0, -0x1;
    sd         $3, 0x0($21);
    b          L001053B0;
    sw        $0, 0x8($21);
  L001052F0:
    addiu      $3, $0, 0x4;
    beql       $4, $3, L00105364;
    addiu     $6, $0, 0x2;
    addiu      $3, $0, 0x2;
    beql       $4, $3, L0010531C;
    andi      $2, $17, 0xFF;
    addiu      $3, $0, 0x1;
    beql       $4, $3, L00105364;
    daddu     $6, $0, $0;
    b          L00105358;
    addiu     $3, $0, -0x1;
  L0010531C:
    andi       $2, $2, 0x8;
    andi       $2, $2, 0xFF;
    beqz       $2, L00105364;
    addiu     $6, $0, 0x1;
    lw         $3, 0xC($20);
    lw         $2, 0x8($20);
    subu       $3, $3, $2;
    bgez       $3, L00105348;
    sra       $2, $3, 2;
    addiu      $2, $3, 0x3;
    sra        $2, $2, 2;
  L00105348:
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    b          L00105364;
    dsubu     $19, $19, $2;
  L00105358:
    sd         $3, 0x0($21);
    b          L001053B0;
    sw        $0, 0x8($21);
  L00105364:
    lw         $4, 0x1C($20);
    jal        Fseek_12fe60;
    dsll      $5, $19, 2;
    beql       $2, $0, L00105388;
    sw        $0, 0x4($20);
    addiu      $3, $0, -0x1;
    sd         $3, 0x0($21);
    b          L001053B0;
    sw        $0, 0x8($21);
  L00105388:
    sw         $0, 0x8($20);
    sw         $0, 0xC($20);
    sw         $0, 0x14($20);
    sw         $0, 0x10($20);
    sw         $0, 0x18($20);
    sb         $0, 0x64($20);
    jal        Ftell_130370;
    lw        $4, 0x1C($20);
    sd         $2, 0x0($21);
    sw         $0, 0x8($21);
  L001053B0:
    ld         $31, 0x60($29);
    lq         $21, 0x50($29);
    lq         $20, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}

