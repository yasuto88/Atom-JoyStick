# Atom-JoyStick

## Overview

Contains case programs of M5Stack Atom-JoyStick.
Example sketches are available in the `examples` directory. The `ConnectionServer` sketch runs a simple HTTP server that exposes joystick values over Wi-Fi.

## 操作用に参考になる主なファイル

- **ライブラリAPI** (`src/AtomJoyStick.*`)
  - ジョイスティックやボタンの値を取得するための関数が AtomJoyStick クラスとして定義されています。初期化 (begin) や各軸／ボタンの読み取り関数がここにあります。
- **ジョイスティックの基本読み取り** (`examples/GetValue/GetValue.ino`)
  - デバイスの初期化から各ジョイスティック軸・バッテリー情報の取得までをシリアルへ出力する最小構成のサンプルです。
- **HTTPサーバーで値を提供** (`examples/ConnectionServer/ConnectionServer.ino`)
  - M5AtomS3 をアクセスポイントとして起動し、/values でジョイスティックのADC値を JSON で返す簡易Webサーバーを実装しています。
- **StampFlyControllerにサーバーを統合** (`examples/StampFlyController/src/main.cpp`)
  - メインコードに AP モードと HTTP サーバーを追加し、/values で操縦値を取得し、/beep でリモートからブザーを鳴らせます。
- **Core2用HTTPサーバーとLED制御** (`examples/Core2WebControl/Core2WebControl.ino`)
  - M5Core2 をアクセスポイントとして起動し、/values でジョイスティック値を返し、/led エンドポイントで内蔵LEDを遠隔制御するサンプルです。
- **Wi‑Fi設定用Webインターフェース** (`examples/StampFlyController/lib/M5AtomS3/examples/Advanced/WIFI/WiFiSetting/WiFiSetting.ino`)
  - アクセスポイントを立ち上げ、ブラウザからSSIDとパスワードを入力して保存・再起動する仕組みを示しています。
- **MQTTによる遠隔通信** (`examples/StampFlyController/lib/M5AtomS3/examples/Advanced/MQTT/MQTT.ino`)
  - Wi‑Fi 接続後に MQTT ブローカーへ接続し、メッセージを Publish/Subscribe する方法を示すサンプルです。

## License

[Atom-JoyStick - MIT](LICENSE)
