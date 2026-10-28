/* The one VU0 register file of the port's EE (include/port/vu0.h).  Only the
 * bring-up model (RG_VU0_MODE=model, RG_VU0_ORACLE) has it; with RG_VU0_LOCAL
 * every translation unit has its own (docs/NATIVE-CPU.md). */
#include "port/vu0.h"

#if !RG_VU0_IS_LOCAL
rg_vu0_state rg_vu0 = {
    /* vf0 = (0, 0, 0, 1.0f); everything else starts at zero, as after reset */
    { { { 0.0f, 0.0f, 0.0f, 1.0f } } },
};
#else
typedef int rg_vu0_no_global_file; /* nothing here: no shared register file */
#endif
