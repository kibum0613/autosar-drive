/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AEB_Core_SWC.h
 *
 * Code generated for Simulink model 'AEB_Core_SWC'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Tue Oct  6 17:07:29 2026
 *
 * Target selection: autosar.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef AEB_Core_SWC_h_
#define AEB_Core_SWC_h_
#ifndef AEB_Core_SWC_COMMON_INCLUDES_
#define AEB_Core_SWC_COMMON_INCLUDES_
#include "Platform_Types.h"
#include "Rte_AEB_Core_SWC.h"
#endif                                 /* AEB_Core_SWC_COMMON_INCLUDES_ */

#include "AEB_Core_SWC_types.h"

/* PublicStructure Variables for Internal Data, for system '<Root>' */
typedef struct {
  float64 headway;                     /* '<S4>/Sum' */
  float64 Divide3;                     /* '<S4>/Divide3' */
  float64 FCWstoppingTime;             /* '<S3>/Sum1' */
  float64 PB1stoppingTime;             /* '<S3>/Sum2' */
  float64 PB2stoppingTime;             /* '<S3>/Sum3' */
  float64 FBstoppingTime;              /* '<S3>/Sum4' */
  float64 decel;                       /* '<Root>/AEBLogic' */
  uint8 Delay_DSTATE;                  /* '<Root>/Delay' */
  uint8 is_active_c5_AEB_Core_SWC;     /* '<Root>/AEBLogic' */
  uint8 is_c5_AEB_Core_SWC;            /* '<Root>/AEBLogic' */
} ARID_DEF_AEB_Core_SWC_T;

/* PublicStructure Variables for Internal Data */
extern ARID_DEF_AEB_Core_SWC_T AEB_Core_SWC_ARID_DEF;/* '<S4>/Sum' */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'AEB_Core_SWC'
 * '<S1>'   : 'AEB_Core_SWC/AEBLogic'
 * '<S2>'   : 'AEB_Core_SWC/Compare To Constant'
 * '<S3>'   : 'AEB_Core_SWC/StoppingTimeCalculation'
 * '<S4>'   : 'AEB_Core_SWC/TTCCalculation'
 */
#endif                                 /* AEB_Core_SWC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
