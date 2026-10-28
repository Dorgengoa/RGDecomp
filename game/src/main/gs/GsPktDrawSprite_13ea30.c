#include "types.h"

extern void GsPktOpenGifTag_13f3b0(void);
extern void GsPktFinalizeTags_13f260(void);

asm void GsPktDrawSprite_13ea30(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    addiu      $6, $0, 0x441;
    sd         $31, 0x20($29);
    daddu      $7, $0, $0;
    sq         $17, 0x10($29);
    addiu      $8, $0, 0x3;
    sq         $16, 0x0($29);
    daddu      $17, $4, $0;
    daddu      $16, $5, $0;
    jal        GsPktOpenGifTag_13f3b0;
    addiu     $5, $0, 0x6;
    lw         $4, 0xF4($17);
    addiu      $3, $0, 0x1;
    lq         $5, 0x0($16);
    addiu      $2, $4, 0x10;
    sw         $2, 0xF4($17);
    sq         $5, 0x0($4);
    lw         $2, 0xF4($17);
    addiu      $4, $2, 0x20;
    sw         $4, 0xF4($17);
    lw         $4, 0x11C($17);
    bnel       $4, $3, L0013EA98;
    addiu     $3, $0, 0x2;
    lq         $3, 0x10($16);
    b          L0013EB30;
    sq        $3, 0x0($2);
  L0013EA98:
    bnel       $4, $3, L0013EAD4;
    lw        $5, 0x10($16);
    lw         $4, 0x10($16);
    lw         $3, 0x128($17);
    addu       $3, $4, $3;
    sw         $3, 0x0($2);
    lw         $4, 0x14($16);
    lw         $3, 0x12C($17);
    addu       $3, $4, $3;
    sw         $3, 0x4($2);
    lw         $3, 0x18($16);
    sw         $3, 0x8($2);
    lw         $3, 0x1C($16);
    b          L0013EB30;
    sw        $3, 0xC($2);
  L0013EAD4:
    lw         $3, 0x128($17);
    lw         $4, 0x130($17);
    addu       $5, $5, $3;
    bgez       $4, L0013EAF0;
    sra       $3, $4, 1;
    addiu      $3, $4, 0x1;
    sra        $3, $3, 1;
  L0013EAF0:
    subu       $3, $5, $3;
    sw         $3, 0x0($2);
    lw         $5, 0x14($16);
    lw         $3, 0x12C($17);
    lw         $4, 0x134($17);
    addu       $5, $5, $3;
    bgez       $4, L0013EB18;
    sra       $3, $4, 1;
    addiu      $3, $4, 0x1;
    sra        $3, $3, 1;
  L0013EB18:
    subu       $3, $5, $3;
    sw         $3, 0x4($2);
    lw         $3, 0x18($16);
    sw         $3, 0x8($2);
    lw         $3, 0x1C($16);
    sw         $3, 0xC($2);
  L0013EB30:
    lw         $4, 0x11C($17);
    addiu      $3, $0, 0x1;
    bnel       $4, $3, L0013EB4C;
    addiu     $3, $0, 0x2;
    lq         $3, 0x20($16);
    b          L0013EBE4;
    sq        $3, 0x10($2);
  L0013EB4C:
    bnel       $4, $3, L0013EB88;
    lw        $5, 0x20($16);
    lw         $4, 0x20($16);
    lw         $3, 0x128($17);
    addu       $3, $4, $3;
    sw         $3, 0x10($2);
    lw         $4, 0x24($16);
    lw         $3, 0x12C($17);
    addu       $3, $4, $3;
    sw         $3, 0x14($2);
    lw         $3, 0x28($16);
    sw         $3, 0x18($2);
    lw         $3, 0x2C($16);
    b          L0013EBE4;
    sw        $3, 0x1C($2);
  L0013EB88:
    lw         $3, 0x128($17);
    lw         $4, 0x130($17);
    addu       $5, $5, $3;
    bgez       $4, L0013EBA4;
    sra       $3, $4, 1;
    addiu      $3, $4, 0x1;
    sra        $3, $3, 1;
  L0013EBA4:
    subu       $3, $5, $3;
    sw         $3, 0x10($2);
    lw         $5, 0x24($16);
    lw         $3, 0x12C($17);
    lw         $4, 0x134($17);
    addu       $5, $5, $3;
    bgez       $4, L0013EBCC;
    sra       $3, $4, 1;
    addiu      $3, $4, 0x1;
    sra        $3, $3, 1;
  L0013EBCC:
    subu       $3, $5, $3;
    sw         $3, 0x14($2);
    lw         $3, 0x28($16);
    sw         $3, 0x18($2);
    lw         $3, 0x2C($16);
    sw         $3, 0x1C($2);
  L0013EBE4:
    jal        GsPktFinalizeTags_13f260;
    daddu     $4, $17, $0;
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

