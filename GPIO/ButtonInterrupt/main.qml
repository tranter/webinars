import QtQuick 2.0
import HighwayDivision 1.0

Rectangle
{
    id: trafficLight

    anchors.fill: parent
    color: "black"

    Rectangle {
        id: button
        width: 90; height: 50
        color: ma.pressed ? "blue" : "lightblue"

        Text {
            anchors.centerIn: parent
            text: "Walk"
        }

        MouseArea {
            id: ma
            anchors.fill: parent
            onClicked: lightBackend.walk()
        }
    }

    Item
    {
        height: parent.height
        width: parent.width/5
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: red
            color: "red"
            opacity: 0
            width: parent.width
            height: width
            radius: width /2
            anchors {
                bottom: yellow.top
                bottomMargin: 5
            }
        }

        Rectangle {
            id: yellow
            opacity: 0
            color: "yellow"
            width: parent.width
            height: width
            radius: width /2
            anchors {
                centerIn: parent
            }
        }

        Rectangle {
            id: green
            opacity: 0
            color: "green"
            width: parent.width
            height: width
            radius: width /2
            anchors {
                top: yellow.bottom
                topMargin: 5
            }
        }
    }

    // These states use the single instance of TrafficLight with the
    // enums from the type registered with QML

    states: [
        State {
            name: "go"
            when: lightBackend.lightState == TrafficLight.Go
            PropertyChanges { target: green; opacity: 1 }
        },
        State {
            name: "slow"
            when: lightBackend.lightState == TrafficLight.Slow
            PropertyChanges { target: yellow; opacity: 1 }
        },
        State {
            name: "stop"
            when: lightBackend.lightState == TrafficLight.Stop
            PropertyChanges { target: red; opacity: 1 }
        }
    ]

    transitions:[
        Transition {
            PropertyAnimation{ properties: "opacity"; duration: 250 }
        }
    ]
}

