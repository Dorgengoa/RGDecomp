/* SPDX-License-Identifier: CC0-1.0
 * x64.linkgate_control: a header-free program linked at test time WITHOUT the
 * low-address flags; tools/x64/linkgate.py must fail the link. */
int rg_ctl_entry(void) { return 0; }
