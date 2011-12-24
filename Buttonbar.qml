// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id:buttonBar
    height: 100;
    width: 200 * buttonBarModel.count + seperatorWidth;
    property int seperatorWidth: 5;
    property VisualItemModel buttonBarModel;
    property int buttonWidth: (width-seperatorWidth)/buttonBarModel.count;

    Component{
        id:buttonBarItem
        Rectangle{
            height: buttons.height
            width: buttonWidth

            property color clicked: "#30ffffff"
            property color regular: "transparent"

            Image{
                source: buttonBarModel.children[index].icon
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 4
            }

            Text{
                anchors.centerIn: parent
                color:(buttonBarModel.children[index].enabled) ? "white" : "grey"
                text: buttonBarModel.children[index].text
            }

            MouseArea{
                id:itemMouseArea
                anchors.fill: parent
                onClicked: {
                    buttonBarModel.children[index].buttonClick();
                }
            }

            Rectangle{
                height: seperatorWidth
                anchors { left: parent.left; right: parent.right; bottom: parent.bottom; leftMargin: 2; rightMargin: 2; bottomMargin: 2}
                color: buttonBarModel.children[index].toggle ? "gold" : "#60ffffff"
                visible: (buttonBarModel.children[index].type==="toggle") ? true : false
            }

            border.color: "darkgrey"
            color: {
                if(buttonBarModel.children[index].enabled) {
                    if (itemMouseArea.pressed) {
                        return clicked
                    } else {
                        return regular
                    }
                } else {
                    return clicked
                }
            }
        }
    }



    Row {
        anchors.fill: parent
        id: buttons
        Rectangle{height: parent.height; width: seperatorWidth; color: "gold" }
        Repeater{
            id: buttonBarList
            model: buttonBarModel.count
            delegate: buttonBarItem
        }
    }

    color: "black"
}
