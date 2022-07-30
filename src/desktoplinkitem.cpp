#include "desktoplinkitem.h"

DesktopLinkItem::DesktopLinkItem()
{
  m_present = false;
  m_toRemove = false;
  m_toAdd = false;
}

const QString &DesktopLinkItem::icon() const
{
  return m_icon;
}

void DesktopLinkItem::setIcon(const QString &newicon)
{
  m_icon = newicon;
}

const QString &DesktopLinkItem::name() const
{
  return m_name;
}

void DesktopLinkItem::setName(const QString &newName)
{
  m_name = newName;
}

const QString &DesktopLinkItem::comment() const
{
  return m_comment;
}

void DesktopLinkItem::setComment(const QString &newComment)
{
  m_comment = newComment;
}

bool DesktopLinkItem::present() const
{
  return m_present;
}

void DesktopLinkItem::setPresent(bool newCurrentlyOn)
{
  m_present = newCurrentlyOn;
}

bool DesktopLinkItem::toRemove() const
{
  return m_toRemove;
}

void DesktopLinkItem::setToRemove(bool newToRemove)
{
  m_toRemove = newToRemove;
}

bool DesktopLinkItem::toAdd() const
{
  return m_toAdd;
}

void DesktopLinkItem::setToAdd(bool newToAdd)
{
  m_toAdd = newToAdd;
}

const QString &DesktopLinkItem::path() const
{
  return m_path;
}

void DesktopLinkItem::setPath(const QString &newPath)
{
  m_path = newPath;
}

const QString &DesktopLinkItem::file() const
{
  return m_file;
}

void DesktopLinkItem::setFile(const QString &newFile)
{
  m_file = newFile;
}

const QString DesktopLinkItem::filepath() const
{
  return m_path + QDir::separator() + m_file;
}
