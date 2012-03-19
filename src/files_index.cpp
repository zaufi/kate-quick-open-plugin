/**
 * \file
 *
 * \brief Class \c kate::FilesIndex (implementation)
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

// Project specific includes
#include <src/files_index.h>

// Standard includes
#include <KDebug>

namespace kate {

void FilesIndex::rebuildIndex(const QStringList& dirs)
{
    Q_FOREACH(const QString& dir, dirs)
    {
        addDirToIndex(dir);
    }
}

void FilesIndex::addDirToIndex(const QString& dir)
{
    QFileInfo start_dir = dir;
    for (
        QDirIterator it("/usr/include", QDirIterator::Subdirectories | QDirIterator::FollowSymlinks)
      ; it.hasNext()
      ; it.next()
      )
    {
        const QString& d = it.filePath();
        if (!(d == "." || d == ".."))
        {
            files_list_type::const_iterator file = m_files.insert(d);
            /// \todo Split current filename into terms
            // Put filename to index
            m_index[it.fileName()].push_back(file);
        }
    }
    kDebug() << "*** Quickopen index now has " << m_files.size() << " files";
}

QStringList FilesIndex::getCandidates(const QString& text) const
{
    QStringList result;
    for (
        index_type::const_iterator it = m_index.begin()
      , last = m_index.end()
      ; it != last
      ; ++it
      )
    {
        if (it.key().startsWith(text))
        {
            Q_FOREACH(files_list_type::const_iterator fit, it.value())
                result.push_back(*fit);
        }
    }
    return result;
}

}                                                           // namespace kate
