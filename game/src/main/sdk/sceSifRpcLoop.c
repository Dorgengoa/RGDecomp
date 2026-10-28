#include "types.h"

extern void sceSifExecRequest(void);
extern void sceSifGetNextRequest(void);
extern void SleepThread(void);

asm void sceSifRpcLoop(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    b          L0011ABF8;
    daddu     $16, $4, $0;
    nop;
  L0011ABF0:
    jal        sceSifExecRequest;
    nop;
  L0011ABF8:
    jal        sceSifGetNextRequest;
    daddu     $4, $16, $0;
    bnez       $2, L0011ABF0;
    daddu     $4, $2, $0;
    jal        SleepThread;
    nop;
    b          L0011ABF8;
    nop;
}
