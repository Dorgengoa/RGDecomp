#include "types.h"

extern void MallocLock_131c20(void);
extern void MallocExtendTop_130e78(void);
extern void MallocUnlock_131ca0(void);

asm void MallocR_1310d0(void)
{
    .set noreorder;
    addiu      $3, $5, 0x13;
    addiu      $29, $29, -0x30;
    sltiu      $2, $3, 0x1F;
    sd         $19, 0x18($29);
    sd         $16, 0x0($29);
    daddu      $19, $4, $0;
    sd         $17, 0x8($29);
    sd         $18, 0x10($29);
    sd         $20, 0x20($29);
    bnez       $2, L00131108;
    sd        $31, 0x28($29);
    addiu      $2, $0, -0x10;
    b          L0013110C;
    and       $17, $3, $2;
  L00131108:
    addiu      $17, $0, 0x10;
  L0013110C:
    jal        MallocLock_131c20;
    daddu     $4, $19, $0;
    sltiu      $2, $17, 0x1F8;
    beqz       $2, L00131178;
    srl       $3, $17, 9;
    lui        $15, 0x45;
    addiu      $2, $15, -0x6790;
    addiu      $2, $2, -0x8;
    addu       $4, $17, $2;
    lw         $16, 0xC($4);
    beq        $16, $4, L00131170;
    srl       $10, $17, 3;
    lw         $3, 0x4($16);
    addiu      $2, $0, -0x4;
    lw         $11, 0xC($16);
    daddu      $4, $19, $0;
    and        $6, $3, $2;
    lw         $8, 0x8($16);
    addu       $3, $16, $6;
    lw         $2, 0x4($3);
    sw         $11, 0xC($8);
    ori        $2, $2, 0x1;
    sw         $8, 0x8($11);
    b          L001317CC;
    sw        $2, 0x4($3);
  L00131170:
    b          L00131254;
    addiu     $10, $10, 0x2;
  L00131178:
    beqz       $3, L001311E0;
    srl       $10, $17, 3;
    sltiu      $2, $3, 0x5;
    beqz       $2, L00131198;
    sltiu     $2, $3, 0x15;
    srl        $2, $17, 6;
    b          L001311E0;
    addiu     $10, $2, 0x38;
  L00131198:
    bnez       $2, L001311E0;
    addiu     $10, $3, 0x5B;
    sltiu      $2, $3, 0x55;
    beqz       $2, L001311B8;
    sltiu     $2, $3, 0x155;
    srl        $2, $17, 12;
    b          L001311E0;
    addiu     $10, $2, 0x6E;
  L001311B8:
    beqz       $2, L001311D0;
    sltiu     $2, $3, 0x555;
    srl        $2, $17, 15;
    b          L001311E0;
    addiu     $10, $2, 0x77;
    nop;
  L001311D0:
    beql       $2, $0, L001311E0;
    addiu     $10, $0, 0x7E;
    srl        $2, $17, 18;
    addiu      $10, $2, 0x7C;
  L001311E0:
    lui        $15, 0x45;
    sll        $3, $10, 3;
    addiu      $2, $15, -0x6790;
    addiu      $4, $0, -0x4;
    addiu      $2, $2, -0x8;
    addu       $5, $3, $2;
    b          L0013120C;
    lw        $16, 0xC($5);
  L00131200:
    bgez       $8, L001316F8;
    addu      $3, $16, $6;
    lw         $16, 0xC($16);
  L0013120C:
    beql       $16, $5, L00131254;
    addiu     $10, $10, 0x1;
    lw         $2, 0x4($16);
    and        $6, $2, $4;
    subu       $3, $17, $6;
    subu       $2, $6, $17;
    dsll32     $3, $3, 0;
    dsll32     $7, $2, 0;
    dsrl32     $3, $3, 0;
    sltu       $2, $6, $17;
    bnez       $2, L00131240;
    dsubu     $8, $0, $3;
    dsrl32     $8, $7, 0;
  L00131240:
    slti       $2, $8, 0x10;
    bnez       $2, L00131200;
    nop;
    addiu      $10, $10, -0x1;
    addiu      $10, $10, 0x1;
  L00131254:
    addiu      $2, $15, -0x6790;
    lw         $16, 0x8($2);
    beq        $16, $2, L00131460;
    addiu     $3, $0, -0x4;
    lw         $2, 0x4($16);
    and        $6, $2, $3;
    sltu       $4, $6, $17;
    beqz       $4, L00131290;
    subu      $2, $6, $17;
    subu       $2, $17, $6;
    dsll32     $2, $2, 0;
    dsrl32     $2, $2, 0;
    b          L00131298;
    dsubu     $8, $0, $2;
    nop;
  L00131290:
    dsll32     $2, $2, 0;
    dsrl32     $8, $2, 0;
  L00131298:
    slti       $2, $8, 0x10;
    bnel       $2, $0, L001312F0;
    addiu     $4, $15, -0x6790;
    addiu      $3, $0, 0x1;
    addu       $9, $16, $17;
    dsll32     $7, $8, 0;
    dsra32     $7, $7, 0;
    or         $3, $8, $3;
    addiu      $5, $15, -0x6790;
    ori        $2, $17, 0x1;
    dsll32     $3, $3, 0;
    dsra32     $3, $3, 0;
    addu       $6, $9, $7;
    sw         $2, 0x4($16);
    daddu      $4, $19, $0;
    sw         $9, 0xC($5);
    sw         $9, 0x8($5);
    sw         $3, 0x4($9);
    sw         $5, 0x8($9);
    sw         $7, 0x0($6);
    b          L001317CC;
    sw        $5, 0xC($9);
  L001312F0:
    sw         $4, 0xC($4);
    bltz       $8, L00131318;
    sw        $4, 0x8($4);
    addu       $3, $16, $6;
    daddu      $4, $19, $0;
    lw         $2, 0x4($3);
    ori        $2, $2, 0x1;
    b          L001317CC;
    sw        $2, 0x4($3);
    nop;
  L00131318:
    sltiu      $2, $6, 0x200;
    beqz       $2, L00131368;
    srl       $3, $6, 9;
    srl        $5, $6, 3;
    addiu      $4, $4, -0x8;
    sll        $3, $5, 3;
    srl        $5, $5, 2;
    addiu      $2, $0, 0x1;
    addu       $11, $3, $4;
    dsllv      $2, $2, $5;
    lw         $3, 0x4($4);
    lw         $8, 0x8($11);
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    or         $3, $3, $2;
    sw         $11, 0xC($16);
    sw         $8, 0x8($16);
    b          L00131458;
    sw        $3, 0x4($4);
    nop;
  L00131368:
    beqz       $3, L001313D0;
    srl       $5, $6, 3;
    sltiu      $2, $3, 0x5;
    beqz       $2, L00131388;
    sltiu     $2, $3, 0x15;
    srl        $2, $6, 6;
    b          L001313D0;
    addiu     $5, $2, 0x38;
  L00131388:
    bnez       $2, L001313D0;
    addiu     $5, $3, 0x5B;
    sltiu      $2, $3, 0x55;
    beqz       $2, L001313A8;
    sltiu     $2, $3, 0x155;
    srl        $2, $6, 12;
    b          L001313D0;
    addiu     $5, $2, 0x6E;
  L001313A8:
    beqz       $2, L001313C0;
    sltiu     $2, $3, 0x555;
    srl        $2, $6, 15;
    b          L001313D0;
    addiu     $5, $2, 0x77;
    nop;
  L001313C0:
    beql       $2, $0, L001313D0;
    addiu     $5, $0, 0x7E;
    srl        $2, $6, 18;
    addiu      $5, $2, 0x7C;
  L001313D0:
    addiu      $2, $15, -0x6790;
    sll        $3, $5, 3;
    addiu      $7, $2, -0x8;
    addu       $11, $3, $7;
    lw         $8, 0x8($11);
    bnel       $8, $11, L00131420;
    lw        $2, 0x4($8);
    addiu      $4, $5, 0x3;
    slti       $3, $5, 0x0;
    movn       $5, $4, $3;
    lw         $3, 0x4($7);
    addiu      $2, $0, 0x1;
    sra        $4, $5, 2;
    dsllv      $2, $2, $4;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    or         $3, $3, $2;
    b          L00131450;
    sw        $3, 0x4($7);
    nop;
  L00131420:
    b          L00131434;
    addiu     $3, $0, -0x4;
  L00131428:
    beql       $8, $11, L00131450;
    lw        $11, 0xC($8);
    lw         $2, 0x4($8);
  L00131434:
    and        $2, $2, $3;
    sltu       $2, $6, $2;
    nop;
    nop;
    bnel       $2, $0, L00131428;
    lw        $8, 0x8($8);
    lw         $11, 0xC($8);
  L00131450:
    sw         $11, 0xC($16);
    sw         $8, 0x8($16);
  L00131458:
    sw         $16, 0x8($11);
    sw         $16, 0xC($8);
  L00131460:
    slti       $2, $10, 0x0;
    addiu      $5, $10, 0x3;
    daddu      $4, $10, $0;
    lui        $20, 0x45;
    movn       $4, $5, $2;
    addiu      $2, $0, 0x1;
    addiu      $3, $20, -0x6798;
    sra        $4, $4, 2;
    lwu        $6, 0x4($3);
    dsllv      $9, $2, $4;
    sltu       $3, $6, $9;
    bnel       $3, $0, L00131614;
    addiu     $4, $20, -0x6798;
    and        $2, $9, $6;
    bnez       $2, L001314E0;
    lui       $2, 0x45;
    addiu      $2, $0, -0x4;
    dsll       $9, $9, 1;
    and        $2, $10, $2;
    and        $3, $9, $6;
    bnez       $3, L001314DC;
    addiu     $10, $2, 0x4;
    daddu      $3, $6, $0;
    nop;
  L001314C0:
    dsll       $9, $9, 1;
    and        $2, $9, $3;
    nop;
    nop;
    nop;
    beqz       $2, L001314C0;
    addiu     $10, $10, 0x4;
  L001314DC:
    lui        $2, 0x45;
  L001314E0:
    addiu      $13, $2, -0x6798;
    daddu      $14, $2, $0;
    daddu      $18, $13, $0;
    sll        $2, $10, 3;
  L001314F0:
    daddu      $11, $10, $0;
    addu       $4, $2, $13;
    daddu      $5, $4, $0;
    lw         $16, 0xC($5);
  L00131500:
    beq        $16, $5, L0013155C;
    slti      $2, $10, 0x3F;
    addiu      $12, $0, -0x4;
    lw         $2, 0x4($16);
  L00131510:
    and        $6, $2, $12;
    subu       $3, $17, $6;
    subu       $2, $6, $17;
    dsll32     $3, $3, 0;
    dsll32     $7, $2, 0;
    dsrl32     $3, $3, 0;
    sltu       $2, $6, $17;
    bnez       $2, L00131538;
    dsubu     $8, $0, $3;
    dsrl32     $8, $7, 0;
  L00131538:
    slti       $2, $8, 0x10;
    beql       $2, $0, L00131720;
    addiu     $3, $0, 0x1;
    bgezl      $8, L00131778;
    addu      $3, $16, $6;
    lw         $16, 0xC($16);
    bnel       $16, $5, L00131510;
    lw        $2, 0x4($16);
    slti       $2, $10, 0x3F;
  L0013155C:
    beqz       $2, L0013156C;
    addiu     $5, $5, 0x8;
    addiu      $5, $5, 0x8;
    addiu      $10, $10, 0x1;
  L0013156C:
    addiu      $10, $10, 0x1;
    andi       $2, $10, 0x3;
    bnel       $2, $0, L00131500;
    lw        $16, 0xC($5);
    dsll32     $2, $9, 0;
    dsra32     $2, $2, 0;
    addiu      $5, $14, -0x6798;
    nor        $3, $0, $2;
    andi       $2, $11, 0x3;
  L00131590:
    bnez       $2, L001315A8;
    addiu     $11, $11, -0x1;
    lw         $2, 0x4($5);
    and        $2, $2, $3;
    b          L001315BC;
    sw        $2, 0x4($5);
  L001315A8:
    addiu      $4, $4, -0x8;
    lw         $2, 0x8($4);
    nop;
    beq        $2, $4, L00131590;
    andi      $2, $11, 0x3;
  L001315BC:
    lwu        $3, 0x4($13);
    dsll       $9, $9, 1;
    sltu       $2, $3, $9;
    bnel       $2, $0, L00131614;
    addiu     $4, $20, -0x6798;
    beqz       $9, L00131610;
    and       $2, $9, $3;
    bnez       $2, L001314F0;
    sll       $2, $10, 3;
    lwu        $3, 0x4($18);
    nop;
  L001315E8:
    dsll       $9, $9, 1;
    and        $2, $9, $3;
    nop;
    nop;
    nop;
    beqz       $2, L001315E8;
    addiu     $10, $10, 0x4;
    b          L001314F0;
    sll       $2, $10, 3;
    nop;
  L00131610:
    addiu      $4, $20, -0x6798;
  L00131614:
    addiu      $5, $0, -0x4;
    lw         $2, 0x8($4);
    lw         $3, 0x4($2);
    and        $3, $3, $5;
    sltu       $2, $3, $17;
    beqz       $2, L00131648;
    subu      $2, $3, $17;
    subu       $2, $17, $3;
    dsll32     $2, $2, 0;
    dsrl32     $2, $2, 0;
    b          L00131650;
    dsubu     $8, $0, $2;
    nop;
  L00131648:
    dsll32     $2, $2, 0;
    dsrl32     $8, $2, 0;
  L00131650:
    addiu      $16, $20, -0x6798;
    addiu      $18, $0, -0x4;
    lw         $3, 0x8($16);
    lw         $2, 0x4($3);
    and        $2, $2, $18;
    sltu       $2, $2, $17;
    bnez       $2, L00131680;
    daddu     $4, $19, $0;
    slti       $2, $8, 0x10;
    beqz       $2, L001317A0;
    addiu     $6, $20, -0x6798;
    daddu      $4, $19, $0;
  L00131680:
    jal        MallocExtendTop_130e78;
    daddu     $5, $17, $0;
    lw         $2, 0x8($16);
    lw         $3, 0x4($2);
    and        $3, $3, $18;
    sltu       $2, $3, $17;
    beqz       $2, L001316B8;
    subu      $2, $3, $17;
    subu       $2, $17, $3;
    dsll32     $2, $2, 0;
    dsrl32     $2, $2, 0;
    b          L001316C0;
    dsubu     $8, $0, $2;
    nop;
  L001316B8:
    dsll32     $2, $2, 0;
    dsrl32     $8, $2, 0;
  L001316C0:
    addiu      $4, $20, -0x6798;
    addiu      $5, $0, -0x4;
    lw         $3, 0x8($4);
    lw         $2, 0x4($3);
    and        $2, $2, $5;
    sltu       $2, $2, $17;
    bnez       $2, L001316E8;
    slti      $2, $8, 0x10;
    beqz       $2, L001317A0;
    addiu     $6, $20, -0x6798;
  L001316E8:
    jal        MallocUnlock_131ca0;
    daddu     $4, $19, $0;
    b          L001317D8;
    daddu     $2, $0, $0;
  L001316F8:
    lw         $11, 0xC($16);
    lw         $2, 0x4($3);
    daddu      $4, $19, $0;
    lw         $8, 0x8($16);
    ori        $2, $2, 0x1;
    sw         $2, 0x4($3);
    sw         $11, 0xC($8);
    b          L001317CC;
    sw        $8, 0x8($11);
    nop;
  L00131720:
    lw         $11, 0xC($16);
    addu       $9, $16, $17;
    dsll32     $7, $8, 0;
    dsra32     $7, $7, 0;
    or         $3, $8, $3;
    lw         $8, 0x8($16);
    addiu      $5, $15, -0x6790;
    ori        $2, $17, 0x1;
    dsll32     $3, $3, 0;
    dsra32     $3, $3, 0;
    addu       $6, $9, $7;
    sw         $11, 0xC($8);
    daddu      $4, $19, $0;
    sw         $8, 0x8($11);
    sw         $2, 0x4($16);
    sw         $9, 0xC($5);
    sw         $9, 0x8($5);
    sw         $3, 0x4($9);
    sw         $5, 0x8($9);
    sw         $7, 0x0($6);
    b          L001317CC;
    sw        $5, 0xC($9);
  L00131778:
    lw         $11, 0xC($16);
    lw         $2, 0x4($3);
    daddu      $4, $19, $0;
    lw         $8, 0x8($16);
    ori        $2, $2, 0x1;
    sw         $2, 0x4($3);
    sw         $11, 0xC($8);
    b          L001317CC;
    sw        $8, 0x8($11);
    nop;
  L001317A0:
    addiu      $2, $0, 0x1;
    lw         $16, 0x8($6);
    or         $2, $8, $2;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    ori        $3, $17, 0x1;
    addu       $5, $16, $17;
    sw         $3, 0x4($16);
    sw         $5, 0x8($6);
    daddu      $4, $19, $0;
    sw         $2, 0x4($5);
  L001317CC:
    jal        MallocUnlock_131ca0;
    nop;
    addiu      $2, $16, 0x8;
  L001317D8:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $31, 0x28($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
