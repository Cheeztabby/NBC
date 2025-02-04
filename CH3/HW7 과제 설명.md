# HW 7

1. HW7_GameModeBase에서 BP_PlayerPawn을 DefaultPawn으로 등록

2. 충돌 컴포넌트 Capsule Component를 RootComponent로 설정

3. SkeletalMeshComponent - SpringArmComponent - CameraComponent 계층 구조로 등록

4. Physics 비활성화

5. InputAction Move, Look을 InputActionMappingContext에 등록. Move, Look 함수를 SetupPlayerInputComponent에서 바인딩

6. 문제 조건에 따라 Move에서 AddMovementInput을 이용하지 않고 AddActorLocalOffset사용. Look에서 AddControllerYawInput, AddControllerPitchInput 함수를 이용하지 않고 AddLocalRotation 사용

   