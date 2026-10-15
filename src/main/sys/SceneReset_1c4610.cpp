#include "types.h"

class A {
    u8 pad000[0x4394];
public:
    /* +0x08 */ virtual void slot08();
};

extern "C" void SceneReset_1c4610(A *self)
{
    self->slot08();
}
