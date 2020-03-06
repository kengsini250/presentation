import QtQuick 2.12
import QtQuick.Window 2.1
import QtQuick.Controls 2.1

import Network.module 1.0

Window {
    id: win
    visible: true
    width: Screen.width
    height: Screen.height

    //    network
    Network{
        id:network
    }

    Image{
        id:img
        cache:false
        width:win.width
        height:Math.round(win.height*2/3)
        source: ""
    }
    Connections{
        target: network
        onPic:{
            if(win.width > 960){
                img.width = win.width/2
                img.x = win.width/4
            }else{
                img.width = win.width
                img.x = 0
            }

            img.source= ""
            img.source="image://pic/"
        }
    }


    Rectangle{
        id:allButton
        width:win.width
        height:Math.round(win.height/3)
        y:img.height
        Rectangle{
            width: win.width
            height: 50
            Button{
                id:b_left
                x:50
                text:"Left"
                width:100
                height: 50
            }
            Button{
                id:b_right
                x:win.width-width-50
                text:"Right"
                width:100
                height: 50
            }

            Connections{
                target:b_left
                onClicked:{
                    network.sendToServer("PL")
                }
            }
            Connections{
                target: b_right
                onClicked:{
                    network.sendToServer("PR")
                }
            }
        }
        Rectangle{
            x: 0
            y: 56
            width: win.width
            height: 50
            Button{
                id:yes
                x:50
                text:"Yes"
                width:100
                height: 50
            }
            Button{
                id:no
                x:win.width-width-50
                text:"No"
                width:100
                height: 50
            }
            Connections{
                target:yes
                onClicked:{
                    network.sendToServer("DY")
                }
            }
            Connections{
                target:no
                onClicked:{
                    network.sendToServer("DN")
                }
            }
        }
        Rectangle{
            x: 0
            y: 112
            width: win.width
            height: 30
            Button{
                id:c
                x: win.width/4
                y: 0
                text:"Connect"
                font.pointSize: 12
                width:100
                height: 30
            }

            TextInput {
                id: textInput
                x: c.x+150
                y: 0
                width: 100
                height: 15
                text: qsTr("192.168.2.175")
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }

            Connections{
                target: c
                onClicked:{
                    network.getIP(textInput.text)
                    network.sendIpPort()
                }
            }



        }

        Rectangle {
            x: 0
            y: 148
            width: win.width
            height: 30

            Connections {
                target: c1
            }

            Button {
                id: sos1
                x: 183
                y: 0
                width: 100
                height: 30
                text: qsTr("通報")
                font.pointSize: 12
            }

            Button {
                id: sos2
                x: 289
                y: 0
                width: 100
                height: 30
                text: qsTr("警報")
                font.pointSize: 12
            }

            Button {
                id: sos3
                x: 69
                y: 0
                width: 100
                height: 30
                text: qsTr("通話")
                font.pointSize: 12
            }
        }
    }
}


