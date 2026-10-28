#include "types.h"

extern s32 CreateSema(void *param);
extern s32 DeleteSema(s32 sema_id);
extern s32 WaitSema(s32 sema_id);
extern void TimerUSec2BusClock_122140(s32);
extern s32 SetTimerAlarm_1222f0(s32, s32, void *);
extern void DelayThreadAlarmHandler_117858(void);

/* Naked `asm void` (lever 6). D_004566B0 hi/lo hardcoded per lever 5;
   `0x80008008`/`0x80008003` are already plain numeric constants in the
   original listing, copied verbatim. `DelayThreadAlarmHandler_117858`'s address is taken
   (lui/addiu pair), passed as a handler-function pointer to
   SetTimerAlarm_1222f0. */

asm void DelayThread_117618(void)
{
    .set noreorder;
    addiu $29, $29, -0x50;
    sd    $17, 0x30($29);
    sd    $31, 0x40($29);
    daddu $17, $4, $0;
    sd    $16, 0x20($29);
    mfc0  $2, $12;
    lui   $3, (0x10000 >> 16);
    and   $2, $2, $3;
    bnel  $2, $0, L0011764C;
    lui   $2, 0x45;
    lui   $2, (0x80008008 >> 16);
    b     L001176CC;
    ori   $2, $2, (0x80008008 & 0xFFFF);
L0011764C:
    addiu $3, $0, 0x1;
    addiu $2, $2, 0x66B0;
    sw    $3, 0x4($29);
    sw    $2, 0x14($29);
    daddu $4, $29, $0;
    jal   CreateSema;
    sw    $0, 0x8($29);
    daddu $16, $2, $0;
    bgez  $16, L00117680;
    daddu $5, $17, $0;
    lui   $2, (0x80008003 >> 16);
    b     L001176CC;
    ori   $2, $2, (0x80008003 & 0xFFFF);
L00117680:
    jal   TimerUSec2BusClock_122140;
    daddu $4, $0, $0;
    lui   $5, 0x11;
    daddu $4, $2, $0;
    addiu $5, $5, 0x7858;
    jal   SetTimerAlarm_1222f0;
    daddu $6, $16, $0;
    daddu $17, $2, $0;
    bgez  $17, L001176B8;
    nop;
    jal   DeleteSema;
    daddu $4, $16, $0;
    b     L001176CC;
    daddu $2, $17, $0;
L001176B8:
    jal   WaitSema;
    daddu $4, $16, $0;
    jal   DeleteSema;
    daddu $4, $16, $0;
    daddu $2, $0, $0;
L001176CC:
    ld    $31, 0x40($29);
    ld    $17, 0x30($29);
    ld    $16, 0x20($29);
    jr    $31;
    addiu $29, $29, 0x50;
}
