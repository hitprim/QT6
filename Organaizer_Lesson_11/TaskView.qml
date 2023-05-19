import QtQuick 2.15
import QtQuick.Controls 2.5

ApplicationWindow{
    id: _taskWindow
    visible: false
    width: 600
    height: 400
    title: "Tasks"

    TableView{
        width: parent.width
        height: parent.height

        model: parent


    }


}
