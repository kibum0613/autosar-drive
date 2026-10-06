# 일반 C(ERT) 코드 vs AUTOSAR 코드 비교

같은 AEB 로직을 두 타깃으로 생성한 결과를 비교했습니다.

- ERT: 원본 `AEB Controller`를 `ert.tlc`로 생성 (`model_gen/ert/AEB.c`)
- AUTOSAR: 입력을 재설계한 `AEB Core`를 `autosar.tlc`로 생성 (`model_gen/autosar/src/AEB_Core_SWC.c`)

동작이 같다는 것은 `test/test_b2b.c` Back-to-Back 테스트로 확인했습니다(AEB-12로 의도적으로 바꾼 인접 차로 감속만 예외).

## 한눈에 보기

| 항목 | ERT (`ert.tlc`) | AUTOSAR (`autosar.tlc`) |
|---|---|---|
| 입력 읽기 | 전역 구조체 직접 접근 `AEB_U.Pose_lead[2] - AEB_U.v_ego` | RTE 함수 `Rte_IRead_AEB_Core_SWC_Step_RelVelocity_RelVelocity()` |
| 출력 쓰기 | `AEB_Y.Deceleration = -AEB_B.decel;` | `Rte_IWrite_AEB_Core_SWC_Step_Deceleration_Deceleration(u0);` |
| 실행 단위 | `AEB_initialize()`, `AEB_step()`, `AEB_terminate()` | 러너블 `AEB_Core_SWC_Init`, `AEB_Core_SWC_Step` |
| 누가 언제 부르나 | `ert_main.c`나 사용자가 직접 호출 | ARXML의 `TIMING-EVENT`(PERIOD 0.01 s)로 OS 태스크에 매핑되어 RTE가 호출 |
| 내부 상태 저장 | `AEB_B`(블록 출력), `AEB_DW`(상태), `AEB_U`/`AEB_Y`(입출력) 전역 구조체 | `AEB_Core_SWC_ARID_DEF` 하나 (입출력은 RTE 버퍼에 있음) |
| 데이터 타입 | `real_T`, `boolean_T` (`rtwtypes.h`) | `float64`, `boolean`, `uint8` (AUTOSAR `Platform_Types.h`) |
| 외부 명세 | 없음 | ARXML 4종: component(포트·러너블·이벤트), interface(S/R 인터페이스), datatype, implementation |
| 단독 빌드 | `rtwtypes.h`만 있으면 됨 | RTE 헤더와 `Std_Types.h`·`Compiler.h` 등 BSW 헤더가 있어야 함 |
| 오브젝트 크기 (gcc -O2, x86-64) | text 1,341 B · data 8 B · bss 160 B | text 1,205 B · data 0 B · bss 64 B (AEB-12 수정 후) |

## 핵심 차이: 데이터가 어디서 오는지 코드가 모른다

ERT 코드는 입력이 `AEB_U`라는 전역 변수에 있다고 가정합니다.
호출하는 쪽이 그 구조체에 값을 채워 넣어야 하므로 코드와 통합 방식이 묶여 있습니다.

AUTOSAR 코드는 `Rte_IRead_...()`만 부릅니다.
값이 같은 ECU의 다른 SWC에서 오는지, CAN으로 다른 ECU에서 오는지는 RTE 설정(ARXML과 시스템 구성)이 정합니다.
그래서 SWC 코드는 손대지 않고 다른 ECU로 옮길 수 있습니다.

## 막혔던 지점 (기록)

- Simulink에서 대상 파일을 `autosar.tlc`로 먼저 바꾸지 않으면 `autosar.api.create`가 AUTOSAR 매핑 생성을 거부했습니다. 순서를 바꿔 해결했습니다(Jira AEB-11).
- AUTOSAR 코드를 gcc로 따로 빌드하려니 `Rte_AEB_Core_SWC.h`, `Std_Types.h`, `Compiler.h`가 필요했습니다. RTE 헤더는 Simulink가 만든 stub을 쓰고 BSW 헤더는 최소 정의를 직접 작성했습니다. RTE 함수 본문은 테스트 더블(`test/rte_test_double.c`)로 대신했습니다.

## 리뷰하며 본 점

- `AEBTrigger`가 `float64`로 나갑니다. 0/1 신호라 `boolean`이나 `uint8`로 바꾸면 통신 부하와 메모리를 줄일 수 있습니다.
- 모든 신호가 `float64`입니다. 배정밀도 FPU가 없는 MCU라면 연산 비용이 커서 `float32`나 고정소수점 검토가 필요합니다.
- 차량 길이 3.7 m, 정지시간 계수(4.0, 3.8, 5.3, 9.8)가 상수로 코드에 박혀 있습니다. 차종별로 튜닝하려면 캘리브레이션 파라미터로 빼야 합니다.
- `AEB_Core_SWC_Init` 러너블에는 이벤트가 연결되어 있지 않습니다(ARXML에 `TIMING-EVENT`만 있음). 통합할 때 초기화 이벤트 연결을 확인해야 합니다.
