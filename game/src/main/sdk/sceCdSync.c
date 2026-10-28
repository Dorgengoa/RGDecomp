#include "types.h"

extern void scePrintf_119288(void);
extern void DelayThread_117618(void);
extern void sceSifCheckStatRpc(void);

asm void sceCdSync(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $31, 0x20($29);
    sd         $17, 0x10($29);
    bnez       $4, L00129D54;
    sd        $16, 0x0($29);
    lui        $2, 0x44;
    lw         $3, 0x7950($2);
    blez       $3, L00129D1C;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7B10;
  L00129D1C:
    lui        $17, 0x44;
    b          L00129D30;
    lui       $16, 0x45;
  L00129D28:
    jal        DelayThread_117618;
    addiu     $4, $0, 0xFA0;
  L00129D30:
    lw         $2, 0x7974($17);
    bnez       $2, L00129D28;
    nop;
    jal        sceSifCheckStatRpc;
    addiu     $4, $16, -0x74F0;
    bnez       $2, L00129D28;
    daddu     $2, $0, $0;
    b          L00129D80;
    ld        $31, 0x20($29);
  L00129D54:
    lui        $2, 0x44;
    lw         $3, 0x7974($2);
    bnez       $3, L00129D7C;
    addiu     $2, $0, 0x1;
    lui        $4, 0x45;
    jal        sceSifCheckStatRpc;
    addiu     $4, $4, -0x74F0;
    bnez       $2, L00129D7C;
    addiu     $2, $0, 0x1;
    daddu      $2, $0, $0;
  L00129D7C:
    ld         $31, 0x20($29);
  L00129D80:
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
