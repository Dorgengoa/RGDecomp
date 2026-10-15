#include "types.h"

typedef struct Sub_FUN_00202d70 {
    u8 pad000[0x24C];
    u8 f24C;
} Sub_FUN_00202d70;

typedef struct Obj_FUN_00202d70 {
    u8 pad000[0x20];
    Sub_FUN_00202d70 *f20;
} Obj_FUN_00202d70;

extern const u8 D_00527020[];
extern Obj_FUN_00202d70 *GetGameData_1fede0(void);
extern void LeaderHudLeaderChangedThunk_503ff0(void);
extern void func_4F7A00(const u8 *p);

void FieldHudReshowMaybe_202d70(void)
{
    Obj_FUN_00202d70 *o;

    o = GetGameData_1fede0();
    if ((o->f20->f24C & 1) != 0) {
        LeaderHudLeaderChangedThunk_503ff0();
        func_4F7A00(D_00527020);
    }
}
