#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void IpuSync_115e50(void);

asm void MpegResetHwMaybe_1107e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    addiu      $2, $0, 0x1;
    sd         $31, 0x0($29);
    sw         $2, 0x828($4);
    jal        DisableIntr_120660;
    sw        $0, 0x1C0($4);
    lui        $6, (0x1000F520 >> 16);
    lui        $7, (0x1000F590 >> 16);
    ori        $6, $6, (0x1000F520 & 0xFFFF);
    lui        $8, (0x10000 >> 16);
    lw         $3, 0x0($6);
    ori        $7, $7, (0x1000F590 & 0xFFFF);
    lui        $4, (0x1000B000 >> 16);
    lui        $5, (0x1000B400 >> 16);
    or         $3, $3, $8;
    ori        $4, $4, (0x1000B000 & 0xFFFF);
    sw         $3, 0x0($7);
    ori        $5, $5, (0x1000B400 & 0xFFFF);
    sw         $0, 0x0($4);
    lui        $3, (0x1000D400 >> 16);
    sw         $0, 0x0($5);
    ori        $3, $3, (0x1000D400 & 0xFFFF);
    sw         $0, 0x0($3);
    lui        $4, (0xFFFEFFFF >> 16);
    ori        $4, $4, (0xFFFEFFFF & 0xFFFF);
    lw         $3, 0x0($6);
    and        $3, $3, $4;
    sw         $3, 0x0($7);
    beqz       $2, L00110864;
    lui       $2, (0x1000B020 >> 16);
    jal        EnableIntr_1206b0;
    nop;
    lui        $2, (0x1000B020 >> 16);
  L00110864:
    lui        $4, (0x1000B420 >> 16);
    ori        $2, $2, (0x1000B020 & 0xFFFF);
    ori        $4, $4, (0x1000B420 & 0xFFFF);
    sw         $0, 0x0($2);
    lui        $3, (0x1000D420 >> 16);
    sw         $0, 0x0($4);
    ori        $3, $3, (0x1000D420 & 0xFFFF);
    sw         $0, 0x0($3);
    lui        $2, (0x10002010 >> 16);
    ori        $2, $2, (0x10002010 & 0xFFFF);
    lui        $3, (0x40000000 >> 16);
    ld         $31, 0x0($29);
    daddu      $4, $0, $0;
    sw         $3, 0x0($2);
    daddu      $5, $0, $0;
    j          IpuSync_115e50;
    addiu     $29, $29, 0x10;
}
