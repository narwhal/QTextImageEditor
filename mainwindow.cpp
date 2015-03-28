#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextImage/qtextimage.h"

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

