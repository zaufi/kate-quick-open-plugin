/**
 * \file
 *
 * \brief Class tester for \c DirectoryScanner
 *
 * \date Sun Mar 18 19:41:19 MSK 2012 -- Initial design
 */
/*
 * KateQuickOpenPlugin is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KateQuickOpenPlugin is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Project specific includes
#include <src/files_index.h>

// Standard includes
// ALERT The following #define must be enabled only in one translation unit
// per unit test binary (which may consists of several such modules)
#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/auto_unit_test.hpp>
// Include the following file if u need to validate some text results
// #include <boost/test/output_test_stream.hpp>
#include <QtCore/QDirIterator>
#include <QtCore/QDebug>
#include <iostream>

// Uncomment if u want to use boost test output streams.
//  Then just output smth to it and valida an output by
//  BOOST_CHECK(out_stream.is_equal("Test text"))
// using boost::test_tools::output_test_stream;

// Your first test function :)
BOOST_AUTO_TEST_CASE(DirectoryScannerTest)
{
    kate::FilesIndex idx;
    QStringList dirs;
    dirs << "/usr/include";
    idx.rebuildIndex(dirs);
    QStringList r = idx.getCandidates("vector");
    Q_FOREACH(const QString& s, r)
    {
        qDebug() << s;
    }
}
