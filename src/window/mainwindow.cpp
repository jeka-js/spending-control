/*************************************************************************************************
 *                                                                                                *
 *  file: mainwindow.cpp                                                                          *
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

#include "defines.h"
#include "mainwindow.h"
#include "version.h"


MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
{
    this->setupUi( this );
    this->setAttribute( Qt::WA_QuitOnClose );

    this->setupMenubar();
    this->setupToolbar();

    #ifdef QT_DEBUG
        this->setWindowTitle( " -= DEVELOPMENT BUILD =- version " + Application::appVersionFull );
    #endif

    this->connect( this->tvTransactions, &QTableView::doubleClicked, this, [this] ( const QModelIndex& index ) {
        int id = this->tvTransactions->model()->index( index.row(), 0 , index.parent() ).data().toInt();
        emit this->editTransaction( id );
    } );
}


void MainWindow::setAccountsStatusModel( QAbstractItemModel* model )
{
    QAbstractItemModel* currentModel = this->tvAccountsStatus->model();

    if( currentModel != nullptr )
    {
        delete currentModel;
    }

    this->tvAccountsStatus->setModel( model );
}


void MainWindow::setLastTransactionsModel( QAbstractItemModel* model )
{
    QAbstractItemModel* currentModel = this->tvTransactions->model();

    if( currentModel != nullptr )
    {
        delete currentModel;
    }

    this->tvTransactions->setModel( model );

    this->tvTransactions->horizontalHeader()->setSectionHidden( 0, true ); // id
    this->tvTransactions->horizontalHeader()->resizeSection( 1, 70 ); // amount
}


void MainWindow::setTotalBalance( const QString& value )
{
    this->lCurrentlyAvailable->setText( value );
}


void MainWindow::resetAccountsStatusData()
{
    this->tvAccountsStatus->reset();
}


void MainWindow::closeEvent( QCloseEvent* event )
{
    emit this->aboutToClose();
    event->accept();
}


void MainWindow::setupMenubar()
{
    this->connect( this->action_FileExit, SIGNAL(triggered()), this, SLOT(close()) );
}


void MainWindow::setupToolbar()
{
    this->toolbarMain->addAction( tr( "Add transaction" ), this, SIGNAL(addTransaction()) );
    this->toolbarMain->addAction( tr( "Manage accounts" ), this, SIGNAL(manageAccounts()) );
    this->toolbarMain->addAction( tr( "Manage categories" ), this, SIGNAL(manageCategories()) );

    this->toolbarMain->addAction( tr( "Exit" ), this, SLOT(close()) );
}
