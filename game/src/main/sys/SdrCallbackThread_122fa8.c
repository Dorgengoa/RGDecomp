#include "types.h"

extern void sceSifInitRpc_119b60(void);
extern void GetThreadId(void);
extern void sceSifSetRpcQueue(void);
extern void sceSifRegisterRpc(void);
extern void sceSifRpcLoop(void);

asm void SdrCallbackThread_122fa8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        sceSifInitRpc_119b60;
    daddu     $4, $0, $0;
    lui        $16, 0x49;
    jal        GetThreadId;
    addiu     $16, $16, -0x1640;
    daddu      $4, $16, $0;
    jal        sceSifSetRpcQueue;
    daddu     $5, $2, $0;
    lui        $4, 0x49;
    lui        $6, 0x12;
    lui        $7, 0x49;
    lui        $5, (0x80000704 >> 16);
    daddu      $10, $16, $0;
    daddu      $8, $0, $0;
    daddu      $9, $0, $0;
    addiu      $6, $6, 0x3018;
    addiu      $7, $7, -0x1680;
    addiu      $4, $4, -0x1628;
    jal        sceSifRegisterRpc;
    ori       $5, $5, (0x80000704 & 0xFFFF);
    daddu      $4, $16, $0;
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    j          sceSifRpcLoop;
    addiu     $29, $29, 0x20;
}
