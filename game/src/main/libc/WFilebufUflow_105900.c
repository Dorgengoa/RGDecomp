#include "types.h"

extern void WFilebufGetcPeek_105c30(void);
extern void WFilebufGetBytesPeekMaybe_105ce0(void);

asm void WFilebufUflow_105900(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    lbu        $2, 0x66($4);
    beqz       $2, L00105984;
    daddu     $16, $4, $0;
    lw         $2, 0x8($16);
    bnel       $2, $0, L00105988;
    lw        $2, 0x8($16);
    lw         $3, 0x14($16);
    lw         $2, 0x10($16);
    sltu       $1, $2, $3;
    beqz       $1, L0010595C;
    daddu     $17, $0, $0;
    lw         $25, 0x0($4);
    lw         $25, 0x34($25);
    jalr $31, $25;
    addiu     $5, $0, -0x1;
    addiu      $3, $0, -0x1;
    bne        $2, $3, L0010595C;
    nop;
    daddiu     $17, $0, 0x1;
  L0010595C:
    beql       $17, $0, L0010596C;
    sw        $0, 0x14($16);
    b          L00105A14;
    addiu     $2, $0, -0x1;
  L0010596C:
    addiu      $2, $16, 0x24;
    sw         $0, 0x10($16);
    sw         $0, 0x18($16);
    sw         $2, 0x4($16);
    sw         $2, 0x8($16);
    sw         $2, 0xC($16);
  L00105984:
    lw         $2, 0x8($16);
  L00105988:
    beql       $2, $0, L001059C8;
    sb        $0, 0x64($16);
    lw         $25, 0x0($16);
    lw         $25, 0x24($25);
    jalr $31, $25;
    daddu     $4, $16, $0;
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L001059B4;
    lw        $2, 0x8($16);
    b          L00105A14;
    daddu     $2, $3, $0;
  L001059B4:
    lw         $3, 0x8($16);
    lhu        $2, 0x0($2);
    addiu      $3, $3, 0x4;
    b          L00105A14;
    sw        $3, 0x8($16);
  L001059C8:
    lw         $2, 0x1C($16);
    bnel       $2, $0, L001059DC;
    lbu       $2, 0x65($16);
    b          L00105A14;
    addiu     $2, $0, -0x1;
  L001059DC:
    beql       $2, $0, L001059F8;
    daddu     $4, $16, $0;
    daddu      $4, $16, $0;
    jal        WFilebufGetcPeek_105c30;
    daddu     $5, $0, $0;
    b          L00105A08;
    addiu     $3, $0, -0x1;
  L001059F8:
    addiu      $5, $0, 0x4;
    jal        WFilebufGetBytesPeekMaybe_105ce0;
    daddu     $6, $0, $0;
    addiu      $3, $0, -0x1;
  L00105A08:
    bne        $2, $3, L00105A14;
    nop;
    daddu      $2, $3, $0;
  L00105A14:
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

