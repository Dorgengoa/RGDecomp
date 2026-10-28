#include "types.h"

extern void CreateSema(void);
extern void CreateThread(void);
extern void DeleteSema(void);
extern void StartThread_1176e0(void);
extern void GetThreadId(void);
extern void ChangeThreadPriority(void);

asm void InitThread_117378(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    sd         $16, 0x50($29);
    lui        $16, 0x44;
    sd         $31, 0x80($29);
    lw         $2, 0x61F8($16);
    sd         $18, 0x70($29);
    bgtz       $2, L00117414;
    sd        $17, 0x60($29);
    lui        $2, 0x45;
    addiu      $3, $0, 0xFF;
    addiu      $17, $2, 0x6698;
    sw         $3, 0x34($29);
    sw         $0, 0x38($29);
    addiu      $4, $29, 0x30;
    sw         $17, 0x44($29);
    jal        CreateSema;
    lui       $18, 0x48;
    bltz       $2, L00117414;
    sw        $2, 0x5FC0($18);
    lui        $2, 0x11;
    lui        $3, 0x48;
    lui        $5, 0x48;
    addiu      $2, $2, 0x72A0;
    addiu      $3, $3, 0x5BC0;
    addiu      $5, $5, 0x5170;
    addiu      $6, $0, 0x400;
    sw         $2, 0x4($29);
    sw         $3, 0x8($29);
    daddu      $4, $29, $0;
    sw         $6, 0xC($29);
    sw         $5, 0x10($29);
    sw         $17, 0x20($29);
    jal        CreateThread;
    sw        $0, 0x14($29);
    daddu      $4, $2, $0;
    bgez       $4, L0011741C;
    sw        $4, 0x61F8($16);
    jal        DeleteSema;
    lw        $4, 0x5FC0($18);
  L00117414:
    b          L0011744C;
    addiu     $2, $0, -0x1;
  L0011741C:
    lui        $2, 0x48;
    addiu      $3, $2, 0x5FC8;
    sw         $0, 0x5FC8($2);
    daddu      $5, $3, $0;
    jal        StartThread_1176e0;
    sw        $0, 0x4($3);
    jal        GetThreadId;
    nop;
    daddu      $4, $2, $0;
    jal        ChangeThreadPriority;
    addiu     $5, $0, 0x1;
    lw         $2, 0x61F8($16);
  L0011744C:
    ld         $31, 0x80($29);
    ld         $18, 0x70($29);
    ld         $17, 0x60($29);
    ld         $16, 0x50($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
