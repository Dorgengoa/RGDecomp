#include "types.h"

extern void KprintfSerialMaybe_119308(void);
extern void sceDeci2ExRecv(void);
extern void QueuePeekWriteDone(void);
extern void sceDeci2ExSend(void);

asm void sceTtyHandler(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    addiu      $2, $0, 0x3;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    daddu      $17, $6, $0;
    sd         $31, 0x30($29);
    daddu      $16, $5, $0;
    beq        $4, $2, L00117C6C;
    sd        $18, 0x20($29);
    slti       $2, $4, 0x4;
    bnez       $2, L00117BA0;
    addiu     $2, $0, 0x4;
    beq        $4, $2, L00117CBC;
    ld        $31, 0x30($29);
    b          L00117CE4;
    ld        $18, 0x20($29);
  L00117BA0:
    blez       $4, L00117CE0;
    ld        $31, 0x30($29);
    beql       $16, $0, L00117C10;
    lw        $18, 0x14($17);
    lw         $2, 0x8($17);
    addu       $2, $2, $16;
    sltiu      $2, $2, 0x141;
    bnez       $2, L00117BCC;
    lui       $4, 0x45;
    jal        KprintfSerialMaybe_119308;
    addiu     $4, $4, 0x66C8;
  L00117BCC:
    lw         $2, 0x8($17);
    andi       $6, $16, 0xFFFF;
    lw         $5, 0x14($17);
    lw         $4, 0x0($17);
    jal        sceDeci2ExRecv;
    addu      $5, $5, $2;
    daddu      $16, $2, $0;
    bgez       $16, L00117BFC;
    nop;
    lui        $4, 0x45;
    jal        KprintfSerialMaybe_119308;
    addiu     $4, $4, 0x66F0;
  L00117BFC:
    lw         $2, 0x8($17);
    addu       $2, $2, $16;
    sw         $2, 0x8($17);
    b          L00117CE0;
    ld        $31, 0x30($29);
  L00117C10:
    addiu      $16, $0, 0xC;
    lhu        $2, 0x0($18);
    slt        $2, $16, $2;
    beqz       $2, L00117C60;
    daddu     $3, $18, $0;
    b          L00117C34;
    lw        $4, 0x18($17);
    nop;
  L00117C30:
    lw         $4, 0x18($17);
  L00117C34:
    addu       $2, $3, $16;
    lbu        $3, 0x0($2);
    addiu      $16, $16, 0x1;
    lw         $2, 0xC($4);
    sb         $3, 0x0($2);
    jal        QueuePeekWriteDone;
    lw        $4, 0x18($17);
    lhu        $2, 0x0($18);
    slt        $2, $16, $2;
    bnel       $2, $0, L00117C30;
    lw        $3, 0x14($17);
  L00117C60:
    sw         $0, 0x8($17);
    b          L00117CE0;
    ld        $31, 0x30($29);
  L00117C6C:
    lw         $6, 0x4($17);
    lw         $4, 0x0($17);
    lw         $5, 0x10($17);
    jal        sceDeci2ExSend;
    andi      $6, $6, 0xFFFF;
    daddu      $5, $2, $0;
    bgezl      $5, L00117CA0;
    lw        $2, 0x10($17);
    lui        $4, 0x45;
    jal        KprintfSerialMaybe_119308;
    addiu     $4, $4, 0x6708;
    b          L00117CD8;
    nop;
  L00117CA0:
    lw         $3, 0x4($17);
    addu       $2, $2, $5;
    subu       $3, $3, $5;
    sw         $2, 0x10($17);
    sw         $3, 0x4($17);
    b          L00117CE0;
    ld        $31, 0x30($29);
  L00117CBC:
    lw         $2, 0x4($17);
    beqz       $2, L00117CD8;
    nop;
    lui        $4, 0x45;
    lw         $5, 0x4($17);
    jal        KprintfSerialMaybe_119308;
    addiu     $4, $4, 0x6720;
  L00117CD8:
    sw         $0, 0xC($17);
    ld         $31, 0x30($29);
  L00117CE0:
    ld         $18, 0x20($29);
  L00117CE4:
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
