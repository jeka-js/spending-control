/*************************************************************************************************
 *                                                                                                *
 *  file: transactionitemsmodel.cpp                                                               *
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
#include "transactionitemsmodel.h"


TransactionItemsModel::TransactionItemsModel( QSqlDatabase database )
  : database( database )
{
    //
}


bool TransactionItemsModel::addRecord( const UniMap& fieldsData, unsigned int* createdId )
{
    //this->beginResetModel();

    DatabaseQuery query( this->database );

    query.prepare(
        "INSERT INTO transaction_items "
            "(transaction_id, name, category_id, amount) "
        "VALUES (?, ?, ?, ?)"
    );

    query.bindValue( 0, fieldsData.value( "transaction_id" ) );
    query.bindValue( 1, fieldsData.value( "name" ) );
    query.bindValue( 2, fieldsData.value( "category_id" ) );
    query.bindValue( 3, fieldsData.value( "amount" ) );

    bool ok = query.exec();

    if( !ok )
    {
        AppLogger->error( "TransactionItemsModel::addTransactionItemRecord - Can't save transaction subitem: " + query.lastError().text() );
    }

    if( createdId )
    {
        if( query.lastInsertId().isValid() )
        {
            *createdId = query.lastInsertId().toInt();
        }
        else
        {
            AppLogger->error( "TransactionItemsModel::addTransactionItemRecord - Can't retrieve last inserted record id" );
        }
    }

    //this->endResetModel();
    //this->records.clear();

    return( ok );
}


bool TransactionItemsModel::clearItemsFor( unsigned int transactionId )
{
    //this->beginResetModel();

    DatabaseQuery query( this->database );

    query.prepare(
        "DELETE FROM transaction_items "
        "WHERE transaction_id = ?"
    );

    query.bindValue( 0, transactionId );

    bool ok = query.exec();

    if( !ok )
    {
        AppLogger->error( "TransactionItemsModel::clearItemsFor - Can't clear subitems: " + query.lastError().text() );
    }

    //this->endResetModel();
    //this->records.clear();

    return( ok );
}


QList<QVariantList> TransactionItemsModel::getItemsForEdit( unsigned int transactionId ) const
{
    DatabaseQuery query( this->database );

    query.prepare(
        "SELECT name, category_id, amount "
        "FROM transaction_items "
        "WHERE transaction_id = ?"
    );

    query.bindValue( 0, transactionId );

    bool ok = query.exec();
    QList<QVariantList> result;

    if( !ok )
    {
        AppLogger->error( "TransactionItemsModel::getItemsForEdit - Can't load subitems: " + query.lastError().text() );
        return( result );
    }

    while( query.next() )
    {
        result.append( QVariantList({
           { query.value( 0 ) },
           { query.value( 1 ) },
           { query.value( 2 ) },
       }));
    }

    return( result );
}
