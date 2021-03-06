// ColorImageViewer
// 
// Copyright (C) 2021 serverfailure71
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
// 
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "Common/AverageColor.hpp"
#include "Common/Image.hpp"
#include "ImageLoader.hpp"

#include <spdlog/spdlog.h>

#include <QFileInfo>
#include <QRunnable>

namespace ColorImageViewer {

class LoaderTask : public QObject, public QRunnable
{
    Q_OBJECT

private:
    int       mId;
    QFileInfo mPath;

public:
    LoaderTask (const int id, const QFileInfo& path)
        : mId   (id)
        , mPath (path)
    {
    }

    auto run () -> void
    {        
        load(mPath);
    }

private:
    auto load (const QFileInfo& path) -> void
    {
        spdlog::info("<LoaderTask:{}> loading image '{}'...", mId, mPath.fileName().toStdString());

        auto image = ImageLoader::load(path);
        auto avg   = CalculateAverageColor(image->image());
        image->averageColor(avg);

        emit loaded(mId, image);

        spdlog::info("<LoaderTask:{}> image loaded", mId);
    }

signals:
    auto loaded (int taskId, Image* image) -> void;
};

} // namespace ColorImageViewer
