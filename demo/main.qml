import QtQuick
import LxUI.Slider 
import LxUI.TestComponent
import LxUI.Theme


Window {

    // FontLoader {
    //     id: loader 
    //     source: "Audiowide-Regular.ttf"
    // }

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

    Rectangle {
        width: 100
        height: 100
        color: Theme.setColor("red",5 )
        Text {
           
            color: Theme.primaryColor
            // font.family: loader.font.family
             font.pointSize: Theme.fontSizes.xs
            
            text: Theme.primaryColor
        }

        MouseArea {
            anchors.fill: parent 
            onClicked : { Theme.setPrimaryColor("yellow")
            console.log(ColorMode.Light)
            }
        }
    }


    // Component.onCompleted:  { 
    //     Theme.setPrimaryColor("green")
    // }
   
}

