import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.3

Window
{
    id : mainWindow
    width: 800
    height: 600
    visible: true
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    SystemPalette { id: activePalette }

    StackView
    {
        id:stack
        anchors.fill: parent
        initialItem: titleScrComponent
    }
    Component
    {
        id:titleScrComponent
        DuctorisTitleWindow
        {
            width: mainWindow.width
            height: mainWindow.height
            onBtnNewGameClicked:
            {
                stack.push(charcterScrComponent);
            }
        }
    }
    Component
    {
        id:charcterScrComponent
        ChooseCharacterScreen
        {
            width: mainWindow.width
            height: mainWindow.height
            onStartGame:
            {
                stack.push(battleScrComponent);

            }
            onExitToTitle:
            {
                stack.pop();
            }
        }
    }
    Component
    {
        id:battleScrComponent
        BattleScreen
        {
            width: mainWindow.width
            height: mainWindow.height
            onBattleScreenReady:
            {
                _ductorisApi.onGameStarted();
            }
            onBtnGoBackToTitle:
            {
                stack.pop();
                //signal that the game is in exit
                _ductorisApi.onExitGame();
            }
        }
    }
}
