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
#include <src/quick_open_plugin.h>

// Standard includes
#include <kate/application.h>
#include <ktexteditor/editor.h>
#include <kate/mainwindow.h>
#include <KActionCollection>
#include <KLocalizedString>                                 /// \todo Where is \c i18n() defiend?
#include <cassert>

namespace kate {
//BEGIN QuickOpenPluginView
QuickOpenPluginView::QuickOpenPluginView(Kate::MainWindow* mw, const KComponentData& data, QuickOpenPlugin* plugin)
  : Kate::PluginView(mw)
  , Kate::XMLGUIClient(data)
  , m_plugin(plugin)
  , m_quick_open(actionCollection()->addAction("file_quick_open"))
{
#if 0
    m_quick_open->setIcon(KIcon("quickopen-file"));
    m_quick_open->setText(i18n("Quick Open..."));
    m_quick_open->setShortcut(QKeySequence(Qt::ALT + Qt::Key_O));
    connect(m_quick_open, SIGNAL(triggered(bool)), this, SLOT(quickOpenDialog()));
#endif

    // Subscribe to configuration changes
    connect(
        m_plugin
      , SIGNAL(sessionDirsChanged(const QStringList&))
      , this
      , SLOT(updateIndex())
      );

    mainWindow()->guiFactory()->addClient(this);

    KTextEditor::CommandInterface* cmdIface =
        qobject_cast<KTextEditor::CommandInterface*>(Kate::application()->editor());

    if (cmdIface) cmdIface->registerCommand(this);

    updateIndex();
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

void QuickOpenPluginView::quickOpenDialog()
{

}

void QuickOpenPluginView::quickOpen(const QString&)
{

}

const QStringList& QuickOpenPluginView::cmds()
{
    static QStringList commands;

    if (commands.empty())
    {
        commands << "qo";
    }

    return commands;
}

bool QuickOpenPluginView::exec(KTextEditor::View*, const QString& cmd, QString& msg)
{
    Q_UNUSED(cmd);
    kDebug() << "Execute quick open command: " << cmd;
    assert("Sanity check" && cmd.startsWith("qo "));
    QString file = cmd.section(' ', 1);

    bool file_really_exists = false;
    if (file[0] != '/')                                     // does it looks like absolute path?
    {
        // No, lets guess what to open...
        // 0) try to merge `file' w/ configured dirs first
        QStringList candidates;
        Q_FOREACH(const QString& dir, m_plugin->sessionDirs())
        {
            const QString candidate = dir + '/' + file;
            kDebug() << "Trying " << candidate;
            QFileInfo fi(candidate);
            if (fi.isReadable())
            {
                candidates.push_back(fi.filePath());
                kDebug() << "Found candidate: " << fi.filePath();
                file_really_exists = true;
            }
        }
        // Did we found smth?
        if (candidates.size() == 1)
        {
            file = candidates[0];
        }
        else if (candidates.size() > 1)
        {
            msg = i18n("Multiple files matched...");
            return false;
        }
        else
        {
            file_really_exists = false;
            assert("No candidates!" && candidates.isEmpty());
            // 1) try to use index to find smth...
            candidates = m_indexer.getCandidates(file);
            kDebug() << "Index lookup return " << candidates.size() << " candidate(s)";
            // Did we found smth?
            if (candidates.size() == 1)
            {
                file = candidates[0];
            }
            else if (candidates.size() > 1)
            {
                msg = i18n("Multiple files matched...");
                return false;
            }
            else
            {
                // dunno where to search it...
                msg = i18n("file not found: ") + file;
                return false;
            }
        }
    }

    // Ok, we;ve got a filename in a `file' variable...
    // Lets try to open it!
    bool result = true;
    QFileInfo fi(file);
    if (file_really_exists || fi.isReadable())
    {
        mainWindow()->openUrl(file);
        msg = i18n("open file: ") + file;
    }
    else
    {
        msg = i18n("file doesn't exists or unreadable: ") + file;
        result = false;
    }
    return result;
}

bool QuickOpenPluginView::help(KTextEditor::View*, const QString& cmd, QString& msg)
{
    Q_UNUSED(cmd);
    assert("Sanity check" && cmd == "qo");
    msg = i18n(
        "<p><b>qo &mdash; quick open file</b></p>"
        "<p>usage: <tt><b>qo filename</b></tt></p>"
      );

    return true;
}

void QuickOpenPluginView::updateIndex()
{
    m_indexer.rebuildIndex(m_plugin->sessionDirs());
}

//END QuickOpenPluginView
}                                                           // namespace kate
