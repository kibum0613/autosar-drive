/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AEB.h
 *
 * Code generated for Simulink model 'AEB'.
 *
 * Model version                  : 9.1
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Tue Oct  6 14:45:49 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef AEB_h_
#define AEB_h_
#ifndef AEB_COMMON_INCLUDES_
#define AEB_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* AEB_COMMON_INCLUDES_ */

#include "AEB_types.h"
#include "rtGetNaN.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T headway;                      /* '<S5>/Sum' */
  real_T Divide3;                      /* '<S5>/Divide3' */
  real_T FCWstoppingTime;              /* '<S4>/Sum1' */
  real_T PB1stoppingTime;              /* '<S4>/Sum2' */
  real_T PB2stoppingTime;              /* '<S4>/Sum3' */
  real_T FBstoppingTime;               /* '<S4>/Sum4' */
  real_T decel;                        /* '<S1>/AEBLogic' */
} B_AEB_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T Delay_DSTATE;                /* '<S1>/Delay' */
  uint8_T is_active_c5_AEB;            /* '<S1>/AEBLogic' */
  uint8_T is_c5_AEB;                   /* '<S1>/AEBLogic' */
} DW_AEB_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Pose_lead[3];                 /* '<Root>/Pose_lead' */
  real_T s_ego;                        /* '<Root>/Actaul position' */
  real_T v_ego;                        /* '<Root>/v_ego' */
} ExtU_AEB_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Deceleration;                 /* '<Root>/Deceleration' */
  real_T AEBTrigger;                   /* '<Root>/AEB Trigger' */
} ExtY_AEB_T;

/* Real-time Model Data Structure */
struct tag_RTM_AEB_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_AEB_T AEB_B;

/* Block states (default storage) */
extern DW_AEB_T AEB_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_AEB_T AEB_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_AEB_T AEB_Y;

/* Model entry point functions */
extern void AEB_initialize(void);
extern void AEB_step(void);
extern void AEB_terminate(void);

/* Real-time Model object */
extern RT_MODEL_AEB_T *const AEB_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('AEBControllerPractice_copy/AEB Controller')    - opens subsystem AEBControllerPractice_copy/AEB Controller
 * hilite_system('AEBControllerPractice_copy/AEB Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'AEBControllerPractice_copy'
 * '<S1>'   : 'AEBControllerPractice_copy/AEB Controller'
 * '<S2>'   : 'AEBControllerPractice_copy/AEB Controller/AEBLogic'
 * '<S3>'   : 'AEBControllerPractice_copy/AEB Controller/Compare To Constant'
 * '<S4>'   : 'AEBControllerPractice_copy/AEB Controller/StoppingTimeCalculation'
 * '<S5>'   : 'AEBControllerPractice_copy/AEB Controller/TTCCalculation'
 */
#endif                                 /* AEB_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
