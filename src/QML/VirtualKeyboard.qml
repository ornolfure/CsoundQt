import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    width: 640
    height: 180
    id: root
    color:  backgroundColor
    property string backgroundColor: "#c0c0c0"

    signal genNote(variant on, variant note, variant channel, variant velocity);
    signal newCCvalue(int channel, int cc, int value)

    property int octave: controls.octave
    property int channel: controls.channel
    property int velocity: controls.velocity


    ColumnLayout {
        id: layout
        anchors.fill: parent
        spacing: 6

        RowLayout {
            Layout.leftMargin: 5
            Layout.rightMargin: 5
            spacing: 5

            Repeater {
                model: 3

                ControlSlider {
                    Layout.fillWidth: true
                    ccNumber: index+1
                    onCcValueChanged: {
                        //console.log("CC:", channel, ccNumber, value)
                        newCCvalue(channel, ccNumber, value )
                    }
                    Keys.forwardTo: keyboard
                }
            }
        }

        Controls {
            id: controls
            Layout.fillWidth: true
            Layout.rightMargin: 5
            Layout.leftMargin: 5
            Keys.forwardTo: keyboard;
        }

        Keyboard {
            Layout.fillWidth: true
            Layout.fillHeight: true
            numOctaves: controls.numOctaves
            id: keyboard
            onGenNote: {
                root.genNote(on, note + (12*root.octave), root.channel, root.velocity)
            }
        }
    }

}
