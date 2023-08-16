#include "PlayMelody.h"
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

class LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint8_t SW1_PIN{ 4U };  // 다음곡 버튼
const uint8_t SW2_PIN{ 5U };  // 이전곡 버튼
const uint8_t SW3_PIN{ 6U };  // 플레이 버튼
const uint8_t SW4_PIN{ 7U };  // 정지 버튼
const uint8_t BUZZER_PIN{ 8U };

uint16_t number = 0;
struct Song {
  int id;
  char title[29];
  char melody[1200];
};
Song songs;

// 곡 (ID, TITLE, MELODY)
const char input1[] = "{\"ID\": 1,\"TITLE\": \"TalesWeaver-Reminisence\",\"MELODY\": \"t90v12l8b+.a+>d+.c4<a+g+g.g+g.d+4l16&d+d+g+a+l8b+.a+>d+.c4gg+g.d+.c<a+4g+4b+.a+>d+.c4<a+g+g.g+a+.d+4.d+f4f>c&c2<g+2g2v13<f.l16<gg+n39gg+4gg+n39g+g4gg+n39g+g&g2v12l8.>b+a+8>d+c<a+8n51a+g+g8d+4c4b+a+8n51a+4>g8g+8gd+<d+16b+8d+&d+8d+8b+a+8>d+c<a+8n51gg+l8gd+4n32d+f.b+.c+g+.&g+a+l16b+g4d+8.fg2f8>cc&c4<f8b+g&g4>d+8.<a+8b+8a+8.fg+8ga+gf8.b+8fb+8g8.>d+8c+8.c4<<a+>cd+g+b+4.d+8f8c+b+d+fb+8g8d+>d+8n39l8c+c4gg+g.d+c.<g+4fg+g+.a+.b+g2f+4o6c4o3f.b+a+.>d+4c+c<a+g+16a+b+d+4.l16d+g+d+l8.c+f8b+a+4>g4d+<f16b+4a+4>c4c<d+l16g+a+>c4defga+4l8g+gg+4.d+f4<a+g+>c+4<a+.>c16l4rv15cdel8.fb+8a+fb+8a+gg+8g8d+<g+8>c4fb+8a+>e4l12cgg+l8.gd+c8<a+4g+4fb+8a+f>d+8c+cgg+8l4gn56fc8<a+8g+gfl12fg+a+b+4l16fg+a+b+l8.fb+8a+fb+8a+gl8gg+gd+c.d+f.b+a+.>e4l16&ecgg+l8g.d+c<g+16f+4>c4c.<a+g+.>c4l12rb+a+l8.gd+8c<g+2f<g+8a+8>e16&e4l12<a+g+a+l8.gg+8gf+2c+2l8&c+fg+a+b+rf4e4gg+g4f.c4<g+16>f4o1v12l16>a+c+f+8.c+f+8a+c+f+8.c+l8f+>g.fg.g+.>cd+.g+.f2&f16g+b+a+1\"}";
const char input2[] = "{\"ID\": 2,\"TITLE\": \"MapleStory-LithHarbor\",\"MELODY\": \"t135v15l32o21v12l8da>f+e4f+d<ada>f+e4f+d<adga>d4<agadga>d4<agada>f+e4f+d<ada>f+e4f+d<adga>d4<agadga>d4<agada>f+e4f+d<ada>f+e4f+d<av15l8<da>el4.f+g8are4l8f+r<ga>d4.eg4.rg64f+16.&f+64&f+e4dv12l8dga>d4<agadga>d4<agada>f+e4f+d<adv15gf+e4d4c+d2def+ga4dc+<bar4>b4ag4f+4.gabe4g4.g4.a4.b4>edc+l16c-r8.c+r<al8r.da>d<ada>d<ada>d<ada>d<af+2.gf+ga4a2ref+ga4b4.f+gf+e4d4ef+1g2.rd&d1dg>d<ada>d<av15d4<a4b>c+4dgf+4e4d4c+d1f+gae4g4.f+2.ededrc+4c-4c+d1f+2g2adf+e4c+4<b4ab4rf+gl4a.b.aba8g8gf+8e8f+l2a.r8b>c+d1e4<a>c+4l32rf+2.&f+8.&f+g1d1l8da>d<ada>d<av15f+2.l8gf+ga2.rl2bar>c+d.<a4g.f+4ae1f+4g4d1rf+4g4aerl4f+gf+d2c+<bl8abrf+gar4b2a4d4eg4f+ef+l4ra2.b2.>c+d1e1f+1rg.b8>c+d.<a.r.>f+8e8dc+.l8d<a>ef+4.gad<a>el4f+ga8l8<da>d<ada>d<ada>d<ada>d<av15l4><f+g.f+.ag8f+.edl16c+r<b8r8ar4.rg8a8l4>d<a8>erg2f+ag8f+.ed2c+2l8d<ga>dre4.adf+e4c+4<b4ab4rf+gl4a.b.aba8g8gf+8e8f+a2.r8b2>c+2d1e<a2>c+d1&\"}";
const char input3[] = "{\"ID\": 3,\"TITLE\": \"UnderTail-Megalovania\",\"MELODY\": \"t120v15l16>dd>d8<ar8g+rg8f8dfgcc>d8<ar8g+rg8f8dfg<bb>>d8<ar8g+rg8f8dfg<a+a+>>d8<ar8g+rg8f8dfgdd>d8<ar8g+rg8f8dfgcc>d8<ar8g+rg8f8dfg<bb>>d8<ar8g+rg8f8dfg<a+a+>>d8<ar8g+rg8f8dfgf8ffrf8f8d8d4rf8ffrg8g+8g64g+64g32fdfgr8f8ffrg8g+rl8ab+a.>ddl16d<a>dc4rg4<a8aara8a8g8g4ra8aara8gra8>dr<al8g>d<agfb+gfen58l16cdrf8b+2r2rfdfgg+gfdl32g+gfdf8g2l16rg+8ab+8ag+gfdel8fga>cc+<g+l16g+gfg2rl8<fga>fl4edefgea2l16ag+gf+fed+dc+2d+2o2l2v15>>><a+.>f4edf1&f1<a+.>f4eddl24dc+c<ba+ag+gf+fed+d1v15l16>dd>d8<ar8g+rg8f8dfgcc>d8<ar8g+rg8f8dfg<bb>>d8<ar8g+rg8f8dfg<bb>>d8<ar8g+rg8f8dfgdd>d8<ar8g+rg8f8dfgcc>d8<ar8g+rg8f8dfgdd>d8<ar8g+rg8f8dfgdd>d8<ar8g+rg8f8dfg<f8f8n46f8f8f8<a+a+a+>f8g8g8cg8g8g8cccg8a8a8da8g+8g+8c+c+c+g+8>>c8c8<cb+8b8b8<bbb>b8f8f8n58f8f8f8<a+a+a+>f8g8g8cg8g8g8cccg8dd>d8<ar8g+rg8f8dfgdd>d8<ar8g+rg8f8dfg<a+a+>>d8<ar8g+rg8f8dfgcc>d8<ar8g+rg8f8dfgdd>d8<ar8g+rg8f8dfgdd>d8<ar8g+rg8f8dfg<a+a+>>d8<ar8g+rg8f8dfgcc>d8<ar8g+rg8f8dfg\"}";
const char input4[] = "{\"ID\": 4,\"TITLE\": \"NewJeans-ditto\",\"MELODY\": \"t134v14l8>c+c+4<f+a2&av8e1v13e1a&a2.v14>c+c+4<f+l2a&a8v13eeeel8.f+f+f+8f+4r4f+f+f+8f+4r4eee8e4r4eee8ec+c+8ddd8d4r4ddd8df+e8c+c+l8c+c-16c+.<ae>e2e2<a>c+4c+<f+f+ab4>c+c+c+<f+f+abg+>c+c+c+16r16<f+f+aba>c+c+c+c+c+dc+<b4.ar4>dc+<b4.ar4>dc+<b4n37b4.n37ba2>e2<a>c+4c+<f+f+ab4>c+4c+<f+f+abf+>c+c+c+<f+f+aba>c+4c+c+c+dc+<b4.ar4>dc+<b4.ar4>dc+<b4n37ba4rv14>f+l4f+g+af+>c+2&c+8r<f+8f+g+ae>c+2&c+8r<f+8f+g+aav13l8.eee8ec+d8ee4&e16eef+8l4ec+2r8v14e8f+g+af+>c+2&c+8r<f+8f+g+a>c+8<a8b.a8g+e8e8v13<a>c+8c+.<av14l8.>eee8ec+d8ee4&e16v13eef+8l4ec+2r8v14f+8f+g+an49v15l8.f+f+f+8f+4r4f+f+f+8f+4r4eee8e4r4eee8ec+c+8ddd8d4r4ddd8df+e8c+c+c+8c-16c+l4rv14f+g+an49v15l8.f+f+f+8f+4r8<a8>f+f+f+8f+ag+8eee8e4r4eee8ec+c+8ddd8d4r4ddd8df+e8c+c+l8c+c-16c+.<af+v14>e2e2v13<a>c+4c+<f+f+ab4>c+4c+<f+f+abf+>c+4c+<f+f+aba>c+4c+c+c+dc+l4.<ba>d8c+8<bal8>dc+<b4n37ba4rv14>f+l4f+g+af+>c+2&c+8r<f+8f+g+a>c+8<a8b.a8g+e8e.c+8c+.<al8.>eee8ec+d8ee4&e16v13eef+8l4ec+2r8v14f+8f+g+an49v15l8.f+f+f+8f+4r4f+f+f+8f+4r4eee8e4r4eee8ec+c+8ddd8d4r4ddd8df+e8c+c+c+8c-16c+l4rf+g+an49l8.f+f+f+8f+4r8<a8>f+f+f+8f+ag+8eee8e4r4eee8ec+c+8ddd8d4r4ddd8df+e8c+c+l8c+c-16c+.<af+v14>e2e2v13f+&f+2.v14>c+c+4<f+a2&av8e1v13e1a&a2.v14>c+c+4<f+a2&av13a2\"}";
//const char input5[] = "{\"ID\": 5,\"TITLE\": \"YOUNHA-EventHorizon\",\"MELODY\": \"t98v15b8l16n61b8e8c+8ebe>ec+<beb8n61b8f4f+bn61f4a8e>f+8ec+<eabn61ea4eg>ef+8<b8gn61eg>dc+<bl8aee16ae>c+.<ea16b16n61ee16ae>c+.<ea16b16n61d+d+16a>d+.f+2<abn61b2&b<g+2l16ro6e&e4.r8<c+c-c+8.c-c+8.c+<baa8r8n61b>c+8.c-c+8.c+<bal8aa>f+ec+4<bbaabn61g+4a4.abn61b4>edc+4<b4b4a4.n61bbaa4f+a4bn61b2&brl16n61b>c+8.c-c+8.c+<baa8r8n61b>c+8.c-c+8.c+<baa8>f+8ee8c+l8c+.<b.baab>c+c+4dee4l16aa8.ee8.dd8c+c+8e8aa8.ee8.dd8c+l8c+c+<bbaa>f+f+f+4ef+f+4ab4v12ba16bb+ba.aae.a2&a16r4ba16bb+ba.aaal16ee8ddc+2&c+l8def+e4f+g+a4bb+b4a4.v15bn73l16c+r>d8c+8<b8b8.ab>c+4&c+d8c+8<b8b8a8b>c+8.n61rl8dc+<bb.a16g>f+ec+4<bba4l16f+g+a8.f+f+g+a8aba4eg+a8.eeg+a8aba8>c+8<bb8aa4l8af+a4v14bv13n73v12b2rv15bn73l16c+r>d8c+8<b8b8.ab>c+4&c+d8c+8<b8b8a8b>c+8.n61rl8dc+<bb.a16g>f+ec+4<bba4l16f+g+a8.f+f+g+a8aba4eg+a8.eeg+a8aba8>c+8<bb8aa4l8af+a4bn73b2e>dc+16c+<a16a4af+a1&a\"}";
//const char input6[] = "{\"ID\": 6,\"TITLE\": \"Kartrider-MansionTheme\",\"MELODY\": \"t124v15l16grgrgf+g8b+4bbgr8.aaf+8r8aaf+8r4grgrgf+g8b+4bbgr8.aaf+8r8aaf+8r8<ef+g8g8gf+g8f+4d4e8.aa4g+ra4>ef+g8rgb+4.b8argrf+v12<a>df+v15gv12c-dgv15gv12cegv15adf+ab8b8b8bbl8ba4.gggg16g16gf+4.ceg4c-dg4b4aga2bbbb16b16ba4.gggg16g16gf+4.ceg4c-dg4b4a16g16f+g>dgf+e4.ef+.g.ad4.l16c-cd4.<d8c4.c-c<a4>e4d4.gf+l8gab>de4.ef+.g.ad4.l16c-cd4c-4c4.c-ce8d8c8<b8a4<a4b4del24f+gab4>d4l8<f+.g.agf+gb>e4d4c4ef+g4d4<b4agaef+4b4>d4<f+.g.agf+gb>e4d4c4gf+gdc<bbbaag2>c4d+4<g.g+.a+g+gg+>cf4d+4c+4fgg+4d+4c4<a+g+a+fg4>c4d+4<g.g+.a+g+gg+>cf4d+4c+4g+gg+a+>cc+cc<a+a+g+2d4<g4b+4bab4ga16b16b+bar>d4<g4b+4bab4ga16b16agf+g>d4g4g4f+d<b4gab4>d4cc-c<bg4rl16f+ga4b4>c4d4g8g8gf+g8b+4bbgr8.aaf+8r8aaf+8r4g8g8gf+g8b+4bbgr8.aaf+8r8aaf+8r8<ef+g8g8gf+g8f+4d4e4a8.ag+8a4>ef+g8rgb+4.b8argrf+v12<a>df+v15gv12c-dgv15gv12cegv15adf+ag1.\"}]";

