#include "types.h"
typedef char *va_list;
extern void VfprintfR_1374e0(void *out, const char *fmt, va_list ap);

asm void Fprintf_12f9a0(void *out, const char *fmt, ...)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $6, 0x30($29);
    addiu      $6, $29, 0x30;
    sd         $31, 0x0($29);
    sd         $7, 0x38($29);
    sd         $8, 0x40($29);
    sd         $9, 0x48($29);
    sd         $10, 0x50($29);
    sd         $11, 0x58($29);
    swc1       $f12, 0x10($29);
    swc1       $f13, 0x14($29);
    swc1       $f14, 0x18($29);
    swc1       $f15, 0x1C($29);
    swc1       $f16, 0x20($29);
    swc1       $f17, 0x24($29);
    swc1       $f18, 0x28($29);
    jal        VfprintfR_1374e0;
    swc1      $f19, 0x2C($29);
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
