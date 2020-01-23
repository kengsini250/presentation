# presentation


ファイルの構成

メインファイル
サーバー & クライアント（serverフォルダ）
携帯アプリ(phoneフォルダ)

テスト用(ラズベリーパイの模擬)
pytestフォルダ
クライアント(clientフォルダ)
OpenCVクライアント(OpenCVClientフォルダ)

Serverフォルダの構成
Mainwindow	Uiの表示
Client		クライアントの接続
Clientthread	マルチスレッド
Server		サーバー
Dataformat	画像データ、マイコンのデータフォーマット

携帯アプリ(phoneフォルダ) の構成
Main.qml	UIとメイン処理
Network		ネットワーク通信
Phonevideo	
Showimage	画像を表示する


pytestフォルダの構成
pythonを使ってマイコンの模擬
クライアント(clientフォルダ) の構成
OpenCVの機能がついていないマイコンの模擬（ドアロック）
OpenCVクライアント(OpenCVClientフォルダ) の構成
OpenCVの機能がついているマイコンの模擬（カメラ）


通信の流れ：
  1.サーバーは新しい接続を待っています。(server)
2.新しいクライアントがあれば、新しいスレッドを作って、データがあれば、サーバーに転送する。(clientthread)
3.TCP通信が始まる。クライアントからもらったデータは他のマイコンまで転送する(server)
  4.マイコンは自分のPIDを送って、サーバーはPIDによって
   マイコンの種類を確認します。(client)
	データフォーマットの例：!1565656　
		!：PIDのデータ
		1：カメラ 2：ドア3：携帯

