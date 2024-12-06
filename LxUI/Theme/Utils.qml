pragma Singleton
import LxUI.Theme
import QtQuick
QtObject {
    function getColor(colorKey, shade){
        if(!shade){
            return ColorHelperCache.getColorHelper(colorKey).color
        }
        else{
            return Theme.getColorValue(colorKey, shade)
        }
    }
}