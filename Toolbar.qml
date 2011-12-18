// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id:toolbar
    height: 100;
    property int buttonWidth: 200;
    property int seperatorWidth: 5;
    property list<VisualItemModel> toolboxes;
    // for some reason qml lists don't have a count function, may use javascript later
    property int toolboxNumber: 0;
    property int toolboxIndex: 0;
    property int toolbarWidth: calcWidth()

    function calcWidth()
    {
        var a = 0;
        console.log("a:" + a + " tbc:" + toolboxNumber)
        for(var i=0;i < toolboxNumber;i ++)
        {
        a += toolboxes[i].count * buttonWidth + seperatorWidth;
        }
        console.log("width " + a)
        return a;
    }

    width: toolbarWidth;

    Component{
        id:toolbarItem
        Rectangle{
            height: buttons.height
            width: buttonWidth
            property color clicked: "#30ffffff"
            property color regular: "transparent"

            Image{
                source: toolboxes[toolboxIndex].children[index].icon
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 4
            }

            Text{
                anchors.centerIn: parent
                color:"white"
                text: toolboxes[toolboxIndex].children[index].text
            }

            MouseArea{
                id:itemMouseArea
                anchors.fill: parent
                onClicked: toolboxes[toolboxIndex].children[index].buttonClick()
            }
            border.color: "darkgrey"
            color: itemMouseArea.pressed ? clicked : regular
        }
    }

    Component{
        id: toolboxItem
        Row{
        anchors.fill: parent
        Rectangle{ height: buttons.height; width: seperatorWidth; color: "gold"}

        Repeater{
            model:toolboxes[toolboxIndex].count
            delegate:toolbarItem
        }
        }
    }
    Component.onCompleted: {toolboxIndex ++ }

    Row {
        anchors.fill: parent
        id: buttons

        ListView{
            model: toolboxNumber
            delegate: toolboxItem
        }
    }

    color: "black"
}
