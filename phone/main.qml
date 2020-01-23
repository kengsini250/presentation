import QtQuick 2.12
import QtQuick.Window 2.1
import QtQuick.Controls 2.1

// import Network.module 1.0

Window {
    id: win
    visible: true
    // width: Screen.width
    // height: Screen.height
    width: 400
    height: 660

    //network
    // Network{
        // id:network
    // }

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
            img.source= ""
            img.source="image://pic/"
        }
    }


    Rectangle{
        id:allButton
        width:win.width
        height:Math.round(win.height/3)
        y:img.height
        Item{
            Button{
                id:left
                x:50
                text:"Left"
                width:100
                height: 50
            }
            Button{
                id:right
                x:win.width-width-50
                text:"Right"
                width:100
                height: 50
            }

            Connections{
                target:left
                onClicked:{
                    // network.sendToServer("PL")
                }
            }
            Connections{
                target: right
                onClicked:{
                    // network.sendToServer("PR")
                }
            }
        }
        Item{
            Button{
                id:yes
                x:50
                y:70
                text:"Yes"
                width:100
                height: 50
            }
            Button{
                id:no
                x:win.width-width-50
                y:70
                text:"No"
                width:100
                height: 50
            }
            Connections{
                target:yes
                onClicked:{
                    // network.sendToServer("DY")
                }
            }
            Connections{
                target:no
                onClicked:{
                    // network.sendToServer("DN")
                }
            }
        }
        Item{
            Button{
                id:c
                x:win.width/2-50
                y:180
                text:"Connect"
                width:100
                height: 50
            }
            Connections{
                target: c
                onClicked:{
                    // network.sendIpPort()
                }
            }
        }
    }
}
