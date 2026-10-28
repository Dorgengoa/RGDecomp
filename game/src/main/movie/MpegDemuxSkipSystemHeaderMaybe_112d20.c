#include "types.h"

asm void MpegDemuxSkipSystemHeaderMaybe_112d20(void)
{
    .set noreorder;
    daddu      $6, $4, $0;
    ld         $2, 0x0($6);
    lw         $3, 0x18($6);
    dsll32     $2, $2, 24;
    addiu      $3, $3, -0x38;
    sd         $2, 0x0($6);
    slti       $4, $3, 0x39;
    beqz       $4, L00112DA4;
    sw        $3, 0x18($6);
    lw         $8, 0x20($6);
    ld         $9, 0x8($6);
    nop;
  L00112D50:
    lw         $5, 0x14($6);
    addiu      $2, $0, 0x38;
    lw         $7, 0x18($6);
    lbu        $3, 0x0($5);
    subu       $2, $2, $7;
    ld         $4, 0x0($6);
    dsllv      $3, $3, $2;
    addiu      $5, $5, 0x1;
    or         $4, $4, $3;
    sltu       $2, $5, $8;
    sd         $4, 0x0($6);
    bnez       $2, L00112D8C;
    sw        $5, 0x14($6);
    lw         $2, 0x1C($6);
    sw         $2, 0x14($6);
  L00112D8C:
    addiu      $2, $7, 0x8;
    slti       $3, $2, 0x39;
    bnez       $3, L00112D50;
    sw        $2, 0x18($6);
    b          L00112DAC;
    ld        $2, 0x0($6);
  L00112DA4:
    ld         $9, 0x8($6);
    ld         $2, 0x0($6);
  L00112DAC:
    daddiu     $5, $9, 0x38;
    lw         $3, 0x18($6);
    dsll32     $2, $2, 8;
    sd         $5, 0x8($6);
    addiu      $3, $3, -0x28;
    sd         $2, 0x0($6);
    slti       $4, $3, 0x39;
    beqz       $4, L00112E2C;
    sw        $3, 0x18($6);
    lw         $8, 0x20($6);
    daddu      $9, $5, $0;
  L00112DD8:
    lw         $5, 0x14($6);
    addiu      $2, $0, 0x38;
    lw         $7, 0x18($6);
    lbu        $3, 0x0($5);
    subu       $2, $2, $7;
    ld         $4, 0x0($6);
    dsllv      $3, $3, $2;
    addiu      $5, $5, 0x1;
    or         $4, $4, $3;
    sltu       $2, $5, $8;
    sd         $4, 0x0($6);
    bnez       $2, L00112E14;
    sw        $5, 0x14($6);
    lw         $2, 0x1C($6);
    sw         $2, 0x14($6);
  L00112E14:
    addiu      $2, $7, 0x8;
    slti       $3, $2, 0x39;
    bnez       $3, L00112DD8;
    sw        $2, 0x18($6);
    b          L00112E34;
    daddiu    $2, $9, 0x28;
  L00112E2C:
    daddu      $9, $5, $0;
    daddiu     $2, $9, 0x28;
  L00112E34:
    ld         $4, 0x0($6);
    sd         $2, 0x8($6);
    addiu      $3, $0, 0x1;
    dsrl32     $2, $4, 31;
    bne        $2, $3, L00112EE8;
    addiu     $10, $0, 0x38;
    addiu      $11, $0, 0x1;
    lw         $2, 0x18($6);
    nop;
  L00112E58:
    dsll       $3, $4, 24;
    sd         $3, 0x0($6);
    addiu      $2, $2, -0x18;
    slti       $3, $2, 0x39;
    beqz       $3, L00112EC8;
    sw        $2, 0x18($6);
    lw         $8, 0x20($6);
    ld         $9, 0x8($6);
  L00112E78:
    lw         $3, 0x14($6);
    lw         $7, 0x18($6);
    lbu        $4, 0x0($3);
    ld         $5, 0x0($6);
    subu       $2, $10, $7;
    dsllv      $4, $4, $2;
    addiu      $3, $3, 0x1;
    or         $5, $5, $4;
    sltu       $2, $3, $8;
    sd         $5, 0x0($6);
    bnez       $2, L00112EB0;
    sw        $3, 0x14($6);
    lw         $2, 0x1C($6);
    sw         $2, 0x14($6);
  L00112EB0:
    addiu      $2, $7, 0x8;
    slti       $3, $2, 0x39;
    bnez       $3, L00112E78;
    sw        $2, 0x18($6);
    b          L00112ED0;
    ld        $2, 0x0($6);
  L00112EC8:
    ld         $9, 0x8($6);
    ld         $2, 0x0($6);
  L00112ED0:
    daddiu     $3, $9, 0x18;
    sd         $3, 0x8($6);
    daddu      $4, $2, $0;
    dsrl32     $3, $4, 31;
    beql       $3, $11, L00112E58;
    lw        $2, 0x18($6);
  L00112EE8:
    jr         $31;
    addiu     $2, $0, 0x1;
}
