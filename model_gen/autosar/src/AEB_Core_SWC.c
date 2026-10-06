/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AEB_Core_SWC.c
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

#include "AEB_Core_SWC.h"
#include "Platform_Types.h"
#include <math.h>

/* Named constants for Chart: '<Root>/AEBLogic' */
#define AEB_Core_SWC_IN_Default        ((uint8)1U)
#define AEB_Core_SWC_IN_FCW            ((uint8)2U)
#define AEB_Core_SWC_IN_Full_Braking   ((uint8)3U)
#define AEB_Core_SW_IN_Partial_Braking1 ((uint8)4U)
#define AEB_Core_SW_IN_Partial_Braking2 ((uint8)5U)

/* PublicStructure Variables for Internal Data */
ARID_DEF_AEB_Core_SWC_T AEB_Core_SWC_ARID_DEF;/* '<S4>/Sum' */

/* Model step function */
void AEB_Core_SWC_Step(void)
{
  float64 rtb_Divide11;
  float64 u0;
  sint32 tmp;
  uint8 rtb_FCWactivate;
  boolean rtb_AND;
  boolean rtb_Compare;

  /* RelationalOperator: '<S2>/Compare' incorporates:
   *  Constant: '<S2>/Constant'
   *  Inport: '<Root>/LeadLatOffset'
   */
  rtb_Compare = (Rte_IRead_AEB_Core_SWC_Step_LeadLatOffset_LeadLatOffset() >
                 -3.1);

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/const1'
   *  Inport: '<Root>/RelDistance'
   */
  AEB_Core_SWC_ARID_DEF.headway =
    Rte_IRead_AEB_Core_SWC_Step_RelDistance_RelDistance() - 3.7;

  /* Abs: '<S4>/Abs' incorporates:
   *  Inport: '<Root>/RelVelocity'
   *  Signum: '<S4>/Sign'
   */
  rtb_Divide11 = Rte_IRead_AEB_Core_SWC_Step_RelVelocity_RelVelocity();
  u0 = fabs(rtb_Divide11);

  /* Saturate: '<S4>/Saturation' */
  if (u0 > 100.0) {
    u0 = 100.0;
  } else if (u0 < 0.01) {
    u0 = 0.01;
  }

  /* Product: '<S4>/Divide3' incorporates:
   *  Saturate: '<S4>/Saturation'
   */
  AEB_Core_SWC_ARID_DEF.Divide3 = AEB_Core_SWC_ARID_DEF.headway / u0;

  /* Signum: '<S4>/Sign' */
  if (rtb_Divide11 < 0.0) {
    tmp = -1;
  } else {
    tmp = (rtb_Divide11 > 0.0);
  }

  /* Product: '<S4>/Divide11' incorporates:
   *  Signum: '<S4>/Sign'
   */
  rtb_Divide11 = AEB_Core_SWC_ARID_DEF.Divide3 * (float64)tmp;

  /* Product: '<S3>/Divide12' incorporates:
   *  Inport: '<Root>/EgoVelocity'
   *  Product: '<S3>/Divide1'
   *  Product: '<S3>/Divide3'
   *  Product: '<S3>/Divide5'
   *  RelationalOperator: '<Root>/Relational Operator1'
   */
  u0 = Rte_IRead_AEB_Core_SWC_Step_EgoVelocity_EgoVelocity();

  /* Sum: '<S3>/Sum1' incorporates:
   *  Constant: '<S3>/const3'
   *  Constant: '<S3>/const6'
   *  Inport: '<Root>/EgoVelocity'
   *  Product: '<S3>/Divide12'
   */
  AEB_Core_SWC_ARID_DEF.FCWstoppingTime = u0 / 4.0 + 1.2;

  /* Sum: '<S3>/Sum2' incorporates:
   *  Constant: '<Root>/const6'
   *  Constant: '<S3>/const7'
   *  Product: '<S3>/Divide5'
   */
  AEB_Core_SWC_ARID_DEF.PB1stoppingTime = u0 / 3.8 + 0.08;

  /* Sum: '<S3>/Sum3' incorporates:
   *  Constant: '<Root>/const4'
   *  Constant: '<S3>/const7'
   *  Product: '<S3>/Divide3'
   */
  AEB_Core_SWC_ARID_DEF.PB2stoppingTime = u0 / 5.3 + 0.08;

  /* Sum: '<S3>/Sum4' incorporates:
   *  Constant: '<Root>/const5'
   *  Constant: '<S3>/const7'
   *  Product: '<S3>/Divide1'
   */
  AEB_Core_SWC_ARID_DEF.FBstoppingTime = u0 / 9.8 + 0.08;

  /* Logic: '<Root>/AND' incorporates:
   *  Constant: '<Root>/const3'
   *  Delay: '<Root>/Delay'
   *  RelationalOperator: '<Root>/Relational Operator1'
   */
  rtb_AND = ((u0 <= 0.27777777777777779) && (AEB_Core_SWC_ARID_DEF.Delay_DSTATE
              != 0));

  /* Chart: '<Root>/AEBLogic' incorporates:
   *  Constant: '<Root>/const4'
   *  Constant: '<Root>/const5'
   *  Constant: '<Root>/const6'
   *  Delay: '<Root>/Delay'
   */
  if (AEB_Core_SWC_ARID_DEF.is_active_c5_AEB_Core_SWC == 0) {
    AEB_Core_SWC_ARID_DEF.is_active_c5_AEB_Core_SWC = 1U;
    AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC = AEB_Core_SWC_IN_Default;
    AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 0U;
    rtb_FCWactivate = 0U;
    AEB_Core_SWC_ARID_DEF.decel = 0.0;
  } else {
    switch (AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC) {
     case AEB_Core_SWC_IN_Default:
      AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 0U;
      rtb_FCWactivate = 0U;
      if ((fabs(rtb_Divide11) < AEB_Core_SWC_ARID_DEF.FCWstoppingTime) &&
          (rtb_Divide11 < 0.0)) {
        AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC = AEB_Core_SWC_IN_FCW;
        rtb_FCWactivate = 1U;
        AEB_Core_SWC_ARID_DEF.decel = 0.0;
      }
      break;

     case AEB_Core_SWC_IN_FCW:
      AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 0U;
      rtb_FCWactivate = 1U;
      u0 = fabs(rtb_Divide11);
      if ((u0 < AEB_Core_SWC_ARID_DEF.PB1stoppingTime) && (rtb_Divide11 < 0.0))
      {
        AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC =
          AEB_Core_SW_IN_Partial_Braking1;
        AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 1U;
        AEB_Core_SWC_ARID_DEF.decel = 3.8;
      } else if (u0 >= 1.2 * AEB_Core_SWC_ARID_DEF.FCWstoppingTime) {
        AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC = AEB_Core_SWC_IN_Default;
        rtb_FCWactivate = 0U;
        AEB_Core_SWC_ARID_DEF.decel = 0.0;
      }
      break;

     case AEB_Core_SWC_IN_Full_Braking:
      AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 3U;
      rtb_FCWactivate = 1U;
      if (rtb_AND) {
        AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC = AEB_Core_SWC_IN_Default;
        AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 0U;
        rtb_FCWactivate = 0U;
        AEB_Core_SWC_ARID_DEF.decel = 0.0;
      }
      break;

     case AEB_Core_SW_IN_Partial_Braking1:
      AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 1U;
      rtb_FCWactivate = 1U;
      if ((fabs(rtb_Divide11) < AEB_Core_SWC_ARID_DEF.PB2stoppingTime) &&
          (rtb_Divide11 < 0.0)) {
        AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC =
          AEB_Core_SW_IN_Partial_Braking2;
        AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 2U;
        AEB_Core_SWC_ARID_DEF.decel = 5.3;
      } else if (rtb_AND) {
        AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC = AEB_Core_SWC_IN_Default;
        AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 0U;
        rtb_FCWactivate = 0U;
        AEB_Core_SWC_ARID_DEF.decel = 0.0;
      }
      break;

     default:
      /* case IN_Partial_Braking2: */
      AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 2U;
      rtb_FCWactivate = 1U;
      if ((fabs(rtb_Divide11) < AEB_Core_SWC_ARID_DEF.FBstoppingTime) &&
          (rtb_Divide11 < 0.0)) {
        AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC = AEB_Core_SWC_IN_Full_Braking;
        AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 3U;
        AEB_Core_SWC_ARID_DEF.decel = 9.8;
      } else if (rtb_AND) {
        AEB_Core_SWC_ARID_DEF.is_c5_AEB_Core_SWC = AEB_Core_SWC_IN_Default;
        AEB_Core_SWC_ARID_DEF.Delay_DSTATE = 0U;
        rtb_FCWactivate = 0U;
        AEB_Core_SWC_ARID_DEF.decel = 0.0;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/AEBLogic' */

  /* Switch: '<Root>/Check the lane' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (rtb_Compare) {
    tmp = rtb_FCWactivate;
  } else {
    tmp = 0;
  }

  /* Outport: '<Root>/AEBTrigger' incorporates:
   *  Switch: '<Root>/Check the lane'
   */
  Rte_IWrite_AEB_Core_SWC_Step_AEBTrigger_AEBTrigger(tmp);

  /* Switch: '<Root>/Check the lane (decel)' incorporates:
   *  Constant: '<Root>/Constant'
   *  Gain: '<Root>/Gain'
   */
  if (rtb_Compare) {
    u0 = -AEB_Core_SWC_ARID_DEF.decel;
  } else {
    u0 = 0.0;
  }

  /* Outport: '<Root>/Deceleration' incorporates:
   *  Switch: '<Root>/Check the lane (decel)'
   */
  Rte_IWrite_AEB_Core_SWC_Step_Deceleration_Deceleration(u0);
}

/* Model initialize function */
void AEB_Core_SWC_Init(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
