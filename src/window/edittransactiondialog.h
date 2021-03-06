/*************************************************************************************************
 *                                                                                                *
 *  file: edittransactiondialog.h                                                                 *
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

#ifndef EDIT_TRANSACTION_DIALOG_H
#define EDIT_TRANSACTION_DIALOG_H

#include <QDialog>

#include "delegate/treecomboboxdelegate.h"
#include "delegate/doublespinboxdelegate.h"
#include "types.h"
#include "ui_edittransactiondialog.h"


class EditTransactionDialog : public QDialog, protected Ui::EditTransactionDialog
{
    Q_OBJECT

    public:
        explicit EditTransactionDialog( QWidget* parent = nullptr );
        ~EditTransactionDialog();

        void setAccountsList( const UniMap& accounts );
        void setIncomeCategoriesModel( QAbstractItemModel* model );
        void setOutcomeCategoriesModel( QAbstractItemModel* model );

        void setValues( const UniMap& fieldsData );

    signals:
        void saveData( UniMap fieldsData );

    protected slots:
        void setCurrentDate();
        void changeType();
        void clearPageValues( int page );
        void clearAllValues();

        void createSubitem( const QVariantList& values = QVariantList() );
        void deleteSubitem();

        void recalculateSubitemsAmount( int changedRow, int changedColumn );

    protected:
        void setupSubitemsWidget();

        int getCategoryId( TreeComboBox* comboBox ) const;

        int getCurrentType() const;
        UniMap getCurrentPageValues() const;

        void okClicked();
        bool isRequiredFieldsFilled();

        enum SubitemColumn
        {
            Name,
            CategoryId,
            Amount
        };

        unsigned int transactionId = 0;

        TreeComboBoxDelegate* subitemCategoryDelegare = nullptr;
        DoubleSpinboxDelegate* subitemAmountDelegate = nullptr;
};


#endif // EDIT_TRANSACTION_DIALOG_H
