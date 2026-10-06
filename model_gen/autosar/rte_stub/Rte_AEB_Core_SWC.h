/* This file contains stub implementations of the AUTOSAR RTE functions.
   The stub implementations can be used for testing the generated code in
   Simulink, for example, in SIL/PIL simulations of the component under
   test. Note that this file should be replaced with an appropriate RTE
   file when deploying the generated code outside of Simulink.

   This file is generated for:
   Atomic software component:  "AEB_Core_SWC"
   ARXML schema: "R23-11"
   File generated on: "Tue Oct 06 14:57:26 2026"  */

#ifndef Rte_AEB_Core_SWC_h
#define Rte_AEB_Core_SWC_h
#include "Rte_Type.h"
#include "Compiler.h"

/* Data access functions */
#define Rte_IRead_AEB_Core_SWC_Step_EgoVelocity_EgoVelocity Rte_IRead_AEB_Core_SWC_AEB_Core_SWC_Step_EgoVelocity_EgoVelocity

float64 Rte_IRead_AEB_Core_SWC_Step_EgoVelocity_EgoVelocity(void);

#define Rte_IRead_AEB_Core_SWC_Step_LeadLatOffset_LeadLatOffset Rte_IRead_AEB_Core_SWC_AEB_Core_SWC_Step_LeadLatOffset_LeadLatOffset

float64 Rte_IRead_AEB_Core_SWC_Step_LeadLatOffset_LeadLatOffset(void);

#define Rte_IRead_AEB_Core_SWC_Step_RelDistance_RelDistance Rte_IRead_AEB_Core_SWC_AEB_Core_SWC_Step_RelDistance_RelDistance

float64 Rte_IRead_AEB_Core_SWC_Step_RelDistance_RelDistance(void);

#define Rte_IRead_AEB_Core_SWC_Step_RelVelocity_RelVelocity Rte_IRead_AEB_Core_SWC_AEB_Core_SWC_Step_RelVelocity_RelVelocity

float64 Rte_IRead_AEB_Core_SWC_Step_RelVelocity_RelVelocity(void);

#define Rte_IWrite_AEB_Core_SWC_Step_AEBTrigger_AEBTrigger Rte_IWrite_AEB_Core_SWC_AEB_Core_SWC_Step_AEBTrigger_AEBTrigger

void Rte_IWrite_AEB_Core_SWC_Step_AEBTrigger_AEBTrigger(float64 u);

#define Rte_IWriteRef_AEB_Core_SWC_Step_AEBTrigger_AEBTrigger Rte_IWriteRef_AEB_Core_SWC_AEB_Core_SWC_Step_AEBTrigger_AEBTrigger

float64* Rte_IWriteRef_AEB_Core_SWC_Step_AEBTrigger_AEBTrigger(void);

#define Rte_IWrite_AEB_Core_SWC_Step_Deceleration_Deceleration Rte_IWrite_AEB_Core_SWC_AEB_Core_SWC_Step_Deceleration_Deceleration

void Rte_IWrite_AEB_Core_SWC_Step_Deceleration_Deceleration(float64 u);

#define Rte_IWriteRef_AEB_Core_SWC_Step_Deceleration_Deceleration Rte_IWriteRef_AEB_Core_SWC_AEB_Core_SWC_Step_Deceleration_Deceleration

float64* Rte_IWriteRef_AEB_Core_SWC_Step_Deceleration_Deceleration(void);

/* Entry point functions */
extern FUNC(void, AEB_Core_SWC_CODE) AEB_Core_SWC_Init(void);
extern FUNC(void, AEB_Core_SWC_CODE) AEB_Core_SWC_Step(void);

#endif
