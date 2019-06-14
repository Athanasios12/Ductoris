import QtQuick 2.0

Rectangle
{
    id: container

    property string text: "Button"
    signal clicked
    color: activePalette.button
    Text
    {
        id: buttonLabel
        anchors.centerIn: container
        color: activePalette.buttonText
        text: container.text
    }
    width: buttonLabel.width + 20; height: buttonLabel.height + 5
    border { width: 1; color: Qt.darker(activePalette.button) }
    antialiasing: true
    radius: 8

    // color the button with a gradient
    gradient: Gradient
    {
        GradientStop
        {
            position: 0.0
            color:
            {
                if (mouseArea.pressed)
                    return activePalette.dark
                else
                    return activePalette.light
            }
        }
        GradientStop { position: 1.0; color: activePalette.button }
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        onClicked: container.clicked();
    }
}
