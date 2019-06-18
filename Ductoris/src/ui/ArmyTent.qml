import QtQuick 2.0

Rectangle
{
    id: tent
    width : 200
    height: 200
    signal tentClicked
    color: "#00000000"

    function setTentParameters(imgSource, width, height)
    {
        tent.width = width;
        tent.height = height;
        tentImg.source = imgSource;
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            console.log("Tent Clicked");
            tentClicked();
        }
    }

    Image
    {
        id: tentImg
        width : parent.width
        height: parent.height
        anchors.fill: parent
        source: "images/tent.png"
    }
}
