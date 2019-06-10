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
    StackView
    {
        id:stack
        anchors.fill: parent
        initialItem: titleScrComponent
    }
    Component
    {
        id:battleScrComponent
        BattleScreen
        {
            width: mainWindow.width
            height: mainWindow.height
            onBtnGoBackToTitle:
            {
                stack.pop();
                //signal that the game is in exit
                _ductorisApi.onExitGame();
            }
        }
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
                stack.push(battleScrComponent);
                _ductorisApi.onGameStarted();
            }
        }
    }
}
