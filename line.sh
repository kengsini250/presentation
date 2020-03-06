#!/bin/bash
photo_file="/home/ubuntu/Documents/face.jpg"
#トークンを記述
token="---"
#解像度の設定
#raspistill -w 1280 -h 1024 -o $photo_file
#メッセージを送信
curl -X POST -H "Authorization: Bearer ${token}"  -F "message = DATA" -F "imageFile=@${photo_file}" https://notify-api.line.me/api/notify
