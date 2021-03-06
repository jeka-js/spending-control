/*************************************************************************************************
 *                                                                                                *
 *  file: mainwindow.h                                                                            *
 *                                                                                                *
 *  SpendingControl                                                                               *
 *  Copyright (C) 2017 Eugene Melnik <jeka7js@gmail.com>                                          *
 *                                                                                                *
 *  SpendingControl is free software; you can redistribute it and/or modify it under the terms of *
 *  the GNU General Public License as published by the Free Software Foundation; either version 2 *
 *  of the License, or (at your option) any later version.                                        *
 *                                                                                                *
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;     *
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.     *
 *  See the GNU General Public License for more details.                                          *
 *                                                                                                *
 *  You should have received a copy of the GNU General Public License along with this program.    *
 *  If not, see <http://www.gnu.org/licenses/>.                                                   *
 *                                                                                                *
  *************************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>

#include "ui_mainwindow.h"


class MainWindow : public QMainWindow, protected Ui::MainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow( QWidget* parent = nullptr );

        void setAccountsStatusModel( QAbstractItemModel* model );
        void setLastTransactionsModel( QAbstractItemModel* model );
        void setTotalBalance( const QString& value );
        void resetAccountsStatusData();

    signals:
        void addTransaction();
        void editTransaction( int id );
        void manageAccounts();
        void manageCategories();

        void aboutToClose();

    protected slots:
        void closeEvent( QCloseEvent* event ) override;

    protected:
        void setupMenubar();
        void setupToolbar();
};


#endif // MAINWINDOW_H
