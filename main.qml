// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: root
    width: 1000; height: 400
    color: "lightgrey"

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
    }

    VisualItemModel {
        id:smallbuttonModel
        Button{
            text: "1"
        }
        Button{
            text: "2"
        }
        Button{
            text: "3"
        }
    }

    Toolbar{
        id:normalButtonToolbar
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        toolboxes: [buttonModel, otherButtons]
        toolboxNumber: 2
    }

    Toolbar{
        height: 50
        buttonWidth: 50
        anchors.top: normalButtonToolbar.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        toolboxes: [smallbuttonModel]
        toolboxNumber: 1
    }
}
