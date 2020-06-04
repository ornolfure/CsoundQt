import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item {
    id: ccRect
    height: cc.height + 2

    property int ccNumber: 1

    signal ccValueChanged(int ccNumber, int value);

    RowLayout {
        anchors.fill: parent
        spacing: 5

        Label {id: ccLabel; text: qsTr("CC"); }
        SpinBox {id: cc;
            minimumValue: 1; maximumValue: 119; stepSize: 1;
            value: ccNumber;
            onValueChanged: ccNumber = value;
            Keys.forwardTo: ccRect
        }

        Slider {
            id: valueSlider;
            Layout.fillWidth: true
            minimumValue: 0 ; maximumValue: 127; stepSize: 1;
            value: 0
            onValueChanged: ccValueChanged(cc.value, value)
        }
    }
}

