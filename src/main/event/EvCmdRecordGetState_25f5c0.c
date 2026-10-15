#include "types.h"

extern u8 *GetGameData_1fede0(void);
extern void ScriptSetRefInt_26a1e0(s32, s32);
extern s32 *RecordGetPayloadIfKind3F_430ab0(void *);
extern s32 *RecordGetPayloadIfKind3E_430ad0(void *);
extern s32 *RecordGetPayloadIfKind3D_430af0(void *);
extern s32 *RecordGetPayloadIfKind3C_430b10(void *);
extern s32 *RecordGetPayloadIfKind32_430b30(void *);
extern s32 *RecordGetPayloadIfKind28_430b50(void *);
extern s32 *RecordGetPayloadIfKind1E_430b70(void *);

s32 EvCmdRecordGetState_25f5c0(s64 *arg0, s32 arg1)
{
    u8 *root;
    s32 *info;
    s32 sub;
    s32 a;
    s32 c;
    s32 type;
    s32 val;
    s32 *p;

    root = GetGameData_1fede0();
    info = *(s32 **)(*(u8 **)(root + 0x24) + 0x1188);
    type = info[0];
    sub = info[1];
    a = info[2];
    c = info[6];
    if (arg1 > 0) {
        ScriptSetRefInt_26a1e0((s32)arg0++, a);
    }
    if (arg1 >= 2) {
        ScriptSetRefInt_26a1e0((s32)arg0++, c);
    }
    val = 0;
    if (type == 3) {
        p = RecordGetPayloadIfKind1E_430b70(*(void **)(root + 0x24));
        if (p != 0) {
            val = *p;
        }
    } else if (type == 4) {
        p = RecordGetPayloadIfKind28_430b50(*(void **)(root + 0x24));
        if (p != 0) {
            val = *p;
        }
    } else if (type == 5) {
        p = RecordGetPayloadIfKind32_430b30(*(void **)(root + 0x24));
        if (p != 0) {
            val = *p;
        }
    } else if (type == 6) {
        if (sub == 0x3C) {
            p = RecordGetPayloadIfKind3C_430b10(*(void **)(root + 0x24));
            if (p != 0) {
                val = *p;
            }
        } else if (sub == 0x3D) {
            p = RecordGetPayloadIfKind3D_430af0(*(void **)(root + 0x24));
            if (p != 0) {
                val = *p;
            }
        } else if (sub == 0x3E) {
            p = RecordGetPayloadIfKind3E_430ad0(*(void **)(root + 0x24));
            if (p != 0) {
                val = *p;
            }
        } else if (sub == 0x3F) {
            p = RecordGetPayloadIfKind3F_430ab0(*(void **)(root + 0x24));
            if (p != 0) {
                val = *p;
            }
        }
    }
    if (arg1 >= 3) {
        ScriptSetRefInt_26a1e0((s32)arg0, val);
    }
    return 1;
}
