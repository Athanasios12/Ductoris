import QtQuick 2.6
import QtQuick.Controls 2.2
Rectangle
{
    id : titleWindow
    width: 800
    height: 600
    color : "blue"
    signal btnNewGameClicked
    SystemPalette { id: activePalette }
    Rectangle
    {
        id: toolBar
        width: parent.width; height: 30
        color: activePalette.window
        anchors.bottom: parent.bottom

        Button
        {
            objectName: "btnStartGame"
            anchors { left: parent.left; verticalCenter: parent.verticalCenter }
            height: parent.height
            text: "New Game"
            onClicked:
            {
               titleWindow.btnNewGameClicked();
            }
        }
    }
}
