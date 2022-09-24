# M5Core2_SG90_StackChan_VoiceText_Ataru
M5Core2_SG90_StackChan_VoiceText_Ataru

@mongonta555 さんが[ｽﾀｯｸﾁｬﾝ M5GoBottom版組み立てキット](https://raspberrypi.mongonta.com/about-products-stackchan-m5gobottom-version/ "Title")の頒布を始められたので、それに対応したｽﾀｯｸﾁｬﾝファームを作ってみました。<br>

![画像ataru](images/ataru.png)<br>

---
### M5GoBottom版ｽﾀｯｸﾁｬﾝ本体を作るのに必要な物、及び作り方 ###
こちらを参照してください。<br>
* [ｽﾀｯｸﾁｬﾝ M5GoBottom版組み立てキット](https://raspberrypi.mongonta.com/about-products-stackchan-m5gobottom-version/ "Title")<br>

### このプログラムをビルドするのに必要な物 ###

※ 2022/9/24の変更でM5Unifiedに対応しました。
最新環境でビルドができない、動作しないといった場合まずはバージョンを下記に合わせてみてください。

* arduino-esp32(v2.0.5で動作確認しました。)
* Arduino IDE (バージョン 1.8.16で動作確認をしました。)<br>
* [M5Unified](https://github.com/m5stack/M5Unified)ライブラリ(バージョン 0.0.7で動作確認をしました。)
* [M5Stack-Avatar](https://github.com/meganetaaan/m5stack-avatar/ "Title")ライブラリ(バージョン 0.8.1で動作確認をしました。)<br>※ v0.8.1だと標準のAvatarFaceホワイトが水色になってしまう不具合がありますが動作に支障はありません。
* [ServoEasing](https://github.com/ArminJo/ServoEasing/ "Title")ライブラリ(バージョン 2.4.0で動作確認をしました。)<br>
* [ESP32Servo](https://github.com/madhephaestus/ESP32Servo/ "Title")ライブラリ(バージョン 0.9.0で動作確認をしました。)<br>
* [ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio/ "Title")ライブラリ(バージョン 1.9.7で動作確認をしました。)<br><br>

---

---

M5Stack Core2の場合、M5Stack-AvatarとHOYA社が提供する[VoiceText Web APIサービス](https://cloud.voicetext.jp/webapi "Title")を使った音声合成(TTS)を使うことができます。


VoiceText TTSは、kghrlaboさんのesp32_text_to_speechを参考にさせていただきました。<br>
オリジナルはこちら。<br>
esp32_text_to_speech <https://github.com/kghrlabo/esp32_text_to_speech><br>

### VoiceTextの有効化 ###
* M5Core2_SG90_StackChan_VoiceText_Ataru.inoの22行目のコメントを外して”USE_VOICE_TEXT”を有効化してください。

### WiFiの設定 ###
* M5Core2_SG90_StackChan_VoiceText_Ataru.inoの31行目付近、SSIDとPASSWORDを設定してください。

### VoiceText Wev API api キーの設定 ###
* AudioFileSourceVoiceTextStream.cppの30行目付近、YOUR_TSS_API_KEYを設定してください。<br>
APIキーは、[ここ](https://cloud.voicetext.jp/webapi/ "Title")の「無料利用登録」から申請すれば、メールで送られて来ます。<br>

---

### 使い方 ###
* VoiceTextを有効にしていない場合：M5Stack Core2のボタンA,B,Cを押すと、それぞれ異なった顔を表示します。　<br>
* VoiceTextを有効にしている場合：M5Stack Core2のボタンA,B,Cを押すと、それぞれ異なった顔と声でしゃべります。　<br>
音声データをダウンロード中は顔にハートマークが表示されます。<br>
TTSのパラメータの詳細はこちらを参照してください。<br>
[VoiceText Web API [API マニュアル](https://cloud.voicetext.jp/webapi/docs/api/ "Title")]
<br><br>

