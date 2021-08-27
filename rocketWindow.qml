import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick3D 1.15
import Qt.labs.wavefrontmesh 1.1
import QtQuick.Shapes 1.14
import QtQuick3D.Materials 1.14
import QtRemoteObjects 5.15
import QtQuick.Scene3D 2.14

Item {
    visible: true

    View3D {
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "#808080"
            backgroundMode: SceneEnvironment.Color
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }
        PerspectiveCamera {
            position: Qt.vector3d(0, 400, 600)
            eulerRotation.x: -30
            clipFar: 2000
        }
        DirectionalLight {
            id: light1
            color: Qt.rgba(1.0, 0.1, 0.1, 1.0)
            ambientColor: Qt.rgba(0.1, 0.1, 0.1, 1.0)
            position: Qt.vector3d(0, 200, 0)
            rotation: Quaternion.fromEulerAngles(-135, -90, 0)
            shadowMapQuality: Light.ShadowMapQualityHigh
            visible: checkBox1.checked
            castsShadow: checkBoxShadows.checked
            brightness: slider1.sliderValue
            SequentialAnimation on rotation {
                loops: Animation.Infinite
                QuaternionAnimation {
                    to: Quaternion.fromEulerAngles(-45, -90, 0)
                    duration: 2000
                    easing.type: Easing.InOutQuad
                }
                QuaternionAnimation {
                    to: Quaternion.fromEulerAngles(-135, -90, 0)
                    duration: 2000
                    easing.type: Easing.InOutQuad
                }
            }
        }
    //! [rocket model]
        Model {
            id: rocket
            x: 10
            source: "rocket.mesh"
            z: 0
            eulerRotation.z: 180
            eulerRotation.y: -180
            eulerRotation.x: 0
            y: 263.726
            scale: Qt.vector3d(1, 50, 50)
            materials: [
                DefaultMaterial {
                    diffuseColor: Qt.rgba(0.9, 0.9, 0.9, 1.0)
                }
            ]

        }
        //! [rocket model]
        //! [Animation of rocket model]
SequentialAnimation on y{
    running: true
    loops: Animation.Infinite
    NumberAnimation {target: rocket; property: "eulerRotation.x"; to: 45; duration: 1000; easing.type:  "OutQuad"}
    NumberAnimation {target: rocket; property: "eulerRotation.x"; to: 0; duration: 1000; easing.type:  "OutQuad"}
    NumberAnimation {target: rocket; property: "eulerRotation.y"; to: -125; duration: 1000; easing.type:  "OutQuad"}
    NumberAnimation {target: rocket; property: "eulerRotation.y"; to: -180; duration: 1000; easing.type:  "OutQuad"}
}
//! [Animation of rocket model]
        Model {
            id: cube
            source: "#Cube"
            scale.x: 80.18332
            scale.z: 44.18978
            scale.y: 0
            materials: cubeMaterial
            DefaultMaterial {
                id: cubeMaterial
                diffuseColor: "#4aee45"
            }
        }
    }



}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.5;height:480;width:640}
}
##^##*/
