#include "types.h"

extern void FilebufGetcPeek_105f30(void);
extern void FilebufGetBytesPeekMaybe_105fe0(void);

asm void FilebufUflow_104d80(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    lbu        $2, 0x36($4);
    beqz       $2, L00104E04;
    daddu     $16, $4, $0;
    lw         $2, 0x8($16);
    bnel       $2, $0, L00104E08;
    lw        $2, 0x8($16);
    lw         $3, 0x14($16);
    lw         $2, 0x10($16);
    sltu       $1, $2, $3;
    beqz       $1, L00104DDC;
    daddu     $17, $0, $0;
    lw         $25, 0x0($4);
    lw         $25, 0x34($25);
    jalr $31, $25;
    addiu     $5, $0, -0x1;
    addiu      $3, $0, -0x1;
    bne        $2, $3, L00104DDC;
    nop;
    daddiu     $17, $0, 0x1;
  L00104DDC:
    beql       $17, $0, L00104DEC;
    sw        $0, 0x14($16);
    b          L00104E94;
    addiu     $2, $0, -0x1;
  L00104DEC:
    addiu      $2, $16, 0x24;
    sw         $0, 0x10($16);
    sw         $0, 0x18($16);
    sw         $2, 0x4($16);
    sw         $2, 0x8($16);
    sw         $2, 0xC($16);
  L00104E04:
    lw         $2, 0x8($16);
  L00104E08:
    beql       $2, $0, L00104E48;
    sb        $0, 0x34($16);
    lw         $25, 0x0($16);
    lw         $25, 0x24($25);
    jalr $31, $25;
    daddu     $4, $16, $0;
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L00104E34;
    lw        $2, 0x8($16);
    b          L00104E94;
    daddu     $2, $3, $0;
  L00104E34:
    lw         $3, 0x8($16);
    lbu        $2, 0x0($2);
    addiu      $3, $3, 0x1;
    b          L00104E94;
    sw        $3, 0x8($16);
  L00104E48:
    lw         $2, 0x1C($16);
    bnel       $2, $0, L00104E5C;
    lbu       $2, 0x35($16);
    b          L00104E94;
    addiu     $2, $0, -0x1;
  L00104E5C:
    beql       $2, $0, L00104E78;
    daddu     $4, $16, $0;
    daddu      $4, $16, $0;
    jal        FilebufGetcPeek_105f30;
    daddu     $5, $0, $0;
    b          L00104E88;
    addiu     $3, $0, -0x1;
  L00104E78:
    addiu      $5, $0, 0x1;
    jal        FilebufGetBytesPeekMaybe_105fe0;
    daddu     $6, $0, $0;
    addiu      $3, $0, -0x1;
  L00104E88:
    bne        $2, $3, L00104E94;
    nop;
    daddu      $2, $3, $0;
  L00104E94:
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

