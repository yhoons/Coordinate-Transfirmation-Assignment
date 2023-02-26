# Coordinate-Transformation-Assignment

## Environment:
- mac m1 (Ventura 13.0)


## TODO:
- eigen3, Pangolin build
- refactoring
- code review

![화면_기록_2023-02-26_오전_12_28_34_AdobeExpress](https://user-images.githubusercontent.com/79200729/221390820-0dd43109-f680-4383-ab7c-7b12fbaa0f2a.gif)


## Issues:

### 1. java install error

- 이미 로컬에 Java가 설치되어있고 환경변수도 설정했지만 계속 설치하라는 문제

-> ./scripts/install_prerequisites.sh -m brew all 명령어를 통해 필수 라이브러리 설치 가능했지만 Java install error는 해결하지 못했습니다.


<img width="1150" alt="스크린샷 2023-02-24 오후 8 34 51" src="https://user-images.githubusercontent.com/79200729/221390895-3fe5ae4e-81c9-4fc8-8609-b7524dc76cf2.png">

   
### 2. main에 pangolin 상대경로 문제

->Opencv, Eigen3 같은 경우 상대 경로를 잘 찾아갔지만 Pangoling의 경우 pathing이 되지않아 절대 경로로 설정하였습니다.

### 3. OpenGL 라이브러리 파일 참조 문제

-> 원인은 정확히 모르겠으나, 1번 해결 방법으로 인해 해결된 것 같습니다.

<img width="1233" alt="스크린샷 2023-02-24 오후 6 55 35" src="https://user-images.githubusercontent.com/79200729/221391143-ca6da66d-280f-4a81-a61a-c46a82325625.png">


Refactoring에 대한 이해가 많이 부족한 것 같습니다. 열심히 공부하겠습니다.
