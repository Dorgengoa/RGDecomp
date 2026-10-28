#include "types.h"

extern void IpuByteAlign_110168(void);
extern void IpuSkipBitsThunk2_10de00(void);
extern void IpuShowBits_10dd70(void);
extern void IpuSkip32Bits_110160(void);
extern void IpuGetBits_10dc88(void);

asm void MpegParseExtUserData_10fdf8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    lui        $2, 0x45;
    sd         $16, 0x30($29);
    sd         $17, 0x40($29);
    daddu      $16, $4, $0;
    sd         $31, 0x80($29);
    sd         $20, 0x70($29);
    sd         $19, 0x60($29);
    sd         $18, 0x50($29);
    addiu      $7, $2, 0x63B8;
    ldl        $3, 0x7($7);
    ldr        $3, 0x0($7);
    ldl        $5, 0xF($7);
    ldr        $5, 0x8($7);
    ldl        $6, 0x17($7);
    ldr        $6, 0x10($7);
    sdl        $3, 0x7($29);
    sdr        $3, 0x0($29);
    sdl        $5, 0xF($29);
    sdr        $5, 0x8($29);
    sdl        $6, 0x17($29);
    sdr        $6, 0x10($29);
    ldl        $3, 0x1F($7);
    ldr        $3, 0x18($7);
    ldl        $5, 0x27($7);
    ldr        $5, 0x20($7);
    lw         $6, 0x28($7);
    sdl        $3, 0x1F($29);
    sdr        $3, 0x18($29);
    sdl        $5, 0x27($29);
    sdr        $5, 0x20($29);
    sw         $6, 0x28($29);
    jal        IpuByteAlign_110168;
    addiu     $17, $0, 0x1;
    b          L0010FE94;
    daddu     $4, $16, $0;
  L0010FE88:
    jal        IpuSkipBitsThunk2_10de00;
    nop;
    daddu      $4, $16, $0;
  L0010FE94:
    jal        IpuShowBits_10dd70;
    addiu     $5, $0, 0x18;
    daddu      $4, $16, $0;
    beq        $2, $17, L0010FEB4;
    addiu     $5, $0, 0x8;
    lw         $2, 0x878($16);
    beqz       $2, L0010FE88;
    nop;
  L0010FEB4:
    addiu      $18, $0, 0x1B5;
    addiu      $20, $0, 0x1B2;
    b          L0010FF8C;
    addiu     $19, $0, 0xA;
    nop;
  L0010FEC8:
    bne        $2, $18, L0010FF44;
    daddu     $4, $16, $0;
  L0010FED0:
    jal        IpuSkip32Bits_110160;
    addiu     $17, $0, 0x1;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x4;
    sltu       $3, $19, $2;
    movn       $2, $0, $3;
    sll        $2, $2, 2;
    addu       $3, $29, $2;
    lw         $2, 0x0($3);
    jalr $31, $2;
    daddu     $4, $16, $0;
    jal        IpuByteAlign_110168;
    daddu     $4, $16, $0;
    b          L0010FF1C;
    daddu     $4, $16, $0;
  L0010FF10:
    jal        IpuSkipBitsThunk2_10de00;
    nop;
    daddu      $4, $16, $0;
  L0010FF1C:
    jal        IpuShowBits_10dd70;
    addiu     $5, $0, 0x18;
    daddu      $4, $16, $0;
    beq        $2, $17, L0010FF90;
    addiu     $5, $0, 0x8;
    lw         $2, 0x878($16);
    beqz       $2, L0010FF10;
    nop;
    b          L0010FF8C;
    nop;
  L0010FF44:
    jal        IpuSkip32Bits_110160;
    addiu     $17, $0, 0x1;
    jal        IpuByteAlign_110168;
    daddu     $4, $16, $0;
    b          L0010FF6C;
    daddu     $4, $16, $0;
    nop;
  L0010FF60:
    jal        IpuSkipBitsThunk2_10de00;
    nop;
    daddu      $4, $16, $0;
  L0010FF6C:
    jal        IpuShowBits_10dd70;
    addiu     $5, $0, 0x18;
    daddu      $4, $16, $0;
    beq        $2, $17, L0010FF90;
    addiu     $5, $0, 0x8;
    lw         $2, 0x878($16);
    beqz       $2, L0010FF60;
    nop;
  L0010FF8C:
    daddu      $4, $16, $0;
  L0010FF90:
    jal        IpuShowBits_10dd70;
    addiu     $5, $0, 0x20;
    beq        $2, $18, L0010FED0;
    daddu     $4, $16, $0;
    beq        $2, $20, L0010FEC8;
    ld        $31, 0x80($29);
    ld         $20, 0x70($29);
    ld         $19, 0x60($29);
    ld         $18, 0x50($29);
    ld         $17, 0x40($29);
    ld         $16, 0x30($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}

