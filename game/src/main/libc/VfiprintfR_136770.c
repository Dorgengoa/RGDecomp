#include "types.h"

extern void StdioSinit_12f8b8(void);
extern void func_001367E8(void);
extern void Swsetup_139000(void);
extern void Sbprintf_1366b8(void);
extern void MbtowcR_1317f8(void);
extern void Sprint_136670(void);
extern void memchr(void);
extern void strlen(void);
extern void UModDi3_13a430(void);
extern void UDivDi3_139eb0(void);

asm void VfiprintfR_136770(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $17, 0x8($29);
    daddu      $17, $5, $0;
    sd         $18, 0x10($29);
    daddu      $18, $6, $0;
    sd         $31, 0x18($29);
    lw         $4, 0x54($16);
    bnez       $4, L001367A8;
    lui       $2, 0x45;
    lw         $2, -0x67A8($2);
    sw         $2, 0x54($16);
    daddu      $4, $2, $0;
  L001367A8:
    lw         $2, 0x38($4);
    bnez       $2, L001367C4;
    daddu     $5, $16, $0;
    jal        StdioSinit_12f8b8;
    nop;
    lw         $4, 0x54($16);
    daddu      $5, $16, $0;
  L001367C4:
    ld         $16, 0x0($29);
    daddu      $6, $17, $0;
    ld         $17, 0x8($29);
    daddu      $7, $18, $0;
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    j          func_001367E8;
    addiu     $29, $29, 0x20;
    nop;
    addiu      $29, $29, -0x140;
    sd         $16, 0xF0($29);
    daddu      $16, $6, $0;
    sd         $20, 0x110($29);
    sd         $17, 0xF8($29);
    sd         $18, 0x100($29);
    sd         $19, 0x108($29);
    sd         $21, 0x118($29);
    sd         $22, 0x120($29);
    sd         $23, 0x128($29);
    sd         $30, 0x130($29);
    sd         $31, 0x138($29);
    sw         $5, 0x9C($29);
    sw         $0, 0x98($29);
    lhu        $3, 0xC($5);
    andi       $2, $3, 0x8;
    beqz       $2, L00136840;
    daddu     $20, $7, $0;
    daddu      $4, $5, $0;
    lw         $2, 0x10($4);
    bnel       $2, $0, L0013685C;
    andi      $3, $3, 0x1A;
  L00136840:
    jal        Swsetup_139000;
    lw        $4, 0x9C($29);
    bnez       $2, L001373B0;
    addiu     $2, $0, -0x1;
    lw         $5, 0x9C($29);
    lhu        $3, 0xC($5);
    andi       $3, $3, 0x1A;
  L0013685C:
    addiu      $2, $0, 0xA;
    bne        $3, $2, L00136890;
    addiu     $23, $29, 0x10;
    lw         $3, 0x9C($29);
    lh         $2, 0xE($3);
    bltz       $2, L00136890;
    daddu     $4, $3, $0;
    daddu      $5, $16, $0;
    jal        Sbprintf_1366b8;
    daddu     $6, $20, $0;
    b          L001373B4;
    ld        $16, 0xF0($29);
    nop;
  L00136890:
    sw         $0, 0x8($29);
    sw         $23, 0x0($29);
    daddu      $18, $16, $0;
    sw         $0, 0x4($29);
    sw         $0, 0xA0($29);
    nop;
  L001368A8:
    daddu      $19, $18, $0;
    addiu      $17, $0, 0x25;
  L001368B0:
    lui        $5, 0x45;
    lui        $2, 0x45;
    lw         $4, -0x67A8($5);
    addiu      $5, $29, 0x94;
    lw         $7, -0x67A0($2);
    daddu      $6, $18, $0;
    jal        MbtowcR_1317f8;
    addiu     $8, $29, 0x98;
    daddu      $16, $2, $0;
    blezl      $16, L001368F0;
    subu      $17, $18, $19;
    lw         $2, 0x94($29);
    bne        $2, $17, L001368B0;
    addu      $18, $18, $16;
    addiu      $18, $18, -0x1;
    subu       $17, $18, $19;
  L001368F0:
    beqz       $17, L0013694C;
    nop;
    sw         $17, 0x4($23);
    sw         $19, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $2, 0x4($29);
    lw         $3, 0x8($29);
    addiu      $2, $2, 0x1;
    addu       $3, $3, $17;
    slti       $4, $2, 0x8;
    sw         $3, 0x8($29);
    bnez       $4, L00136940;
    sw        $2, 0x4($29);
    lw         $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
    addiu      $3, $29, 0x10;
    daddu      $23, $3, $0;
  L00136940:
    lw         $4, 0xA0($29);
    addu       $4, $4, $17;
    sw         $4, 0xA0($29);
  L0013694C:
    blez       $16, L0013737C;
    lw        $2, 0x8($29);
    sb         $0, 0x90($29);
    addiu      $18, $18, 0x1;
    sw         $0, 0xA4($29);
    daddu      $22, $0, $0;
    daddu      $30, $0, $0;
    addiu      $21, $0, -0x1;
  L0013696C:
    lbu        $4, 0x0($18);
  L00136970:
    sll        $2, $4, 24;
    addiu      $18, $18, 0x1;
    sra        $17, $2, 24;
  L0013697C:
    addiu      $3, $17, -0x20;
  L00136980:
    sltiu      $2, $3, 0x59;
    beqz       $2, L00136E60;
    sll       $2, $3, 2;
    lui        $3, 0x46;
    addu       $3, $3, $2;
    lw         $3, -0x7D40($3);
    jr         $3;
    nop;
    lb         $2, 0x90($29);
    bnel       $2, $0, L00136970;
    lbu       $4, 0x0($18);
    b          L001369E4;
    addiu     $2, $0, 0x20;
    nop;
    b          L0013696C;
    ori       $22, $22, 0x1;
    daddu      $2, $20, $0;
    lw         $30, 0x0($2);
    bgez       $30, L0013696C;
    addiu     $20, $20, 0x8;
    negu       $30, $30;
    b          L0013696C;
    ori       $22, $22, 0x4;
    nop;
    addiu      $2, $0, 0x2B;
  L001369E4:
    lbu        $4, 0x0($18);
    b          L00136970;
    sb        $2, 0x90($29);
    lb         $17, 0x0($18);
    addiu      $2, $0, 0x2A;
    bne        $17, $2, L00136A20;
    addiu     $18, $18, 0x1;
    daddu      $2, $20, $0;
    lw         $16, 0x0($2);
    daddu      $21, $16, $0;
    slti       $2, $21, -0x1;
    beqz       $2, L0013696C;
    addiu     $20, $20, 0x8;
    b          L0013696C;
    addiu     $21, $0, -0x1;
  L00136A20:
    addiu      $2, $17, -0x30;
    sltiu      $2, $2, 0xA;
    beqz       $2, L00136A58;
    daddu     $16, $0, $0;
  L00136A30:
    sll        $2, $16, 2;
    addu       $2, $2, $16;
    sll        $2, $2, 1;
    addu       $2, $2, $17;
    lb         $17, 0x0($18);
    addiu      $16, $2, -0x30;
    addiu      $2, $17, -0x30;
    sltiu      $2, $2, 0xA;
    bnez       $2, L00136A30;
    addiu     $18, $18, 0x1;
  L00136A58:
    daddu      $21, $16, $0;
    slti       $2, $21, -0x1;
    bnel       $2, $0, L0013697C;
    addiu     $21, $0, -0x1;
    b          L00136980;
    addiu     $3, $17, -0x20;
    b          L0013696C;
    ori       $22, $22, 0x80;
    daddu      $16, $0, $0;
    nop;
  L00136A80:
    sll        $2, $16, 2;
    addu       $2, $2, $16;
    sll        $2, $2, 1;
    addu       $2, $2, $17;
    lb         $17, 0x0($18);
    addiu      $16, $2, -0x30;
    addiu      $2, $17, -0x30;
    sltiu      $2, $2, 0xA;
    bnez       $2, L00136A80;
    addiu     $18, $18, 0x1;
    b          L0013697C;
    daddu     $30, $16, $0;
    b          L0013696C;
    ori       $22, $22, 0x40;
    lb         $3, 0x0($18);
    addiu      $2, $0, 0x6C;
    bne        $3, $2, L00136AD8;
    lbu       $4, 0x0($18);
    addiu      $18, $18, 0x1;
    b          L0013696C;
    ori       $22, $22, 0x20;
    nop;
  L00136AD8:
    b          L00136970;
    ori       $22, $22, 0x10;
    daddu      $2, $20, $0;
    addiu      $20, $20, 0x8;
    lbu        $3, 0x0($2);
    addiu      $19, $29, 0x50;
    addiu      $5, $0, 0x1;
    sw         $5, 0xA8($29);
    b          L00136E74;
    sb        $3, 0x0($19);
    ori        $22, $22, 0x10;
    andi       $2, $22, 0x10;
    beqz       $2, L00136B20;
    daddu     $2, $20, $0;
    addiu      $20, $20, 0x8;
    b          L00136B40;
    ld        $16, 0x0($2);
    nop;
  L00136B20:
    andi       $2, $22, 0x40;
    beqz       $2, L00136B38;
    daddu     $2, $20, $0;
    addiu      $20, $20, 0x8;
    b          L00136B40;
    lh        $16, 0x0($2);
  L00136B38:
    addiu      $20, $20, 0x8;
    lw         $16, 0x0($2);
  L00136B40:
    bgez       $16, L00136D40;
    addiu     $3, $0, 0x1;
    addiu      $2, $0, 0x2D;
    dsubu      $16, $0, $16;
    b          L00136D40;
    sb        $2, 0x90($29);
    andi       $2, $22, 0x10;
    beqz       $2, L00136B80;
    andi      $2, $22, 0x40;
    daddu      $3, $20, $0;
    addiu      $20, $20, 0x8;
    lw         $2, 0x0($3);
    lw         $3, 0xA0($29);
    b          L001368A8;
    sd        $3, 0x0($2);
    nop;
  L00136B80:
    beqz       $2, L00136BA0;
    daddu     $3, $20, $0;
    addiu      $20, $20, 0x8;
    lw         $2, 0x0($3);
    lw         $4, 0xA0($29);
    b          L001368A8;
    sh        $4, 0x0($2);
    nop;
  L00136BA0:
    addiu      $20, $20, 0x8;
    lw         $2, 0x0($3);
    lw         $5, 0xA0($29);
    b          L001368A8;
    sw        $5, 0x0($2);
    nop;
    ori        $22, $22, 0x10;
    andi       $2, $22, 0x10;
    beqz       $2, L00136BD8;
    daddu     $2, $20, $0;
    addiu      $20, $20, 0x8;
    b          L00136BF8;
    ld        $16, 0x0($2);
    nop;
  L00136BD8:
    andi       $2, $22, 0x40;
    beqz       $2, L00136BF0;
    daddu     $2, $20, $0;
    addiu      $20, $20, 0x8;
    b          L00136BF8;
    lhu       $16, 0x0($2);
  L00136BF0:
    addiu      $20, $20, 0x8;
    lwu        $16, 0x0($2);
  L00136BF8:
    b          L00136D3C;
    daddu     $3, $0, $0;
    lui        $2, 0x46;
    daddu      $3, $20, $0;
    addiu      $2, $2, -0x7DA0;
    lw         $16, 0x0($3);
    addiu      $20, $20, 0x8;
    ori        $22, $22, 0x2;
    sw         $2, 0xAC($29);
    addiu      $3, $0, 0x2;
    b          L00136D3C;
    addiu     $17, $0, 0x78;
    daddu      $2, $20, $0;
    lw         $19, 0x0($2);
    bnez       $19, L00136C40;
    addiu     $20, $20, 0x8;
    lui        $2, 0x46;
    addiu      $19, $2, -0x7D88;
  L00136C40:
    bltz       $21, L00136C78;
    daddu     $5, $0, $0;
    daddu      $4, $19, $0;
    jal        memchr;
    daddu     $6, $21, $0;
    beqz       $2, L00136C6C;
    subu      $2, $2, $19;
    sw         $2, 0xA8($29);
    slt        $2, $21, $2;
    beql       $2, $0, L00136E78;
    sb        $0, 0x90($29);
  L00136C6C:
    b          L00136E74;
    sw        $21, 0xA8($29);
    nop;
  L00136C78:
    jal        strlen;
    daddu     $4, $19, $0;
    b          L00136E74;
    sw        $2, 0xA8($29);
    ori        $22, $22, 0x10;
    andi       $2, $22, 0x10;
    beqz       $2, L00136CA8;
    daddu     $2, $20, $0;
    addiu      $20, $20, 0x8;
    b          L00136CC8;
    ld        $16, 0x0($2);
    nop;
  L00136CA8:
    andi       $2, $22, 0x40;
    beqz       $2, L00136CC0;
    daddu     $2, $20, $0;
    addiu      $20, $20, 0x8;
    b          L00136CC8;
    lhu       $16, 0x0($2);
  L00136CC0:
    addiu      $20, $20, 0x8;
    lwu        $16, 0x0($2);
  L00136CC8:
    b          L00136D3C;
    addiu     $3, $0, 0x1;
    lui        $2, 0x46;
    b          L00136CE8;
    addiu     $2, $2, -0x7D80;
    nop;
    lui        $2, 0x46;
    addiu      $2, $2, -0x7DA0;
  L00136CE8:
    sw         $2, 0xAC($29);
    andi       $2, $22, 0x10;
    beqz       $2, L00136D08;
    daddu     $2, $20, $0;
    addiu      $20, $20, 0x8;
    b          L00136D28;
    ld        $16, 0x0($2);
    nop;
  L00136D08:
    andi       $2, $22, 0x40;
    beqz       $2, L00136D20;
    daddu     $2, $20, $0;
    addiu      $20, $20, 0x8;
    b          L00136D28;
    lhu       $16, 0x0($2);
  L00136D20:
    addiu      $20, $20, 0x8;
    lwu        $16, 0x0($2);
  L00136D28:
    andi       $2, $22, 0x1;
    beqz       $2, L00136D3C;
    addiu     $3, $0, 0x2;
    ori        $2, $22, 0x2;
    movn       $22, $2, $16;
  L00136D3C:
    sb         $0, 0x90($29);
  L00136D40:
    bltz       $21, L00136D50;
    sw        $21, 0xA4($29);
    addiu      $2, $0, -0x81;
    and        $22, $22, $2;
  L00136D50:
    bnez       $16, L00136D64;
    addiu     $19, $29, 0x78;
    lw         $2, 0xA4($29);
    beqz       $2, L00136E54;
    subu      $2, $29, $19;
  L00136D64:
    addiu      $2, $0, 0x1;
    beq        $3, $2, L00136E04;
    sltiu     $2, $16, 0xA;
    beqz       $3, L00136D98;
    addiu     $4, $0, 0x7;
    addiu      $2, $0, 0x2;
    beq        $3, $2, L00136E20;
    lui       $2, 0x46;
    addiu      $19, $2, -0x7D68;
    jal        strlen;
    daddu     $4, $19, $0;
    b          L00136E78;
    sw        $2, 0xA8($29);
  L00136D98:
    and        $2, $16, $4;
    dsrl       $16, $16, 3;
    daddiu     $2, $2, 0x30;
    addiu      $19, $19, -0x1;
    andi       $3, $2, 0xFF;
    bnez       $16, L00136D98;
    sb        $3, 0x0($19);
    andi       $2, $22, 0x1;
    beqz       $2, L00136E50;
    addiu     $2, $0, 0x30;
    beql       $3, $2, L00136E54;
    subu      $2, $29, $19;
    addiu      $19, $19, -0x1;
    b          L00136E50;
    sb        $2, 0x0($19);
    nop;
  L00136DD8:
    jal        UModDi3_13a430;
    addiu     $5, $0, 0xA;
    daddu      $4, $16, $0;
    daddiu     $2, $2, 0x30;
    addiu      $19, $19, -0x1;
    andi       $2, $2, 0xFF;
    addiu      $5, $0, 0xA;
    jal        UDivDi3_139eb0;
    sb        $2, 0x0($19);
    daddu      $16, $2, $0;
    sltiu      $2, $16, 0xA;
  L00136E04:
    beqz       $2, L00136DD8;
    daddu     $4, $16, $0;
    daddiu     $2, $16, 0x30;
    addiu      $19, $19, -0x1;
    andi       $2, $2, 0xFF;
    b          L00136E50;
    sb        $2, 0x0($19);
  L00136E20:
    addiu      $4, $0, 0xF;
    nop;
  L00136E28:
    lw         $3, 0xAC($29);
    and        $2, $16, $4;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    addiu      $19, $19, -0x1;
    addu       $2, $3, $2;
    dsrl       $16, $16, 4;
    lbu        $3, 0x0($2);
    bnez       $16, L00136E28;
    sb        $3, 0x0($19);
  L00136E50:
    subu       $2, $29, $19;
  L00136E54:
    addiu      $2, $2, 0x78;
    b          L00136E78;
    sw        $2, 0xA8($29);
  L00136E60:
    beqz       $17, L00137378;
    addiu     $19, $29, 0x50;
    addiu      $4, $0, 0x1;
    sw         $4, 0xA8($29);
    sb         $17, 0x0($19);
  L00136E74:
    sb         $0, 0x90($29);
  L00136E78:
    lw         $21, 0xA8($29);
    lw         $5, 0xA4($29);
    lb         $3, 0x90($29);
    slt        $2, $21, $5;
    lbu        $4, 0x90($29);
    beqz       $3, L00136EA0;
    movn      $21, $5, $2;
    b          L00136EA8;
    addiu     $21, $21, 0x1;
    nop;
  L00136EA0:
    andi       $2, $22, 0x2;
    addu       $21, $2, $21;
  L00136EA8:
    andi       $2, $22, 0x84;
    bnez       $2, L00136F98;
    sw        $2, 0xB0($29);
    subu       $16, $30, $21;
    blez       $16, L00136F98;
    slti      $2, $16, 0x11;
    bnez       $2, L00136F48;
    lui       $8, 0x46;
    addiu      $7, $0, 0x10;
    addiu      $6, $8, -0x7DC0;
    sw         $7, 0x4($23);
    nop;
  L00136ED8:
    sw         $6, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $2, 0x4($29);
    lw         $3, 0x8($29);
    addiu      $2, $2, 0x1;
    addiu      $3, $3, 0x10;
    slti       $4, $2, 0x8;
    sw         $3, 0x8($29);
    bnez       $4, L00136F30;
    sw        $2, 0x4($29);
    lw         $4, 0x9C($29);
    daddu      $5, $29, $0;
    sq         $6, 0xC0($29);
    sq         $7, 0xD0($29);
    jal        Sprint_136670;
    sq        $8, 0xE0($29);
    lq         $6, 0xC0($29);
    lq         $7, 0xD0($29);
    bnez       $2, L00137398;
    lq        $8, 0xE0($29);
    addiu      $3, $29, 0x10;
    daddu      $23, $3, $0;
  L00136F30:
    addiu      $16, $16, -0x10;
    slti       $2, $16, 0x11;
    beql       $2, $0, L00136ED8;
    sw        $7, 0x4($23);
    b          L00136F4C;
    sw        $16, 0x4($23);
  L00136F48:
    sw         $16, 0x4($23);
  L00136F4C:
    addiu      $2, $8, -0x7DC0;
    sw         $2, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $3, 0x4($29);
    lw         $2, 0x8($29);
    addiu      $3, $3, 0x1;
    addu       $2, $2, $16;
    slti       $4, $3, 0x8;
    sw         $2, 0x8($29);
    bnez       $4, L00136F94;
    sw        $3, 0x4($29);
    lw         $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
    addiu      $4, $29, 0x10;
    daddu      $23, $4, $0;
  L00136F94:
    lbu        $4, 0x90($29);
  L00136F98:
    beqz       $4, L00136FF0;
    addiu     $2, $0, 0x1;
    addiu      $3, $29, 0x90;
    sw         $2, 0x4($23);
    sw         $3, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $3, 0x4($29);
    lw         $2, 0x8($29);
    addiu      $3, $3, 0x1;
    addiu      $2, $2, 0x1;
    slti       $4, $3, 0x8;
    sw         $2, 0x8($29);
    bnez       $4, L00137054;
    sw        $3, 0x4($29);
    lw         $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
    addiu      $5, $29, 0x10;
    b          L00137054;
    daddu     $23, $5, $0;
  L00136FF0:
    andi       $2, $22, 0x2;
    beqz       $2, L00137054;
    addiu     $2, $0, 0x30;
    addiu      $4, $0, 0x2;
    sb         $2, 0x80($29);
    addiu      $3, $29, 0x80;
    sb         $17, 0x81($29);
    sw         $4, 0x4($23);
    sw         $3, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $3, 0x4($29);
    lw         $2, 0x8($29);
    addiu      $3, $3, 0x1;
    addiu      $2, $2, 0x2;
    slti       $4, $3, 0x8;
    sw         $2, 0x8($29);
    bnez       $4, L00137054;
    sw        $3, 0x4($29);
    lw         $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
    addiu      $2, $29, 0x10;
    daddu      $23, $2, $0;
  L00137054:
    lw         $3, 0xB0($29);
    addiu      $2, $0, 0x80;
    bne        $3, $2, L00137140;
    lw        $2, 0xA4($29);
    subu       $16, $30, $21;
    blez       $16, L00137144;
    lw        $3, 0xA8($29);
    slti       $2, $16, 0x11;
    bnez       $2, L001370F0;
    lui       $7, 0x46;
    addiu      $6, $0, 0x10;
    addiu      $17, $7, -0x7DB0;
    sw         $6, 0x4($23);
  L00137088:
    sw         $17, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $2, 0x4($29);
    lw         $3, 0x8($29);
    addiu      $2, $2, 0x1;
    addiu      $3, $3, 0x10;
    slti       $4, $2, 0x8;
    sw         $3, 0x8($29);
    bnez       $4, L001370D8;
    sw        $2, 0x4($29);
    lw         $4, 0x9C($29);
    daddu      $5, $29, $0;
    sq         $6, 0xC0($29);
    jal        Sprint_136670;
    sq        $7, 0xD0($29);
    lq         $6, 0xC0($29);
    bnez       $2, L00137398;
    lq        $7, 0xD0($29);
    addiu      $4, $29, 0x10;
    daddu      $23, $4, $0;
  L001370D8:
    addiu      $16, $16, -0x10;
    slti       $2, $16, 0x11;
    beql       $2, $0, L00137088;
    sw        $6, 0x4($23);
    b          L001370F4;
    sw        $16, 0x4($23);
  L001370F0:
    sw         $16, 0x4($23);
  L001370F4:
    addiu      $2, $7, -0x7DB0;
    sw         $2, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $3, 0x4($29);
    lw         $2, 0x8($29);
    addiu      $3, $3, 0x1;
    addu       $2, $2, $16;
    slti       $4, $3, 0x8;
    sw         $2, 0x8($29);
    bnez       $4, L0013713C;
    sw        $3, 0x4($29);
    lw         $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
    addiu      $5, $29, 0x10;
    daddu      $23, $5, $0;
  L0013713C:
    lw         $2, 0xA4($29);
  L00137140:
    lw         $3, 0xA8($29);
  L00137144:
    subu       $16, $2, $3;
    blez       $16, L00137220;
    lw        $2, 0xA8($29);
    slti       $2, $16, 0x11;
    bnez       $2, L001371D0;
    lui       $7, 0x46;
    addiu      $6, $0, 0x10;
    addiu      $17, $7, -0x7DB0;
    sw         $6, 0x4($23);
  L00137168:
    sw         $17, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $2, 0x4($29);
    lw         $3, 0x8($29);
    addiu      $2, $2, 0x1;
    addiu      $3, $3, 0x10;
    slti       $4, $2, 0x8;
    sw         $3, 0x8($29);
    bnez       $4, L001371B8;
    sw        $2, 0x4($29);
    lw         $4, 0x9C($29);
    daddu      $5, $29, $0;
    sq         $6, 0xC0($29);
    jal        Sprint_136670;
    sq        $7, 0xD0($29);
    lq         $6, 0xC0($29);
    bnez       $2, L00137398;
    lq        $7, 0xD0($29);
    addiu      $4, $29, 0x10;
    daddu      $23, $4, $0;
  L001371B8:
    addiu      $16, $16, -0x10;
    slti       $2, $16, 0x11;
    beql       $2, $0, L00137168;
    sw        $6, 0x4($23);
    b          L001371D4;
    sw        $16, 0x4($23);
  L001371D0:
    sw         $16, 0x4($23);
  L001371D4:
    addiu      $2, $7, -0x7DB0;
    sw         $2, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $3, 0x4($29);
    lw         $2, 0x8($29);
    addiu      $3, $3, 0x1;
    addu       $2, $2, $16;
    slti       $4, $3, 0x8;
    sw         $2, 0x8($29);
    bnez       $4, L0013721C;
    sw        $3, 0x4($29);
    lw         $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
    addiu      $5, $29, 0x10;
    daddu      $23, $5, $0;
  L0013721C:
    lw         $2, 0xA8($29);
  L00137220:
    sw         $19, 0x0($23);
    sw         $2, 0x4($23);
    addiu      $23, $23, 0x8;
    lw         $2, 0x4($29);
    lw         $3, 0x8($29);
    lw         $4, 0xA8($29);
    addiu      $2, $2, 0x1;
    sw         $2, 0x4($29);
    addu       $3, $3, $4;
    slti       $4, $2, 0x8;
    bnez       $4, L0013726C;
    sw        $3, 0x8($29);
    lw         $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
    addiu      $5, $29, 0x10;
    daddu      $23, $5, $0;
  L0013726C:
    andi       $2, $22, 0x4;
    beqz       $2, L00137338;
    subu      $16, $30, $21;
    blez       $16, L0013733C;
    lw        $4, 0xA0($29);
    slti       $2, $16, 0x11;
    bnez       $2, L001372F8;
    lui       $8, 0x46;
    addiu      $19, $0, 0x10;
    addiu      $17, $8, -0x7DC0;
    sw         $19, 0x4($23);
  L00137298:
    sw         $17, 0x0($23);
    addiu      $23, $23, 0x8;
    lw         $2, 0x4($29);
    lw         $3, 0x8($29);
    addiu      $2, $2, 0x1;
    addiu      $3, $3, 0x10;
    slti       $4, $2, 0x8;
    sw         $3, 0x8($29);
    bnez       $4, L001372E0;
    sw        $2, 0x4($29);
    lw         $4, 0x9C($29);
    daddu      $5, $29, $0;
    jal        Sprint_136670;
    sq        $8, 0xE0($29);
    bnez       $2, L00137398;
    lq        $8, 0xE0($29);
    addiu      $2, $29, 0x10;
    daddu      $23, $2, $0;
  L001372E0:
    addiu      $16, $16, -0x10;
    slti       $2, $16, 0x11;
    beql       $2, $0, L00137298;
    sw        $19, 0x4($23);
    b          L001372FC;
    sw        $16, 0x4($23);
  L001372F8:
    sw         $16, 0x4($23);
  L001372FC:
    addiu      $2, $8, -0x7DC0;
    sw         $2, 0x0($23);
    lw         $3, 0x4($29);
    lw         $2, 0x8($29);
    addiu      $3, $3, 0x1;
    addu       $2, $2, $16;
    slti       $4, $3, 0x8;
    sw         $2, 0x8($29);
    bnez       $4, L00137338;
    sw        $3, 0x4($29);
    lw         $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
  L00137338:
    lw         $4, 0xA0($29);
  L0013733C:
    slt        $2, $21, $30;
    movz       $30, $21, $2;
    lw         $3, 0x8($29);
    addu       $4, $4, $30;
    beqz       $3, L00137368;
    sw        $4, 0xA0($29);
    lw         $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
  L00137368:
    addiu      $5, $29, 0x10;
    sw         $0, 0x4($29);
    b          L001368A8;
    daddu     $23, $5, $0;
  L00137378:
    lw         $2, 0x8($29);
  L0013737C:
    beqz       $2, L00137394;
    lw        $4, 0x9C($29);
    jal        Sprint_136670;
    daddu     $5, $29, $0;
    bnez       $2, L0013739C;
    lw        $2, 0x9C($29);
  L00137394:
    sw         $0, 0x4($29);
  L00137398:
    lw         $2, 0x9C($29);
  L0013739C:
    lw         $4, 0xA0($29);
    lhu        $3, 0xC($2);
    addiu      $2, $0, -0x1;
    andi       $3, $3, 0x40;
    movz       $2, $4, $3;
  L001373B0:
    ld         $16, 0xF0($29);
  L001373B4:
    ld         $17, 0xF8($29);
    ld         $18, 0x100($29);
    ld         $19, 0x108($29);
    ld         $20, 0x110($29);
    ld         $21, 0x118($29);
    ld         $22, 0x120($29);
    ld         $23, 0x128($29);
    ld         $30, 0x130($29);
    ld         $31, 0x138($29);
    jr         $31;
    addiu     $29, $29, 0x140;
}

