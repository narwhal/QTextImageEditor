#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextImage/qtextimage.h"


#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font("monospace");
    font.setStyleHint(QFont::Monospace);
    ui->editor->setFont(font);

    ui->colorEditor->setModel(&model);
    ui->colorEditor->horizontalHeader()->setSectionResizeMode(PenModel::Glyph, QHeaderView::ResizeToContents);
    ui->colorEditor->horizontalHeader()->setSectionResizeMode(PenModel::PenColor, QHeaderView::Fixed);
    ui->colorEditor->horizontalHeader()->setSectionResizeMode(PenModel::BrushColor, QHeaderView::Stretch);

    connect(&model, &PenModel::dataChanged, this, &MainWindow::draw);

    ui->editor->setPlainText(QStringLiteral(
        ". . . . 1 1 1 . . . .\n"
        ". . 1 . . . . . 1 . .\n"
        ". 1 . . . . . . . 1 .\n"
        "1 . . 2 . . . 3 . . 1\n"
        "1 . . . # . # . . . 1\n"
        "1 . . . . # . . . . 1\n"
        "1 . . . # . # . . . 1\n"
        "1 . . 3 . . . 2 . . 1\n"
        ". 1 . . . . . . . 1 .\n"
        ". . 1 . . . . . 1 . .\n"
        ". . . 1 1 1 1 1 . . .\n"));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_editor_textChanged() {
    draw();
}

void MainWindow::draw() {
    QSet<char> drawnGlyphs;
    QTextImage ti = QTextImage::parse(ui->editor->toPlainText().toLatin1());
    QImage img = ti.render(10, [this, &drawnGlyphs](char glyph, QPainter &painter){
        drawnGlyphs.insert(glyph);
        QPair<QPen, QBrush> config = model.glyphConfig(glyph);
        painter.setPen(config.first);
        painter.setBrush(config.second);
    });
    ui->preview->setPixmap(QPixmap::fromImage(img));
    model.setVisibleGlyphs(drawnGlyphs);
}

void MainWindow::on_actionAboutQt_triggered() {
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAbout_triggered() {
    QString title = tr("About QTextImageEditor");
    QString text = tr("<p>QTextImageEditor is a simple ASCIImage editor based on <a href=\"https://github.com/narwhal/QTextImage\">QTextImage</a>.</p>"
                      "<p>The ASCIImage format was created by <a href=\"http://cocoamine.net\">Charles Parnot</a>, see the <a href=\"http://asciimage.org\">official website</a> for documentation about the format.</p>"
                      "<p>QTextImageEditor is free software, licensed under a BSD-like license you can read in the LICENSE file.</p<"
                      "<p>Copyright © 2015 <a href=\"http://www.narwhal.it\">Narwhal Software</a></p>");
    QMessageBox msgBox(title, text, QMessageBox::Information, 0, 0, 0, this
    #ifdef Q_WS_MAC
    , Qt::WindowTitleHint | Qt::WindowSystemMenuHint
    #endif
    );
    QIcon icon = msgBox.windowIcon();
    QSize size = icon.actualSize(QSize(64, 64));
    msgBox.setIconPixmap(icon.pixmap(size));
    msgBox.setTextFormat(Qt::RichText);
    msgBox.exec();
}
