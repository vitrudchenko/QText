#include "storage/fileitem.h"
#include "qtabwidgetex.h"
#include "qtabbarex.h"

QTabWidgetEx::QTabWidgetEx(QWidget* parent)
    : QTabWidget(parent) {
    QTabBarEx* bar = new QTabBarEx();
    this->setTabBar(bar);

    connect(bar, &QTabBarEx::tabMoved, this, &QTabWidgetEx::onTabMoved);
    //this->setTabsClosable(true);
}


int QTabWidgetEx::addTab(QWidget* widget, const QString& text) {
    FileItem* item = dynamic_cast<FileItem*>(widget);

    int index = QTabWidget::addTab(widget, text);
    this->stylizeTab(item, index);
    return index;
}

void QTabWidgetEx::stylizeTab(FileItem* item, int index) {
    QTabBar* tabBar = this->tabBar();
    QColor color = tabBar->tabTextColor(index);
    bool isDark = Settings::forceDarkMode();
    //bool isDark = ((color.red() + color.green() + color.blue()) / 3) < 64;
    QColor newColor;
    QIcon newIcon;
    switch (item->type()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    case FileType::Markdown: //green
        newColor = isDark ? QColor(70, 132, 98) : QColor(90, 152, 118);
        newIcon = QIcon(":/icons/48x48/markdown.png");
        break;
#endif
    case FileType::Html: //blue
        newColor = isDark ? QColor(65, 65, 225) : QColor(85, 85, 245);
        newIcon = QIcon(":/icons/48x48/html.png");
        break;
    default:
        newColor = isDark ? QColor(255, 255, 255) : QColor(0, 0, 0);
        newIcon = QIcon(":/icons/48x48/txt.png");
        break;
    }

    if (Settings::tabTextColorPerType()) { //playing with color
        this->tabBar()->setTabTextColor(index, newColor);
    }

    QFont font = this->tabBar()->font();
    font.setBold(true);
    this->tabBar()->setFont(font);

    if (!newIcon.isNull()) {
        if (isDark) {
            QImage image = newIcon.pixmap(48, 48).toImage();
            image.invertPixels(QImage::InvertRgb);
            newIcon = QIcon(QPixmap::fromImage(image));
        }
        this->tabBar()->setTabIcon(index, newIcon);
    }
}

void QTabWidgetEx::onTabMoved(int from, int to) {
    auto fileFrom = dynamic_cast<FileItem*>(this->widget(from));
    this->setTabText(from, fileFrom->title());
    auto fileTo = dynamic_cast<FileItem*>(this->widget(to));
    this->setTabText(to, fileTo->title());
    emit tabMoved(from, to);
}
