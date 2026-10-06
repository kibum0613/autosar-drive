/* RTE test double for AEB_Core_SWC.
 * Plays the role of the RTE on the host: the test writes sensor values into
 * rte_in, calls the runnable, then reads what the SWC wrote into rte_out. */
#ifndef RTE_TEST_DOUBLE_H
#define RTE_TEST_DOUBLE_H

#include "Platform_Types.h"

typedef struct {
  float64 RelDistance;    /* [m]   lead x - ego x            */
  float64 LeadLatOffset;  /* [m]   lead lateral position     */
  float64 RelVelocity;    /* [m/s] lead v - ego v            */
  float64 EgoVelocity;    /* [m/s]                           */
} RteIn_T;

typedef struct {
  float64 AEBTrigger;     /* 0 / 1                           */
  float64 Deceleration;   /* [m/s^2] negative while braking  */
  uint32  writeCount;     /* number of IWrite calls observed */
} RteOut_T;

extern RteIn_T  rte_in;
extern RteOut_T rte_out;

void Rte_TestDouble_Reset(void);

#endif /* RTE_TEST_DOUBLE_H */
