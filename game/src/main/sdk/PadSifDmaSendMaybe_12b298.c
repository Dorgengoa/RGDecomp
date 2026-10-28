#include "types.h"

extern void sceSifDmaStat(void);
extern void SyncDCache(void);
extern void sceSifSetDma(void);
extern void scePrintf_119288(void);

asm void PadSifDmaSendMaybe_12b298(void)
{
    .set noreorder;
    addiu      $29, $29, -0x150;
    addiu      $3, $0, 0x1C;
    sd         $18, 0x120($29);
    sd         $16, 0x100($29);
    daddu      $18, $4, $0;
    daddu      $16, $5, $0;
    addiu      $4, $0, 0x70;
    mult1      $4, $18, $4;
    mult       $3, $16, $3;
    sd         $19, 0x130($29);
    lui        $19, 0x49;
    sd         $31, 0x140($29);
    sd         $17, 0x110($29);
    addiu      $2, $19, -0x12B0;
    addu       $3, $3, $4;
    addu       $5, $2, $3;
    daddu      $2, $5, $0;
    lw         $4, 0xC($5);
    beqz       $4, L0012B2F8;
    lw        $17, 0x4($2);
    jal        sceSifDmaStat;
    nop;
    bgez       $2, L0012B36C;
    lui       $2, 0x45;
  L0012B2F8:
    addiu      $7, $0, 0x1C;
    addiu      $3, $0, 0x70;
    mult       $7, $16, $7;
    mult1      $3, $18, $3;
    lw         $6, 0x0($17);
    addiu      $19, $19, -0x12B0;
    daddu      $4, $17, $0;
    addiu      $5, $17, 0x1F;
    addiu      $6, $6, 0x1;
    addu       $18, $7, $3;
    andi       $2, $6, 0x1;
    addu       $3, $19, $18;
    sll        $2, $2, 5;
    lw         $16, 0x8($3);
    sw         $6, 0x0($17);
    jal        SyncDCache;
    addu      $16, $16, $2;
    addiu      $2, $0, 0x20;
    sw         $16, 0x4($29);
    sw         $17, 0x0($29);
    daddu      $4, $29, $0;
    sw         $2, 0x8($29);
    addiu      $5, $0, 0x1;
    jal        sceSifSetDma;
    sw        $0, 0xC($29);
    daddu      $4, $2, $0;
    bnez       $4, L0012B388;
    addu      $3, $19, $18;
    lui        $2, 0x45;
  L0012B36C:
    lw         $3, -0x6AF4($2);
    beqz       $3, L0012B380;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7CD0;
  L0012B380:
    b          L0012B390;
    daddu     $2, $0, $0;
  L0012B388:
    addiu      $2, $0, 0x1;
    sw         $4, 0xC($3);
  L0012B390:
    ld         $31, 0x140($29);
    ld         $19, 0x130($29);
    ld         $18, 0x120($29);
    ld         $17, 0x110($29);
    ld         $16, 0x100($29);
    jr         $31;
    addiu     $29, $29, 0x150;
}
