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
        anchors { top: parent.top; bottom: parent.bottom }
        signal clicked(int x, int y)
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
            acceptedButtons: Qt.LeftButton
            onClicked:
            {
                personSpriteSequence.newX = mouseArea.mouseX - Math.floor(personSpriteSequence.width / 2);
                personSpriteSequence.newY = mouseArea.mouseY - Math.floor(personSpriteSequence.height / 2);
                //dodać sprawdzenie czy nie wyszedł poza planszę
                if(personSpriteSequence.newX < 0)
                {
                    personSpriteSequence.newX = 0;
                }
                if(personSpriteSequence.newY < 0)
                {
                    personSpriteSequence.newY = 0;
                }
                if(personAnimation.running)
                {
                    personAnimation.stop();
                }
                var timeX = Math.floor(Math.abs(personSpriteSequence.newX - personSpriteSequence.x) * personSpriteSequence.speed);
                var timeY = Math.floor(Math.abs(personSpriteSequence.newY - personSpriteSequence.y) * personSpriteSequence.speed);
                if(timeX > timeY)
                {
                    personSpriteSequence.time = timeX;
                }
                else
                {
                    personSpriteSequence.time = timeY;
                }
                personAnimation.start();
            }
        }
        //ustaw żeby frame rate sprite'a zalezal od szybkosc speed ktora tez mowi o tym jak szybko sie przemieszcza
        //dodaj rotację - atan(dx/dy) - kat obrotu dla nowej pozycji(liczona od srodka sprite'a)
        //predkosc rotacji jest stala i bazuje na predkosci przemieszczania jednostki - speed ->anglespeed
        //Zrobic z sprite sequence osobny plik qml tak aby mozna było tworzyć ich wiele na mapie, generycznie z parametryzowanych
        //
        SpriteSequence
        {
            id: personSpriteSequence
            width : 100
            height : 100
            x : Math.floor((parent.width / 2) - (width / 2))
            y: Math.floor((parent.height / 2) - (height / 2))
            interpolate: false
            goalSprite: ""
            property int newX: 0
            property int newY: 0
            property int speed: 5 // 1px/ 5ms
            property int time: 0
            Sprite
            {
                name: "personStand"
                source: "sprites/Commander_sprite_still.png"
                frameCount: 1
                frameWidth: 100
                frameHeight: 100
                frameRate: 10
                to : {"personStand" : 1, "personWalk" : 0.1}
            }
            Sprite
            {
                name: "personWalk"
                source: "sprites/Commander_sprite.png"
                frameCount: 2
                frameWidth: 100
                frameHeight: 100
                frameRate: 4
                to : {"personStand" : 1}
            }
        }
        SequentialAnimation
        {
            id: personAnimation
            ParallelAnimation
            {
               ScriptAction { script: personSpriteSequence.goalSprite = "personWalk"; }
               NumberAnimation
               {
                   target: personSpriteSequence; property: "x"; to : personSpriteSequence.newX; duration: personSpriteSequence.time
               }
               NumberAnimation
               {
                   target: personSpriteSequence; property: "y"; to : personSpriteSequence.newY; duration: personSpriteSequence.time
               }
            }
            ScriptAction { script: personSpriteSequence.goalSprite = "personStand"; }
        }
    }
}
