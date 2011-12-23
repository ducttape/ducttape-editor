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
        }
        Button{
            text: "open"
        }
        Button{
            id:toggleButton
            text: toggle ? "on" : "off"
            type: "toggle"
        }
    }

    VisualItemModel {
        id:smalltabModel
        Button{
            text: "1"
            Rectangle{color:"blue"; anchors.fill: parent
                Text{text: "one"; color: "black"; anchors.centerIn: parent}}
        }
        Button{
            text: "2"
            Rectangle{color:"green"; anchors.fill: parent
                Text{text: "dos"; color: "black"; anchors.centerIn: parent}}
        }
        Button{
            text: "3"
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
            width: parent.width/2
            buttonBarModel: buttonModel
        }
        Buttonbar{
            id:otherButtonbar
            height: parent.height
            width: parent.width/2
            buttonBarModel:otherButtons
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
        width: parent.width;

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
    color: toggleButton.toggle ? "black" : "white"
}
