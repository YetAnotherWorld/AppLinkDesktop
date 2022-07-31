// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 Guillaume Frognier <guillaume.frognier@laposte.net>
import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami

import org.kde.AppLinkDesktop 1.0

Kirigami.ApplicationWindow {
  id: root

  //title: i18nc("@title:window", "Kdesktop")
  required property DesktopLinkModel desktopLinkModel

  width: Kirigami.Units.gridUnit * 26
  height: Kirigami.Units.gridUnit * 36
  minimumWidth: Kirigami.Units.gridUnit * 20
  minimumHeight: Kirigami.Units.gridUnit * 20

  onClosing: App.saveWindowGeometry(root)
  globalDrawer: Kirigami.GlobalDrawer {
    //titleIcon: "desktop"
    isMenu: !root.isMobile
    actions: [
      Kirigami.Action {
        text: i18n("About AppLinkDesktop")
        icon.name: "help-about"
        onTriggered: pageStack.layers.push('qrc:About.qml')
      },
      Kirigami.Action {
        text: i18n("Quit")
        icon.name: "application-exit"
        onTriggered: Qt.quit()
      }
    ]
  }

  //  footer: Controls.ToolBar {
  //    Controls.ToolButton {
  //      anchors{
  //        right: parent.right
  //      }
  //      id: applyButton
  //      icon.name: "dialog-ok-apply"
  //      display: AbstractButton.IconOnly
  //    }
  //  }
  pageStack.initialPage: Kirigami.ScrollablePage {
    id: page
    actions.main: Kirigami.Action {
      id: applyAction
      icon.name: "dialog-ok-apply"
      onTriggered: {
        showPassiveNotification("apply triggered")
        desktopLinkModel.applyChange()
      }
    }

    Kirigami.CardsListView {
      id: list
      model: desktopLinkModel
      delegate: listDelegate
      Component {
        id: listDelegate
        Kirigami.AbstractCard {
          contentItem: Item {
            implicitWidth: delegateLayout.implicitWidth
            implicitHeight: delegateLayout.implicitHeight
            GridLayout {
              id: delegateLayout
              anchors {
                left: parent.left
                right: parent.right
                top: parent.top
              }
              rowSpacing: Kirigami.Units.largeSpacing
              columnSpacing: Kirigami.Units.largeSpacing
              columns: width > Kirigami.Units.gridUnit * 20 ? 4 : 2
              Kirigami.Icon {
                source: model.icon
                //fallback: "emblem-error"
                Layout.fillWidth: true
                Layout.maximumHeight: Kirigami.Units.iconSizes.huge
                Layout.maximumWidth: Kirigami.Units.iconSizes.huge
                Layout.preferredWidth: height
              }
              ColumnLayout {

                Kirigami.Heading {
                  Layout.fillWidth: true
                  wrapMode: Text.WordWrap
                  level: 2
                  text: model.name
                }
                Kirigami.Separator {
                  Layout.fillWidth: true
                }
                Controls.Label {
                  Layout.fillWidth: true
                  wrapMode: Text.WordWrap
                  text: model.comment
                }
              }
              Controls.Button {
                visible: model.toadd
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.columnSpan: 2
                text: "cancel add"
                onClicked: {
                  showPassiveNotification("cancel add clicked")
                  model.toadd = false
                }
              }
              Controls.Button {
                visible: model.toremove
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.columnSpan: 2
                text: "cancel remove"
                onClicked: {
                  showPassiveNotification("cancel remove clicked")
                  model.toremove = false
                }
              }
              Controls.Button {
                visible: !model.present && !model.toadd && !model.toremove
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.columnSpan: 2
                text: "add desktop link"
                onClicked: {
                  showPassiveNotification("add desktop link clicked")
                  model.toadd = true
                }
              }
              Controls.Button {
                visible: model.present && !model.toadd && !model.toremove
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.columnSpan: 2
                text: "remove desktop link"
                onClicked: {
                  showPassiveNotification("remove desktop link clicked")
                  model.toremove = true
                }
              }
            }
          }
        }
      }
    }
  }
}
