import QtQuick 2.6

Item {
    visible: true
    width: 600
    height: 800

    Item
    {
        id: gameCanvas
        objectName: "backgroundArea"
        width: parent.width
        anchors { top: parent.top; bottom: toolBar.top }
        signal clicked(int x, int y)
        Image
        {
            id: background
            anchors.fill: parent
            source: "background_samegame.jpg"
            fillMode: Image.PreserveAspectCrop
        }

        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
            onClicked: gameCanvas.clicked(mouse.x, mouse.y);
        }
    }

}
