/* Back-to-back test: ERT code (SIL build of the original AEB Controller)
 * vs. AUTOSAR SWC code (redesigned AEB Core). Same scenario, same 10 ms
 * steps; every output sample must match exactly.
 *
 * ERT inputs are raw positions (Pose_lead, s_ego, v_ego). The redesign moved
 * the subtraction to the radar side, so the harness feeds the SWC with
 * RelDistance = x_lead - s_ego and RelVelocity = v_lead - v_ego. */
#include <math.h>
#include <string.h>
#include "AEB.h"
#include "AEB_Core_SWC.h"
#include "rte_test_double.h"
#include "mini_junit.h"

#define DT 0.01

typedef struct {
  double leadX, leadY, leadV, leadA;  /* lead start state, accel [m/s2]  */
  double egoV;                        /* ego start speed [m/s]           */
  double seconds;
} scenario_t;

static const scenario_t *g_sc;

static void b2b_run(void)
{
  const scenario_t *sc = g_sc;
  double egoX = 0.0, egoV = sc->egoV, lx = sc->leadX, lv = sc->leadV;
  double maxDiff = 0.0;
  int k, n = (int)(sc->seconds / DT), firstK = -1;

  memset(&AEB_B, 0, sizeof(AEB_B));
  memset(&AEB_DW, 0, sizeof(AEB_DW));
  memset(&AEB_U, 0, sizeof(AEB_U));
  memset(&AEB_Y, 0, sizeof(AEB_Y));
  AEB_initialize();
  memset(&AEB_Core_SWC_ARID_DEF, 0, sizeof(AEB_Core_SWC_ARID_DEF));
  Rte_TestDouble_Reset();
  AEB_Core_SWC_Init();

  for (k = 0; k < n; k++) {
    double d1, d2;
    /* ERT */
    AEB_U.Pose_lead[0] = lx;
    AEB_U.Pose_lead[1] = sc->leadY;
    AEB_U.Pose_lead[2] = lv;
    AEB_U.s_ego = egoX;
    AEB_U.v_ego = egoV;
    AEB_step();
    /* AUTOSAR */
    rte_in.RelDistance = lx - egoX;
    rte_in.LeadLatOffset = sc->leadY;
    rte_in.RelVelocity = lv - egoV;
    rte_in.EgoVelocity = egoV;
    AEB_Core_SWC_Step();

    d1 = fabs(AEB_Y.Deceleration - rte_out.Deceleration);
    d2 = fabs(AEB_Y.AEBTrigger - rte_out.AEBTrigger);
    if (d1 > maxDiff) maxDiff = d1;
    if (d2 > maxDiff) maxDiff = d2;
    if ((d1 > 0.0 || d2 > 0.0) && firstK < 0) firstK = k;

    /* plant: ego follows the ERT command, lead follows its profile */
    egoV += AEB_Y.Deceleration * DT;
    if (egoV < 0.0) egoV = 0.0;
    egoX += egoV * DT;
    lv += sc->leadA * DT;
    if (lv < 0.0) lv = 0.0;
    lx += lv * DT;
  }
  MJ_CHECK(maxDiff == 0.0, "max |diff| = %g, first at t = %.2f s", maxDiff, firstK * DT);
}

static const scenario_t SC[] = {
  /* leadX leadY leadV leadA egoV  T  */
  { 200.0,  0.0,  0.0,  0.0, 25.0, 15.0 },  /* stationary lead            */
  {  80.0,  0.0, 15.0, -4.0, 20.0, 15.0 },  /* lead brakes hard            */
  {  60.0,  0.0, 20.0,  0.0, 20.0, 10.0 },  /* same speed, no closing      */
  {  30.0,  0.0, 25.0,  0.0, 20.0, 10.0 },  /* lead pulls away             */
  { 120.0, -3.5,  0.0,  0.0, 22.0, 15.0 },  /* lead in adjacent lane       */
  {  25.0,  0.0,  0.0,  0.0, 20.0, 10.0 },  /* late detection, short gap   */
};
static const char *NAMES[] = {
  "B2B stationary lead 200 m @ 25 m/s",
  "B2B lead brakes -4 m/s2",
  "B2B equal speed",
  "B2B lead pulls away",
  "B2B adjacent-lane lead",
  "B2B late detection 25 m @ 20 m/s",
};

int main(int argc, char **argv)
{
  size_t i;
  for (i = 0; i < sizeof(SC) / sizeof(SC[0]); i++) {
    g_sc = &SC[i];
    mj_run(NAMES[i], b2b_run, 0, 0);
  }
  return mj_finish("AEB.back_to_back", argc > 1 ? argv[1] : NULL) ? 1 : 0;
}
