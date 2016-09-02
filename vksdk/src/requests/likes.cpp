/*
  Copyright (C) 2016 Petr Vytovtov
  Contact: Petr Vytovtov <osanwe@protonmail.ch>
  All rights reserved.

  This file is part of Kat.

  Kat is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Kat is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Kat.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "likes.h"

Likes::Likes(QObject *parent) : QObject(parent)
{}

Likes::~Likes()
{}

void Likes::setApi(ApiRequest *api) {
    _api = api;
}

void Likes::addPost(int ownerId, int itemId) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("type", "post");
    query->addQueryItem("owner_id", QString("%1").arg(ownerId));
    query->addQueryItem("item_id", QString("%1").arg(itemId));
    _api->makeApiGetRequest("likes.add", query, ApiRequest::LIKES_ADD);
}

//void Likes::gotResponse(QJsonValue value, ApiRequest::TaskType type) {
//    switch (type) {
//    case ApiRequest::LIKES_ADD:
//        emit addedLike(value.toObject().value("likes").toInt());
//        break;

//    default:
//        break;
//    }
//}

