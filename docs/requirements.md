# AEB_Core_SWC 요구사항과 테스트 추적표

Stateflow 차트(AEBLogic)와 블록 구성을 읽고 SWC가 지켜야 할 동작을 요구사항으로 정리했습니다.
각 요구사항은 `test/test_swc_unit.c`의 테스트 하나와 1:1로 연결됩니다.

| ID | 요구사항 | 근거(모델) | 테스트 | 결과 |
|---|---|---|---|---|
| REQ-01 | TTC가 FCW 정지시간(v/4+1.2 s) 이상이면 경고·제동 없음 | AEBLogic Default 상태 | t_no_action_when_far | PASS |
| REQ-02 | 선행차가 멀어지면(RelVelocity>0) 작동하지 않음 | TTC 부호 조건 `TTC < 0` | t_no_action_when_lead_pulls_away | PASS |
| REQ-03 | 제동 전에 FCW 경고가 먼저 나감 | Default → FCW 전이 | t_fcw_before_braking | PASS |
| REQ-04 | 감속 단계는 FCW → PB1(3.8) → PB2(5.3) → FB(9.8) 순서로만 올라감 | 상태 전이 구조 | t_stages_never_skip | PASS |
| REQ-05 | 25 m/s, 정지 선행차 200 m 조건에서 충돌 없이 정지 | 폐루프 시뮬레이션 | t_stops_before_stationary_lead | PASS |
| REQ-06 | 정지(v ≤ 1 km/h) 후 경고·감속 해제 | `v_ego <= 0.2778 && Delay != 0` | t_release_after_stop | PASS |
| REQ-07 | FCW는 TTC ≥ 1.2 × FCW 정지시간일 때만 해제(히스테리시스) | FCW → Default 전이 | t_fcw_hysteresis | PASS |
| REQ-08 | 인접 차로 선행차(y ≤ -3.1 m)에는 AEBTrigger 0 | Switch "Check the lane" | t_no_trigger_adjacent_lane | PASS |
| REQ-09 | 인접 차로 선행차에는 Deceleration도 0 | Switch "Check the lane (decel)" (AEB-12로 추가) | t_no_decel_adjacent_lane | PASS |
| REQ-10 | Step 러너블은 매 주기 출력 포트 2개를 모두 기록 | Outport 2개 | t_every_step_writes_both_ports | PASS |
| REQ-11 | 옆 차로에서 끼어든(cut-in) 선행차에도 FCW가 제동보다 먼저 나감 | (모델에 없음) | t_cut_in_fcw_before_braking | XFAIL · AEB-13 |

## Back-to-Back 테스트

`test/test_b2b.c`는 같은 시나리오를 두 생성 코드에 동시에 넣고 10 ms마다 출력을 비교합니다.

- ERT 코드: 원본 AEB Controller(입력 Pose_lead, s_ego, v_ego)
- AUTOSAR 코드: 재설계한 AEB Core SWC(입력 RelDistance, LeadLatOffset, RelVelocity, EgoVelocity)

정지 선행차, 선행차 급제동, 등속, 이탈, 근거리 늦은 감지 5개 시나리오에서 최대 오차 0입니다.
입력 구조를 바꾸는 재설계가 동작을 바꾸지 않았다는 증거로 씁니다.
인접 차로 시나리오는 AEB-12 수정으로 의도적으로 달라진 부분이라 AEBTrigger는 기준과 같고 Deceleration은 0인지를 봅니다.

## AEB-12 (REQ-09) · 수정 완료

- 발견: 차선 판정 Switch가 AEBTrigger에만 걸려 있었습니다. 인접 차로(y = -3.5 m) 정지 차량에 경고는 0인데 감속 명령은 -3.8 → -5.3 m/s²가 나갔습니다.
- 원래 강의 통합 모델에서는 플랜트 쪽 Switch가 AEBTrigger로 감속을 다시 걸러서 실제 오제동은 없었습니다. 하지만 SWC를 따로 떼어 다른 ECU에 붙이면 이 전제가 사라집니다.
- 수정: Deceleration 경로에도 같은 조건의 Switch "Check the lane (decel)"을 넣고 AUTOSAR 코드를 다시 생성했습니다. 수정 전 모델은 `AEB_Core_SWC_before_AEB12.slx`로 남겼습니다.
- 확인: REQ-09 XFAIL → PASS, 나머지 요구사항과 B2B 시나리오는 그대로 통과합니다.

## AEB-13 (REQ-11) · 열린 이슈

- AEB-12 수정 뒤 끼어들기 상황을 시험하다 발견했습니다.
- 상태도는 선행차가 옆 차로에 있어도 TTC만 보고 단계를 올립니다. 그래서 선행차가 t = 3 s에 끼어드는 순간 AEBTrigger 1과 감속 -5.3 m/s²가 동시에 나가고 FCW 경고 단계가 없습니다.
- 조치 후보: 차선 조건을 상태도 입력으로 넣어 차로 밖이면 Default로 돌아가게 하기.
