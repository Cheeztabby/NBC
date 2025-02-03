# HW6 게임 설명



TPS 템플릿 캐릭터를 이용하여 장애물을 피해 스테이지를 클리어 하는 것이 최종 목표입니다.



### 구현 내용

1. HW6_GameModeBase

   언리얼 프로젝트가 레포지토리 용량을 많이 사용하여 과제마다 계속 만들기 어렵다고 판단했습니다. 따라서 프로젝트를 공유하려 했습니다.

   그렇게 하려면 과제를 특정 레벨로 구현하여 계속해서 진행해야 합니다. 특정 레벨에서만 사용하는 게임 오브젝트는 GameMode 혹은 GameModeBase가 맞는 것 같아 GameModeBase를 상속받아 만들었습니다.

   HW6_GameModeBase에서는 해당 레벨을 초기화합니다. 지금 HW6 같은 경우에는 스테이지를 구성하고 있는 Tile, RotatingPlatform, MovingPlatform을 에디터 상에서 조절가능한 세팅 값들을 이용하여 Spawn합니다.

   랜덤 함수를 이용하여 스폰하면서 RotatingPlatform의 Speed, 액터의 길이, MovingPlatform의 Speed, MaxRange 등이 변화합니다.

2.  MovingPlatform

   특정 거리의 1차원 운동을 반복하는 플랫폼입니다. 거리와 속도를 조절할 수 있습니다.

3.  RotatingPlatform

   특정 속도로 회전하는 플랫폼입니다. 

4. Tile

   Tile은 단순히 발판 이외에도 주어진 도전과제의 예시인 트랩으로 사용됩니다.

   Tile은 특정 확률로 Trap으로 스폰되며 Trap으로 설정된 Tile은 타이머를 이용하여 특정 시간에만 Trap으로 작동합니다. Trap으로 작동되는 시간에는 머티리얼을 변화 시켜 플레이어가 피해갈 수 있도록 했습니다.

   Trap으로 작동하는 시간에는 물리법칙이 적용되어 건드리면 떨어집니다. 

   충돌 감지는 적절하게 BoxComponent를 부착하여 OnOverlapBegin 델리게이트 함수를 바인딩하여 충돌을 체크합니다.

