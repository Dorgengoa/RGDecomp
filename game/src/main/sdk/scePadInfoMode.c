#include "types.h"

extern void scePadGetDmaStr(void);

asm void scePadInfoMode(void)
{
    .set noreorder;
    daddu      $8, $4, $0;
    addiu      $3, $0, 0x70;
    addiu      $4, $0, 0x1C;
    mult1      $3, $8, $3;
    mult       $4, $5, $4;
    addiu      $29, $29, -0xB0;
    lui        $2, 0x49;
    sd         $17, 0x90($29);
    sd         $16, 0x80($29);
    addiu      $2, $2, -0x12B0;
    sd         $31, 0xA0($29);
    daddu      $16, $6, $0;
    addu       $4, $4, $3;
    addu       $2, $2, $4;
    lw         $3, 0x10($2);
    beqz       $3, L0012BDBC;
    daddu     $17, $7, $0;
    daddu      $4, $8, $0;
    jal        scePadGetDmaStr;
    daddu     $6, $29, $0;
    lbu        $3, 0x72($29);
    addiu      $2, $0, 0x1;
    bne        $3, $2, L0012BDC0;
    daddu     $2, $0, $0;
    lbu        $2, 0x71($29);
    addiu      $4, $0, 0x2;
    beq        $2, $4, L0012BDC0;
    daddu     $2, $0, $0;
    beq        $16, $4, L0012BD60;
    slti      $2, $16, 0x3;
    beqz       $2, L0012BD30;
    addiu     $2, $0, 0x3;
    beq        $16, $3, L0012BD48;
    daddu     $2, $0, $0;
    b          L0012BDC4;
    ld        $31, 0xA0($29);
  L0012BD30:
    beq        $16, $2, L0012BD74;
    addiu     $2, $0, 0x4;
    beq        $16, $2, L0012BD88;
    daddu     $2, $0, $0;
    b          L0012BDC4;
    ld        $31, 0xA0($29);
  L0012BD48:
    lbu        $3, 0x65($29);
    addiu      $2, $0, 0xF3;
    beq        $3, $2, L0012BDBC;
    srl       $2, $3, 4;
    b          L0012BDC4;
    ld        $31, 0xA0($29);
  L0012BD60:
    lbu        $2, 0x64($29);
    beq        $2, $3, L0012BDBC;
    lbu       $2, 0x69($29);
    b          L0012BDB0;
    sll       $2, $2, 1;
  L0012BD74:
    lbu        $2, 0x64($29);
    beq        $2, $3, L0012BDBC;
    lbu       $2, 0x69($29);
    b          L0012BDC4;
    ld        $31, 0xA0($29);
  L0012BD88:
    lbu        $2, 0x64($29);
    beq        $2, $3, L0012BDBC;
    addiu     $2, $0, -0x1;
    bne        $17, $2, L0012BDA4;
    lbu       $2, 0x68($29);
    b          L0012BDC4;
    ld        $31, 0xA0($29);
  L0012BDA4:
    slt        $2, $17, $2;
    beqz       $2, L0012BDBC;
    sll       $2, $17, 1;
  L0012BDB0:
    addu       $3, $29, $2;
    b          L0012BDC0;
    lhu       $2, 0x50($3);
  L0012BDBC:
    daddu      $2, $0, $0;
  L0012BDC0:
    ld         $31, 0xA0($29);
  L0012BDC4:
    ld         $17, 0x90($29);
    ld         $16, 0x80($29);
    jr         $31;
    addiu     $29, $29, 0xB0;
}
