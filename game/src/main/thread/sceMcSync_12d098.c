#include "types.h"

extern void PollSema(void);
extern void WaitSema(void);
extern void SignalSema(void);

asm void sceMcSync_12d098(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $19, 0x30($29);
    lui        $19, 0x45;
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    daddu      $21, $6, $0;
    sd         $18, 0x20($29);
    daddu      $20, $5, $0;
    lw         $2, -0x6AA8($19);
    daddu      $18, $4, $0;
    sd         $31, 0x60($29);
    sd         $17, 0x10($29);
    bnez       $2, L0012D0D8;
    sd        $16, 0x0($29);
    b          L0012D138;
    addiu     $2, $0, -0x1;
  L0012D0D8:
    lui        $17, 0x45;
    jal        PollSema;
    lw        $4, -0x6AA0($17);
    bnez       $18, L0012D0FC;
    slti      $16, $2, 0x0;
    beqz       $16, L0012D0FC;
    lw        $4, -0x6AA0($17);
    jal        WaitSema;
    daddu     $16, $0, $0;
  L0012D0FC:
    beqz       $20, L0012D10C;
    sltiu     $16, $16, 0x1;
    lw         $2, -0x6AA8($19);
    sw         $2, 0x0($20);
  L0012D10C:
    beqz       $16, L0012D138;
    daddu     $2, $16, $0;
    beqz       $21, L0012D128;
    sw        $0, -0x6AA8($19);
    lui        $2, 0x49;
    lw         $3, 0x5C0($2);
    sw         $3, 0x0($21);
  L0012D128:
    lui        $2, 0x45;
    jal        SignalSema;
    lw        $4, -0x6AA4($2);
    daddu      $2, $16, $0;
  L0012D138:
    ld         $31, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}
