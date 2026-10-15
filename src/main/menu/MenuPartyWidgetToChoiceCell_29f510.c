#include "types.h"

extern s32 UiSetWidgetPos_290f60(s32, void *, s16, s16);
extern s16 D_0047EC20;
extern s16 D_0047EC22;
extern s16 D_0047EC24;
extern s16 D_0047EC26;

typedef struct {s16 a,b;} S2;
s32 MenuPartyWidgetToChoiceCell_29f510(void *arg0, void *arg1, void *arg2) {
    s16 tableA[2];
    s16 tableB[2];

    if (arg2 == NULL) {
        return 0;
    }
    *(S2 *)tableA = *(S2 *)&D_0047EC20;
    *(S2 *)tableB = *(S2 *)&D_0047EC24;
    UiSetWidgetPos_290f60(*(s32 *)((u8 *)arg0 + 0x4C4), arg1,
                 tableA[*(s16 *)((u8 *)arg2 + 0x10)],
                 tableB[*(s16 *)((u8 *)arg2 + 0x12)]);
    return 1;
}
