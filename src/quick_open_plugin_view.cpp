/**
 * \file
 *
 * \brief Class \c kate::QuickOpenPluginView (implementation)
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

// Project specific includes
#include <src/quick_open_plugin_view.h>

// Standard includes
#include <kate/mainwindow.h>
#include <KActionCollection>
#include <KLocalizedString>                                 /// \todo Where is \c i18n() defiend?

namespace kate {
//BEGIN QuickOpenPluginView
QuickOpenPluginView::QuickOpenPluginView(Kate::MainWindow* mw, const KComponentData& data, QuickOpenPlugin* plugin)
  : Kate::PluginView(mw)
  , Kate::XMLGUIClient(data)
  , m_plugin(plugin)
  , m_quick_open(actionCollection()->addAction("file_quick_open"))
{
    m_quick_open->setIcon(KIcon("quickopen-file"));
    m_quick_open->setText(i18n("Quick Open..."));
    m_quick_open->setShortcut(QKeySequence(Qt::ALT + Qt::Key_O));
    connect(m_quick_open, SIGNAL(triggered(bool)), this, SLOT(quickOpen()));

    mainWindow()->guiFactory()->addClient(this);
}

QuickOpenPluginView::~QuickOpenPluginView() {
    mainWindow()->guiFactory()->removeClient(this);
}

void QuickOpenPluginView::readSessionConfig(KConfigBase*, const QString& groupPrefix)
{
    kDebug() << "Reading session config: " << groupPrefix;
}

void QuickOpenPluginView::writeSessionConfig(KConfigBase*, const QString& groupPrefix)
{
    kDebug() << "Writing session config: " << groupPrefix;
}

void QuickOpenPluginView::quickOpen()
{

}
//END QuickOpenPluginView
}                                                           // namespace kate
