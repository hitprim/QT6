import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import TaskModel 1.0


Window {
    width: 250
    height: 200
    visible: true
    title: qsTr("Organizer")

    property int taskCount: taskModel.getCount()



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


        MessageDialog {
            id: _messageDialog
            title: "Error"

            Component.onCompleted: visible = false
        }

        Button{
            text: "Add Task"
            onClicked: {
                var taskName = _TaskName.text;
                var deadline = _deadline.text;
                var progress = _progressSlider.value;



                if(taskName.trim().length === 0){

                    _messageDialog.text = "Empty Field"
                    _messageDialog.visible = true
                    _messageDialog.open()
                    return;

                }

                if(!_deadline.text.match(/^\d{1,2}\.\d{1,2}\.\{4}$/)){

                    _messageDialog.text = "Wrong Date Field"
                    _messageDialog.visible = true
                    _messageDialog.open()
                    return;

                }

                taskModel.addTask(taskName, deadline, progress)

                _TaskName.text = "";
                _deadline.text = "";
                _progressSlider.value = 0;

                taskCount = taskModel.getCount()
            }
        }


        Text{
            text: "Task count: " + taskCount
        }

    }

}
