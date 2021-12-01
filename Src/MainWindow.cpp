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

#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

#include "Loader.hpp"
#include "ImageItem.hpp"

namespace ColorImageViewer {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow (parent)
    , mUI         (new Ui::MainWindow())
    , mImageGrid  (new ImageGrid())
    , mScene      (new QGraphicsScene())
{
    mUI->setupUi(this);

    LoadDirectory("t:/demo");
    mImageGrid->SetScene(mScene);


    setCentralWidget(mImageGrid);
    setFocusPolicy(Qt::StrongFocus);
    setWindowTitle("Color Image Viewer");
}

auto MainWindow::LoadDirectory (QString path) -> bool
{
    auto loader = Loader();

    return loader.LoadDirectory(path, mScene);
}

} //namespace ColorImageViewer
