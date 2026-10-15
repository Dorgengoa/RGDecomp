#include "types.h"

class C_00368390 {
public:
    /* +0x008 */ virtual void s008();
    /* +0x00C */ virtual void s00C();
    /* +0x010 */ virtual void s010();
    /* +0x014 */ virtual void s014();
    /* +0x018 */ virtual void s018();
    /* +0x01C */ virtual void s01C();
    /* +0x020 */ virtual void s020();
    /* +0x024 */ virtual void s024();
    /* +0x028 */ virtual void s028();
    /* +0x02C */ virtual void s02C();
    /* +0x030 */ virtual void s030();
    /* +0x034 */ virtual void s034();
    /* +0x038 */ virtual void s038();
    /* +0x03C */ virtual void s03C();
    /* +0x040 */ virtual void s040();
    /* +0x044 */ virtual void s044();
    /* +0x048 */ virtual void s048();
    /* +0x04C */ virtual void s04C();
    /* +0x050 */ virtual void s050();
    /* +0x054 */ virtual void s054();
    /* +0x058 */ virtual void s058();
    /* +0x05C */ virtual void s05C();
    /* +0x060 */ virtual void v60();
    /* +0x064 */ virtual void s064();
    /* +0x068 */ virtual void s068();
    /* +0x06C */ virtual void v6C();
};

extern "C" void MemStackReset_14d830(void *p);

extern "C" void DataTableClear_368390(C_00368390 *o)
{
    o->v6C();
    o->v60();
    if (*(s16 *)((u8 *)o + 0x78) > 0) {
        MemStackReset_14d830((u8 *)o + 0x14);
    }
}
