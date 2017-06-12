/*************************************************************************************************
 *                                                                                                *
 *  file: transactionitemsmodel.h                                                                 *
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

#ifndef TRANSACTION_ITEMS_MODEL_H
#define TRANSACTION_ITEMS_MODEL_H

#include "database/query.h"
#include "types.h"


class TransactionItemsModel
{
    public:
        TransactionItemsModel( QSqlDatabase database );

        bool addRecord( const UniMap& fieldsData, unsigned int* createdId = nullptr );

        bool clearItemsFor( unsigned int transactionId );

        QList<QVariantList> getItemsForEdit( unsigned int transactionId ) const;

    protected:
        QSqlDatabase database;
};


#endif // TRANSACTION_ITEMS_MODEL_H
