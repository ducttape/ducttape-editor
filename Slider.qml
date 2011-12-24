// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: slider;
    height: 100; width: 100; color: "#555555"

    property int maximumValue: 100;
    property int minimumValue: 0;
    property real value: 0;
    property real roundedValue: 0;
    onValueChanged: updatePos();
    property int maxXValue: width - handle.width;
    property int handleThick: 20;
    property real stepSize: 1;
    property bool indicatorVisible: false;

    function updatePos() {
        if (maximumValue > minimumValue) {
            var round = Math.round(value/stepSize) * stepSize
            roundedValue = round
            var pos = (round - minimumValue)/(maximumValue - minimumValue) * maxXValue
            handle.x = pos
        } else {
            console.log("maximum value: " + maximumValue + " is not greater than the minimum value: " + minimumValue)
            handle.x =  0
        }
    }

    Rectangle{anchors.left: parent.left; height: parent.height; width: handle.x; color: "gold"}

    Rectangle{
        id: handle;
        height: parent.height
        width: handleThick;

        MouseArea{
            id: handleMouseArea
            anchors.fill: parent;
            drag {target: parent; axis: Drag.XAxis;
                minimumX: 0; maximumX: maxXValue;
            }
            onPositionChanged: value = (maximumValue - minimumValue) * (handle.x / maxXValue)
        }
        border.color: "lightgrey"
        color: handleMouseArea.pressed ? "#444444" : "#333333"
    }
}
