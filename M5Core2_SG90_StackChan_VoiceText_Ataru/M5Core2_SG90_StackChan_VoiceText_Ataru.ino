#include <Arduino.h>

#include <M5Unified.h>
#if defined(ARDUINO_M5STACK_Core2)
  #define SERVO_PIN_X 13
  #define SERVO_PIN_Y 14
#elif defined( ARDUINO_M5STACK_FIRE )
  #define SERVO_PIN_X 21
  #define SERVO_PIN_Y 22
#elif defined( ARDUINO_M5Stack_Core_ESP32 )
  #define SERVO_PIN_X 21
  #define SERVO_PIN_Y 22
#endif

#include <Avatar.h> // https://github.com/meganetaaan/m5stack-avatar
#include <ServoEasing.hpp> // https://github.com/ArminJo/ServoEasing       
#include "AtaruFace.h"
#include "RamFace.h"

#if defined(ARDUINO_M5STACK_Core2)
//#define USE_VOICE_TEXT //for M5STACK_Core2 Only
#endif

#ifdef USE_VOICE_TEXT
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SLipSync.h"
#include "AudioFileSourceVoiceTextStream.h"

const char *SSID = "YOUR_WIFI_SSID";
const char *PASSWORD = "YOUR_WIFI_PASSWORD";

AudioGeneratorMP3 *mp3;
AudioFileSourceVoiceTextStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2SLipSync *out;
const int preallocateBufferSize = 40*1024;
uint8_t *preallocateBuffer;
#endif

using namespace m5avatar;
Avatar avatar;
Face* faces[3];
ColorPalette* cps[3];

#define START_DEGREE_VALUE_X 90
#define START_DEGREE_VALUE_Y 90

ServoEasing servo_x;
ServoEasing servo_y;

void behavior(void *args)
{
  float gazeX, gazeY;
  DriveContext *ctx = (DriveContext *)args;
  Avatar *avatar = ctx->getAvatar();
   for (;;)
  {
#ifdef USE_VOICE_TEXT
    int level = out->getLevel();
    level = abs(level);
    if(level > 10000)
    {
      level = 10000;
    }
    float open = (float)level/10000.0;
    avatar->setMouthOpenRatio(open);
#endif
 
    vTaskDelay(1/portTICK_PERIOD_MS);
//    delay(50);
  }
}

void servoloop(void *args)
{
  float gazeX, gazeY;
  DriveContext *ctx = (DriveContext *)args;
  for (;;)
  {
    Avatar *avatar = ctx->getAvatar();
    avatar->getGaze(&gazeY, &gazeX);
    servo_x.setEaseTo(START_DEGREE_VALUE_X + (int)(20.0 * gazeX));
    if(gazeY < 0) {
      servo_y.setEaseTo(START_DEGREE_VALUE_Y + (int)(20.0 * gazeY));
    } else {
      servo_y.setEaseTo(START_DEGREE_VALUE_Y + (int)(10.0 * gazeY));
    }
    synchronizeAllServosStartAndWaitForAllServosToStop();
    vTaskDelay(33/portTICK_PERIOD_MS);
  }
}

void setup() {
  
#ifdef USE_VOICE_TEXT
  preallocateBuffer = (uint8_t*)ps_malloc(preallocateBufferSize);
#endif
  auto cfg = M5.config();
  M5.begin(cfg);
  
  auto spk_config = M5.Speaker.config();
  spk_config.sample_rate = 88200;
  spk_config.stereo = false;
  M5.Speaker.config(spk_config);
  //M5.Speaker.begin();

  if (servo_x.attach(SERVO_PIN_X, START_DEGREE_VALUE_X, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE)) {
    Serial.print("Error attaching servo x");
  }
  if (servo_y.attach(SERVO_PIN_Y, START_DEGREE_VALUE_Y, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE)) {
    Serial.print("Error attaching servo y");
  }
  servo_x.setEasingType(EASE_QUADRATIC_IN_OUT);
  servo_y.setEasingType(EASE_QUADRATIC_IN_OUT);
  setSpeedForAllServos(60);

#ifdef USE_VOICE_TEXT
  M5.Lcd.setBrightness(100);
  M5.Lcd.clear();
  M5.Lcd.setTextSize(2);
  delay(1000);

  Serial.println("Connecting to WiFi");
  M5.Lcd.print("Connecting to WiFi");
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
    M5.Lcd.print(".");
  }
  Serial.println("\nConnected");
  M5.Lcd.println("\nConnected");
  M5.Speaker.tone(2000, 500);
  delay(500);
  M5.Speaker.tone(1000, 500);
  delay(1000);
  
  audioLogger = &Serial;
  out = new AudioOutputI2SLipSync(0, 0);
  out->SetPinout(12, 0, 2);           // ピン配列を指定（BCK, LRCK, DATA)BashCopy
  out->SetOutputModeMono(false);
  mp3 = new AudioGeneratorMP3();
