/**
 * \file
 *
 * \brief Class \c kate::QuickOpenPluginConfigPage (interface)
 *
 * \date Mon Feb 27 01:22:13 MSK 2012 -- Initial design
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

#ifndef __SRC__QUICK_OPEN_PLUGIN_CONFIG_PAGE_H__
#  define __SRC__QUICK_OPEN_PLUGIN_CONFIG_PAGE_H__

// Project specific includes
#  include <src/ui_path_config.h>

// Standard includes
#  include <kate/plugin.h>
#  include <kate/pluginconfigpageinterface.h>

namespace kate {
class QuickOpenPlugin;                                      // forward declaration

/**
 * \brief [Type brief class description here]
 *
 * [More detailed description here]
 *
 */
class QuickOpenPluginConfigPage : public Kate::PluginConfigPage
{
    Q_OBJECT

public:
    /// Default constructor
    QuickOpenPluginConfigPage(QWidget* = 0, QuickOpenPlugin* = 0);
    /// Destructor
    virtual ~QuickOpenPluginConfigPage() {}

    /// \name PluginConfigPage interface implementation
    //@{
    void apply();
    void reset();
    void defaults();
    //@}

private:
    QuickOpenPlugin* const m_plugin;
    Ui_PathListConfigWidget* const m_quick_path_list;
};

}                                                           // namespace kate
#endif                                                      // __SRC__QUICK_OPEN_PLUGIN_CONFIG_PAGE_H__
