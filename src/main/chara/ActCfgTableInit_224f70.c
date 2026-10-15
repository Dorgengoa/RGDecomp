#include "types.h"

extern void ActCfgTableReset_225160(void);

void ActCfgTableInit_224f70(void *arg0, s32 arg1, s8 *arg2, s64 arg3, s16 arg4, s32 arg5, s16 arg6, s32 arg7, f32 fparg0, f32 fparg1,
                   s32 arg_sp0, s32 arg_sp8, s32 arg_sp10, s32 arg_sp18, s32 arg_sp20, s32 arg_sp28, s32 arg_sp30, s32 arg_sp38,
                   s32 arg_sp40, s32 arg_sp48, s32 arg_sp50, s32 arg_sp58, s32 arg_sp60, s32 arg_sp68, s32 arg_sp70, s32 arg_sp78,
                   s32 arg_sp80, s32 arg_sp88, s32 arg_sp90, s32 arg_sp98, s32 arg_spA0, s32 arg_spA8, s32 arg_spB0, s32 arg_spB8,
                   s32 arg_spC0, s32 arg_spC8, s32 arg_spD0)
{
    ActCfgTableReset_225160();
    if (arg1 < 0 || arg2 == NULL || *arg2 == 0) {
        return;
    }
    {
        *(s8 **)((u8 *)arg0 + 0x14) = arg2;
        *(s16 *)((u8 *)arg0 + 0x12) = arg1;
        *(s64 *)((u8 *)arg0 + 0x0) = arg3;
        *(s16 *)((u8 *)arg0 + 0x10) = arg4;
        *(f32 *)((u8 *)arg0 + 0x8) = fparg0;
        *(f32 *)((u8 *)arg0 + 0xC) = fparg1;
        *(s32 *)((u8 *)arg0 + 0x20) = arg5;
        if (arg5 != 0) {
            *(s16 *)((u8 *)arg0 + 0x5C) = arg6;
        }
        *(s32 *)((u8 *)arg0 + 0x24) = arg7;
        if (arg7 != 0) {
            *(s16 *)((u8 *)arg0 + 0x5E) = (s16) arg_sp0;
        }
        *(s32 *)((u8 *)arg0 + 0x28) = arg_sp8;
        if (arg_sp8 != 0) {
            *(s16 *)((u8 *)arg0 + 0x60) = (s16) arg_sp10;
        }
        *(s32 *)((u8 *)arg0 + 0x2C) = arg_sp18;
        if (arg_sp18 != 0) {
            *(s16 *)((u8 *)arg0 + 0x62) = (s16) arg_sp20;
        }
        *(s32 *)((u8 *)arg0 + 0x30) = arg_sp28;
        if (arg_sp28 != 0) {
            *(s16 *)((u8 *)arg0 + 0x64) = (s16) arg_sp30;
        }
        *(s32 *)((u8 *)arg0 + 0x34) = arg_sp38;
        if (arg_sp38 != 0) {
            *(s16 *)((u8 *)arg0 + 0x66) = (s16) arg_sp40;
        }
        *(s32 *)((u8 *)arg0 + 0x38) = arg_sp48;
        if (arg_sp48 != 0) {
            *(s16 *)((u8 *)arg0 + 0x68) = (s16) arg_sp50;
        }
        *(s32 *)((u8 *)arg0 + 0x3C) = arg_sp58;
        if (arg_sp58 != 0) {
            *(s16 *)((u8 *)arg0 + 0x6A) = (s16) arg_sp60;
        }
        *(s32 *)((u8 *)arg0 + 0x40) = arg_sp68;
        if (arg_sp68 != 0) {
            *(s16 *)((u8 *)arg0 + 0x6C) = (s16) arg_sp70;
        }
        *(s32 *)((u8 *)arg0 + 0x44) = arg_sp78;
        if (arg_sp78 != 0) {
            *(s16 *)((u8 *)arg0 + 0x6E) = (s16) arg_sp80;
        }
        *(s32 *)((u8 *)arg0 + 0x48) = arg_sp88;
        if (arg_sp88 != 0) {
            *(s16 *)((u8 *)arg0 + 0x70) = (s16) arg_sp90;
        }
        *(s32 *)((u8 *)arg0 + 0x4C) = arg_sp98;
        if (arg_sp98 != 0) {
            *(s16 *)((u8 *)arg0 + 0x72) = (s16) arg_spA0;
        }
        *(s32 *)((u8 *)arg0 + 0x50) = arg_spA8;
        if (arg_spA8 != 0) {
            *(s16 *)((u8 *)arg0 + 0x74) = (s16) arg_spB0;
        }
        *(s32 *)((u8 *)arg0 + 0x54) = arg_spB8;
        if (arg_spB8 != 0) {
            *(s16 *)((u8 *)arg0 + 0x76) = (s16) arg_spC0;
        }
        *(s32 *)((u8 *)arg0 + 0x58) = arg_spC8;
        if (arg_spC8 != 0) {
            *(s16 *)((u8 *)arg0 + 0x78) = (s16) arg_spD0;
        }
    }
}
