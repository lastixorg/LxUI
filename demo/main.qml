import QtQuick
import LxUI 1.0

Window {

    width: 640
    height: 400
    visible: true
    title: qsTr("DEMO")
    Slider{
         id: slider
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        width: 100
        height: 100
    }

    
    TestComponent {
        id: testComp
        width: 100
        height: 100
        anchors.centerIn: parent
    }

   
}

