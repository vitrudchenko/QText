/* Josip Medved <jmedved@jmedved.com> * www.medo64.com * MIT License */

#include <QDebug>
#include "appsetupmutex.h"
#include <windows.h>


const int mutexNameLength = 4096;

AppSetupMutex::AppSetupMutex(const QString& mutexName) {
#if defined(Q_OS_WIN)
    wchar_t mutexNameChars[mutexNameLength];  // Unicode
    int len = mutexName.toWCharArray(mutexNameChars);
    assert(len + 1 < mutexNameLength);
    mutexNameChars[len] = '\0';

    // Convert to ANSI for CreateMutexA
    char mutexNameAnsi[mutexNameLength];
    WideCharToMultiByte(CP_ACP, 0, mutexNameChars, -1, mutexNameAnsi, mutexNameLength, NULL, NULL);

    _mutexHandle = CreateMutexA(NULL, false, mutexNameAnsi);

    if (_mutexHandle != nullptr) {
        qDebug().noquote() << "[AppSetupMutex]" << mutexName << "created as" << _mutexHandle;
    }
    else {
        qDebug().noquote() << "[AppSetupMutex]" << mutexName << "could not be created";
    }
#else
    Q_UNUSED(mutexName)
#endif
}


AppSetupMutex::~AppSetupMutex() {
#if defined(Q_OS_WIN)
    CloseHandle(_mutexHandle);
    qDebug().noquote() << "[AppSetupMutex]" << _mutexHandle << "closed";
#endif
}
