# QRコードエンコーダー

制作：k22120　牧野遥斗

## 制作経緯
Githubの講習会などを行なった時に、出席確認のためにQRコードを作成する機会が多く、
QRコードを作成するのが大変だったので、プログラムを起動してコピペをしてもらえれば
簡単に表示できるQRコードエンコーダーを作成した。

## GitのレポジトリURL
https://github.com/harutiro/myqrencode

## 使用方法
今回ライブラリを用いて開発しているため、makeファイルを作成しました。
ですのでmakeファイルを用いたコンパイルをよろしくお願いします。

〜コンパイル方法〜
```
rm -f myqrencode && make myqrencode && ./myqrencode
```

〜実行画面〜
```
> QRコード化したい文字を入力してください
https://google.com/

// URLでも文字列でも対応しています

> 6文字(全角のみ)まで中に表示することができます。
こんにちは

// QRコードの中心に文字が表示されます。
// 顔文字やQRコードの説明を書いてみてください。
// 全角にしか対応していないのでご注意ください。
```

## 使用ライブラリについて
今回ProjectNAYUKI様のQRコードエンコードライブラリを用いて開発をおこないました

URL: https://www.nayuki.io/page/qr-code-generator-library#c

## リリースについて
brewを用いて各PCにインストールができるようになっています。
気になった方はインストールをしてみてください。

〜インストール手順〜
```
//インストールするリソースを追加
> brew tap harutiro/myqrencode
//インストール
> brew install myqrencode
//実行
> myqrencode
```

## 作成した資料一覧について
HomeBrewのリリース方法をまとめた記事
https://zenn.dev/articles/bf66acd8fabf63/edit

QRエンコーダーの使い方をまとめた記事
https://qiita.com/harutiro/items/025353cec772a3c47388

