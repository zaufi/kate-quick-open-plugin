/**
 * \file
 *
 * \brief Class \c kate::QuickOpenPluginConfigPage (implementation)
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

// Project specific includes
#include <src/quick_open_plugin_config_page.h>

// Standard includes
#include <KDebug>
#include <KDirSelectDialog>
#include <KTabWidget>

namespace kate {
//BEGIN QuickOpenPluginConfigPage
QuickOpenPluginConfigPage::QuickOpenPluginConfigPage(
    QWidget* parent
  , QuickOpenPlugin* plugin
  )
  : Kate::PluginConfigPage(parent)
  , m_plugin(plugin)
  , m_quick_path_list(new Ui_PathListConfigWidget())
{
    QLayout* layout = new QVBoxLayout(this);
    KTabWidget* tab = new KTabWidget(this);
    layout->addWidget(tab);
    layout->setMargin(0);

    QWidget* paths_tab = new QWidget(tab);
    m_quick_path_list->setupUi(paths_tab);
    m_quick_path_list->addButton->setIcon(KIcon("list-add"));
    m_quick_path_list->delButton->setIcon(KIcon("list-remove"));
    tab->addTab(paths_tab, i18n("Quick Search Paths List"));

    QWidget* pss_tab = new QWidget(tab);
    tab->addTab(pss_tab, i18n("Other Settings"));

    // Connect add/del buttons to actions
    connect(m_quick_path_list->addButton, SIGNAL(clicked()), this, SLOT(addDir()));
    connect(m_quick_path_list->delButton, SIGNAL(clicked()), this, SLOT(delDir()));

    // Populate configuration w/ dirs
    reset();
}

void QuickOpenPluginConfigPage::reset()
{
    kDebug() << "Reseting configuration";
}
void QuickOpenPluginConfigPage::apply()
{
    kDebug() << "Applying configuration";
}
void QuickOpenPluginConfigPage::defaults()
{
    kDebug() << "Default configuration requested";
}

void QuickOpenPluginConfigPage::addDir()
{
    KUrl dir_uri = KDirSelectDialog::selectDirectory(KUrl(), true, this);
    if (dir_uri != KUrl())
    {
        const QString& dir_str = dir_uri.toLocalFile();
        if (!contains(dir_str))
            new QListWidgetItem(dir_str, m_quick_path_list->pathsList);
    }
}

void QuickOpenPluginConfigPage::delDir()
{
    m_quick_path_list->pathsList->removeItemWidget(
        m_quick_path_list->pathsList->currentItem()
      );
}

bool QuickOpenPluginConfigPage::contains(const QString& dir)
{
    for (int i = 0; i < m_quick_path_list->pathsList->count(); ++i)
        if (m_quick_path_list->pathsList->item(i)->text() == dir)
            return true;
    return false;
}

//END QuickOpenPluginConfigPage
}                                                           // namespace kate
