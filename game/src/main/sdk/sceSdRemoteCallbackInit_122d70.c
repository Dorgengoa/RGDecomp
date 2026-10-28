#include "types.h"

extern void sceSdRemote_1229e8(void);
extern void CreateThread(void);
extern void StartThread_1176e0(void);
extern void scePrintf_119288(void);

asm void sceSdRemoteCallbackInit_122d70(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $17, 0x40($29);
    lui        $17, 0x44;
    sd         $16, 0x30($29);
    lw         $2, 0x790C($17);
    daddu      $16, $4, $0;
    bgez       $2, L00122E54;
    sd        $31, 0x50($29);
    lui        $5, 0x44;
    lui        $2, 0x44;
    lui        $3, 0x44;
    lui        $6, 0x44;
    lui        $7, 0x44;
    lui        $8, 0x44;
    lui        $9, 0x44;
    lui        $10, 0x44;
    lui        $11, 0x44;
    sw         $0, 0x78F0($5);
    sw         $0, 0x78E8($2);
    addiu      $4, $0, 0x1;
    sw         $0, 0x78EC($3);
    ori        $5, $0, 0xE620;
    sw         $0, 0x78F4($6);
    sw         $0, 0x78F8($7);
    sw         $0, 0x78FC($8);
    sw         $0, 0x7900($9);
    sw         $0, 0x7904($10);
    jal        sceSdRemote_1229e8;
    sw        $0, 0x7908($11);
    lui        $3, 0x12;
    lui        $2, 0x49;
    lui        $5, 0x45;
    lui        $6, 0x48;
    addiu      $3, $3, 0x2FA8;
    addiu      $2, $2, -0x2680;
    addiu      $5, $5, 0x6D00;
    addiu      $6, $6, 0x5170;
    addiu      $7, $0, 0x1000;
    sw         $3, 0x4($29);
    sw         $2, 0x8($29);
    daddu      $4, $29, $0;
    sw         $7, 0xC($29);
    sw         $16, 0x14($29);
    sw         $5, 0x20($29);
    jal        CreateThread;
    sw        $6, 0x10($29);
    bltz       $2, L00122E54;
    sw        $2, 0x790C($17);
    daddu      $4, $2, $0;
    sw         $2, 0x20($29);
    jal        StartThread_1176e0;
    daddu     $5, $0, $0;
    bgez       $2, L00122E58;
    lw        $2, 0x20($29);
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x6D18;
  L00122E54:
    addiu      $2, $0, -0x1;
  L00122E58:
    ld         $31, 0x50($29);
    ld         $17, 0x40($29);
    ld         $16, 0x30($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
