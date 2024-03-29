import QtQuick 2.6
import QtQuick.Controls 2.2

Rectangle
{
    id : titleWindow
    width: 800
    height: 600
    color : "blue"
    signal btnNewGameClicked
    signal btnLoadGameClicked
    signal btnExitGameClicked

    Button
    {
        id: btnNewGame
        objectName: "btnNewGame"
        anchors { horizontalCenter: parent.horizontalCenter;}
        y: Math.floor(parent.height / 4)
        height: 60
        width : 200
        text: "New Game"
        onClicked:
        {
           titleWindow.btnNewGameClicked();
        }
    }

    Button
    {
        id: btnLoadGame
        objectName: "btnLoadGame"
        anchors { horizontalCenter: parent.horizontalCenter;}
        y: Math.floor(parent.height / 2)
        height: 60
        width : 200
        text: "Load Game"
        onClicked:
        {
           titleWindow.btnLoadGameClicked();
        }
    }

    Button
    {
        id: btnExitGame
        objectName: "btnExitGame"
        anchors { horizontalCenter: parent.horizontalCenter;}
        y: Math.floor(parent.height * 0.75)
        height: 60
        width : 200
        text: "Exit Game"
        onClicked:
        {
           titleWindow.btnExitGameClicked();
        }
    }
}
