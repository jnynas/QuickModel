
import QtQuick 1.0

Rectangle {
    width: 360
    height: 360

    function testReplace()
    {
        var obj = {};
        obj['key1'] = "replaced1";
        obj['key2'] = "replaced2";

        quickmdl.setItem(0, obj);

    }

    Component
    {
        id: myDelegate

        Item
        {
            id: wrapper
            width: listView.width; height: 30
            clip: true

            Row
            {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 10
                Column { Text { text: key1 } }
                Column { Text { text: key2 } }
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        model: quickmdl
        delegate:  myDelegate
    }

    Rectangle {
        id: button1
        color: "red"
        width: 96; height: 24; anchors.centerIn: parent
        Text { text: "insert" }
        MouseArea {
            anchors.fill: parent
            onClicked: quickmdl.testInsert()
        }

 /*   Rectangle {
        id: button2
        color: "blue"
        width: 96; height: 24; anchors.centerIn: parent
        Text { text: "replace" }
        MouseArea {
            anchors.fill: parent
            onClicked: testReplace()
        }*/
    }
}


