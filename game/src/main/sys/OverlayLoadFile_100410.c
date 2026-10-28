#include "types.h"

extern void FileReadAll_1004b0(void);
extern void OverlayLoadNotifyStubMaybe_100400(void);
extern void FlushCache(void);
extern void memset(void);
extern void RunStaticCtors_100df0(void);

asm void OverlayLoadFile_100410(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x30($29);
    sq         $18, 0x20($29);
    sq         $17, 0x10($29);
    daddu      $18, $5, $0;
    sq         $16, 0x0($29);
    jal        FileReadAll_1004b0;
    daddu     $17, $0, $0;
    daddu      $16, $2, $0;
    blezl      $16, L0010048C;
    daddu     $2, $17, $0;
    jal        OverlayLoadNotifyStubMaybe_100400;
    daddu     $4, $18, $0;
    lw         $17, 0x14($18);
    jal        FlushCache;
    daddu     $4, $0, $0;
    jal        FlushCache;
    addiu     $4, $0, 0x2;
    beql       $17, $0, L00100474;
    lw        $4, 0x18($18);
    addu       $4, $18, $16;
    daddu      $6, $17, $0;
    jal        memset;
    daddu     $5, $0, $0;
    lw         $4, 0x18($18);
  L00100474:
    daddu      $6, $0, $0;
    lw         $5, 0x1C($18);
    jal        RunStaticCtors_100df0;
    daddu     $7, $0, $0;
    addiu      $17, $0, 0x1;
    daddu      $2, $17, $0;
  L0010048C:
    ld         $31, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

