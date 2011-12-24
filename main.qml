// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: root
    width: 1000; height: 600

    VisualItemModel {
        id:buttonModel
        Button{
            text: "nothing"
            icon: "images/nothing.png"
            enabled: false
        }
        Button{
            text: "quit"
            icon: "images/quit.png"
            onButtonClick: Qt.quit()
        }
    }

    VisualItemModel {
        id:otherButtons
        Button{
            text: "save"
            enabled: false
        }
        Button{
            text: "open"
        }
        Button{
            id:toggleButton
            text: toggle ? "lights: on" : "lights: off"
            type: "toggle"
        }
    }

    VisualItemModel {
        id:smalltabModel
        Button{
            text: "1"
            Rectangle{color:"blue"; anchors.fill: parent
                Text{text: "one" ; color: "black"; anchors.centerIn: parent}}
        }
        Button{
            text: "2"
            Rectangle{color:"green"; anchors.fill: parent
                Text{text: "dos"; color: "black"; anchors.centerIn: parent}}
        }
        Button{
            icon: "images/nothing.png"
            enabled: false
            Rectangle{color:"red"; anchors.fill: parent
                Text{text:"drei"; color: "black"; anchors.centerIn: parent}}
        }
    }

    Row{
        id: toolbar
        anchors.top: parent.top
        width: parent.width
        height: 50
        Buttonbar{
            id:normalButtonToolbar
            height: parent.height
            width: parent.width/2 - slider.width
            buttonBarModel: buttonModel
        }
        Buttonbar{
            id:otherButtonbar
            height: parent.height
            width: parent.width/2
            buttonBarModel:otherButtons
        }
        Rectangle{
            id: slider
            border.color: "darkgrey"
            color: "black"
            width: 200
            height: parent.height

            Slider{
                id: sliderItem
                width: parent.width; height: parent.height / 4;
                handleThick: 20;
                maximumValue: 1;
                stepSize: .2;
                anchors.bottom: parent.bottom;
            }

            Text{
                text: sliderItem.roundedValue;
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top; anchors.topMargin: 10;
                color: "white"
            }
        }
    }

    Rectangle{
        width: 200
        anchors.left:parent.left
        anchors.top: toolbar.bottom
        anchors.bottom: parent.bottom
        TabBar{
            id: tabBar
            anchors.top: parent.top
            width: parent.width
            height: 50
            tabBarModel: smalltabModel
        }

        Rectangle{
            id: tabView
            anchors.top: tabBar.bottom
            anchors.bottom: parent.bottom
            width: parent.width

            Repeater{
                model:smalltabModel
            }

            function newTab(lastindex, index) {
                smalltabModel.children[lastindex].visible = false;
                smalltabModel.children[index].visible = true;
            }

            Component.onCompleted: {
                for(var i = 0; i < smalltabModel.children.length; i++) {
                    smalltabModel.children[i].visible = false;
                }
                tabBar.newTab.connect(newTab)
                newTab(0, 0)
            }
        }
    }

    color: toggleButton.toggle ? "white" : "black"
}
