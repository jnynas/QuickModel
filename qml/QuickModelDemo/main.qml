// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 360
    height: 360
    Component {
        id: dlg
        Item {
            width: parent.width
            height: 100
            Text {
                id: t1
                anchors.left: parent.left
                anchors.top: parent.top

                text: key1
                width: 50
            }
            Text {
                anchors.left: t1.right
                anchors.top: parent.top

                text: key2
            }

            id: name
        }
    }

    ListView {
        id: lv
        model: quickmdl
        delegate: dlg
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
