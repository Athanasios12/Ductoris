import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle
{
    id : chracterChoiceWindow
    objectName: "chracterChoiceWindow"
    width: 800
    height: 600
    color : "green"
    signal startGame
    signal exitToTitle

    Component
    {
        id: leaderDelegate
        Item
        {
            width: 200;
            height: 40;
            Column
            {
                Text{text: '<b>Leader:</b> ' + name}
            }
        }
    }
    Rectangle
    {
        id: widgetArea
        width: parent.width - 40
        height:parent.height - 40
        x: 20
        y: 20
        color: parent.color
        Rectangle
        {
            id: leaderList
            color: "purple"
            width: 200
            height: 120
            anchors.top:  parent.top
            anchors.left: parent.left

            ListView
            {
                id:lstLeaderType
                anchors.fill: parent
                flickableDirection: Flickable.AutoFlickDirection

                model: LeaderTypeListModel {}
                delegate: leaderDelegate
                highlight: Rectangle {color: "lightsteelblue"; radius: 5}
                focus: true
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    lstLeaderType.currentIndex = lstLeaderType.indexAt(mouse.x, mouse.y);
                }
            }
        }
        Rectangle
        {
            color: "white"
            anchors.right: parent.right
            anchors.top: parent.top
            width: 300
            height: 200
            TextArea
            {
                anchors.fill: parent
                text : "Leader type and army description";
            }
        }

        Button
        {
            id: btnStartGame
            objectName: "btnStartGame"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 60
            width : 200
            text: "Start Game"
            onClicked:
            {
               _ductorisApi.onChosenLeader(lstLeaderType.currentIndex);
               chracterChoiceWindow.startGame();
            }
        }

        Button
        {
            id: btnExitToTitle
            objectName: "btnExitToTitle"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            height: 60
            width : 200
            text: "Exit"
            onClicked:
            {
               chracterChoiceWindow.exitToTitle();
            }
        }
    }
}
