#include "types.h"

extern void FlushCache(void);
extern void sceDeci2Open(void);
extern void QueueInit(void);

asm void sceTtyInit(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    daddu      $4, $0, $0;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    jal        FlushCache;
    lui       $16, 0x48;
    addiu      $17, $16, 0x6510;
    lui        $6, 0x11;
    addiu      $4, $0, 0x210;
    addiu      $6, $6, 0x7B60;
    jal        sceDeci2Open;
    daddu     $5, $17, $0;
    sw         $2, 0x6510($16);
    lw         $2, 0x6510($16);
    bgez       $2, L00117F8C;
    lui       $4, 0x48;
    b          L00117FE8;
    daddu     $2, $0, $0;
  L00117F8C:
    lui        $2, 0x48;
    sw         $0, 0xC($17);
    lui        $3, (0x20000002 >> 16);
    addiu      $4, $4, 0x6680;
    addiu      $2, $2, 0x6540;
    or         $2, $2, $3;
    sw         $0, 0x4($17);
    or         $4, $4, $3;
    sw         $0, 0x8($17);
    sw         $4, 0x14($17);
    addiu      $6, $0, 0x210;
    sw         $2, 0x10($17);
    addiu      $5, $0, 0x45;
    addiu      $3, $0, 0x48;
    addiu      $4, $0, 0x100;
    sh         $6, (0x20000004 & 0xFFFF)($2);
    sb         $5, (0x20000006 & 0xFFFF)($2);
    sb         $3, (0x20000007 & 0xFFFF)($2);
    sw         $0, (0x20000008 & 0xFFFF)($2);
    jal        QueueInit;
    sh        $0, (0x20000002 & 0xFFFF)($2);
    sw         $2, 0x18($17);
    addiu      $2, $0, 0x1;
  L00117FE8:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