const char* inputs[] = { input1, input2, input3, input4};  // 필요에 따라 더 많은 입력 추가
const uint16_t MAX_SONGS = sizeof(inputs) / sizeof(char*); // 최대 곡 갯수
char temp[1300]; // 불러온 JSON 저장할 변수

// 순환 재생을 위한 변수
int currentSongIndex = 0;

void setup() {
  Serial.begin(115200UL);

  pinMode(BUZZER_PIN, OUTPUT);  // 부저 출력

  lcd.init();       // LCD 초기화
  lcd.backlight();  // LCD 뒤에 불이 들어오는 조절
  lcd.home();       // LCD 커서 위치가 (0, 0)에 위치

  lcd.print("MP3 PLAYER");
  lcd.setCursor(0, 1);
  lcd.print("1STOP2PLAY 3< 4>");
}

void loop() {
  bool sw1_state = digitalRead(SW1_PIN);
  bool sw2_state = digitalRead(SW2_PIN);
  bool sw3_state = digitalRead(SW3_PIN);
  bool sw4_state = digitalRead(SW4_PIN);

  if (sw1_state) {
    lcd.clear();
    if (number < MAX_SONGS) {
      number++;
    } else {
      number = 1;
    }
    Serial.print(F("Parsing JSON for song: "));
    Serial.println(number);
    jsonParsing(inputs[number - 1]);
    // LCD 화면에 제목 출력
    splitAndPrint(number, songs.title, lcd);
    delay(500UL);
  } else if (sw2_state) {
    lcd.clear();
    if (number > 1) {
      number--;
    } else {
      number = MAX_SONGS;
    }
    Serial.print(F("Parsing JSON for song: "));
    Serial.println(number);
    jsonParsing(inputs[number - 1]);
    // LCD 화면에 제목 출력
    splitAndPrint(number, songs.title, lcd);
    delay(500UL);
  }

  if (sw3_state) {
    Serial.print(F("Playing song number: "));
    Serial.println(currentSongIndex + 1);
    if (songs.melody != "") {
      PlayMelody(BUZZER_PIN, songs.melody);
    } else {
      Serial.println("Melody is empty.");
    }
    delay(500UL);
  } else if (sw4_state) {
    Serial.println(F("Stopping song."));
    delay(500UL);
  }
}

