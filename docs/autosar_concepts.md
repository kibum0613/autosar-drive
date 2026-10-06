# Classic AUTOSAR 개념 정리 (이 저장소 기준)

개념은 AUTOSAR 공식 문서와 MathWorks 문서를 기준으로 정리하고 이 저장소에서 확인한 실제 예를 붙였습니다.

## 1. 계층 구조

| 계층 | 역할 | 이 프로젝트에서 |
|---|---|---|
| Application Layer (ASW) | 차량 기능을 구현하는 SWC가 있는 곳 | `AEB_Core_SWC` |
| RTE | SWC를 특정 ECU 배치와 무관하게 만들어 주는 중간층. SWC 간, SWC와 BSW 간 통신을 연결 | `Rte_IRead`/`Rte_IWrite` 호출. 실제 RTE 대신 테스트 더블 사용 |
| Services Layer (BSW) | OS, 통신, 메모리, 진단 같은 공통 서비스 | 없음 (`Std_Types.h` 등 헤더만 최소 정의) |
| ECU Abstraction Layer (BSW) | 상위 계층을 ECU 보드 배치와 무관하게 만듦 | 없음 |
| Microcontroller Abstraction Layer (MCAL) | 상위 계층을 MCU와 무관하게 만드는 최하위 드라이버 | 없음. S32K144에서 레지스터를 직접 다룬 부분이 MCAL이 감추는 영역 |
| Complex Drivers (CDD) | 표준에 없는 장치나 타이밍이 엄격한 기능을 하드웨어에서 RTE까지 직접 연결 | 없음 |

## 2. SWC · 포트 · 인터페이스

- **SWC (Software Component)**: 기능 단위. 이 저장소의 SWC는 `APPLICATION-SW-COMPONENT-TYPE` `AEB_Core_SWC`입니다.
- **포트**: SWC의 입출력 창구입니다.
  - R-Port(받는 쪽) 4개: `RelDistance`, `LeadLatOffset`, `RelVelocity`, `EgoVelocity`
  - P-Port(주는 쪽) 2개: `AEBTrigger`, `Deceleration`
- **인터페이스**: 포트로 무엇이 오가는지 정합니다.
  - Sender-Receiver(S/R): 데이터를 보내고 받습니다. 이 저장소의 6개 포트가 모두 S/R이고 데이터 타입은 `float64`입니다.
  - Client-Server(C/S): 함수를 호출하고 결과를 받습니다(예: NvM 읽기, 진단 서비스). 이 저장소에는 없습니다.

## 3. 러너블과 이벤트

- **러너블(Runnable)**: SWC 안에서 실제로 실행되는 C 함수입니다. `AEB_Core_SWC_Init`, `AEB_Core_SWC_Step` 두 개입니다.
- **RTE 이벤트**: 러너블을 언제 실행할지 정합니다. `Event_AEB_Core_SWC_Step`은 `TIMING-EVENT` PERIOD 0.01 s로 10 ms마다 Step을 실행합니다.
- 통합 단계에서 이 러너블들은 OS 태스크에 매핑됩니다. 모델을 고정 스텝 0.01 s로 바꿔 검증한 이유가 여기 있습니다.

## 4. Implicit vs Explicit 통신

| 방식 | API | 동작 |
|---|---|---|
| Implicit (이 저장소) | `Rte_IRead`, `Rte_IWrite` | RTE가 러너블 시작 전에 입력을 복사해 두고 끝난 뒤 출력을 내보냅니다. 한 번 실행되는 동안 값이 바뀌지 않습니다 |
| Explicit | `Rte_Read`, `Rte_Write` | 호출하는 순간 바로 읽고 씁니다. `Rte_IsUpdated` 같은 API로 새 값 여부를 확인할 수 있습니다 |

AEB처럼 한 주기 안에서 TTC와 정지시간을 같은 입력으로 계산해야 하는 로직은 Implicit 방식이 일관성을 지키기 쉽습니다.

## 5. ARXML

SWC가 무엇을 주고받고 언제 실행되는지를 적은 XML 명세입니다. 통합 툴은 이 파일을 읽고 RTE를 생성합니다.

| 파일 | 담긴 것 |
|---|---|
| `AEB_Core_SWC_component.arxml` | SWC, 포트 6개, 러너블 2개, `TIMING-EVENT`, 각 러너블의 읽기·쓰기 접근 |
| `AEB_Core_SWC_interface.arxml` | S/R 인터페이스 6개와 데이터 요소 |
| `AEB_Core_SWC_datatype.arxml` | `float64` 등 구현 데이터 타입과 기본 타입(64 bit IEEE754) |
| `AEB_Core_SWC_implementation.arxml` | 생성된 소스·헤더 목록, 언어(C) |

## 6. 도구 흐름과 A-SPICE

요구사항 → 작업 티켓 → 커밋 → 자동 빌드·테스트 → 결과를 요구사항에 연결하는 추적성이 A-SPICE와 기능안전 심사에서 요구됩니다.
이 저장소에서는 아래처럼 작게 재현했습니다.

- 요구사항 `docs/requirements.md` (REQ-01~11)
- 테스트 이름에 요구사항 ID를 넣고 Jenkins JUnit 보고서에서 ID별 결과 확인
- 테스트로 찾은 문제는 Jira 버그(AEB-12, AEB-13)로 등록하고 커밋 메시지에 티켓 번호 기록

실무에서는 요구사항 관리에 Codebeamer 같은 도구를 쓰지만 이 실습에서는 Markdown 표로 대신했습니다.

## 참고

- AUTOSAR, Layered Software Architecture (CP R24-11): https://www.autosar.org/fileadmin/standards/R24-11/CP/AUTOSAR_CP_EXP_LayeredSoftwareArchitecture.pdf
- AUTOSAR Classic Platform: https://www.autosar.org/standards/classic-platform
- MathWorks, Configure AUTOSAR Sender-Receiver Communication: https://www.mathworks.com/help/autosar/ug/configure-autosar-sender-receiver-communication.html
- MathWorks, Configure AUTOSAR Runnables and Events: https://www.mathworks.com/help/autosar/ug/configure-autosar-runnables-and-events.html
