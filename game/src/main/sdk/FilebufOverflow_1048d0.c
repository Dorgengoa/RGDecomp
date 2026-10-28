#include "types.h"

extern void Swbuf_138e90(void);
extern void memcpy(void);
extern void FilebufPutBytesMaybe_106100(void);

asm void FilebufOverflow_1048d0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $31, 0x40($29);
    sq         $19, 0x30($29);
    sq         $18, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $4, $0;
    lw         $2, 0x1C($4);
    bnez       $2, L00104900;
    daddu     $16, $5, $0;
    b          L00104C94;
    addiu     $2, $0, -0x1;
  L00104900:
    lbu        $2, 0x36($17);
    beql       $2, $0, L0010497C;
    addiu     $2, $0, 0x1;
    lw         $2, 0x14($17);
    bnez       $2, L00104978;
    nop;
    lw         $3, 0x8($17);
    lw         $2, 0xC($17);
    sltu       $1, $3, $2;
    beql       $1, $0, L00104968;
    addiu     $3, $17, 0x24;
    lw         $25, 0x0($17);
    addiu      $4, $29, 0x50;
    daddu      $5, $17, $0;
    daddu      $6, $0, $0;
    addiu      $7, $0, 0x2;
    lw         $25, 0x10($25);
    jalr $31, $25;
    addiu     $8, $0, 0x8;
    ld         $3, 0x50($29);
    addiu      $2, $0, -0x1;
    bne        $3, $2, L00104964;
    nop;
    b          L00104C98;
    ld        $31, 0x40($29);
  L00104964:
    addiu      $3, $17, 0x24;
  L00104968:
    addiu      $2, $17, 0x34;
    sw         $3, 0x14($17);
    sw         $3, 0x10($17);
    sw         $2, 0x18($17);
  L00104978:
    addiu      $2, $0, 0x1;
  L0010497C:
    sb         $2, 0x34($17);
    lbu        $2, 0x35($17);
    beql       $2, $0, L00104BA4;
    lw        $18, 0x10($17);
    lw         $19, 0x10($17);
    lw         $2, 0x14($17);
    sltu       $1, $19, $2;
    beqz       $1, L00104AB0;
    nop;
    lw         $3, 0x1C($17);
  L001049A4:
    lb         $18, 0x0($19);
    lw         $2, 0x8($3);
    addiu      $2, $2, -0x1;
    bgez       $2, L00104A28;
    sw        $2, 0x8($3);
    lw         $5, 0x1C($17);
    lw         $3, 0x8($5);
    lw         $2, 0x18($5);
    slt        $2, $3, $2;
    bnez       $2, L00104A10;
    nop;
    lw         $2, 0x0($5);
    addiu      $4, $0, 0xA;
    sb         $18, 0x0($2);
    lw         $5, 0x1C($17);
    lw         $3, 0x0($5);
    lbu        $2, 0x0($3);
    beq        $2, $4, L00104A00;
    nop;
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($5);
    b          L00104A08;
    lbu       $2, 0x0($3);
  L00104A00:
    jal        Swbuf_138e90;
    nop;
  L00104A08:
    b          L00104A20;
    nop;
  L00104A10:
    dsll32     $4, $18, 24;
    jal        Swbuf_138e90;
    dsra32    $4, $4, 24;
    nop;
  L00104A20:
    b          L00104A48;
    nop;
  L00104A28:
    lw         $2, 0x1C($17);
    lw         $2, 0x0($2);
    sb         $18, 0x0($2);
    lw         $4, 0x1C($17);
    lw         $3, 0x0($4);
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($4);
    lbu        $2, 0x0($3);
  L00104A48:
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L00104A54;
    andi      $3, $18, 0xFF;
  L00104A54:
    addiu      $2, $0, -0x1;
    bnel       $3, $2, L00104AA0;
    lw        $2, 0x14($17);
    lw         $4, 0x10($17);
    sltu       $1, $4, $19;
    beql       $1, $0, L00104C94;
    addiu     $2, $0, -0x1;
    lw         $2, 0x14($17);
    daddu      $5, $19, $0;
    jal        memcpy;
    subu      $6, $2, $19;
    lw         $3, 0x10($17);
    lw         $2, 0x14($17);
    subu       $3, $3, $19;
    addu       $2, $2, $3;
    sw         $2, 0x14($17);
    addiu      $2, $0, -0x1;
    b          L00104C94;
    nop;
  L00104AA0:
    addiu      $19, $19, 0x1;
    sltu       $2, $19, $2;
    bnel       $2, $0, L001049A4;
    lw        $3, 0x1C($17);
  L00104AB0:
    lw         $5, 0x10($17);
    lw         $4, 0x14($17);
    not        $2, $16;
    sltiu      $2, $2, 0x1;
    lw         $3, 0x14($17);
    xori       $2, $2, 0x1;
    subu       $4, $5, $4;
    andi       $5, $2, 0xFF;
    addu       $2, $3, $4;
    beqz       $5, L00104B94;
    sw        $2, 0x14($17);
    lw         $3, 0x1C($17);
    dsll32     $18, $16, 24;
    dsra32     $18, $18, 24;
    lw         $2, 0x8($3);
    addiu      $2, $2, -0x1;
    bgez       $2, L00104B60;
    sw        $2, 0x8($3);
    lw         $5, 0x1C($17);
    lw         $3, 0x8($5);
    lw         $2, 0x18($5);
    slt        $2, $3, $2;
    bnel       $2, $0, L00104B50;
    dsll32    $4, $18, 24;
    lw         $2, 0x0($5);
    addiu      $4, $0, 0xA;
    sb         $18, 0x0($2);
    lw         $5, 0x1C($17);
    lw         $3, 0x0($5);
    lbu        $2, 0x0($3);
    beq        $2, $4, L00104B40;
    nop;
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($5);
    b          L00104B48;
    lbu       $2, 0x0($3);
  L00104B40:
    jal        Swbuf_138e90;
    nop;
  L00104B48:
    b          L00104B58;
    nop;
  L00104B50:
    jal        Swbuf_138e90;
    dsra32    $4, $4, 24;
  L00104B58:
    b          L00104B84;
    addiu     $3, $0, -0x1;
  L00104B60:
    lw         $2, 0x1C($17);
    lw         $2, 0x0($2);
    sb         $18, 0x0($2);
    lw         $4, 0x1C($17);
    lw         $3, 0x0($4);
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($4);
    lbu        $2, 0x0($3);
    addiu      $3, $0, -0x1;
  L00104B84:
    bnel       $2, $3, L00104B8C;
    andi      $3, $18, 0xFF;
  L00104B8C:
    not        $2, $3;
    sltiu      $5, $2, 0x1;
  L00104B94:
    beql       $5, $0, L00104C84;
    addiu     $2, $0, -0x1;
    b          L00104C94;
    addiu     $2, $0, -0x1;
  L00104BA4:
    lw         $2, 0x14($17);
    sltu       $1, $18, $2;
    beqz       $1, L00104C20;
    nop;
    lb         $6, 0x0($18);
  L00104BB8:
    daddu      $4, $17, $0;
    jal        FilebufPutBytesMaybe_106100;
    addiu     $5, $0, 0x1;
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L00104C10;
    lw        $2, 0x14($17);
    lw         $4, 0x10($17);
    sltu       $1, $4, $18;
    beql       $1, $0, L00104C94;
    addiu     $2, $0, -0x1;
    lw         $2, 0x14($17);
    daddu      $5, $18, $0;
    jal        memcpy;
    subu      $6, $2, $18;
    lw         $3, 0x10($17);
    lw         $2, 0x14($17);
    subu       $3, $3, $18;
    addu       $2, $2, $3;
    sw         $2, 0x14($17);
    addiu      $2, $0, -0x1;
    b          L00104C94;
    nop;
  L00104C10:
    addiu      $18, $18, 0x1;
    sltu       $2, $18, $2;
    bnel       $2, $0, L00104BB8;
    lb        $6, 0x0($18);
  L00104C20:
    lw         $5, 0x10($17);
    lw         $4, 0x14($17);
    not        $2, $16;
    lw         $3, 0x14($17);
    sltiu      $2, $2, 0x1;
    xori       $2, $2, 0x1;
    daddu      $18, $0, $0;
    subu       $4, $5, $4;
    addu       $3, $3, $4;
    beqz       $2, L00104C70;
    sw        $3, 0x14($17);
    dsll32     $6, $16, 24;
    daddu      $4, $17, $0;
    dsra32     $6, $6, 24;
    jal        FilebufPutBytesMaybe_106100;
    addiu     $5, $0, 0x1;
    addiu      $3, $0, -0x1;
    bne        $2, $3, L00104C70;
    nop;
    daddiu     $18, $0, 0x1;
  L00104C70:
    beqz       $18, L00104C80;
    nop;
    b          L00104C94;
    addiu     $2, $0, -0x1;
  L00104C80:
    addiu      $2, $0, -0x1;
  L00104C84:
    bne        $16, $2, L00104C90;
    nop;
    daddu      $16, $0, $0;
  L00104C90:
    daddu      $2, $16, $0;
  L00104C94:
    ld         $31, 0x40($29);
  L00104C98:
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}

