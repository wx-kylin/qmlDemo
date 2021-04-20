import QtQuick 2.1
import QtQuick.Window 2.1

Window {
    id: window

    x:960
    y:540
    width: 320
    height: 240
    color: "#000000"
    title: "Test Window with color " + color
//    flags: Qt.Window | Qt.WindowFullscreenButtonHint
    flags: Qt.BypassWindowManagerHint | Qt.FramelessWindowHint
}
