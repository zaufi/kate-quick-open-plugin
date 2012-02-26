/**
 * \file
 *
 * \brief Class \c kate::QuickOpenPlugin (interface)
 *
 * \date Mon Feb 27 01:04:26 MSK 2012 -- Initial design
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

#ifndef __SRC__QUICK_OPEN_PLUGIN_H__
#  define __SRC__QUICK_OPEN_PLUGIN_H__

// Project specific includes

// Standard includes
#  include <kate/plugin.h>
#  include <kate/pluginconfigpageinterface.h>
#  include <KTextEditor/Document>
#  include <cassert>

namespace kate {

/**
 * \brief [Type brief class description here]
 *
 * [More detailed description here]
 *
 */
class QuickOpenPlugin : public Kate::Plugin, public Kate::PluginConfigPageInterface
{
    Q_OBJECT
    Q_INTERFACES(Kate::PluginConfigPageInterface)

public:

    /// Default constructor
    QuickOpenPlugin(QObject* = 0, const QList<QVariant>& = QList<QVariant>());
    /// Destructor
    virtual ~QuickOpenPlugin();
    /// Create a new view of this plugin for the given main window
    Kate::PluginView *createView(Kate::MainWindow*);
    /// \name Plugin interface implementation
    //@{
    void readSessionConfig(KConfigBase*, const QString&);
    void writeSessionConfig(KConfigBase*, const QString&);
    //@}
    /// Create a config page w/ given number and parent
    Kate::PluginConfigPage* configPage(uint = 0, QWidget* = 0, const char* = 0);
    /// Get number of configuration pages for this plugin
    uint configPages() const
    {
        return 1;
    }
    /// Get short name of a config page by number
    QString configPageName(uint number = 0) const
    {
        Q_UNUSED(number)
        assert("This plugin have the only configuration page" && number == 0);
        return "Quick Open";
    }
    QString configPageFullName(uint number = 0) const
    {
        Q_UNUSED(number)
        assert("This plugin have the only configuration page" && number == 0);
        return "Quick Open Settings";
    }
    KIcon configPageIcon(uint number = 0) const
    {
        Q_UNUSED(number)
        assert("This plugin have the only configuration page" && number == 0);
        return KIcon("quickopen-file");
    }
};

}                                                           // namespace kate
#endif                                                      // __SRC__QUICK_OPEN_PLUGIN_H__
