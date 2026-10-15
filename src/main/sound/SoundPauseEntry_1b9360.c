/* MATCH (s41m). Stale pre-match note follows -- PARKED s15j: m2c's own draft reads "sp38" which is never declared (an
   aliased field of the opaque sp30 buffer SoundResolveKey_1b9970 fills). Needs the
   retail .s read to recover the real stack layout before a build round
   trip is worth spending. */
#include "types.h"

typedef struct {
    u8 pad0[4];
    s16 unk4;
    s8 unk6;
    u8 pad7[0xA - 7];
    s8 unkA;
} Rec001B9360;

typedef struct {
    u8 pad0[8];
    Rec001B9360 *unk8;
    u8 padC[4];
} Buf001B9360;
typedef struct {
    u8 pad0[0x18];
    s32 unk18;
    s32 unk1C;
    u8 pad20[0x154 - 0x20];
    s32 unk154;
} Row001B9360;

typedef struct {
    u8 pad0[6];
    s8 unk6;
    u8 pad8[0x18 - 8];
    s32 *unk18;
    void *unk1C;
} Elem001B9360;

void SoundSendCmd_1b6cc0(s32, s32, s32, Row001B9360 *);    /* extern */
void SoundResolveKey_1b9970(Buf001B9360 *, u32, s32);         /* extern */
extern u8 D_0049EB10[];

void SoundPauseEntry_1b9360(u32 arg0, s32 arg1) {
    Buf001B9360 sp30;
    Rec001B9360 *rec;
    s32 var_16;
    s32 temp_3_2;
    s32 temp_6;
    s8 temp_3;
    u32 var_17;
    Row001B9360 *var_16_2;
    Elem001B9360 *var_4;
    Row001B9360 *var_5;
    Row001B9360 *var_7;

    var_17 = arg0;
    var_16 = arg1;
    if (var_17 != -1U) {
        SoundResolveKey_1b9970(&sp30, var_17, var_16);
        rec = sp30.unk8;
        if (rec != NULL && rec->unk6 == 4) {
            temp_3 = rec->unkA;
            if (temp_3 >= 0) {
                var_16 = rec->unk4;
                var_17 = (u32)(temp_3 & 0xFF) << 0x18;
            }
        }
    }
    if (var_17 != -1U) {
        temp_3_2 = (var_17 >> 0x18) & 0xFF;
        temp_6 = (var_17 >> 0x10) & 0xFF;
        if ((temp_3_2 < 0) || (temp_3_2 > 0x10)) {
            var_7 = NULL;
        } else {
            var_7 = (Row001B9360 *)(D_0049EB10 + (temp_3_2 * 0x1E0));
        }
        if (var_7 != NULL) {
            if (!((temp_6 >= 0) && (temp_6 < 5))) {
                var_5 = NULL;
            } else {
                var_5 = (Row001B9360 *)((u8 *) var_7 + (temp_6 * 0x38) + 0x18);
            }
            if (var_5 != NULL) {
                if (!((var_16 >= 0) && (var_16 < var_5->unk18))) {
                    var_4 = NULL;
                } else {
                    var_4 = (Elem001B9360 *)((u8 *) var_5->unk1C + (var_16 * 0xC));
                }
                if ((var_4 != NULL) && (var_4->unk6 == 2) && (var_7->unk154 == 1)) {
                    if (!((temp_3_2 >= 0) && (temp_3_2 <= 0x10))) {
                        var_16_2 = NULL;
                    } else {
                        var_16_2 = (Row001B9360 *)(D_0049EB10 + (temp_3_2 * 0x1E0));
                    }
                    if ((var_16_2 != NULL) && (var_16_2->unk154 == 1)) {
                        SoundSendCmd_1b6cc0(0xD, 1, (s32) *(s32 *)((u8 *)var_16_2 + 8), var_7);
                        var_16_2->unk154 = 3;
                    }
                }
            }
        }
    }
}
