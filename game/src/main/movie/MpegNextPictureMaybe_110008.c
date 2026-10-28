#include "types.h"

extern void IpuByteAlign_110168(void);
extern void IpuSkipBitsThunk2_10de00(void);
extern void IpuShowBits_10dd70(void);
extern void IpuGetBits_10dc88(void);
extern void MpegParseSequenceHeader_10f510(void);
extern void MpegParseGopHeader_10f7c0(void);
extern void MpegParsePictureHeader_10f860(void);
extern void MpegInvokeCallback_111340(void);

asm void MpegNextPictureMaybe_110008(void)
{
    .set noreorder;
    addiu      $29, $29, -0xB0;
    sd         $23, 0x90($29);
    sd         $22, 0x80($29);
    addiu      $23, $0, 0x1B3;
    sd         $21, 0x70($29);
    addiu      $22, $0, 0x5;
    sd         $20, 0x60($29);
    addiu      $21, $0, 0x100;
    sd         $19, 0x50($29);
    addiu      $20, $0, 0x1B7;
    sd         $18, 0x40($29);
    addiu      $19, $0, 0x1B8;
    sd         $16, 0x20($29);
    addiu      $18, $0, -0x1;
    sd         $31, 0xA0($29);
    daddu      $16, $4, $0;
    sd         $17, 0x30($29);
    lw         $2, 0x878($16);
  L00110050:
    bnez       $2, L00110130;
    addiu     $2, $0, -0x1;
    daddu      $4, $16, $0;
    jal        IpuByteAlign_110168;
    addiu     $17, $0, 0x1;
    b          L0011007C;
    daddu     $4, $16, $0;
    nop;
  L00110070:
    jal        IpuSkipBitsThunk2_10de00;
    addiu     $5, $0, 0x8;
    daddu      $4, $16, $0;
  L0011007C:
    jal        IpuShowBits_10dd70;
    addiu     $5, $0, 0x18;
    beq        $2, $17, L00110098;
    daddu     $4, $16, $0;
    lw         $2, 0x878($16);
    beqz       $2, L00110070;
    nop;
  L00110098:
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x20;
    daddu      $3, $2, $0;
    beq        $3, $23, L001100DC;
    sltiu     $2, $3, 0x1B4;
    beqz       $2, L001100C4;
    nop;
    beq        $3, $21, L001100FC;
    nop;
    b          L00110050;
    lw        $2, 0x878($16);
  L001100C4:
    beq        $3, $20, L00110130;
    daddu     $2, $0, $0;
    beq        $3, $19, L001100EC;
    nop;
    b          L00110050;
    lw        $2, 0x878($16);
  L001100DC:
    jal        MpegParseSequenceHeader_10f510;
    daddu     $4, $16, $0;
    b          L00110050;
    lw        $2, 0x878($16);
  L001100EC:
    jal        MpegParseGopHeader_10f7c0;
    daddu     $4, $16, $0;
    b          L00110050;
    lw        $2, 0x878($16);
  L001100FC:
    jal        MpegParsePictureHeader_10f860;
    daddu     $4, $16, $0;
    lw         $4, 0x868($16);
    daddu      $5, $29, $0;
    sw         $22, 0x0($29);
    sd         $18, 0x10($29);
    jal        MpegInvokeCallback_111340;
    sd        $18, 0x8($29);
    ld         $2, 0x10($29);
    ld         $3, 0x8($29);
    sd         $2, 0x840($16);
    sd         $3, 0x838($16);
    lw         $2, 0x160($16);
  L00110130:
    ld         $31, 0xA0($29);
    ld         $23, 0x90($29);
    ld         $22, 0x80($29);
    ld         $21, 0x70($29);
    ld         $20, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0xB0;
}
