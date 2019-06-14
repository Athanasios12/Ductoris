import QtQuick 2.6

Rectangle
{
    id: battleWindowScreen
    objectName: "battleWindowScreen"
    width: 800
    height: 600
    color: "white"
    signal btnGoBackToTitle
    signal battleScreenReady
    Item
    {
        id: gameCanvas
        objectName: "gameCanvas"
        width: parent.width
        height: parent.height - 30
        anchors { top: parent.top;}
        SystemPalette { id: activePalette }
        signal clicked(int x, int y, int mouseBtn)

        Image
        {
            id: background
            anchors.fill: parent
            source: "maps/battlemap.png"
            fillMode: Image.PreserveAspectCrop
        }

        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked:
            {
                gameCanvas.clicked(mouse.x, mouse.y, mouse.button);
                _ductorisApi.onGameCanvasClicked(mouse.x, mouse.y, mouse.button);
            }
        }
        Component.onCompleted:
        {
            _ductorisApi.onGameStarted();
        }
    }

    Rectangle
    {
        id: toolBar
        width: parent.width; height: 30
        color: activePalette.window
        anchors.bottom: parent.bottom

        Button
        {
            objectName: "btnNewGame"
            anchors { left: parent.left; verticalCenter: parent.verticalCenter }
            height: parent.height
            text: "New Game"            
        }
        Button
        {
            objectName: "btnGoToTitle"
            anchors { right: parent.right; }
            height: parent.height
            text: "Exit"
            onClicked:
            {
                battleWindowScreen.btnGoBackToTitle();
            }
        }
    }
    FpsCounter
    {
        id: fpsCounter
        anchors.right: parent.right
        anchors.top: parent.top
    }    
}
