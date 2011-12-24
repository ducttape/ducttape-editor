// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    property string text
    property string icon
    property string type
    property bool enabled: true
    property bool toggle: false
    anchors.fill: parent

    signal buttonClick()
    onButtonClick: {
        console.log(text + " pressed")
        toggle= toggle ? false : true
    }
}
