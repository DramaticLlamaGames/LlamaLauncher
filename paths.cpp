#include "paths.h"
#include <QApplication>
#include <QDir>
#include <QMessageBox>

#ifdef _WIN32
#else
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

QString getAppDir() {
    size_t buf_size = 0;
    size_t read_size;
    QString result;
    do {
        buf_size += 256;
        char* buf = new char[buf_size];
        read_size = readlink("/proc/self/exe", buf, buf_size);
        if(read_size < 0) {
            int err = errno;
            QMessageBox::critical(0, QApplication::tr("Critical Error"), QApplication::tr("Error determining application directory: %1").arg(strerror(err)));
            exit(-1);
        } else if(read_size < buf_size) {
            buf[read_size] = '\0';
            result = buf;
            printf("%s\n", buf);
        }
        delete[] buf;
        printf("pass: tried to read %ld and got %ld\n", buf_size, read_size);
    } while(read_size >= buf_size);
    return result;
}
#endif

void switchToAppDir() {
    QDir::setCurrent(getAppDir());
}

QString getConfigDir() {
    QString appdata_dir;
#ifdef _WIN32
#else
    appdata_dir = QDir::homePath() + QDir::separator() + ".config";
#endif
    return appdata_dir + QDir::separator() + PUBLISHER + QDir::separator() + APPNAME + QDir::separator();
}