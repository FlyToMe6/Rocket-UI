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
            source: "rocket.mesh"
            eulerRotation.z: 178.99059
            eulerRotation.y: 174.71434
            eulerRotation.x: 11.93338
            y: -100
            scale: Qt.vector3d(1, 50, 50)
            materials: [
                DefaultMaterial {
                    diffuseColor: Qt.rgba(0.9, 0.9, 0.9, 1.0)
                }
            ]

            NumberAnimation  on eulerRotation.y {
                loops: Animation.Infinite
                duration: 5000
                from: 0
                to: -360
            }
        }
 }

    //! [rocket model]

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
