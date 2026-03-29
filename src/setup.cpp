#include "setup.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>

#if defined(Q_OS_WIN)
    #include <windows.h>
#endif

bool Setup::autostart() {
    return nativeAutostartCheck();
}

void Setup::setAutostart(bool newAutostart) {
    if (newAutostart) {
        nativeAutostartAdd();
    } else {
        nativeAutostartRemove();
    }
}


#if defined(Q_OS_WIN)

void Setup::nativeAutostartAdd() {
    QString valueName = QCoreApplication::applicationName();
    QString value = QString("\"%1\" --hide").arg(QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));

    HKEY runKey = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_WRITE, &runKey) == ERROR_SUCCESS) {
        LPCWSTR namePtr = reinterpret_cast<LPCWSTR>(valueName.utf16());
        LPCWSTR valuePtr = reinterpret_cast<LPCWSTR>(value.utf16());
        RegSetValueExW(runKey, namePtr, 0, REG_SZ,
            reinterpret_cast<const BYTE*>(valuePtr),
            (value.length() + 1) * sizeof(wchar_t));
    }
    RegCloseKey(runKey);
}

void Setup::nativeAutostartRemove() {
    QString valueName = QCoreApplication::applicationName();
    HKEY runKey = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_WRITE, &runKey) == ERROR_SUCCESS) {
        LPCWSTR namePtr = reinterpret_cast<LPCWSTR>(valueName.utf16());
        RegDeleteValueW(runKey, namePtr);
    }
    RegCloseKey(runKey);
}

bool Setup::nativeAutostartCheck() {
    QString valueName = QCoreApplication::applicationName();
    QString expectedValue = QString("\"%1\" --hide").arg(QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    bool isFound = false;

    HKEY runKey = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_READ, &runKey) == ERROR_SUCCESS) {
        wchar_t valueBuffer[4096];
        DWORD valueBufferSize = sizeof(valueBuffer);
        LPCWSTR namePtr = reinterpret_cast<LPCWSTR>(valueName.utf16());

        if (RegGetValueW(runKey, nullptr, namePtr, RRF_RT_REG_SZ, nullptr,
            valueBuffer, &valueBufferSize) == ERROR_SUCCESS) {
            QString value = QString::fromWCharArray(valueBuffer);
            isFound = (expectedValue.compare(value) == 0);
        }
    }
    RegCloseKey(runKey);
    return isFound;
}

#elif defined(Q_OS_LINUX)

void Setup::nativeAutostartAdd() {
    QDir autostartDirectory(QDir::cleanPath(QDir::homePath() + "/.config/autostart"));
    if (!autostartDirectory.exists()) { autostartDirectory.mkpath("."); }
    QString autostartFile = QDir::cleanPath(autostartDirectory.path() + "/qtext.desktop");
    QString execLine = QCoreApplication::applicationFilePath() + " --hide";

    QFile file(autostartFile);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "[Desktop Entry]" << endl;
        stream << "Name=QText" << endl;
        stream << "Exec=" << execLine << endl;
        stream << "Terminal=false" << endl;
        stream << "Type=Application" << endl;
        stream << "StartupNotify=false" << endl;
        stream << "X-GNOME-Autostart-enabled=true" << endl;
    }
}

void Setup::nativeAutostartRemove() {
    QDir autostartDirectory(QDir::cleanPath(QDir::homePath() + "/.config/autostart"));
    if (!autostartDirectory.exists()) { autostartDirectory.mkpath("."); }
    QString autostartFile = QDir::cleanPath(autostartDirectory.path() + "/qtext.desktop");
    QFile::remove(autostartFile);
}

bool Setup::nativeAutostartCheck() {
    QDir autostartDirectory(QDir::cleanPath(QDir::homePath() + "/.config/autostart"));
    if (!autostartDirectory.exists()) { autostartDirectory.mkpath("."); }
    QString autostartFile = QDir::cleanPath(autostartDirectory.path() + "/qtext.desktop");
    QString execLine = QCoreApplication::applicationFilePath() + " --hide";

    QFile file(autostartFile);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            if (line.startsWith("Exec=")) {
                QStringList parts = line.split("=");
                QString execLineFound = parts[1].trimmed();
                if (execLine.compare(execLineFound, Qt::CaseSensitive) == 0) { return true; }
                break;
            }
        }
    }
    return false;
}

#endif
