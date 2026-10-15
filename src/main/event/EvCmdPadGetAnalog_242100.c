#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern u8 D_004B2570[];

extern f32 PadGetAnalogLXNorm_183af0(u8 *p);
extern f32 PadGetAnalogLYNorm_183a50(u8 *p);
extern f32 PadGetAnalogRXNorm_183c30(u8 *p);
extern f32 PadGetAnalogRYNorm_183b90(u8 *p);
extern void ScriptSetRefFloat_249010(E8 *q, f32 v);

s32 EvCmdPadGetAnalog_242100(E8 *q, s32 n)
{
    if (n > 0) {
        ScriptSetRefFloat_249010(q++, PadGetAnalogLXNorm_183af0(D_004B2570));
    }
    if (n > 1) {
        ScriptSetRefFloat_249010(q++, PadGetAnalogLYNorm_183a50(D_004B2570));
    }
    if (n > 2) {
        ScriptSetRefFloat_249010(q++, PadGetAnalogRXNorm_183c30(D_004B2570));
    }
    if (n > 3) {
        ScriptSetRefFloat_249010(q, PadGetAnalogRYNorm_183b90(D_004B2570));
    }
    return 1;
}
