
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
        for (i=0;i<=100;i++)
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
        obj['key1'] = "replaced1";
        obj['key2'] = "replaced2";

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
        width: 96; height: 24; anchors.centerIn: parent
        Text { text: "insert" }
        MouseArea {
            anchors.fill: parent
            onClicked: buildModel()
        }
          }
    Component.onCompleted: buildModel();


}


