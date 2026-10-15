#include "types.h"

typedef struct {
    u8 pad0[0x128];
    s32 unk128;
} Elem128_001DC580;

typedef struct {
    u8 pad0[0x178];
    s32 unk178;
} Elem178_001DC580;

typedef struct {
    u8 pad0[0x1C8];
    s16 unk1C8;
    s16 unk1CA;
} Obj001DC580;

s32 MapAreaGetBlockCount_1dce20(Obj001DC580 *);                    /* extern */
s32 MapAreaGetBlocks_1dce30(Obj001DC580 *);                    /* extern */
s32 MapAreaGetShareCount_1dce50(Obj001DC580 *);                    /* extern */
s32 MapAreaGetShares_1dce60(Obj001DC580 *);                    /* extern */
s32 MapDataIsStreamActive_1e7920(s32);                              /* extern */
s32 MapDataIsLoaded_1e79d0();                                 /* extern */

void MapAreaRebuildActiveLists_1dc580(Obj001DC580 *arg0) {
    Elem178_001DC580 *temp_3;
    Elem128_001DC580 *temp_2;
    s32 var_21;
    s32 var_20_2;
    s32 var_20;
    s32 var_19;
    s32 temp_17_2;
    s32 temp_17;
    s32 var_4;
    s32 var_3;
    s32 temp_19;
    s32 temp_18;

    temp_19 = arg0->unk1C8;
    temp_18 = arg0->unk1CA;
    arg0->unk1C8 = 0;
    arg0->unk1CA = 0;
    if (MapDataIsLoaded_1e79d0() != 0) {
        var_21 = MapAreaGetShares_1dce60(arg0);
        if (var_21 != 0) {
            temp_17 = MapAreaGetShareCount_1dce50(arg0);
            var_20 = 0;
            while (var_20 < temp_17) {
                if (MapDataIsStreamActive_1e7920(var_21) != 0) {
                    ((Elem128_001DC580 *)((u8 *) arg0 + (arg0->unk1C8 * 4)))->unk128 = var_21;
                    arg0->unk1C8 = (s16) (arg0->unk1C8 + 1);
                }
                var_20 += 1;
                var_21 += 0x58;
            }
            var_3 = arg0->unk1C8;
            while (var_3 < temp_19) {
                temp_2 = (Elem128_001DC580 *)((u8 *) arg0 + (var_3 * 4));
                var_3 += 1;
                temp_2->unk128 = 0;
            }
        }
        var_20_2 = MapAreaGetBlocks_1dce30(arg0);
        if (var_20_2 != 0) {
            temp_17_2 = MapAreaGetBlockCount_1dce20(arg0);
            var_19 = 0;
            while (var_19 < temp_17_2) {
                if (MapDataIsStreamActive_1e7920(var_20_2) != 0) {
                    ((Elem178_001DC580 *)((u8 *) arg0 + (arg0->unk1CA * 4)))->unk178 = var_20_2;
                    arg0->unk1CA = (s16) (arg0->unk1CA + 1);
                }
                var_19 += 1;
                var_20_2 += 0xCC;
            }
            var_4 = arg0->unk1CA;
            while (var_4 < temp_18) {
                temp_3 = (Elem178_001DC580 *)((u8 *) arg0 + (var_4 * 4));
                var_4 += 1;
                temp_3->unk178 = 0;
            }
        }
    }
}
