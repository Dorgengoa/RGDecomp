#include "types.h"

extern void MemStackClear_14dff0(void *);
extern void CharaDataRecInit_1ee610(void *);
extern void ListNodeInit_1ef9d0(void *);
extern void ListAppendTail_1ef9e0(void *, void *);
extern void IdSlotTableInit_1efa30(void *);
extern u8 D_004B3910[16];

typedef struct {
    u8 pad000[0xF88];
    s16 unkF88;
    u8 pad8A[0xF90 - 0xF8A];
    void *unkF90;
    s32 unkF94;
} Obj;

void CharaDataMgrInit_1edf40(u8 *arg0) {
    s32 var_16;
    s32 var_16_2;
    s32 var_16_3;
    s32 var_4;
    Obj *temp_2;

    *(void **)(arg0 + 0xF90) = NULL;
    var_16 = 0;
    *(s32 *)(arg0 + 0xF94) = 0;
    do {
        CharaDataRecInit_1ee610(arg0 + (var_16 * 0x74));
        var_16 += 1;
    } while (var_16 < 0x20);
    var_16_2 = 0;
    do {
        MemStackClear_14dff0(arg0 + (var_16_2 * 0x58) + 0xE80);
        var_16_2 += 1;
    } while (var_16_2 < 3);
    var_4 = 0;
    do {
        temp_2 = (Obj *)(arg0 + (var_4 * 2));
        var_4 += 1;
        temp_2->unkF88 = -1;
    } while (var_4 < 3);
    *(void **)(arg0 + 0xF90) = arg0;
    ListNodeInit_1ef9d0(arg0);
    var_16_3 = 1;
    do {
        ListAppendTail_1ef9e0(*(void **)(arg0 + 0xF90), arg0 + (var_16_3 * 0x74));
        var_16_3 += 1;
    } while (var_16_3 < 0x20);
    IdSlotTableInit_1efa30(&D_004B3910);
}
