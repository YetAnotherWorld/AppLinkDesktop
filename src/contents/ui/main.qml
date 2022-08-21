// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2022 Guillaume Frognier <guillaume.frognier@laposte.net>
import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami

import org.kde.AppLinkDesktop 1.0

Kirigami.ApplicationWindow {
  id: root

  required property DesktopLinkModel desktopLinkModel

  width: Kirigami.Units.gridUnit * 26
  height: Kirigami.Units.gridUnit * 36
  minimumWidth: Kirigami.Units.gridUnit * 20
  minimumHeight: Kirigami.Units.gridUnit * 20

  onClosing: App.saveWindowGeometry(root)
  globalDrawer: Kirigami.GlobalDrawer {
    isMenu: !root.isMobile
    actions: [
      Kirigami.Action {
        text: i18n("About AppLinkDesktop")
        icon.name: "help-about"
        onTriggered: pageStack.layers.push('qrc:About.qml')
      },
      Kirigami.Action {
        text: i18n("Quit")
        icon.name: "gtk-quit"
        onTriggered: Qt.quit()
      }
    ]
  }

  pageStack.initialPage: Kirigami.ScrollablePage {
    id: page
    actions.main: Kirigami.Action {
      id: applyAction
      icon.name: "dialog-ok-apply"
      text: i18n("Apply")
      tooltip: i18n("Apply the modification(s)")
      onTriggered: {
        showPassiveNotification(i18n("Applyed"))
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
                icon.name: "gtk-cancel"
                text: i18n("Cancel add")
                display: "TextBesideIcon"
                Controls.ToolTip.visible: hovered
                Controls.ToolTip.delay: 1000
                Controls.ToolTip.text: i18n("Cancel the addition of the application's link on the desktop")
                onClicked: {
                  showPassiveNotification(i18n("Add canceled"))
                  model.toadd = false
                }
              }
              Controls.Button {
                visible: model.toremove
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.columnSpan: 2
                icon.name: "gtk-cancel"
                text: i18n("Cancel remove")
                display: "TextBesideIcon"
                Controls.ToolTip.visible: hovered
                Controls.ToolTip.delay: 1000
                Controls.ToolTip.text: i18n("Cancel the removal of the application's link on the desktop")
                onClicked: {
                  showPassiveNotification(i18n("Remove canceled"))
                  model.toremove = false
                }
              }
              Controls.Button {
                visible: !model.present && !model.toadd && !model.toremove
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.columnSpan: 2
                icon.name: "bqm-add"
                text: i18n("Add desktop link")
                display: "TextBesideIcon"
                Controls.ToolTip.visible: hovered
                Controls.ToolTip.delay: 1000
                Controls.ToolTip.text: i18n("Add a link to the application on the desktop")
                onClicked: {
                  showPassiveNotification(i18n("Desktop link added"))
                  model.toadd = true
                }
              }
              Controls.Button {
                visible: model.present && !model.toadd && !model.toremove
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.columnSpan: 2
                icon.name: "delete"
                text: i18n("Remove desktop link")
                display: "TextBesideIcon"
                Controls.ToolTip.visible: hovered
                Controls.ToolTip.delay: 1000
                Controls.ToolTip.text: i18n("Remove the link to the application on the desktop")
                onClicked: {
                  showPassiveNotification(i18n("Desktop link removed"))
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
