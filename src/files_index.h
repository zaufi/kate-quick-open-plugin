/**
 * \file
 *
 * \brief Class \c kate::FilesIndex (interface)
 *
 * \date Sun Mar 18 20:33:38 MSK 2012 -- Initial design
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

#ifndef __SRC__FILES_INDEX_H__
#  define __SRC__FILES_INDEX_H__

// Project specific includes

// Standard includes
#include <QtCore/QDirIterator>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QSet>
#include <QtCore/QStringList>

namespace kate {

/**
 * \brief [Type brief class description here]
 *
 * [More detailed description here]
 *
 */
class FilesIndex
{
public:
    /// Default constructor
    FilesIndex() {}

    /// Get candidates by string
    QStringList getCandidates(const QString&) const;

    /// (Re)build index of files using givel directories list
    void rebuildIndex(const QStringList&);

private:
    /// Type to hold collected files
    typedef QSet<QString> files_list_type;
    /// Type to map term into set of iterators to available files
    typedef QMap<QString, QList<files_list_type::const_iterator> > index_type;

    /// Add files from given directory to the index
    void addDirToIndex(const QString&);

    files_list_type m_files;                                ///< List of found files
    index_type m_index;                                     ///< Index
};

}                                                           // namespace kate
#endif                                                      // __SRC__FILES_INDEX_H__
