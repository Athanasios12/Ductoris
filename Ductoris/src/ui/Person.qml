import QtQuick 2.6

//ustaw żeby frame rate sprite'a zalezal od szybkosc speed ktora tez mowi o tym jak szybko sie przemieszcza
//dodaj rotację - atan(dx/dy) - kat obrotu dla nowej pozycji(liczona od srodka sprite'a)
//predkosc rotacji jest stala i bazuje na predkosci przemieszczania jednostki - speed ->anglespeed
//Zrobic z sprite sequence osobny plik qml tak aby mozna było tworzyć ich wiele na mapie, generycznie z parametryzowanych
//
Rectangle
{
    id: person
    x : 0
    y: 0
    color: "#00000000"
    //color : "red"
    rotation:0
    //animation properties
    property int newX: 0
    property int newY: 0
    property int newAngleRotation: 0
    property int rotationSpeed: 5
    property int speed: 5 // 1px/ 5ms
    property int time: 0
    property int gameCanvasWidth: 0
    property int gameCanvasHeight: 0
    //id aliases - to access from different file
    property alias personSpriteSequence: personSpriteSequence
    property alias personAnimation: personAnimation
    //signals
    signal finished
    signal positionChanged(int x, int y, int rotation)

    //funtion that can be connected to from backend c++ class
    function onSetSpeed(speed)
    {
        person.speed = speed;
    }

    function onSetSpriteData(spriteType, sourceImg, frameCount, frameWidth, frameHeight, frameRate)
    {
        var spriteSet = true;
        var sprite = standSprite;
        switch(spriteType)
        {
        case 0:
            sprite = standSprite;
            break;
        case 1:
            sprite = walkSprite
            break;
        default:
            spriteSet = false;
            break;
        //add another sprites for attack, defence and so on
        }
        if(spriteSet)
        {
            sprite.source = sourceImg;
            sprite.frameCount = frameCount;
            sprite.frameWidth = frameWidth;
            sprite.frameHeight = frameHeight;
            sprite.frameRate = frameRate;
        }
    }

    onXChanged:
    {
        positionChanged(person.x, person.y, person.rotation);
    }

    onYChanged:
    {
        positionChanged(person.x, person.y, person.rotation);
    }

    onRotationChanged:
    {
        positionChanged(person.x, person.y, person.rotation);
    }

    //qml slot
    function onUpdateMovementData(newX, newY, time, rotation)
    {
        person.newX = newX;
        person.newY = newY;
        if(person.newX < 0)
        {
            person.newX = 0;
        }
        if(person.newY < 0)
        {
            person.newY = 0;
        }
        if(person.newX + person.width > gameCanvasWidth)
        {
            person.newX = gameCanvasWidth - person.width;
        }
        if(person.newY + person.height > gameCanvasHeight)
        {
            person.newY = gameCanvasHeight - person.height;
        }
        person.time = time;
        person.newAngleRotation = rotation;
        if(person.personAnimation.running)
        {
            person.personAnimation.stop();
        }
        person.personAnimation.start();
    }

    function onUpdateMovementStats(speed, rotationSpeed)
    {
        person.speed = speed;
        person.rotation = rotationSpeed;
    }

    SpriteSequence
    {
        id: personSpriteSequence
        width : person.width
        height : person.height
        anchors.centerIn: person.Center
        interpolate: false
        goalSprite: ""
        Sprite
        {
            id: standSprite
            name: "personStand"
            source: "sprites/Commander_sprite_still.png"
            frameCount: 1
            frameWidth: person.width
            frameHeight: person.height
            frameRate: 10
            to : {"personStand" : 1, "personWalk" : 0}
        }
        Sprite
        {
            id: walkSprite
            name: "personWalk"
            source: "sprites/Commander_sprite.png"
            frameCount: 2
            frameWidth: person.width
            frameHeight: person.height
            frameRate: 4
            to : {"personWalk" : 0,"personStand" : 0.1}
        }
    }
    SequentialAnimation
    {
        id: personAnimation
        RotationAnimation
        {
            target:person; from : person.rotation; to : person.rotation + newAngleRotation; duration: rotationSpeed * Math.abs(newAngleRotation)
        }
        ParallelAnimation
        {
           ScriptAction { script: personSpriteSequence.goalSprite = "personWalk"; }
           NumberAnimation
           {
               target: person; property: "x"; to : person.newX; duration: person.time
           }
           NumberAnimation
           {
               target: person; property: "y"; to : person.newY; duration: person.time
           }
        }
        ScriptAction { script: personSpriteSequence.goalSprite = "personStand"; }
        ScriptAction { script: person.finished(); }
    }

}
