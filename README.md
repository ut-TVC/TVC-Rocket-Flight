<div align="center">

# TVC-로켓비행 코드 

<a href="https://www.arduino.cc">
    <img alt="arduino" src="https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white" /></a>
<a href="https://www.iso.org/standard/74528.html">
    <img alt="C" src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" /></a>
<a href="https://isocpp.org">
    <img alt="C++" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" /></a>
<br>
<br>

이 저장소에서는 모델 로켓들에대한 thrust vector control (이하 TVC) 소스코드가 포함되어 있습니다. 해당 소프트웨어는 주 기계(state-machine*유한상태기계*)와 PID 제어 루프로 구성되어있으며 로켓이 동력으로 상승하는 동안 로켓의 상승 방향을 조정합니다.

<img alt="flight video" src="https://github.com/tomkuttler/TVC-Rocket-Flight-Code/blob/main/flight.gif" width="400" />

</div>

<details>
<summary>목차</summary>

- [다운로드](#다운로드)
- [사용법](#사용법)
- [기능들](#기능들)
    - [State Machine](#state-machine)
    - [PID-제어-루프](#PID-제어-루프)
    - [낙하산 전개](#낙하산-전개)
- [라이센스](#라이센스)
- [원본레포지토리]()
</details>

## 다운로드

이 소프트웨어를 사용하기위해서는 Teensy 4.1 보드와 Teensy Loader Application이 포함된 Arduino IDE 가 필요합니다. 다음 단계를 따라 소프트웨어를 다운로드 할 수 있습니다.

1. 해당 저장소의 코드를 컴퓨터로 다운 받습니다.
2. `TVC-Flight-Code.ino` 를  Arduino IDE 에서 열어주세요
3. Teensy 보드에 컴파일된 코드를 적용해주세요 .

## 사용법

- 이 소프트웨어와 함께 TVC 시스템을 사용하려면 두 개의 서보로 회전할 수 있는 비행 컨트롤러와 모터 마운트가 필요합니다. 
- 'Rocket.h' 및 'StateMachine.h' 파일의 매개 변수를 특정 로켓에 맞게 조정해야 합니다.   
- 올바른 매개 변수를 적용한 후 코드를 Teensy에 업로드합니다. 
- 로켓을 발사하기 전에 비행 컨트롤러의 전원을 켜는 것을 잊지 마세요.
- 소프트웨어는 자동으로 발사를 감지하며, TVC 시스템은 PID 제어 루프를 기반으로 로켓이 상승하는 동안 자동으로 로켓의 방향을 조정합니다. 
- 로켓을 테스트하거나 발사할 때는 모든 안전 지침을 따르고 항상 안전하고 합법적인 방식으로 테스트를 수행하는 것이 중요합니다.

## 기능들

### State Machine

The state machine  현재 비행 상태를 기반으로 모형 로켓을 제어하고 있습니다. The state machine 는 다음 4가지 상태가 있습니다.:

- `LAUNCH_PAD_IDLE`: TVC 시스템이 초기화되고 로켓이 발사를 기다리는 초기화 상태입니다.
- `ASCENT`: TVC 시스템이 동력 상승 중 로켓의 방향을 제어하는 상승 상태입니다.
- `DESCENT`: TVC 시스템이 비활성화되고 로켓이 낙하하는 하강 상태입니다.
- `LANDED`: 로켓이 복구를 기다리는 착륙 상태입니다.

### PID-제어-루프

PID 제어 루프는 로켓의 현재 방향과 원하는 방향에 따라 모터 마운트의 방향을 조정하는 역할을 합니다. TVC 시스템은 x 방향의 방향과 y 방향의 방향의 방향으로 두 개의 개별 PID 제어 루프를 사용합니다.

Each PID control loop has three components:

각 PID 제어 루프에는 세 가지 구성 요소가 있습니다:

- 비례: 비례 성분은 현재 방향과 원하는 방향의 차이에 따라 로켓의 방향을 조정합니다.
- 적분: 적분 구성 요소는 현재 방향과 원하는 방향 사이의 누적 오차를 기반으로 로켓의 방향을 조정합니다.
- 도함수: 도함수 구성 요소는 현재 방향과 원하는 방향 사이의 오차 변화 속도에 따라 로켓의 방향을 조정합니다.

TVC 시스템은 두 개의 개별 PID 제어 루프를 사용하여 모터 마운트에 짐벌을 가하는 두 개의 서보를 사용하여 로켓의 방향을 x 방향과 y 방향 모두에서 독립적으로 조정할 수 있습니다.

### 낙하산-전개

TVC 시스템은 상승 중 로켓의 방향을 제어하는 반면, 낙하산을 배치하는 데는 별도의 기계식 낙하산 분사 시스템이 사용됩니다. 이 시스템은 스프링과 로켓이 상승 상태에서 하강 상태로 전환할 때 상태 기계의 신호에 의해 트리거되는 서보로 구성됩니다. 상승에서 하강으로 전환하는 동안 낙하산을 분사함으로써 로켓은 손상을 입지 않고 안전하게 감속하여 지상으로 돌아갈 수 있습니다.

## 라이센스 

이 프로젝트는 [MIT 라이선스](https://opensource.org/licenses/MIT) )에 따라 라이선스가 부여됩니다. 원작자에게 저작권을 부여하는 한 개인 및 상업적 목적 모두에 이 소프트웨어를 자유롭게 사용, 수정 및 배포할 수 있습니다. 라이선스에 대한 자세한 내용은 'LICENCE' 파일을 참조하세요.

## 원본레포지토리

해당 레포지토리는 다음 레포지토리의 포크본입니다. 
- [TVC-Rocket-Flight-Code](https://github.com/tomkuttler/TVC-Rocket-Flight-Code)