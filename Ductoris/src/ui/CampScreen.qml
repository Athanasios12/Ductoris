import QtQuick 2.0

Rectangle
{
    id: armyCampWindow
    objectName: "armyCampWindow"
    width: 800
    height: 600
    signal startBattle
    signal exitToTitle

    Rectangle
    {
        id: widgetArea
        width: parent.width - 40
        height:parent.height - 40
        x: 20
        y: 20
        color: parent.color

        ArmyTent
        {
            id: leaderTent
            objectName: "leaderTent"
            width: 200
            height: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter:  parent.verticalCenter
        }
        Button
        {
            id: btnStartBattle
            objectName: "btnStartBattle"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 60
            width : 200
            text: "Start Battle"
            onClicked:
            {
               armyCampWindow.startBattle();
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
               armyCampWindow.exitToTitle();
            }
        }
    }

}
