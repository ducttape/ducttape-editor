// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    property string text
    property string icon
    property string type
    property int toggle: 0
    anchors.fill: parent

    signal buttonClick()
    onButtonClick: {
        console.log(text + " pressed")
        toggle= toggle ? 0 : 1
    }
}
