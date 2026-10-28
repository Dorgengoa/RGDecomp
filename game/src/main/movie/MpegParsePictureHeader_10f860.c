#include "types.h"

extern void IpuGetBits_10dc88(void);
extern void IpuSkipBitsThunk2_10de00(void);
extern void MpegParseExtUserData_10fdf8(void);

asm void MpegParsePictureHeader_10f860(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    addiu      $5, $0, 0xA;
    sd         $16, 0x0($29);
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    jal        IpuGetBits_10dc88;
    daddu     $16, $4, $0;
    daddu      $17, $2, $0;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x3;
    sw         $2, 0x160($16);
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x10;
    lw         $3, 0x160($16);
    addiu      $2, $3, -0x2;
    sltiu      $2, $2, 0x2;
    beqz       $2, L0010F8D0;
    daddu     $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    sw         $2, 0x164($16);
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x3;
    sw         $2, 0x168($16);
    lw         $3, 0x160($16);
  L0010F8D0:
    addiu      $2, $0, 0x3;
    bne        $3, $2, L0010F90C;
    daddu     $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    sw         $2, 0x16C($16);
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x3;
    b          L0010F908;
    sw        $2, 0x170($16);
    nop;
  L0010F900:
    jal        IpuSkipBitsThunk2_10de00;
    addiu     $5, $0, 0x8;
  L0010F908:
    daddu      $4, $16, $0;
  L0010F90C:
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    bnez       $2, L0010F900;
    daddu     $4, $16, $0;
    jal        MpegParseExtUserData_10fdf8;
    daddu     $4, $16, $0;
    lw         $3, 0x160($16);
    daddu      $5, $0, $0;
    addiu      $2, $0, 0x3;
    beq        $3, $2, L0010F958;
    daddu     $4, $0, $0;
    beql       $17, $0, L0010F95C;
    lw        $2, 0x85C($16);
    bgezl      $17, L0010F954;
    sw        $0, 0x864($16);
    lw         $2, 0x864($16);
    sltiu      $5, $2, 0x1;
    sw         $0, 0x864($16);
  L0010F954:
    daddu      $4, $17, $0;
  L0010F958:
    lw         $2, 0x85C($16);
  L0010F95C:
    addu       $3, $2, $17;
    beqz       $5, L0010F97C;
    sw        $3, 0x1BC($16);
    slt        $2, $4, $17;
    bnel       $2, $0, L0010F980;
    lw        $2, 0x860($16);
    addiu      $2, $3, 0x400;
    sw         $2, 0x1BC($16);
  L0010F97C:
    lw         $2, 0x860($16);
  L0010F980:
    lw         $4, 0x1BC($16);
    ld         $31, 0x20($29);
    slt        $3, $2, $4;
    ld         $17, 0x10($29);
    movn       $2, $4, $3;
    sw         $2, 0x860($16);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

