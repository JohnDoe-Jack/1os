# 1os

12ステップで作る組込みOS自作入門(KOZOS)を参考にしながら作成する予定のレポジトリ

## 外部ツール

[書き込みツール](https://cubeatsystems.com/kz_h8write/)

### 書き込み方法

Minicom等でシリアル通信をしている場合は終了させておく。
フラッシュ書き込み時は、4連ディップスイッチを左から順にON,ON,OFF,ONにする

``` bash
sudo make write
```

### シリアルモニタ

ROMから起動するので、4連ディップスイッチを左から順にON,OFF,ON,OFFにする

``` bash
# 初回設定時
# 9600bps, 8bit, non parity, 1 stop bit
# その他の設定は全て無効
minicom -s -o
```
