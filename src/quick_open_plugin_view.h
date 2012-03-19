/**
 * \file
 *
 * \brief Class \c kate::QuickOpenPluginView (interface)
 *
 * \date Mon Feb 27 01:23:55 MSK 2012 -- Initial design
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

#ifndef __SRC__QUICK_OPEN_PLUGIN_VIEW_H__
#  define __SRC__QUICK_OPEN_PLUGIN_VIEW_H__

// Project specific includes
# include <src/files_index.h>

// Standard includes
#  include <kate/plugin.h>
#  include <ktexteditor/commandinterface.h>
#  include <KTextEditor/View>
#  include <KAction>

namespace kate {
class QuickOpenPlugin;                                      // forward declaration

/**
 * \brief [Type brief class description here]
 *
 * [More detailed description here]
 *
 */
class QuickOpenPluginView
  : public Kate::PluginView
  , public Kate::XMLGUIClient
  , public KTextEditor::Command
{
    Q_OBJECT

public:
    /// Default constructor
    QuickOpenPluginView(Kate::MainWindow*, const KComponentData&, QuickOpenPlugin*);
    /// Destructor
    ~QuickOpenPluginView();

    /// \name PluginView interface implementation
    //@{
    void readSessionConfig(KConfigBase*, const QString&);
    void writeSessionConfig(KConfigBase*, const QString&);
    //@}

    /// \name Command interface implementation
    //@{
    const QStringList& cmds();
    bool exec(KTextEditor::View*, const QString&, QString&);
    bool help(KTextEditor::View*, const QString&, QString&);
    //@}

private Q_SLOTS:
    void quickOpenDialog();
    void quickOpen(const QString&);
    void updateIndex();

private:
    QuickOpenPlugin* m_plugin;
    KAction* m_quick_open;                                  ///< <em>Quick Open</em> action
    FilesIndex m_indexer;
};

}                                                           // namespace kate
#endif                                                      // __SRC__QUICK_OPEN_PLUGIN_VIEW_H__
