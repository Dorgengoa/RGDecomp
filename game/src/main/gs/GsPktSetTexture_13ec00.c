#include "types.h"

extern void NameTableCopyNode_15ad70(void);
extern void GsTex1SetFilter_15ac10(void);

asm void GsPktSetTexture_13ec00(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $31, 0x10($29);
    sq         $16, 0x0($29);
    beqz       $5, L0013EC70;
    daddu     $16, $4, $0;
    jal        NameTableCopyNode_15ad70;
    addiu     $4, $16, 0x78;
    lw         $5, 0xE0($16);
    jal        GsTex1SetFilter_15ac10;
    addiu     $4, $16, 0x78;
    lw         $8, 0xF4($16);
    addiu      $7, $0, 0x3F;
    addiu      $6, $0, 0x14;
    addiu      $5, $0, 0x6;
    addiu      $4, $0, 0x8;
    sd         $0, 0x0($8);
    addiu      $3, $8, 0x40;
    sd         $7, 0x8($8);
    ld         $7, 0xB8($16);
    sd         $7, 0x10($8);
    sd         $6, 0x18($8);
    ld         $6, 0xB0($16);
    sd         $6, 0x20($8);
    sd         $5, 0x28($8);
    ld         $5, 0xC0($16);
    sd         $5, 0x30($8);
    sd         $4, 0x38($8);
    sw         $3, 0xF4($16);
  L0013EC70:
    ld         $31, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

