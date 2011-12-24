// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1


Rectangle {
    id: tabBox
    height: 100;
    width: 100;
    property VisualItemModel tabBarModel;
    property int tabWidth: width/tabBarModel.count;
    property int tabIndex: 0;

    signal newTab(int lastindex, int index);

    onNewTab: {
        tabBar.children[tabIndex].color = "transparent"
        tabIndex = index
        tabBar.children[tabIndex].color = "#30ffffff"
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
                color:(tabBarModel.children[index].enabled) ? "white" : "grey"
                text: tabBarModel.children[index].text
            }

            MouseArea{
                id:itemMouseArea
                anchors.fill: parent
                onClicked: {
                    if(tabBarModel.children[index].enabled) {
                        newTab(tabIndex, index);
                    }
                    tabBarModel.children[index].buttonClick()
                }
            }

            Rectangle{
                width: parent.width
                height: 5
                anchors.bottom: parent.bottom
                color: {
                    if(tabBarModel.children[index].enabled) {
                        if (tabIndex===index) {
                            return "transparent"
                        } else {
                            return "gold"
                        }
                    } else {
                        return "grey"
                    }
                }
            }

            border.color: "darkgrey"
            color: notsel
        }
    }
    Component.onCompleted:
    {
        newTab(tabIndex, tabIndex)
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
