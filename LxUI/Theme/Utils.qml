pragma Singleton
import LxUI.Theme
import QtQuick

QtObject {
    function getColor(colorKey, shade) {
        if (!shade) {
            return Theme.getColorHelper(colorKey).color;
        } else {
            return Theme.getColorValue(colorKey, shade);
        }
    }

    // Convert RGB values from non-linear sRGB encoding to a linear color space
    function gammaCorrect(c) {
        if (c <= 0.03928) {
            return c / 12.92;
        } else {
            return Math.pow((c + 0.055) / 1.055, 2.4);
        }
    }

    function calculateLuminance(color) {
        // QML color automatically provides r, g, b components between 0 and 1
        let rLinear = gammaCorrect(color.r);
        let gLinear = gammaCorrect(color.g);
        let bLinear = gammaCorrect(color.b);

        // Calculate luminance using the standard coefficients
        // these coefficients represent the human eye's sensitivity to each color
        return 0.2126 * rLinear + 0.7152 * gLinear + 0.0722 * bLinear;
    }

    function isLightColor(color, threshold = 0.179) {
        // Colors with luminance above threshold are considered "light"
        return calculateLuminance(color) > threshold;
    }
}
