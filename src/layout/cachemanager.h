/*
 *  OpenBangla Keyboard
 *  Copyright (C) 2016 Muhammad Mominul Huque <mominul2082@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CACHE_MANAGER_H
#define CACHE_MANAGER_H

#include <QString>
#include <QJsonObject>
#include <QMap>
#include <QVector>

class CacheManager {
  QMap<QString, QVector<QString>> tempCache;
  QJsonObject candidateSel;
  QMap<QString, QVector<QString>> base;
public:
  CacheManager();

  void setTempCache(QString key, QVector<QString> suggestions);
  QVector<QString> getTempCache(QString key);

/* TODO: Add Suffix implementation
  void removeAllBase() {
    base.clear();
  }

  QVector<QString> baseForKey(QString key) {
    return base[key];
  }

  void setBase(QVector<QString> aBase, QString aKey) {
    base[aKey] = aBase;
  }*/

  void loadCandidateSelection();
  QString getCandidateSelection(QString word);
  void writeCandidateSelection(QString word, QString sel);
  void removeCandidateSelection(QString word);
  void saveCandidateSelection();
};

#endif /* end of include guard: CACHE_MANAGER_H */
