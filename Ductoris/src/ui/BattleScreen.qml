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
        //to c++ c
//        function calculateRotation()
//        {
//            //new position in global coordinates system
//            var X_g = person.newX - person.x;
//            var Y_g = person.newY - person.y;
//            //transform to person coordinate system orientation
//            var Phi = person.rotation;
//            var X_p = Math.floor((X_g * Math.cos((Phi / 180) * Math.PI)) + (Y_g * Math.sin((Phi / 180) * Math.PI)));
//            var Y_p = Math.floor((-X_g * Math.sin((Phi / 180) * Math.PI)) + (Y_g * Math.cos((Phi / 180) * Math.PI)));
//            var alpha = 0;
//            if(X_p >= 0)
//            {
//                alpha = 180 -((Math.atan2(X_p, Y_p) * 180) / Math.PI);
//            }
//            else
//            {
//                alpha = -180 - ((Math.atan2(X_p, Y_p) * 180) / Math.PI);
//            }
//            person.newAngleRotation = Math.floor(alpha);
//        }

//        onClicked:
//        {
//            //move this to c++ backend class for Person
//            console.log("Canvas clicked");
//            if(mouseBtn === Qt.LeftButton)
//            {
//                person.newX = x - Math.floor(person.width / 2);
//                person.newY = y - Math.floor(person.height / 2);

//                //dodać sprawdzenie czy nie wyszedł poza planszę
//                if(person.newX < 0)
//                {
//                    person.newX = 0;
//                }
//                if(person.newY < 0)
//                {
//                    person.newY = 0;
//                }
//                if(person.newX + person.width > gameCanvas.width)
//                {
//                    person.newX = gameCanvas.width - person.width;
//                }
//                if(person.newY + person.height > gameCanvas.height)
//                {
//                    person.newY = gameCanvas.height - person.height;
//                }
//                if(person.personAnimation.running)
//                {
//                    person.personAnimation.stop();
//                }
//                var timeX = Math.floor(Math.abs(person.newX - person.x) * person.speed);
//                var timeY = Math.floor(Math.abs(person.newY - person.y) * person.speed);
//                if(timeX > timeY)
//                {
//                    person.time = timeX;
//                }
//                else
//                {
//                    person.time = timeY;
//                }
//                //rotation calculation
//                calculateRotation();
//                person.personAnimation.start();
//            }
//            else if(mouseBtn === Qt.RightButton)
//            {
//                //attack animation
//                console.log("Attack");
//            }
//        }

        Image
        {
            id: background
            anchors.fill: parent
            source: "maps/battlemap.png"
            fillMode: Image.PreserveAspectCrop
        }

//        Person
//        {
//            id: person
//            width : 100
//            height : 100
//            rotation: 0
//            x : Math.floor((gameCanvas.width / 2) - (person.width / 2))
//            y: Math.floor((gameCanvas.height / 2) - (person.height / 2))
//        }

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
