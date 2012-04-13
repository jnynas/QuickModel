
import QtQuick 1.0

Rectangle {
    width: 360
    height: 360

    function randomString() {
        var chars = "abcdefghiklmnopqrstuvwxyz";
        var string_length = 8;
        var randomstring = '';
        for (var i=0; i<string_length; i++) {
            var rnum = Math.floor(Math.random() * chars.length);
            randomstring += chars.substring(rnum,rnum+1);
        }
        return randomstring.toString();
    }
    function buildModel()
    {
        var keys=new Array('name','occupation','salary');

        var i=0;
        quickmdl.setFields(keys);
        for (i=0;i<=10;i++)
        {

            var a = randomString();
            var b = randomString();

            var obj1 = {};
            obj1['name'] = a;
            obj1['occupation'] = b;
            obj1['salary'] = Math.floor(Math.random() * 10000);
            quickmdl.append(obj1)
        }
    }

    function testReplace()
    {
        var obj = {};
        obj['name'] = "replace";
        obj['occupation'] = "occu";
        obj['salary'] = 1000;

        quickmdl.set(0, obj);

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
                Column { Text { text: name } }
                Column { Text { text: occupation } }
                Column { Text { text: salary } }
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
        width: 50; height: 24; anchors.right: parent.right
        Text { text: "replace first" }
        MouseArea {
            anchors.fill: parent
            onClicked: testReplace()
        }
    }



    Rectangle {
        id: button2
        color: "blue"
        width: 50; height: 24; anchors.right: parent.right; anchors.top: button1.bottom;
        Text { text: "clear" }
        MouseArea {
            anchors.fill: parent
            onClicked: quickmdl.clear()
        }
    }

    Rectangle {
        id: button3
        color: "green"
        width: 50; height: 24; anchors.right: parent.right; anchors.top: button2.bottom;
        Text { text: "remove last" }
        MouseArea {
            anchors.fill: parent
            onClicked: quickmdl.remove(quickmdl.count()-1)
        }
    }

    Rectangle {
        id: button4
        color: "purple"
        width: 50; height: 24; anchors.right: parent.right; anchors.top: button3.bottom;
        Text { text: "add 10" }
        MouseArea {
            anchors.fill: parent
            onClicked: buildModel()
        }
    }

    Component.onCompleted: buildModel();


}


