import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import TaskModel 1.0


Window {
    width: 250
    height: 200
    visible: true
    title: qsTr("Organizer")

    Column{
        spacing: 10
        anchors.fill: parent

        TextField{
            id: _TaskName
            placeholderText: "Task Name"
        }

        TextField{
            id: _deadline
            placeholderText: "Deadline (d.mm.yyyy)"
        }

        Slider {
            id: _progressSlider
            snapMode: "SnapAlways"
            from: 0
            to: 10
            stepSize: 1

            TextInput {
                id: _valueIndicator
                readOnly: true
                width: 40
                height: 20
                font.pixelSize: 14
                text: _progressSlider.value.toFixed(0)

                anchors {
                    horizontalCenter: _progressSlider.right
                    right: _progressSlider.right
                    margins: 15
                }
            }

            onValueChanged: {
                _valueIndicator.text = value.toFixed(0);
            }
        }

        Button{
            text: "Add Task"
            onClicked: {
                var taskName = _TaskName.text;
                var deadline = _deadline.text;
                var progress = _progressSlider.value;
                taskModel.addTask(taskName, deadline, progress)
                _TaskName.text = "";
                _deadline.text = "";
                _progressSlider.value = 0;
            }
        }
    }

}
