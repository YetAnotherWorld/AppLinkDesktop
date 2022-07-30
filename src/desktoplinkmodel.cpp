#include "desktoplinkmodel.h"
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QStandardPaths>

DesktopLinkModel::DesktopLinkModel(QObject *parent) : QAbstractListModel(parent)
{
  qDebug() << "DesktopLinkModel::DesktopLinkModel(QObject *parent)" << Qt::endl;
  loadData();
}

QHash<int, QByteArray> DesktopLinkModel::roleNames() const
{
  return {
    {Roles::IconRole, QByteArrayLiteral("icon")},
    {Roles::NameRole, QByteArrayLiteral("name")},
    {Roles::CommentRole, QByteArrayLiteral("comment")},
    {Roles::PresentRole, QByteArrayLiteral("present")},
    {Roles::RemoveRole, QByteArrayLiteral("toremove")},
    {Roles::AddRole, QByteArrayLiteral("toadd")}
    //
  };
}

QVariant DesktopLinkModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() || index.row() < 0 || index.row() >= m_data.count())
  {
    return {};
  }

  auto desktopAppLink = m_data.at(index.row());

  switch (role)
  {
  case Roles::IconRole:
    return desktopAppLink.icon();
  case Roles::NameRole:
    return desktopAppLink.name();
  case Roles::CommentRole:
    return desktopAppLink.comment();
  case Roles::PresentRole:
    return desktopAppLink.present();
  case Roles::RemoveRole:
    return desktopAppLink.toRemove();
  case Roles::AddRole:
    return desktopAppLink.toAdd();
  }

  return {};
}

int DesktopLinkModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return m_data.size();
}

bool DesktopLinkModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (index.row() < 0 || index.row() >= m_data.count())
  {
    return false;
  }

  auto &desktopAppLink = m_data[index.row()];

  switch (role)
  {
  case Roles::RemoveRole:
    desktopAppLink.setToRemove(value.toBool());
    break;
  case Roles::AddRole:
    desktopAppLink.setToAdd(value.toBool());
    break;
  }

  emit dataChanged(index, index, {role});
  return true;
}

void DesktopLinkModel::applyChange()
{
  qDebug() << "DesktopLinkModel::applyChange()" <<Qt::endl;

  const QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
  beginResetModel();
  for (DesktopLinkItem &dli : m_data)
  {
    if (dli.toAdd())
    {
      //Add desktop link
      QFile::copy(dli.filepath(),desktopPath+QDir::separator()+dli.file());
      QFile copyFile(desktopPath+QDir::separator()+dli.file());
      QFileDevice::Permissions initialPermission = copyFile.permissions();
      copyFile.setPermissions(initialPermission | QFile::ExeGroup | QFile::ExeOther | QFile::ExeOther | QFile::ExeUser);
      //Set toadd to false and present to true
      dli.setToAdd(false);
      dli.setPresent(true);
    }
    else if (dli.toRemove())
    {
      //Remove desktop link
      QFile rmFile(desktopPath+QDir::separator()+dli.file());
      rmFile.remove();
      //Set toremove to false and present to false
      dli.setToRemove(false);
      dli.setPresent(false);
    }
  }
  endResetModel();
}

bool DesktopLinkModel::loadData()
{
  beginResetModel();
  m_data.clear();
  const QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
  QDir desktopDir(desktopPath);
  desktopDir.setNameFilters({"*.desktop"});
  const QStringList desktopFiles = desktopDir.entryList();

  const QString appPath = QDir::rootPath() + "/usr/share/applications";
  QDir appDir(appPath);
  appDir.setNameFilters({"*.desktop"});
  const QStringList appFiles = appDir.entryList();

  for (const QString &appFile : appFiles)
  {
    QSettings settings(appPath + QDir::separator() + appFile, QSettings::IniFormat);
    DesktopLinkItem dli;
    settings.beginGroup("Desktop Entry");
    bool skip = false;
    skip |= settings.value("NoDisplay").toBool();
    skip |= settings.value("Hidden").toBool();
    skip |= settings.value("NotShownIn").toBool();
    skip |= settings.value("OnlyShownIn").toBool();
    if (skip)
      continue;
    dli.setPath(appPath);
    dli.setFile(appFile);
    dli.setName(settings.value("Name").toString());
    dli.setIcon(settings.value("Icon").toString());
    dli.setComment(settings.value("Comment").toString());
    settings.endGroup();
    dli.setPresent(desktopFiles.contains(appFile));
    // qDebug() << "appFile: " << appFile << (df.present()? " is on the desktop" : " is not on the desktop") <<
    // Qt::endl;
    m_data.append(dli);
  }

  beginResetModel();
  return true;
}
