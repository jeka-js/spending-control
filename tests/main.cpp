/*************************************************************************************************
 *                                                                                                *
 *  file: main.cpp                                                                                *
 *                                                                                                *
 *  SpendingControl Tests                                                                         *
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

#include <QtTest>

#include "database/manager_tests.h"


int main( int argc, char** argv )
{
    QObject* tests[] = {
        new DatabaseManagerTests()
    };

    int result = 0;

    for( QObject* test : tests )
    {
        result |= QTest::qExec( test, argc, argv );
    }

    return( result );
}
