import QtQuick 2.6

Rectangle
{
    id: battleWindowScreen
    width: 800
    height: 600
    color: "white"    
    Item
    {
        id: gameCanvas
        objectName: "backgroundArea"
        width: parent.width
        height: parent.height - 30
        anchors { top: parent.top;}
        SystemPalette { id: activePalette }
        signal clicked(int x, int y)
        Image
        {
            id: background
            anchors.fill: parent
            source: "maps/battlemap.png"
            fillMode: Image.PreserveAspectCrop
        }        
        Person
        {
            id: person
            width : 100
            height : 100
            x : Math.floor((gameCanvas.width / 2) - (person.width / 2))
            y: Math.floor((gameCanvas.height / 2) - (person.height / 2))
        }
//        Rectangle
//        {
//            id: person
//            width : 100
//            height : 100
//            x : Math.floor((gameCanvas.width / 2) - (person.width / 2))
//            y: Math.floor((gameCanvas.height / 2) - (person.height / 2))
//            //animation properties
//            property int newX: 0
//            property int newY: 0
//            property int newAngleRotation: 0
//            property int rotationSpeed: 1
//            property int speed: 5 // 1px/ 5ms
//            property int time: 0
//            color: "#00000000"
//            SpriteSequence
//            {
//                id: personSpriteSequence
//                width : person.width
//                height : person.height
//                anchors.centerIn: person.Center
//                interpolate: false
//                goalSprite: ""

//                Sprite
//                {
//                    id: standSprite
//                    name: "personStand"
//                    source: "sprites/Commander_sprite_still.png"
//                    frameCount: 1
//                    frameWidth: person.width
//                    frameHeight: person.height
//                    frameRate: 10
//                    to : {"personStand" : 1, "personWalk" : 0.1}
//                }
//                Sprite
//                {
//                    id: walkSprite
//                    name: "personWalk"
//                    source: "sprites/Commander_sprite.png"
//                    frameCount: 2
//                    frameWidth: person.width
//                    frameHeight: person.height
//                    frameRate: 4
//                    to : {"personStand" : 1}
//                }
//            }
//            SequentialAnimation
//            {
//                id: personAnimation
//                ParallelAnimation
//                {
//                   ScriptAction { script: personSpriteSequence.goalSprite = "personWalk"; }
//                   NumberAnimation
//                   {
//                       target: person; property: "x"; to : person.newX; duration: person.time
//                   }
//                   NumberAnimation
//                   {
//                       target: person; property: "y"; to : person.newY; duration: person.time
//                   }
//                }
//                ScriptAction { script: personSpriteSequence.goalSprite = "personStand"; }
//            }
//        }

        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked:
            {
                if(mouse.button === Qt.LeftButton)
                {
                    person.newX = mouseArea.mouseX - Math.floor(person.width / 2);
                    person.newY = mouseArea.mouseY - Math.floor(person.height / 2);
                    //dodać sprawdzenie czy nie wyszedł poza planszę
                    if(person.newX < 0)
                    {
                        person.newX = 0;
                    }
                    if(person.newY < 0)
                    {
                        person.newY = 0;
                    }
                    if(person.personAnimation.running)
                    {
                        person.personAnimation.stop();
                    }
                    var timeX = Math.floor(Math.abs(person.newX - person.x) * person.speed);
                    var timeY = Math.floor(Math.abs(person.newY - person.y) * person.speed);
                    if(timeX > timeY)
                    {
                        person.time = timeX;
                    }
                    else
                    {
                        person.time = timeY;
                    }
                    person.personAnimation.start();
                }
                else
                {
                    //attack animation
                    console.log("Attack");
                }
            }
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
            onClicked: console.log("This doesn't do anything yet...")
        }
    }
}