#endif

  faces[0] = new AtaruFace();
  faces[1] = new RamFace();
  faces[2] = avatar.getFace();
  cps[0] = new ColorPalette();
  cps[1] = new ColorPalette();
  cps[2] = new ColorPalette();
  cps[0]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[0]->set(COLOR_BACKGROUND, TFT_WHITE);
  cps[0]->set(COLOR_SECONDARY, TFT_WHITE);
  cps[1]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[1]->set(COLOR_BACKGROUND, TFT_WHITE);
  cps[1]->set(COLOR_SECONDARY, TFT_WHITE);
  cps[2]->set(COLOR_PRIMARY, TFT_WHITE);
  cps[2]->set(COLOR_BACKGROUND, TFT_BLACK);
  cps[2]->set(COLOR_SECONDARY, TFT_WHITE);

  avatar.init(8);
  avatar.setFace(faces[0]);
  avatar.setColorPalette(*cps[0]);
  avatar.addTask(behavior, "behavior");
  avatar.addTask(servoloop, "servoloop");
}

#ifdef USE_VOICE_TEXT
//char *text1 = "こんにちは、世界！";
char *text1 = "こんにちは、僕の名前はあたるです。よろしくね！";
char *text2 = "こんにちは、私の名前はラムちゃんです。よろしくね！";
char *text3 = "こんにちは、私の名前はスタックちゃんです。よろしくね！";
char *tts_parms1 ="&emotion_level=2&emotion=happiness&format=mp3&speaker=takeru&volume=200&speed=100&pitch=130";
char *tts_parms2 ="&emotion_level=2&emotion=happiness&format=mp3&speaker=hikari&volume=200&speed=120&pitch=130";
char *tts_parms3 ="&emotion_level=4&emotion=anger&format=mp3&speaker=bear&volume=200&speed=120&pitch=100";

void VoiceText_tts(char *text,char *tts_parms) {
    file = new AudioFileSourceVoiceTextStream( text, tts_parms);
    buff = new AudioFileSourceBuffer(file, preallocateBuffer, preallocateBufferSize);
    delay(100);
    mp3->begin(buff, out);
}
#endif

void loop() {
  M5.update();
#ifdef USE_VOICE_TEXT
  static int lastms = 0;
  if (M5.BtnA.wasPressed())
  {
    M5.Speaker.tone(2000, 500);
    avatar.setFace(faces[0]);
    avatar.setColorPalette(*cps[0]);
    delay(1000);
    avatar.setExpression(Expression::Happy);
    VoiceText_tts(text1, tts_parms1);
    avatar.setExpression(Expression::Neutral);
    Serial.println("mp3 begin");
  }
  if (M5.BtnB.wasPressed())
  {
    M5.Speaker.tone(2000, 500);
    avatar.setFace(faces[1]);
    avatar.setColorPalette(*cps[1]);
    delay(1000);
    avatar.setExpression(Expression::Happy);
    VoiceText_tts(text2, tts_parms2);
    avatar.setExpression(Expression::Neutral);
    Serial.println("mp3 begin");
  }
  if (M5.BtnC.wasPressed())
  {
    M5.Speaker.tone(2000, 500);
    avatar.setFace(faces[2]);
    avatar.setColorPalette(*cps[2]);
    delay(1000);
    avatar.setExpression(Expression::Happy);
    VoiceText_tts(text3, tts_parms3);
    avatar.setExpression(Expression::Neutral);
    Serial.println("mp3 begin");
  }
  if (mp3->isRunning()) {
    if (millis()-lastms > 1000) {
      lastms = millis();
      Serial.printf("Running for %d ms...\n", lastms);
      Serial.flush();
     }
    if (!mp3->loop()) {
      mp3->stop();
      out->setLevel(0);
      delete file;
      delete buff;
      Serial.println("mp3 stop");
    }
  }
#else
  if (M5.BtnA.wasPressed())
  {
    avatar.setFace(faces[0]);
    avatar.setColorPalette(*cps[0]);
  }
  if (M5.BtnB.wasPressed())
  {
    avatar.setFace(faces[1]);
    avatar.setColorPalette(*cps[1]);
  }
  if (M5.BtnC.wasPressed())
  {
    avatar.setFace(faces[2]);
    avatar.setColorPalette(*cps[2]);
  }
#endif
}
