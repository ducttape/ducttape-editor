// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1


Rectangle {
    id: tabBox
    height: 100;
    width: 100;
    property VisualItemModel tabBarModel;
    property int tabWidth: width/tabBarModel.count;
    property int tabIndex: 0;

    signal newTab();

    function tabClicked(index) {
        console.log("tabIndex " + tabIndex + " index " + index)
        tabBar.children[tabIndex].color = "transparent"
        tabIndex = index
        console.log("changed tabIndex to " + tabIndex)
        tabBar.children[tabIndex].color = "#30ffffff"
        newTab()
    }

    Component{
        id:tabBarItem
        Rectangle{
            height: tabBar.height
            width: tabWidth

            property color selected: "#30ffffff"
            property color notsel: "transparent"

            Image{
                source: tabBarModel.children[index].icon
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 4
            }

            Text{
                anchors.centerIn: parent
                color:"white"
                text: tabBarModel.children[index].text
            }

            MouseArea{
                id:itemMouseArea
                anchors.fill: parent
                onClicked: {tabClicked(index); tabBarModel.children[index].buttonClick()}
            }
            border.color: "darkgrey"
            color: notsel
        }
    }
    Component.onCompleted:
    {
        tabClicked(tabIndex)
    }

    Rectangle{
        height: parent.height / 10; width: parent.width; color: "gold"
        anchors.bottom: parent.bottom
    }

    Row{
        anchors.fill: parent
        id: tabBar
        Repeater{
        model: tabBarModel.count
        delegate: tabBarItem
        }
    }
    color: "black"
}
