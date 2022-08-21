/*
    SPDX-License-Identifier: GPL-2.0-or-later
    SPDX-FileCopyrightText: 2022 Guillaume Frognier <guillaume.frognier@laposte.net>
*/

#include <QIcon>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QtQml>

#include "about.h"
#include "app.h"
#include "version-applinkdesktop.h"
#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedString>

constexpr auto APPLICATION_ID = "org.kde.AppLinkDesktop";

#include "applinkdesktopconfig.h"

#include "desktoplinkmodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName(QStringLiteral("KDE"));
  //QCoreApplication::setApplicationName(QStringLiteral("AppLinkDesktop"));
  KLocalizedString::setApplicationDomain("applinkdesktop");

  KAboutData aboutData(
    // The program name used internally.
    QStringLiteral("AppLinkDesktop"),
    // A displayable program name string.
    i18nc("@title", "AppLinkDesktop"),
    // The program version string.
    QStringLiteral(APPLINKDESKTOP_VERSION_STRING),
    // Short description of what the app does.
    i18n("Simple application for managing applications' links on the desktop"),
    // The license this code is released under.
    KAboutLicense::GPL,
    // Copyright Statement.
    i18n("(c) 2022")
  );
  aboutData.addAuthor(
    i18nc("@info:credit", "Guillaume Frognier"),
    i18nc("@info:credit", "Author Role"),
    QStringLiteral("guillaume.hello.world@gmail.com"),
    QStringLiteral("https://kde.org/")
  );
  KAboutData::setApplicationData(aboutData);
  QGuiApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("AppLinkDesktop.svg")));

  QQmlApplicationEngine engine;

  auto config = AppLinkDesktopConfig::self();

  qmlRegisterSingletonInstance(APPLICATION_ID, 1, 0, "Config", config);

  AboutType about;
  qmlRegisterSingletonInstance(APPLICATION_ID, 1, 0, "AboutType", &about);

  App application;
  qmlRegisterSingletonInstance(APPLICATION_ID, 1, 0, "App", &application);

  engine.rootContext()->setContextObject(new KLocalizedContext(&engine));

  qmlRegisterUncreatableType<DesktopLinkModel>(
    APPLICATION_ID, 1, 0, "DesktopLinkModel", QStringLiteral("Must be created from C++")
  );
  auto desktopLinkModel = new DesktopLinkModel(qApp);

  engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
  engine.setInitialProperties({{"desktopLinkModel", QVariant::fromValue(desktopLinkModel)}});

  engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

  if (engine.rootObjects().isEmpty())
  {
    return -1;
  }

  return app.exec();
}
