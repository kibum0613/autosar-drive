/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AEB.c
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

#include "AEB.h"
#include "rtwtypes.h"
#include <math.h>
#include "rt_nonfinite.h"

/* Named constants for Chart: '<S1>/AEBLogic' */
#define AEB_IN_Default                 ((uint8_T)1U)
#define AEB_IN_FCW                     ((uint8_T)2U)
#define AEB_IN_Full_Braking            ((uint8_T)3U)
#define AEB_IN_Partial_Braking1        ((uint8_T)4U)
#define AEB_IN_Partial_Braking2        ((uint8_T)5U)

/* Block signals (default storage) */
B_AEB_T AEB_B;

/* Block states (default storage) */
DW_AEB_T AEB_DW;

/* External inputs (root inport signals with default storage) */
ExtU_AEB_T AEB_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_AEB_T AEB_Y;

/* Real-time model */
static RT_MODEL_AEB_T AEB_M_;
RT_MODEL_AEB_T *const AEB_M = &AEB_M_;

/* Model step function */
void AEB_step(void)
{
  real_T rtb_Add1;
  real_T rtb_Divide11;
  uint8_T rtb_FCWactivate;
  boolean_T rtb_AND;

  /* Sum: '<S5>/Sum' incorporates:
   *  Constant: '<S5>/const1'
   *  Inport: '<Root>/Actaul position'
   *  Inport: '<Root>/Pose_lead'
   *  Sum: '<S1>/Add'
   */
  AEB_B.headway = (AEB_U.Pose_lead[0] - AEB_U.s_ego) - 3.7;

  /* Sum: '<S1>/Add1' incorporates:
   *  Inport: '<Root>/Pose_lead'
   *  Inport: '<Root>/v_ego'
   */
  rtb_Add1 = AEB_U.Pose_lead[2] - AEB_U.v_ego;

  /* Abs: '<S5>/Abs' */
  rtb_Divide11 = fabs(rtb_Add1);

  /* Saturate: '<S5>/Saturation' */
  if (rtb_Divide11 > 100.0) {
    rtb_Divide11 = 100.0;
  } else if (rtb_Divide11 < 0.01) {
    rtb_Divide11 = 0.01;
  }

  /* Product: '<S5>/Divide3' incorporates:
   *  Saturate: '<S5>/Saturation'
   */
  AEB_B.Divide3 = AEB_B.headway / rtb_Divide11;

  /* Signum: '<S5>/Sign' */
  if (rtIsNaN(rtb_Add1)) {
    rtb_Add1 = (rtNaN);
  } else if (rtb_Add1 < 0.0) {
    rtb_Add1 = -1.0;
  } else {
    rtb_Add1 = (rtb_Add1 > 0.0);
  }

  /* Product: '<S5>/Divide11' incorporates:
   *  Signum: '<S5>/Sign'
   */
  rtb_Divide11 = AEB_B.Divide3 * rtb_Add1;

  /* Sum: '<S4>/Sum1' incorporates:
   *  Constant: '<S4>/const3'
   *  Constant: '<S4>/const6'
   *  Inport: '<Root>/v_ego'
   *  Product: '<S4>/Divide12'
   */
  AEB_B.FCWstoppingTime = AEB_U.v_ego / 4.0 + 1.2;

  /* Sum: '<S4>/Sum2' incorporates:
   *  Constant: '<S1>/const6'
   *  Constant: '<S4>/const7'
   *  Inport: '<Root>/v_ego'
   *  Product: '<S4>/Divide5'
   */
  AEB_B.PB1stoppingTime = AEB_U.v_ego / 3.8 + 0.08;

  /* Sum: '<S4>/Sum3' incorporates:
   *  Constant: '<S1>/const4'
   *  Constant: '<S4>/const7'
   *  Inport: '<Root>/v_ego'
   *  Product: '<S4>/Divide3'
   */
  AEB_B.PB2stoppingTime = AEB_U.v_ego / 5.3 + 0.08;

  /* Sum: '<S4>/Sum4' incorporates:
   *  Constant: '<S1>/const5'
   *  Constant: '<S4>/const7'
   *  Inport: '<Root>/v_ego'
   *  Product: '<S4>/Divide1'
   */
  AEB_B.FBstoppingTime = AEB_U.v_ego / 9.8 + 0.08;

  /* Logic: '<S1>/AND' incorporates:
   *  Constant: '<S1>/const3'
   *  Delay: '<S1>/Delay'
   *  Inport: '<Root>/v_ego'
   *  RelationalOperator: '<S1>/Relational Operator1'
   */
  rtb_AND = ((AEB_U.v_ego <= 0.27777777777777779) && (AEB_DW.Delay_DSTATE != 0));

  /* Chart: '<S1>/AEBLogic' incorporates:
   *  Constant: '<S1>/const4'
   *  Constant: '<S1>/const5'
   *  Constant: '<S1>/const6'
   *  Delay: '<S1>/Delay'
   */
  if (AEB_DW.is_active_c5_AEB == 0) {
    AEB_DW.is_active_c5_AEB = 1U;
    AEB_DW.is_c5_AEB = AEB_IN_Default;
    AEB_DW.Delay_DSTATE = 0U;
    rtb_FCWactivate = 0U;
    AEB_B.decel = 0.0;
  } else {
    switch (AEB_DW.is_c5_AEB) {
     case AEB_IN_Default:
      AEB_DW.Delay_DSTATE = 0U;
      rtb_FCWactivate = 0U;
      if ((fabs(rtb_Divide11) < AEB_B.FCWstoppingTime) && (rtb_Divide11 < 0.0))
      {
        AEB_DW.is_c5_AEB = AEB_IN_FCW;
        rtb_FCWactivate = 1U;
        AEB_B.decel = 0.0;
      }
      break;

     case AEB_IN_FCW:
      AEB_DW.Delay_DSTATE = 0U;
      rtb_FCWactivate = 1U;
      rtb_Add1 = fabs(rtb_Divide11);
      if ((rtb_Add1 < AEB_B.PB1stoppingTime) && (rtb_Divide11 < 0.0)) {
        AEB_DW.is_c5_AEB = AEB_IN_Partial_Braking1;
        AEB_DW.Delay_DSTATE = 1U;
        AEB_B.decel = 3.8;
      } else if (rtb_Add1 >= 1.2 * AEB_B.FCWstoppingTime) {
        AEB_DW.is_c5_AEB = AEB_IN_Default;
        rtb_FCWactivate = 0U;
        AEB_B.decel = 0.0;
      }
      break;

     case AEB_IN_Full_Braking:
      AEB_DW.Delay_DSTATE = 3U;
      rtb_FCWactivate = 1U;
      if (rtb_AND) {
        AEB_DW.is_c5_AEB = AEB_IN_Default;
        AEB_DW.Delay_DSTATE = 0U;
        rtb_FCWactivate = 0U;
        AEB_B.decel = 0.0;
      }
      break;

     case AEB_IN_Partial_Braking1:
      AEB_DW.Delay_DSTATE = 1U;
      rtb_FCWactivate = 1U;
      if ((fabs(rtb_Divide11) < AEB_B.PB2stoppingTime) && (rtb_Divide11 < 0.0))
      {
        AEB_DW.is_c5_AEB = AEB_IN_Partial_Braking2;
        AEB_DW.Delay_DSTATE = 2U;
        AEB_B.decel = 5.3;
      } else if (rtb_AND) {
        AEB_DW.is_c5_AEB = AEB_IN_Default;
        AEB_DW.Delay_DSTATE = 0U;
        rtb_FCWactivate = 0U;
        AEB_B.decel = 0.0;
      }
      break;

     default:
      /* case IN_Partial_Braking2: */
      AEB_DW.Delay_DSTATE = 2U;
      rtb_FCWactivate = 1U;
      if ((fabs(rtb_Divide11) < AEB_B.FBstoppingTime) && (rtb_Divide11 < 0.0)) {
        AEB_DW.is_c5_AEB = AEB_IN_Full_Braking;
        AEB_DW.Delay_DSTATE = 3U;
        AEB_B.decel = 9.8;
      } else if (rtb_AND) {
        AEB_DW.is_c5_AEB = AEB_IN_Default;
        AEB_DW.Delay_DSTATE = 0U;
        rtb_FCWactivate = 0U;
        AEB_B.decel = 0.0;
      }
      break;
    }
  }

  /* End of Chart: '<S1>/AEBLogic' */

  /* Outport: '<Root>/Deceleration' incorporates:
   *  Gain: '<S1>/Gain'
   */
  AEB_Y.Deceleration = -AEB_B.decel;

  /* Switch: '<S1>/Check the lane' incorporates:
   *  Constant: '<S3>/Constant'
   *  Inport: '<Root>/Pose_lead'
   *  RelationalOperator: '<S3>/Compare'
   */
  if (AEB_U.Pose_lead[1] > -3.1) {
    /* Outport: '<Root>/AEB Trigger' */
    AEB_Y.AEBTrigger = rtb_FCWactivate;
  } else {
    /* Outport: '<Root>/AEB Trigger' incorporates:
     *  Constant: '<S1>/Constant'
     */
    AEB_Y.AEBTrigger = 0.0;
  }

  /* End of Switch: '<S1>/Check the lane' */
}

/* Model initialize function */
void AEB_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void AEB_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
