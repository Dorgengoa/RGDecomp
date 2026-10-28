/* rgp:protos */
#define RGP_SELF_CharaTableEntryInit_226380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* 20 parameters: 8 in $4..$11 and 12 on the stack at 0x90..0xE8 (8-byte
   slots).  The forwarded call drops p2/p3, which are the two values stored
   into the object afterwards. */

/*rgp*/



void CharaTableEntryInit_226380(void *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                  s32 a7, s32 a8, s32 a9, s32 a10, s32 a11, s32 a12, s32 a13,
                  s32 a14, s32 a15, s32 a16, s32 a17, s32 a18, s32 a19)
{
    CharaTableDataInit_226f80(a0, a1, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14,
                 a15, a16, a17, a18, a19);
    *(s32 *)((u8 *)a0 + 0x34) = a2;
    *(s16 *)((u8 *)a0 + 0x38) = a3;
    *(s16 *)((u8 *)a0 + 0x3A) = 0;
    *(s32 *)((u8 *)a0 + 0x3C) = 0;
    *(s32 *)((u8 *)a0 + 0x40) = 0;
}
