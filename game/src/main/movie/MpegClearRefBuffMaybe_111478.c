#include "types.h"

asm void MpegClearRefBuffMaybe_111478(void)
{
    .set noreorder;
    lw         $3, 0x40($4);
    lw         $2, 0x1C8($3);
    bnel       $2, $0, L00111488;
    sw        $0, 0x28($2);
  L00111488:
    lw         $2, 0x1D8($3);
    bnel       $2, $0, L00111494;
    sw        $0, 0x28($2);
  L00111494:
    lw         $2, 0x1E8($3);
    bnel       $2, $0, L001114A0;
    sw        $0, 0x28($2);
  L001114A0:
    lw         $2, 0x1CC($3);
    bnel       $2, $0, L001114AC;
    sw        $0, 0x28($2);
  L001114AC:
    lw         $2, 0x1DC($3);
    bnel       $2, $0, L001114B8;
    sw        $0, 0x28($2);
  L001114B8:
    lw         $2, 0x1EC($3);
    bnel       $2, $0, L001114C4;
    sw        $0, 0x28($2);
  L001114C4:
    jr         $31;
    addiu     $2, $0, 0x1;
}
