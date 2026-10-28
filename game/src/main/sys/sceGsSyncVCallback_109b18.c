#include "types.h"

extern void sceGsGetGParam_1082a0(void);
extern void DisableIntc_117080(void);
extern void RemoveIntcHandler(void);
extern void AddIntcHandler(void);
extern void EnableIntc_1170e8(void);

asm void sceGsSyncVCallback_109b18(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x10($29);
    sd         $18, 0x20($29);
    sd         $16, 0x0($29);
    sd         $31, 0x30($29);
    jal        sceGsGetGParam_1082a0;
    daddu     $17, $4, $0;
    daddu      $16, $2, $0;
    bnez       $17, L00109B60;
    lw        $18, 0x8($16);
    jal        DisableIntc_117080;
    addiu     $4, $0, 0x2;
    lw         $5, 0xC($16);
    jal        RemoveIntcHandler;
    addiu     $4, $0, 0x2;
    sw         $0, 0x8($16);
    b          L00109B9C;
    sw        $0, 0xC($16);
  L00109B60:
    beql       $18, $0, L00109B80;
    sw        $17, 0x8($16);
    jal        DisableIntc_117080;
    addiu     $4, $0, 0x2;
    lw         $5, 0xC($16);
    jal        RemoveIntcHandler;
    addiu     $4, $0, 0x2;
    sw         $17, 0x8($16);
  L00109B80:
    daddu      $5, $17, $0;
    addiu      $4, $0, 0x2;
    jal        AddIntcHandler;
    addiu     $6, $0, -0x1;
    sw         $2, 0xC($16);
    jal        EnableIntc_1170e8;
    addiu     $4, $0, 0x2;
  L00109B9C:
    daddu      $2, $18, $0;
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

