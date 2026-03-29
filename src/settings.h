#pragma once

#include <QKeySequence>
#include <QString>
#include "medo/config.h"
#include "storage/deletionstyle.h"
#include "storage/filetype.h"

class Settings {

    public:

        static bool alwaysOnTop();
        static void setAlwaysOnTop(bool newAlwaysOnTop);
        static bool defaultAlwaysOnTop() { return false; }

        static int clearUndoInterval();
        static void setClearUndoInterval(int newClearUndoInterval);
        static int defaultClearUndoInterval() { return 15 * 60; } //15 minutes

        static bool colorTrayIcon();
        static void setColorTrayIcon(bool newColorTrayIcon);
        static bool defaultColorTrayIcon() {
            return false; // auto detect
        }

        static QString dataPath();
        static void setDataPath(QString newPath);
        static QString defaultDataPath() { return defaultDataPaths()[0]; }
        static QStringList dataPaths();
        static void setDataPaths(QStringList newPaths);
        static QStringList defaultDataPaths() { return QStringList(Config::dataDirectory()); }

        static FileType defaultFileType();
        static void setDefaultFileType(FileType newDefaultFileType);
        static FileType defaultDefaultFileType() { return FileType::Plain; }

        static DeletionStyle deletionSyle();
        static void setDeletionStyle(DeletionStyle newDeletionStyle);
        static DeletionStyle defaultDeletionStyle() { return DeletionStyle::Delete; }

        static bool followUrlWithCtrl();
        static void setFollowUrlWithCtrl(bool newFollowUrlWithCtrl);
        static bool defaultFollowUrlWithCtrl() { return true; }

        static bool followUrlWithDoubleClick();
        static void setFollowUrlWithDoubleClick(bool newFollowUrlWithDoubleClick);
        static bool defaultFollowUrlWithDoubleClick() { return false; }

        static QFont font();
        static void setFont(QFont newFont);

        static QString fontName();
        static void setFontName(QString newFontName);
        static QString defaultFontName() {
#if defined(Q_OS_WIN)
            return "Calibri";
#else
            return "DejaVu Sans";
#endif
        }

        static int fontSize();
        static void setFontSize(int newFontSize);
        static int defaultFontSize() { return 11; }

        static bool forceDarkMode();
        static bool showToolbar();
        static bool showCloseButtonOnTabs();
        static void setForceDarkMode(bool newForceDarkMode);
        static void setShowToolbar(bool newShowToolbar);
        static void setShowCloseButtonOnTabs(bool newShowCloseButtonOnTabs);
        static bool defaultForceDarkMode() { return false; }
        static bool defaultShowToolbar() { return true; }
        static bool defaultShowCloseButtonOnTabs() { return true; }

        static bool forcePlainCopyPaste();
        static void setForcePlainCopyPaste(bool newForcePlainCopyPaste);
        static bool defaultForcePlainCopyPaste() { return true; }

        static QKeySequence hotkey();
        static void setHotkey(QKeySequence newHotkey);
        static QKeySequence defaultHotkey() {
            QKeySequence defaultHotkey { "" };
            return  defaultHotkey;
        }

        static bool hotkeyTogglesVisibility();
        static void setHotkeyTogglesVisibility(bool newHotkeyTogglesVisibility);
        static bool defaultHotkeyTogglesVisibility() { return true; }

        static bool hotkeyForceDConf();
        static void setHotkeyForceDConf(bool newHotkeyForceDConf);
        static bool defaultHotkeyForceDConf();

        static bool hotkeyForceXcb();
        static void setHotkeyForceXcb(bool newHotkeyForceXcb);
        static bool defaultHotkeyForceXcb();

        static bool minimizeToTray();
        static void setMinimizeToTray(bool newMinimizeToTray);
        static bool defaultMinimizeToTray() { return true; }

        static int quickSaveInterval();
        static void setQuickSaveInterval(int newQuickSaveInterval);
        static int defaultQuickSaveInterval() { return 2500; }

        static bool showInTaskbar();
        static void setShowInTaskbar(bool newShowInTaskbar);
        static bool defaultShowInTaskbar() { return false; }

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
        static bool showMarkdown();
        static void setShowMarkdown(bool newShowMarkdown);
        static bool defaultShowMarkdown() { return true; }
#endif

        static bool tabTextColorPerType();
        static void setTabTextColorPerType(bool newTabTextColorPerType);
        static bool defaultTabTextColorPerType() { return true; }

        static int tabWidth();
        static void setTabWidth(int newTabWidth);
        static int defaultTabWidth() { return 4; }

        static QString timeFormat();
        static void setTimeFormat(QString newTimeFormat);
        static QString defaultTimeFormat() { return QString(); }

        static bool wordWrap();
        static void setWordWrap(bool newWordWrap);
        static bool defaultWordWrap() { return true; }


    public:

        static QString lastFile(QString folder);
        static void setLastFile(QString folder, QString file);

        static QString lastFolder();
        static void setLastFolder(QString folder);

        static bool setupCompleted();
        static void setSetupCompleted(bool newSetupCompleted);

};
