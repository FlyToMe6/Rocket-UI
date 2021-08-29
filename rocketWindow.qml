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
            x: 178.338
            y: 61.388
            color: Qt.rgba(1.0, 1, 1, 1.0)
            z: -36.7472
            brightness: 152
            eulerRotation.z: -1.68426
            eulerRotation.y: 68.13226
            eulerRotation.x: -47.10913
            ambientColor: Qt.rgba(0.1, 0.1, 0.1, 1.0)
            position: Qt.vector3d(0, 200, 0)
            rotation: Quaternion.fromEulerAngles(-135, -90, 0)
            shadowMapQuality: Light.ShadowMapQualityHigh
            visible: checkBox1.checked
            castsShadow: checkBoxShadows.checked

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
                    diffuseColor: "#433434"
                }
            ]

        }
        //! [rocket model]
        //! [Animation of rocket model]
SequentialAnimation on y{
    running: true
    loops: Animation.Infinite

    //launch animation
    NumberAnimation {target: rocket; property: "eulerRotation.x"; to: -4; duration: 1000; easing.type:  "OutQuad"}
    NumberAnimation {target: rocket; property: "z"; to: -2000; duration: 5000; easing.type:  "OutQuad"}

    //back to state
    NumberAnimation {target: rocket; property: "eulerRotation.x"; to: 10; duration: 100; easing.type:  "OutQuad"}
    NumberAnimation {target: rocket; property: "z"; to: 0; duration: 100; easing.type:  "OutQuad"}

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
                diffuseColor: "#235f20"
            }
        }
        Model {
            id: cube1
            x: -407.978
            y: 61.254
            source: "#Cube"
            scale.z: 1.51799
            scale.y: 1.74149
            scale.x: 2.33228
            z: -161.25679
            materials: [cubeMaterial1,cubeMaterial]
            DefaultMaterial {
                id: cubeMaterial1
                diffuseColor: "#daa73f"
                specularTint: "#d43838"
            }
        }

        Model {
            id: cone
            x: -406.923
            y: 144.113
            source: "#Cone"
            eulerRotation.z: -0
            eulerRotation.y: 0
            eulerRotation.x: -0.38666
            scale.z: 2.4734
            scale.y: 0.83447
            scale.x: 3.50125
            z: -167.60451
            materials: coneMaterial
            DefaultMaterial {
                id: coneMaterial
                diffuseColor: "#daa73f"
            }
        }

    }
    Text {
        id: text1
        color: "#ffffff"
        text: qsTr("Rocket launch animation")
        anchors.fill: parent
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
        lineHeightMode: Text.ProportionalHeight
        topPadding: 20
        minimumPointSize: 30
        minimumPixelSize: 30
    }




}
/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.66;height:540;width:720}
}
##^##*/
