#ifndef DESKTOPLINKITEM_H
#define DESKTOPLINKITEM_H

#include<QString>
#include<QDir>

class DesktopLinkItem
{
public:
  DesktopLinkItem();
  const QString &icon() const;
  void setIcon(const QString &newicon);
  const QString &name() const;
  void setName(const QString &newName);
  const QString &comment() const;
  void setComment(const QString &newComment);
  bool present() const;
  void setPresent(bool newCurrentlyOn);
  bool toRemove() const;
  void setToRemove(bool newToRemove);
  bool toAdd() const;
  void setToAdd(bool newToAdd);

  const QString &path() const;
  void setPath(const QString &newPath);
  const QString &file() const;
  void setFile(const QString &newFile);
  const QString filepath() const;

private:
  QString m_path;
  QString m_file;
  QString m_icon;
  QString m_name;
  QString m_comment;
  bool m_present;
  bool m_toRemove;
  bool m_toAdd;
};

#endif // DESKTOPLINKITEM_H

