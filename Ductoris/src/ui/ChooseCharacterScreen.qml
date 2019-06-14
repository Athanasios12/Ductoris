import QtQuick 2.0

Rectangle
{
    id : chracterChoiceWindow
    objectName: "chracterChoiceWindow"
    width: 800
    height: 600
    color : "red"
    signal startGame
    signal exitToTitle

    Button
    {
        id: btnRomanLeader
        objectName: "btnRomanLeader"
        anchors { horizontalCenter: parent.horizontalCenter;}
        y: Math.floor(parent.height / 4)
        height: 60
        width : 200
        text: "Roman Leader"
        onClicked:
        {
           _ductorisApi.onChosenLeader(0);
        }
    }

    Button
    {
        id: btnStartGame
        objectName: "btnStartGame"
        anchors { horizontalCenter: parent.horizontalCenter;}
        y: Math.floor(parent.height / 2)
        height: 60
        width : 200
        text: "Start Game"
        onClicked:
        {
           chracterChoiceWindow.startGame();
        }
    }

    Button
    {
        id: btnExitToTitle
        objectName: "btnExitToTitle"
        anchors { horizontalCenter: parent.horizontalCenter;}
        y: Math.floor(parent.height * 0.75)
        height: 60
        width : 200
        text: "Exit"
        onClicked:
        {
           chracterChoiceWindow.exitToTitle();
        }
    }
}
