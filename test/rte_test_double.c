#include "rte_test_double.h"
#include "Rte_AEB_Core_SWC.h"

RteIn_T  rte_in;
RteOut_T rte_out;

void Rte_TestDouble_Reset(void)
{
  rte_in.RelDistance = 0.0;
  rte_in.LeadLatOffset = 0.0;
  rte_in.RelVelocity = 0.0;
  rte_in.EgoVelocity = 0.0;
  rte_out.AEBTrigger = 0.0;
  rte_out.Deceleration = 0.0;
  rte_out.writeCount = 0U;
}

/* Implicit read (IRead) */
float64 Rte_IRead_AEB_Core_SWC_Step_RelDistance_RelDistance(void)     { return rte_in.RelDistance; }
float64 Rte_IRead_AEB_Core_SWC_Step_LeadLatOffset_LeadLatOffset(void) { return rte_in.LeadLatOffset; }
float64 Rte_IRead_AEB_Core_SWC_Step_RelVelocity_RelVelocity(void)     { return rte_in.RelVelocity; }
float64 Rte_IRead_AEB_Core_SWC_Step_EgoVelocity_EgoVelocity(void)     { return rte_in.EgoVelocity; }

/* Implicit write (IWrite) */
void Rte_IWrite_AEB_Core_SWC_Step_AEBTrigger_AEBTrigger(float64 u)
{
  rte_out.AEBTrigger = u;
  rte_out.writeCount++;
}

void Rte_IWrite_AEB_Core_SWC_Step_Deceleration_Deceleration(float64 u)
{
  rte_out.Deceleration = u;
  rte_out.writeCount++;
}

float64 *Rte_IWriteRef_AEB_Core_SWC_Step_AEBTrigger_AEBTrigger(void)     { return &rte_out.AEBTrigger; }
float64 *Rte_IWriteRef_AEB_Core_SWC_Step_Deceleration_Deceleration(void) { return &rte_out.Deceleration; }
