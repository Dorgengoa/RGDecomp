#include "types.h"

extern void Scalbnf_128f08(void);
extern void Floorf_128e30(void);

asm void KernelRemPio2f_127170(void)
{
    .set noreorder;
    addiu      $2, $6, -0x3;
    addiu      $10, $6, 0x4;
    slti       $3, $2, 0x0;
    addiu      $29, $29, -0x1B0;
    movn       $2, $10, $3;
    sd         $23, 0x188($29);
    sra        $23, $2, 3;
    sw         $8, 0x144($29);
    slti       $2, $23, 0x0;
    sll        $8, $8, 2;
    movn       $23, $0, $2;
    sd         $20, 0x170($29);
    lui        $20, 0x45;
    addu       $20, $20, $8;
    lw         $20, 0x77F0($20);
    sll        $2, $23, 3;
    sd         $18, 0x160($29);
    addiu      $18, $7, -0x1;
    subu       $6, $6, $2;
    addu       $3, $18, $20;
    sd         $17, 0x158($29);
    addiu      $17, $6, -0x8;
    sd         $30, 0x190($29);
    daddu      $30, $5, $0;
    sd         $16, 0x150($29);
    subu       $5, $23, $18;
    sd         $19, 0x168($29);
    sd         $21, 0x178($29);
    sd         $22, 0x180($29);
    sd         $31, 0x198($29);
    swc1       $f20, 0x1A0($29);
    sw         $4, 0x140($29);
    bltz       $3, L00127230;
    sw        $9, 0x148($29);
    sll        $2, $5, 2;
    addiu      $6, $3, 0x1;
    addu       $2, $2, $9;
    addiu      $3, $29, 0x50;
  L00127208:
    bltzl      $5, L0012721C;
    sw        $0, 0x0($3);
    lwc1       $f0, 0x0($2);
    cvt.s.w    $f0, $f0;
    swc1       $f0, 0x0($3);
  L0012721C:
    addiu      $6, $6, -0x1;
    addiu      $3, $3, 0x4;
    addiu      $2, $2, 0x4;
    bnez       $6, L00127208;
    addiu     $5, $5, 0x1;
  L00127230:
    bltz       $20, L001272A0;
    daddu     $6, $0, $0;
    addiu      $2, $29, 0xF0;
    daddu      $4, $18, $0;
    daddu      $7, $2, $0;
    nop;
  L00127248:
    mtc1       $0, $f2;
    bltzl      $18, L0012728C;
    addiu     $6, $6, 0x1;
    addiu      $5, $29, 0x50;
    sll        $2, $4, 2;
    lw         $3, 0x140($29);
    addu       $2, $2, $5;
    addiu      $5, $18, 0x1;
  L00127268:
    lwc1       $f0, 0x0($3);
    addiu      $3, $3, 0x4;
    lwc1       $f1, 0x0($2);
    addiu      $2, $2, -0x4;
    addiu      $5, $5, -0x1;
    mul.s      $f0, $f0, $f1;
    bnez       $5, L00127268;
    add.s     $f2, $f2, $f0;
    addiu      $6, $6, 0x1;
  L0012728C:
    swc1       $f2, 0x0($7);
    slt        $2, $20, $6;
    addiu      $4, $4, 0x1;
    beqz       $2, L00127248;
    addiu     $7, $7, 0x4;
  L001272A0:
    daddu      $16, $20, $0;
  L001272A4:
    sll        $19, $16, 2;
    addiu      $3, $29, 0xF0;
    addu       $2, $3, $19;
    daddu      $5, $16, $0;
    blez       $16, L00127314;
    lwc1      $f20, 0x0($2);
    lui        $1, (0x3B800000 >> 16);
    mtc1       $1, $f4;
    addiu      $3, $2, -0x4;
    lui        $1, (0x43800000 >> 16);
    mtc1       $1, $f3;
    daddu      $4, $29, $0;
    nop;
  L001272D8:
    mul.s      $f0, $f20, $f4;
    lwc1       $f1, 0x0($3);
    addiu      $5, $5, -0x1;
    addiu      $3, $3, -0x4;
    .word      0x460000A4;
    mfc1       $2, $f2;
    mtc1       $2, $f2;
    cvt.s.w    $f2, $f2;
    mul.s      $f0, $f2, $f3;
    sub.s      $f0, $f20, $f0;
    add.s      $f20, $f1, $f2;
    .word      0x46000064;
    swc1       $f1, 0x0($4);
    bgtz       $5, L001272D8;
    addiu     $4, $4, 0x4;
  L00127314:
    mov.s      $f12, $f20;
    jal        Scalbnf_128f08;
    daddu     $4, $17, $0;
    lui        $1, (0x3E000000 >> 16);
    mtc1       $1, $f12;
    mov.s      $f20, $f0;
    daddu      $22, $0, $0;
    jal        Floorf_128e30;
    mul.s     $f12, $f20, $f12;
    lui        $1, (0x41000000 >> 16);
    mtc1       $1, $f1;
    mul.s      $f0, $f0, $f1;
    sub.s      $f20, $f20, $f0;
    .word      0x4600A024;
    mfc1       $21, $f0;
    mtc1       $21, $f0;
    cvt.s.w    $f0, $f0;
    blez       $17, L00127398;
    sub.s     $f20, $f20, $f0;
    addiu      $3, $19, -0x4;
    addiu      $2, $0, 0x8;
    addu       $5, $29, $3;
    subu       $2, $2, $17;
    lw         $3, 0x0($5);
    addiu      $4, $0, 0x7;
    subu       $4, $4, $17;
    srav       $6, $3, $2;
    sllv       $2, $6, $2;
    addu       $21, $21, $6;
    subu       $3, $3, $2;
    sw         $3, 0x0($5);
    b          L001273C4;
    srav      $22, $3, $4;
  L00127398:
    bnez       $17, L001273B0;
    addu      $2, $19, $29;
    lw         $3, -0x4($2);
    b          L001273C4;
    sra       $22, $3, 8;
    nop;
  L001273B0:
    lui        $1, (0x3F000000 >> 16);
    mtc1       $1, $f0;
    c.le.s     $f0, $f20;
    bc1tl      L001273C4;
    addiu     $22, $0, 0x2;
  L001273C4:
    blez       $22, L00127490;
    nop;
    addiu      $21, $21, 0x1;
    blez       $16, L0012741C;
    daddu     $7, $0, $0;
    addiu      $8, $0, 0x100;
    addiu      $4, $0, 0xFF;
    daddu      $3, $29, $0;
    daddu      $6, $16, $0;
  L001273E8:
    bnez       $7, L00127400;
    lw        $5, 0x0($3);
    beqz       $5, L00127408;
    subu      $2, $8, $5;
    b          L00127404;
    addiu     $7, $0, 0x1;
  L00127400:
    subu       $2, $4, $5;
  L00127404:
    sw         $2, 0x0($3);
  L00127408:
    addiu      $6, $6, -0x1;
    nop;
    nop;
    bnez       $6, L001273E8;
    addiu     $3, $3, 0x4;
  L0012741C:
    blez       $17, L0012746C;
    addiu     $2, $0, 0x2;
    addiu      $2, $0, 0x1;
    beq        $17, $2, L00127440;
    addiu     $2, $0, 0x2;
    beql       $17, $2, L00127458;
    addiu     $2, $19, -0x4;
    b          L0012746C;
    nop;
  L00127440:
    addiu      $2, $19, -0x4;
    addu       $4, $29, $2;
    lw         $3, 0x0($4);
    b          L00127464;
    andi      $3, $3, 0x7F;
    nop;
  L00127458:
    addu       $4, $29, $2;
    lw         $3, 0x0($4);
    andi       $3, $3, 0x3F;
  L00127464:
    sw         $3, 0x0($4);
    addiu      $2, $0, 0x2;
  L0012746C:
    bne        $22, $2, L00127490;
    nop;
    lui        $1, (0x3F800000 >> 16);
    mtc1       $1, $f12;
    beqz       $7, L00127490;
    sub.s     $f20, $f12, $f20;
    jal        Scalbnf_128f08;
    daddu     $4, $17, $0;
    sub.s      $f20, $f20, $f0;
  L00127490:
    mtc1       $0, $f0;
    c.eq.s     $f20, $f0;
    bc1f       L001275E0;
    addiu     $6, $16, -0x1;
    slt        $2, $6, $20;
    bnez       $2, L001274D4;
    daddu     $5, $0, $0;
    sll        $2, $6, 2;
    addu       $4, $2, $29;
    nop;
  L001274B8:
    lw         $3, 0x0($4);
    addiu      $4, $4, -0x4;
    addiu      $6, $6, -0x1;
    slt        $2, $6, $20;
    nop;
    beqz       $2, L001274B8;
    or        $5, $5, $3;
  L001274D4:
    bnez       $5, L001275D8;
    addiu     $2, $20, -0x1;
    sll        $2, $2, 2;
    addu       $3, $29, $2;
    lw         $4, 0x0($3);
    bnez       $4, L0012751C;
    addiu     $8, $0, 0x1;
    sll        $2, $20, 2;
    addu       $2, $2, $29;
    addiu      $3, $2, -0x4;
    nop;
  L00127500:
    addiu      $3, $3, -0x4;
    lw         $2, 0x0($3);
    nop;
    nop;
    nop;
    beqz       $2, L00127500;
    addiu     $8, $8, 0x1;
  L0012751C:
    addu       $9, $16, $8;
    addiu      $6, $16, 0x1;
    slt        $2, $9, $6;
    bnez       $2, L001272A4;
    daddu     $16, $9, $0;
    lw         $11, 0x148($29);
    addu       $2, $18, $6;
    addu       $4, $23, $6;
    addiu      $5, $29, 0x50;
    sll        $2, $2, 2;
    sll        $4, $4, 2;
    sll        $3, $6, 2;
    addiu      $7, $29, 0xF0;
    addu       $4, $4, $11;
    daddu      $11, $5, $0;
    addu       $3, $3, $7;
    addu       $8, $2, $5;
    daddu      $10, $9, $0;
    nop;
  L00127568:
    lwc1       $f0, 0x0($4);
    cvt.s.w    $f0, $f0;
    addu       $2, $18, $6;
    mtc1       $0, $f2;
    bltz       $18, L001275B0;
    swc1      $f0, 0x0($8);
    sll        $2, $2, 2;
    lw         $7, 0x140($29);
    addu       $2, $2, $11;
    addiu      $5, $18, 0x1;
  L00127590:
    lwc1       $f0, 0x0($7);
    addiu      $7, $7, 0x4;
    lwc1       $f1, 0x0($2);
    addiu      $2, $2, -0x4;
    addiu      $5, $5, -0x1;
    mul.s      $f0, $f0, $f1;
    bnez       $5, L00127590;
    add.s     $f2, $f2, $f0;
  L001275B0:
    addiu      $6, $6, 0x1;
    swc1       $f2, 0x0($3);
    slt        $2, $10, $6;
    addiu      $8, $8, 0x4;
    addiu      $3, $3, 0x4;
    beqz       $2, L00127568;
    addiu     $4, $4, 0x4;
    b          L001272A4;
    daddu     $16, $9, $0;
    nop;
  L001275D8:
    mtc1       $0, $f0;
    c.eq.s     $f20, $f0;
  L001275E0:
    bc1f       L00127630;
    mov.s     $f12, $f20;
    addiu      $16, $16, -0x1;
    sll        $2, $16, 2;
    addu       $2, $29, $2;
    lw         $3, 0x0($2);
    bnez       $3, L001276A8;
    addiu     $17, $17, -0x8;
    daddu      $3, $2, $0;
    nop;
  L00127608:
    addiu      $3, $3, -0x4;
    addiu      $16, $16, -0x1;
    lw         $2, 0x0($3);
    nop;
    nop;
    beqz       $2, L00127608;
    addiu     $17, $17, -0x8;
    b          L001276A8;
    nop;
    nop;
  L00127630:
    jal        Scalbnf_128f08;
    negu      $4, $17;
    lui        $1, (0x43800000 >> 16);
    mtc1       $1, $f1;
    mov.s      $f20, $f0;
    c.le.s     $f1, $f20;
    bc1f       L001276A0;
    addu      $2, $29, $19;
    lui        $1, (0x3B800000 >> 16);
    mtc1       $1, $f0;
    addiu      $16, $16, 0x1;
    sll        $2, $16, 2;
    addu       $4, $29, $19;
    mul.s      $f0, $f20, $f0;
    addu       $3, $29, $2;
    .word      0x460000A4;
    mfc1       $2, $f2;
    mtc1       $2, $f2;
    cvt.s.w    $f2, $f2;
    mul.s      $f0, $f2, $f1;
    sub.s      $f0, $f20, $f0;
    .word      0x46000064;
    swc1       $f1, 0x0($4);
    .word      0x46001024;
    swc1       $f0, 0x0($3);
    b          L001276A8;
    addiu     $17, $17, 0x8;
    nop;
  L001276A0:
    .word      0x4600A024;
    swc1       $f0, 0x0($2);
  L001276A8:
    lui        $1, (0x3F800000 >> 16);
    mtc1       $1, $f12;
    jal        Scalbnf_128f08;
    daddu     $4, $17, $0;
    daddu      $6, $16, $0;
    bltz       $6, L00127704;
    mov.s     $f2, $f0;
    addiu      $2, $29, 0xF0;
    lui        $1, (0x3B800000 >> 16);
    mtc1       $1, $f1;
    daddu      $4, $2, $0;
    nop;
  L001276D8:
    sll        $2, $6, 2;
    addiu      $6, $6, -0x1;
    addu       $3, $29, $2;
    addu       $2, $4, $2;
    lwc1       $f0, 0x0($3);
    cvt.s.w    $f0, $f0;
    mul.s      $f0, $f2, $f0;
    mul.s      $f2, $f2, $f1;
    bgez       $6, L001276D8;
    swc1      $f0, 0x0($2);
    daddu      $6, $16, $0;
  L00127704:
    bltz       $6, L00127798;
    lui       $2, 0x45;
    addiu      $3, $29, 0xF0;
    daddu      $10, $3, $0;
    addiu      $12, $2, 0x7800;
    addiu      $11, $29, 0xA0;
    nop;
  L00127720:
    mtc1       $0, $f2;
    bltz       $20, L00127780;
    daddu     $8, $0, $0;
    subu       $7, $16, $6;
    bltz       $7, L00127784;
    daddu     $9, $7, $0;
    sll        $2, $6, 2;
    daddu      $5, $12, $0;
    addu       $4, $2, $10;
    lwc1       $f0, 0x0($5);
  L00127748:
    addiu      $5, $5, 0x4;
    lwc1       $f1, 0x0($4);
    addiu      $4, $4, 0x4;
    addiu      $8, $8, 0x1;
    mul.s      $f0, $f0, $f1;
    slt        $2, $20, $8;
    slt        $3, $9, $8;
    bnez       $2, L00127784;
    add.s     $f2, $f2, $f0;
    beql       $3, $0, L00127748;
    lwc1      $f0, 0x0($5);
    b          L00127788;
    sll       $2, $7, 2;
    nop;
  L00127780:
    subu       $7, $16, $6;
  L00127784:
    sll        $2, $7, 2;
  L00127788:
    addiu      $6, $6, -0x1;
    addu       $2, $11, $2;
    bgez       $6, L00127720;
    swc1      $f2, 0x0($2);
  L00127798:
    lw         $5, 0x144($29);
    slti       $2, $5, 0x3;
    beql       $2, $0, L001277C0;
    lw        $6, 0x144($29);
    bgtzl      $5, L00127820;
    daddu     $6, $16, $0;
    beqz       $5, L001277D8;
    andi      $2, $21, 0x7;
    b          L001279A4;
    ld        $16, 0x150($29);
  L001277C0:
    addiu      $2, $0, 0x3;
    beq        $6, $2, L001278A8;
    andi      $2, $21, 0x7;
    b          L001279A4;
    ld        $16, 0x150($29);
    nop;
  L001277D8:
    daddu      $6, $16, $0;
    mtc1       $0, $f2;
    bltz       $6, L0012780C;
    addiu     $3, $29, 0xA0;
    sll        $2, $6, 2;
    addu       $2, $2, $3;
  L001277F0:
    lwc1       $f0, 0x0($2);
    addiu      $2, $2, -0x4;
    addiu      $6, $6, -0x1;
    nop;
    nop;
    bgez       $6, L001277F0;
    add.s     $f2, $f2, $f0;
  L0012780C:
    beqz       $22, L0012799C;
    swc1      $f2, 0x0($30);
    neg.s      $f0, $f2;
    b          L0012799C;
    swc1      $f0, 0x0($30);
  L00127820:
    mtc1       $0, $f2;
    bltz       $6, L00127854;
    addiu     $3, $29, 0xA0;
    sll        $2, $6, 2;
    addu       $2, $2, $3;
    nop;
  L00127838:
    lwc1       $f0, 0x0($2);
    addiu      $2, $2, -0x4;
    addiu      $6, $6, -0x1;
    nop;
    nop;
    bgez       $6, L00127838;
    add.s     $f2, $f2, $f0;
  L00127854:
    beqz       $22, L00127864;
    swc1      $f2, 0x0($30);
    neg.s      $f0, $f2;
    swc1       $f0, 0x0($30);
  L00127864:
    lwc1       $f0, 0xA0($29);
    blez       $16, L00127894;
    sub.s     $f2, $f0, $f2;
    daddu      $6, $16, $0;
    addiu      $2, $29, 0xA4;
  L00127878:
    lwc1       $f0, 0x0($2);
    addiu      $2, $2, 0x4;
    addiu      $6, $6, -0x1;
    nop;
    nop;
    bnez       $6, L00127878;
    add.s     $f2, $f2, $f0;
  L00127894:
    beqz       $22, L0012799C;
    swc1      $f2, 0x4($30);
    neg.s      $f0, $f2;
    b          L0012799C;
    swc1      $f0, 0x4($30);
  L001278A8:
    daddu      $6, $16, $0;
    blez       $6, L001278F0;
    slti      $2, $6, 0x2;
    sll        $2, $6, 2;
    addu       $3, $29, $2;
    addiu      $3, $3, 0x9C;
  L001278C0:
    lwc1       $f1, 0x0($3);
    addiu      $6, $6, -0x1;
    lwc1       $f0, 0x4($3);
    add.s      $f2, $f1, $f0;
    sub.s      $f1, $f1, $f2;
    swc1       $f2, 0x0($3);
    add.s      $f0, $f0, $f1;
    swc1       $f0, 0x4($3);
    bgtz       $6, L001278C0;
    addiu     $3, $3, -0x4;
    daddu      $6, $16, $0;
    slti       $2, $6, 0x2;
  L001278F0:
    bnel       $2, $0, L00127938;
    daddu     $6, $16, $0;
    sll        $2, $6, 2;
    addu       $3, $29, $2;
    addiu      $3, $3, 0x9C;
    nop;
  L00127908:
    lwc1       $f0, 0x0($3);
    addiu      $6, $6, -0x1;
    lwc1       $f1, 0x4($3);
    slti       $2, $6, 0x2;
    add.s      $f2, $f0, $f1;
    sub.s      $f0, $f0, $f2;
    swc1       $f2, 0x0($3);
    add.s      $f1, $f1, $f0;
    swc1       $f1, 0x4($3);
    beqz       $2, L00127908;
    addiu     $3, $3, -0x4;
    daddu      $6, $16, $0;
  L00127938:
    mtc1       $0, $f2;
    slti       $2, $6, 0x2;
    bnez       $2, L0012796C;
    sll       $2, $6, 2;
    addiu      $3, $29, 0xA0;
    addu       $3, $2, $3;
  L00127950:
    lwc1       $f0, 0x0($3);
    addiu      $3, $3, -0x4;
    addiu      $6, $6, -0x1;
    slti       $2, $6, 0x2;
    nop;
    beqz       $2, L00127950;
    add.s     $f2, $f2, $f0;
  L0012796C:
    bnez       $22, L00127980;
    lwc1      $f0, 0xA0($29);
    b          L00127990;
    lwc1      $f1, 0xA4($29);
    nop;
  L00127980:
    neg.s      $f2, $f2;
    lwc1       $f1, 0xA4($29);
    neg.s      $f0, $f0;
    neg.s      $f1, $f1;
  L00127990:
    swc1       $f2, 0x8($30);
    swc1       $f0, 0x0($30);
    swc1       $f1, 0x4($30);
  L0012799C:
    andi       $2, $21, 0x7;
    ld         $16, 0x150($29);
  L001279A4:
    ld         $17, 0x158($29);
    ld         $18, 0x160($29);
    ld         $19, 0x168($29);
    ld         $20, 0x170($29);
    ld         $21, 0x178($29);
    ld         $22, 0x180($29);
    ld         $23, 0x188($29);
    ld         $30, 0x190($29);
    ld         $31, 0x198($29);
    lwc1       $f20, 0x1A0($29);
    jr         $31;
    addiu     $29, $29, 0x1B0;
}
