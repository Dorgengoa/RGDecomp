#include "types.h"

extern void Swbuf_138e90(void);
extern void memcpy(void);
extern void WFilebufPutBytesMaybe_105e00(void);

asm void WFilebufOverflow_1053e0(void)
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
    bnez       $2, L00105410;
    daddu     $16, $5, $0;
    b          L0010580C;
    addiu     $2, $0, -0x1;
  L00105410:
    lbu        $2, 0x66($17);
    beql       $2, $0, L0010548C;
    addiu     $2, $0, 0x1;
    lw         $2, 0x14($17);
    bnez       $2, L00105488;
    nop;
    lw         $3, 0x8($17);
    lw         $2, 0xC($17);
    sltu       $1, $3, $2;
    beql       $1, $0, L00105478;
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
    bne        $3, $2, L00105474;
    nop;
    b          L00105810;
    ld        $31, 0x40($29);
  L00105474:
    addiu      $3, $17, 0x24;
  L00105478:
    addiu      $2, $17, 0x64;
    sw         $3, 0x14($17);
    sw         $3, 0x10($17);
    sw         $2, 0x18($17);
  L00105488:
    addiu      $2, $0, 0x1;
  L0010548C:
    sb         $2, 0x64($17);
    lbu        $2, 0x65($17);
    beql       $2, $0, L001056E4;
    lw        $18, 0x10($17);
    lw         $19, 0x10($17);
    lw         $2, 0x14($17);
    sltu       $1, $19, $2;
    beqz       $1, L001055E0;
    nop;
    lw         $3, 0x1C($17);
  L001054B4:
    lhu        $18, 0x0($19);
    lw         $2, 0x8($3);
    addiu      $2, $2, -0x1;
    bgez       $2, L00105530;
    sw        $2, 0x8($3);
    lw         $5, 0x1C($17);
    lw         $3, 0x8($5);
    lw         $2, 0x18($5);
    slt        $2, $3, $2;
    bnez       $2, L00105520;
    nop;
    lw         $2, 0x0($5);
    addiu      $4, $0, 0xA;
    sb         $18, 0x0($2);
    lw         $5, 0x1C($17);
    lw         $3, 0x0($5);
    lbu        $2, 0x0($3);
    beq        $2, $4, L00105510;
    nop;
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($5);
    b          L00105518;
    lbu       $2, 0x0($3);
  L00105510:
    jal        Swbuf_138e90;
    nop;
  L00105518:
    b          L00105528;
    nop;
  L00105520:
    jal        Swbuf_138e90;
    daddu     $4, $18, $0;
  L00105528:
    b          L00105550;
    nop;
  L00105530:
    lw         $2, 0x1C($17);
    lw         $2, 0x0($2);
    sb         $18, 0x0($2);
    lw         $4, 0x1C($17);
    lw         $3, 0x0($4);
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($4);
    lbu        $2, 0x0($3);
  L00105550:
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L0010555C;
    daddu     $3, $18, $0;
  L0010555C:
    addiu      $2, $0, -0x1;
    bnel       $3, $2, L001055D0;
    lw        $2, 0x14($17);
    lw         $4, 0x10($17);
    sltu       $1, $4, $19;
    beql       $1, $0, L0010580C;
    addiu     $2, $0, -0x1;
    lw         $2, 0x14($17);
    subu       $3, $2, $19;
    bgez       $3, L00105590;
    sra       $2, $3, 2;
    addiu      $2, $3, 0x3;
    sra        $2, $2, 2;
  L00105590:
    sll        $6, $2, 2;
    jal        memcpy;
    daddu     $5, $19, $0;
    lw         $2, 0x10($17);
    subu       $3, $2, $19;
    bgez       $3, L001055B4;
    sra       $2, $3, 2;
    addiu      $2, $3, 0x3;
    sra        $2, $2, 2;
  L001055B4:
    sll        $3, $2, 2;
    lw         $2, 0x14($17);
    addu       $2, $2, $3;
    sw         $2, 0x14($17);
    addiu      $2, $0, -0x1;
    b          L0010580C;
    nop;
  L001055D0:
    addiu      $19, $19, 0x4;
    sltu       $2, $19, $2;
    bnel       $2, $0, L001054B4;
    lw        $3, 0x1C($17);
  L001055E0:
    lw         $3, 0x10($17);
    lw         $2, 0x14($17);
    subu       $3, $3, $2;
    bgez       $3, L001055FC;
    sra       $2, $3, 2;
    addiu      $2, $3, 0x3;
    sra        $2, $2, 2;
  L001055FC:
    sll        $4, $2, 2;
    lw         $3, 0x14($17);
    not        $2, $16;
    sltiu      $2, $2, 0x1;
    xori       $2, $2, 0x1;
    addu       $3, $3, $4;
    andi       $2, $2, 0xFF;
    beqz       $2, L001056D4;
    sw        $3, 0x14($17);
    lw         $3, 0x1C($17);
    andi       $18, $16, 0xFFFF;
    lw         $2, 0x8($3);
    addiu      $2, $2, -0x1;
    bgez       $2, L001056A0;
    sw        $2, 0x8($3);
    lw         $5, 0x1C($17);
    lw         $3, 0x8($5);
    lw         $2, 0x18($5);
    slt        $2, $3, $2;
    bnel       $2, $0, L00105690;
    daddu     $4, $18, $0;
    lw         $2, 0x0($5);
    addiu      $4, $0, 0xA;
    sb         $18, 0x0($2);
    lw         $5, 0x1C($17);
    lw         $3, 0x0($5);
    lbu        $2, 0x0($3);
    beq        $2, $4, L00105680;
    nop;
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($5);
    b          L00105688;
    lbu       $2, 0x0($3);
  L00105680:
    jal        Swbuf_138e90;
    nop;
  L00105688:
    b          L00105698;
    nop;
  L00105690:
    jal        Swbuf_138e90;
    nop;
  L00105698:
    b          L001056C4;
    addiu     $3, $0, -0x1;
  L001056A0:
    lw         $2, 0x1C($17);
    lw         $2, 0x0($2);
    sb         $18, 0x0($2);
    lw         $4, 0x1C($17);
    lw         $3, 0x0($4);
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($4);
    lbu        $2, 0x0($3);
    addiu      $3, $0, -0x1;
  L001056C4:
    bnel       $2, $3, L001056CC;
    daddu     $3, $18, $0;
  L001056CC:
    not        $2, $3;
    sltiu      $2, $2, 0x1;
  L001056D4:
    beql       $2, $0, L001057FC;
    addiu     $2, $0, -0x1;
    b          L0010580C;
    addiu     $2, $0, -0x1;
  L001056E4:
    lw         $2, 0x14($17);
    sltu       $1, $18, $2;
    beqz       $1, L00105788;
    nop;
    lhu        $6, 0x0($18);
  L001056F8:
    daddu      $4, $17, $0;
    jal        WFilebufPutBytesMaybe_105e00;
    addiu     $5, $0, 0x4;
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L00105778;
    lw        $2, 0x14($17);
    lw         $4, 0x10($17);
    sltu       $1, $4, $18;
    beql       $1, $0, L0010580C;
    addiu     $2, $0, -0x1;
    lw         $2, 0x14($17);
    subu       $3, $2, $18;
    bgez       $3, L00105738;
    sra       $2, $3, 2;
    addiu      $2, $3, 0x3;
    sra        $2, $2, 2;
  L00105738:
    sll        $6, $2, 2;
    jal        memcpy;
    daddu     $5, $18, $0;
    lw         $2, 0x10($17);
    subu       $3, $2, $18;
    bgez       $3, L0010575C;
    sra       $2, $3, 2;
    addiu      $2, $3, 0x3;
    sra        $2, $2, 2;
  L0010575C:
    sll        $3, $2, 2;
    lw         $2, 0x14($17);
    addu       $2, $2, $3;
    sw         $2, 0x14($17);
    addiu      $2, $0, -0x1;
    b          L0010580C;
    nop;
  L00105778:
    addiu      $18, $18, 0x4;
    sltu       $2, $18, $2;
    bnel       $2, $0, L001056F8;
    lhu       $6, 0x0($18);
  L00105788:
    lw         $3, 0x10($17);
    lw         $2, 0x14($17);
    subu       $3, $3, $2;
    bgez       $3, L001057A4;
    sra       $2, $3, 2;
    addiu      $2, $3, 0x3;
    sra        $2, $2, 2;
  L001057A4:
    sll        $4, $2, 2;
    lw         $3, 0x14($17);
    not        $2, $16;
    daddu      $18, $0, $0;
    sltiu      $2, $2, 0x1;
    addu       $3, $3, $4;
    xori       $2, $2, 0x1;
    beqz       $2, L001057E8;
    sw        $3, 0x14($17);
    daddu      $4, $17, $0;
    addiu      $5, $0, 0x4;
    jal        WFilebufPutBytesMaybe_105e00;
    daddu     $6, $16, $0;
    addiu      $3, $0, -0x1;
    bne        $2, $3, L001057E8;
    nop;
    daddiu     $18, $0, 0x1;
  L001057E8:
    beqz       $18, L001057F8;
    nop;
    b          L0010580C;
    addiu     $2, $0, -0x1;
  L001057F8:
    addiu      $2, $0, -0x1;
  L001057FC:
    bne        $16, $2, L00105808;
    nop;
    daddu      $16, $0, $0;
  L00105808:
    daddu      $2, $16, $0;
  L0010580C:
    ld         $31, 0x40($29);
  L00105810:
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}

