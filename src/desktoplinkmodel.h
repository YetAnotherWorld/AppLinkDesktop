#ifndef DESKTOPLINKMODEL_H
#define DESKTOPLINKMODEL_H

#include <QAbstractListModel>
#include "desktoplinkitem.h"

class DesktopLinkModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum Roles
  {
    IconRole = Qt::UserRole + 1,
    NameRole,
    CommentRole,
    PresentRole,
    RemoveRole,
    AddRole,
    // //
  };

  explicit DesktopLinkModel(QObject *parent = nullptr);

  QHash<int, QByteArray> roleNames() const override;
  QVariant data(const QModelIndex &index, int role) const override;
  int rowCount(const QModelIndex &parent) const final;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;

  Q_INVOKABLE void applyChange();

  // Q_INVOKABLE void add(const QString &title);
  // Q_INVOKABLE void remove(const int &index);
  // Q_INVOKABLE void clear();

protected:
  bool loadData();

private:
  QList<DesktopLinkItem> m_data;
};

#endif  // DESKTOPLINKMODEL_H
