#include "types.h"

extern void scePrintf_119288(void);

asm void sceGsSyncPath_109030(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $5, $0, $0;
    bnez       $4, L001092C4;
    sd        $31, 0x0($29);
    lui        $2, (0x10009000 >> 16);
    ori        $2, $2, (0x10009000 & 0xFFFF);
    lw         $3, 0x0($2);
    andi       $3, $3, 0x100;
    beqz       $3, L00109084;
    lui       $3, (0x10009000 >> 16);
    lui        $4, (0x1000000 >> 16);
    ori        $3, $3, (0x10009000 & 0xFFFF);
    daddu      $2, $5, $0;
    nop;
  L00109068:
    sltu       $2, $4, $2;
    bnez       $2, L0010918C;
    addiu     $5, $5, 0x1;
    lw         $2, 0x0($3);
    andi       $2, $2, 0x100;
    bnez       $2, L00109068;
    daddu     $2, $5, $0;
  L00109084:
    lui        $2, (0x1000A000 >> 16);
    ori        $2, $2, (0x1000A000 & 0xFFFF);
    lw         $3, 0x0($2);
    andi       $3, $3, 0x100;
    beqz       $3, L001090C4;
    lui       $3, (0x1000A000 >> 16);
    lui        $4, (0x1000000 >> 16);
    ori        $3, $3, (0x1000A000 & 0xFFFF);
    daddu      $2, $5, $0;
  L001090A8:
    sltu       $2, $4, $2;
    bnez       $2, L00109198;
    addiu     $5, $5, 0x1;
    lw         $2, 0x0($3);
    andi       $2, $2, 0x100;
    bnez       $2, L001090A8;
    daddu     $2, $5, $0;
  L001090C4:
    lui        $2, (0x10003C00 >> 16);
    lui        $4, (0x1F000003 >> 16);
    ori        $2, $2, (0x10003C00 & 0xFFFF);
    ori        $4, $4, (0x1F000003 & 0xFFFF);
    lw         $3, 0x0($2);
    and        $3, $3, $4;
    beqz       $3, L00109114;
    lui       $3, (0x1F000003 >> 16);
    lui        $4, (0x10003C00 >> 16);
    lui        $6, (0x1000000 >> 16);
    ori        $4, $4, (0x10003C00 & 0xFFFF);
    ori        $3, $3, (0x1F000003 & 0xFFFF);
    daddu      $2, $5, $0;
  L001090F8:
    sltu       $2, $6, $2;
    bnez       $2, L001091A4;
    addiu     $5, $5, 0x1;
    lw         $2, 0x0($4);
    and        $2, $2, $3;
    bnez       $2, L001090F8;
    daddu     $2, $5, $0;
  L00109114:
    cfc2.ni    $6, $vi29;
    andi       $2, $6, 0x100;
    beqz       $2, L00109144;
    lui       $3, (0x1000000 >> 16);
    daddu      $2, $5, $0;
  L00109128:
    sltu       $2, $3, $2;
    bnez       $2, L001091B0;
    addiu     $5, $5, 0x1;
    cfc2.ni    $6, $vi29;
    andi       $2, $6, 0x100;
    bnez       $2, L00109128;
    daddu     $2, $5, $0;
  L00109144:
    lui        $2, (0x10003020 >> 16);
    ori        $2, $2, (0x10003020 & 0xFFFF);
    lw         $3, 0x0($2);
    andi       $3, $3, 0xC00;
    beqz       $3, L00109184;
    lui       $3, (0x10003020 >> 16);
    lui        $4, (0x1000000 >> 16);
    ori        $3, $3, (0x10003020 & 0xFFFF);
    daddu      $2, $5, $0;
  L00109168:
    sltu       $2, $4, $2;
    bnez       $2, L001091BC;
    addiu     $5, $5, 0x1;
    lw         $2, 0x0($3);
    andi       $2, $2, 0xC00;
    bnez       $2, L00109168;
    daddu     $2, $5, $0;
  L00109184:
    b          L00109338;
    daddu     $2, $0, $0;
  L0010918C:
    lui        $4, 0x45;
    b          L001091C4;
    addiu     $4, $4, 0x5CB0;
  L00109198:
    lui        $4, 0x45;
    b          L001091C4;
    addiu     $4, $4, 0x5D90;
  L001091A4:
    lui        $4, 0x45;
    b          L001091C4;
    addiu     $4, $4, 0x5DC0;
  L001091B0:
    lui        $4, 0x45;
    b          L001091C4;
    addiu     $4, $4, 0x5DF0;
  L001091BC:
    lui        $4, 0x45;
    addiu      $4, $4, 0x5E18;
  L001091C4:
    jal        scePrintf_119288;
    nop;
    lui        $2, (0x10009000 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x10009000 & 0xFFFF);
    addiu      $4, $4, 0x5CE0;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    lui        $2, (0x10009030 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x10009030 & 0xFFFF);
    addiu      $4, $4, 0x5CF0;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    lui        $2, (0x10009010 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x10009010 & 0xFFFF);
    addiu      $4, $4, 0x5D00;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    lui        $2, (0x10009020 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x10009020 & 0xFFFF);
    addiu      $4, $4, 0x5D10;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    lui        $2, (0x1000A000 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x1000A000 & 0xFFFF);
    addiu      $4, $4, 0x5D20;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    lui        $2, (0x1000A030 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x1000A030 & 0xFFFF);
    addiu      $4, $4, 0x5D30;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    lui        $2, (0x1000A010 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x1000A010 & 0xFFFF);
    addiu      $4, $4, 0x5D40;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    lui        $2, (0x1000A020 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x1000A020 & 0xFFFF);
    addiu      $4, $4, 0x5D50;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    lui        $2, (0x10003C00 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x10003C00 & 0xFFFF);
    addiu      $4, $4, 0x5D60;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    lui        $2, (0x10003020 >> 16);
    lui        $4, 0x45;
    ori        $2, $2, (0x10003020 & 0xFFFF);
    addiu      $4, $4, 0x5D78;
    jal        scePrintf_119288;
    lw        $5, 0x0($2);
    b          L00109338;
    addiu     $2, $0, -0x1;
  L001092C4:
    lui        $3, (0x10009000 >> 16);
    lui        $5, (0x1000A000 >> 16);
    ori        $3, $3, (0x10009000 & 0xFFFF);
    ori        $5, $5, (0x1000A000 & 0xFFFF);
    lw         $2, 0x0($3);
    lui        $4, (0x10003C00 >> 16);
    lw         $6, 0x0($5);
    ori        $4, $4, (0x10003C00 & 0xFFFF);
    andi       $2, $2, 0x100;
    lw         $5, 0x0($4);
    sltu       $2, $0, $2;
    andi       $6, $6, 0x100;
    ori        $4, $2, 0x2;
    lui        $3, (0x1F000003 >> 16);
    movn       $2, $4, $6;
    ori        $3, $3, (0x1F000003 & 0xFFFF);
    and        $5, $5, $3;
    ori        $4, $2, 0x4;
    movn       $2, $4, $5;
    cfc2.ni    $6, $vi29;
    lui        $3, (0x10003020 >> 16);
    andi       $6, $6, 0x100;
    ori        $3, $3, (0x10003020 & 0xFFFF);
    ori        $5, $2, 0x8;
    lw         $4, 0x0($3);
    movn       $2, $5, $6;
    ori        $3, $2, 0x10;
    andi       $4, $4, 0xC00;
    movn       $2, $3, $4;
  L00109338:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

