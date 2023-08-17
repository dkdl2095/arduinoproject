아두이노 프로젝트 멜로디 재생기
<p align="center">
  <img alt="ArduinoProjectImg" src="https://github.com/dkdl2095/arduinoproject/assets/71371208/b7b61507-40e4-4cfc-aafb-8d403bde5443"/>
</p>
① LCD 디스플레이 16x2 IIC: GND 52번 아래 GND 연결, 5V 22번 위에 5V 연결, SDA 20번 연결, SCL 21번 연결
② 부저: +를 8번 연결, -를 그림 기준 하단부 GND 연결
③ 스위치 버튼: 풀-다운 방식그림 기준 왼쪽 버튼 6번, 중앙 버튼 5번, 오른쪽 버튼 4번
<p align="center">
 <img alt="ArduinoProjectImg" src="https://github.com/dkdl2095/arduinoproject/assets/71371208/166ed876-b25c-47cc-8edb-0ca6883ee80d"/>
</p>
① 다음, 이전 버튼 누름 Arduino에 저장 되어있는 멜로디를 LCD 디스플레이에 출력을 해준다. (다음 버튼을 누르면 다음 멜로디, 이전 버튼을 누르면 이전 멜로디)
② 재생 버튼을 누르면 현재 LCD 화면에 보이는 멜로디를 PlayMelody 라이브러리를 이용하여 부저가 재생할 수 있게 변환 후 부저가 멜로디 재생시켜준다.
