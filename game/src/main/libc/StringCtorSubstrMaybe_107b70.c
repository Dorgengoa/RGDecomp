#include "types.h"

extern void StringReserve_107e80(void);
extern void StringReplaceFromStringMaybe_107cd0(void);

asm void StringCtorSubstrMaybe_107b70(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $31, 0x30($29);
    sq         $18, 0x20($29);
    sq         $17, 0x10($29);
    daddu      $18, $4, $0;
    sq         $16, 0x0($29);
    daddu      $17, $5, $0;
    sw         $7, 0x48($29);
    sw         $0, 0x0($4);
    sw         $0, 0x4($4);
    sw         $0, 0x8($4);
    lw         $2, 0x0($5);
    andi       $2, $2, 0x1;
    beqz       $2, L00107BB4;
    daddu     $16, $6, $0;
    b          L00107BC0;
    lw        $2, 0x4($17);
  L00107BB4:
    lbu        $2, 0x0($17);
    dsll32     $2, $2, 24;
    dsrl32     $2, $2, 25;
  L00107BC0:
    sltu       $1, $2, $16;
    bnel       $1, $0, L00107BF0;
    daddu     $5, $0, $0;
    subu       $3, $2, $16;
    lw         $2, 0x48($29);
    sltu       $1, $3, $2;
    beqz       $1, L00107BE8;
    sw        $3, 0x4C($29);
    b          L00107BEC;
    addiu     $2, $29, 0x4C;
  L00107BE8:
    addiu      $2, $29, 0x48;
  L00107BEC:
    lw         $5, 0x0($2);
  L00107BF0:
    jal        StringReserve_107e80;
    daddu     $4, $18, $0;
    lw         $9, 0x48($29);
    daddu      $7, $17, $0;
    daddu      $8, $16, $0;
    daddu      $4, $18, $0;
    daddu      $5, $0, $0;
    jal        StringReplaceFromStringMaybe_107cd0;
    daddu     $6, $0, $0;
    daddu      $2, $18, $0;
    ld         $31, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

