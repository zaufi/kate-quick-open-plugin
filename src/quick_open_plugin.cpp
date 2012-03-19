/**
 * \file
 *
 * \brief Class \c kate::QuickOpenPlugin (implementation)
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

// Project specific includes
#include <src/quick_open_plugin.h>
#include <src/quick_open_plugin_view.h>
#include <src/quick_open_plugin_config_page.h>

// Standard includes
#include <kate/application.h>
#include <KAboutData>
#include <KDebug>
#include <KPluginFactory>
#include <KPluginLoader>

K_PLUGIN_FACTORY(QuickOpenPluginFactory, registerPlugin<kate::QuickOpenPlugin>();)
K_EXPORT_PLUGIN(
    QuickOpenPluginFactory(
        KAboutData(
            "katequickopenplugin"
          , "kate_quickopen_plugin"
          , ki18n("Quick Document Open Plugin")
          , "0.1"
          , ki18n("Easy way to find files to open")
          , KAboutData::License_LGPL_V3
          )
      )
  )

namespace kate {
//BEGIN QuickOpenPlugin
QuickOpenPlugin::QuickOpenPlugin(
    QObject* application
  , const QList<QVariant>&
  )
  : Kate::Plugin(static_cast<Kate::Application*>(application), "kate_quickopen_plugin")
  , m_config_dirty(false)
{
}

QuickOpenPlugin::~QuickOpenPlugin()
{
    kDebug() << "Unloading...";
}

Kate::PluginView* QuickOpenPlugin::createView(Kate::MainWindow* parent)
{
    return new QuickOpenPluginView(parent, QuickOpenPluginFactory::componentData(), this);
}

Kate::PluginConfigPage* QuickOpenPlugin::configPage(uint number, QWidget* parent, const char*)
{
    assert("This plugin have the only configuration page" && number == 0);
    if (number != 0)
        return 0;
    return new QuickOpenPluginConfigPage(parent, this);
}

void QuickOpenPlugin::readSessionConfig(KConfigBase* config, const QString& groupPrefix)
{
    kDebug() << "Reading session config: " << groupPrefix;
    // Read session config
    KConfigGroup scg(config, groupPrefix + ":quick-open");
    QStringList dirs = scg.readPathEntry("ConfiguredDirs", QStringList());
    kDebug() << "Got per session dirs list: " << dirs;
    // Assign configuration
    m_dirs = dirs;
    m_config_dirty = false;
}

void QuickOpenPlugin::writeSessionConfig(KConfigBase* config, const QString& groupPrefix)
{
    if (!m_config_dirty)
        return;
    kDebug() << "Writing session config: " << groupPrefix;
    KConfigGroup scg(config, groupPrefix + ":quick-open");
    scg.writePathEntry("ConfiguredDirs", m_dirs);
    scg.sync();
    m_config_dirty = false;
}
//END QuickOpenPlugin
}                                                           // namespace kate
