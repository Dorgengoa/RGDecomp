#include "types.h"

asm void SdrCallbackRpcDispatch_123018(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    daddu      $17, $5, $0;
    sd         $16, 0x0($29);
    lw         $3, 0x0($17);
    andi       $2, $3, 0x100;
    beqz       $2, L00123074;
    lui       $5, 0x44;
    lw         $2, 0x78E8($5);
    beqz       $2, L00123074;
    lui       $2, 0x44;
    lw         $3, 0x7900($2);
    daddu      $16, $28, $0;
    daddu      $28, $3, $0;
    lui        $4, 0x44;
    lw         $2, 0x78E8($5);
    lw         $5, 0x78F4($4);
    jalr $31, $2;
    daddu     $4, $0, $0;
    daddu      $3, $28, $0;
    daddu      $28, $16, $0;
    lw         $3, 0x0($17);
  L00123074:
    andi       $2, $3, 0x200;
    beqz       $2, L001230B8;
    lui       $5, 0x44;
    lw         $2, 0x78EC($5);
    beqz       $2, L001230B8;
    lui       $2, 0x44;
    lw         $3, 0x7904($2);
    daddu      $16, $28, $0;
    daddu      $28, $3, $0;
    lui        $4, 0x44;
    lw         $2, 0x78EC($5);
    lw         $5, 0x78F8($4);
    jalr $31, $2;
    addiu     $4, $0, 0x1;
    daddu      $3, $28, $0;
    daddu      $28, $16, $0;
    lw         $3, 0x0($17);
  L001230B8:
    andi       $2, $3, 0x400;
    beqz       $2, L001230F8;
    lui       $4, 0x44;
    lw         $2, 0x78F0($4);
    beqz       $2, L001230F8;
    lui       $2, 0x44;
    lw         $3, 0x7908($2);
    daddu      $16, $28, $0;
    daddu      $28, $3, $0;
    lui        $6, 0x44;
    lw         $2, 0x78F0($4);
    lw         $4, 0x4($17);
    jalr $31, $2;
    lw        $5, 0x78FC($6);
    daddu      $3, $28, $0;
    daddu      $28, $16, $0;
  L001230F8:
    ld         $31, 0x20($29);
    daddu      $2, $0, $0;
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

