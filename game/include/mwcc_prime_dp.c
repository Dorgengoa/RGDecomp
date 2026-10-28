/* Build-environment primer, NOT a game function and never linked.
 *
 * The CodeWarrior IDE compiled every TU in ONE mwcc process, and mwcc keeps a
 * piece of runtime-call state across TUs: once ANY soft-double helper that
 * takes two GPR arguments (dpmul, dpadd, _dpfgt, __divdi3, ...) has been
 * generated, every later implicit fptodp call is modelled as USING a0/a1.
 * That keeps physical a0/a1 live from the previous call up to the fptodp,
 * so the register allocator skips them in that stretch.  A single-file
 * compile never sets the state.
 *
 * Units whose retail colouring shows this (LoadingScreenFrame_3435d0) list this file
 * BEFORE their source in config/toolchain.txt, so it is compiled first in
 * the same mwcc invocation (its own object, mwcc_prime_dp.o, is discarded).
 * s88m x36.
 */
double mwcc_prime_dp(double a, double b)
{
    return a * b;
}