void splitAndPrint(int number, char* text, LiquidCrystal_I2C& lcd) {
  // 원본 문자열을 복사하여 처리
  char temp[50];  // 가정: 입력 문자열의 최대 길이는 50
  strncpy(temp, text, sizeof(temp));
  temp[sizeof(temp) - 1] = 0;  // 보안: strncpy가 null 문자를 포함하지 않을 수 있으므로, 마지막 문자를 직접 null로 설정

  // '-'를 구분자로 사용하여 문자열 분할
  char* firstLine = strtok(temp, "-");
  char* secondLine = strtok(NULL, "-");

  // 첫 번째 줄 텍스트 출력: number + 첫 번째 줄
  lcd.setCursor(0, 0);
  lcd.print(number);
  lcd.print(". ");
  lcd.print(firstLine);

  // 두 번째 줄 텍스트 출력
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}

void jsonParsing(char input[]) {
  // JSON
  StaticJsonDocument<200> doc;

  // 이전에 파싱한 결과를 초기화합니다.
  songs.id = 0;
  songs.title[0] = '\0';
  songs.melody[0] = '\0';

  // 입력된 JSON 문자열 출력 (디버깅 용도)
  Serial.print(F("JSON input: "));
  Serial.println(input);

  strcpy(temp, input);
  DeserializationError error = deserializeJson(doc, temp);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  if (!doc.is<JsonObject>()) {
    Serial.println(F("Invalid JSON format: Not an object"));
    return;
  }

  JsonObject obj = doc.as<JsonObject>();

  songs.id = obj["ID"];
  const char* titleStr = obj["TITLE"].as<const char*>();
  const char* melodyStr = obj["MELODY"].as<const char*>();
  strncpy(songs.melody, melodyStr, sizeof(songs.melody));
  strncpy(songs.title, titleStr, sizeof(songs.title));
  songs.melody[sizeof(songs.melody) - 1] = 0;  // Ensure null-terminated
  songs.title[sizeof(songs.title) - 1] = 0;    // Ensure null-terminated

  // 곡 정보 확인을 위한 출력
  Serial.print(F("ID: "));
  Serial.println(songs.id);
  Serial.print(F("Title: "));
  Serial.println(songs.title);
  Serial.print(F("Melody: "));
  Serial.println(songs.melody);
  Serial.println();
}
