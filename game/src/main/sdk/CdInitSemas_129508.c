#include "types.h"

extern void CreateSema(void);

asm void CdInitSemas_129508(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    addiu      $3, $0, -0x1;
    sd         $17, 0x30($29);
    lui        $17, 0x44;
    sd         $31, 0x50($29);
    lw         $2, 0x7968($17);
    sd         $18, 0x40($29);
    beq        $2, $3, L00129550;
    sd        $16, 0x20($29);
    lui        $16, 0x44;
    lw         $2, 0x796C($16);
    beq        $2, $3, L00129554;
    lui       $18, 0x44;
    lw         $2, 0x7970($18);
    bne        $2, $3, L001295D8;
    ld        $31, 0x50($29);
    b          L0012955C;
    lui       $2, 0x45;
  L00129550:
    lui        $16, 0x44;
  L00129554:
    lui        $18, 0x44;
    lui        $2, 0x45;
  L0012955C:
    addiu      $3, $0, 0x1;
    addiu      $2, $2, 0x7A18;
    sw         $3, 0x4($29);
    sw         $2, 0x14($29);
    daddu      $4, $29, $0;
    jal        CreateSema;
    sw        $3, 0x8($29);
    lui        $3, 0x45;
    sw         $2, 0x7968($17);
    addiu      $3, $3, 0x7A28;
    daddu      $4, $29, $0;
    jal        CreateSema;
    sw        $3, 0x14($29);
    lui        $3, 0x45;
    sw         $2, 0x796C($16);
    addiu      $3, $3, 0x7A38;
    daddu      $4, $29, $0;
    jal        CreateSema;
    sw        $3, 0x14($29);
    lui        $3, 0x45;
    sw         $2, 0x7970($18);
    addiu      $3, $3, 0x7A48;
    daddu      $4, $29, $0;
    sw         $3, 0x14($29);
    jal        CreateSema;
    sw        $0, 0x8($29);
    lui        $3, 0x44;
    sw         $2, 0x7960($3);
    lui        $2, 0x44;
    sw         $0, 0x7974($2);
    ld         $31, 0x50($29);
  L001295D8:
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
