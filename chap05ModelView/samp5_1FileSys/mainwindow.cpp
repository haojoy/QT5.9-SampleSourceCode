﻿#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setCentralWidget(ui->splitterMain);  //设置主布局，填充满窗口

    //    model=new QDirModel(this);//QDirModel无单独线程

    model=new QFileSystemModel(this); //QFileSystemModel提供单独线程，推荐使用
    model->setRootPath(QDir::currentPath()); //设置根目录

    // 拖动窗口最小时不让窗口消失
    ui->splitter_3->setChildrenCollapsible(false);
    ui->splitter_2->setChildrenCollapsible(false);
    ui->splitter->setChildrenCollapsible(false);

    ui->treeView->setModel(model); //设置数据模型
    ui->listView->setModel(model); //设置数据模型
    ui->tableView->setModel(model); //设置数据模型

    // 拖动改变窗口列未正确拉伸文件名显示问题
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
//信号与槽关联，treeView单击时，其目录设置为listView和tableView的根节点
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),
            ui->listView,SLOT(setRootIndex(QModelIndex)));

    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),
            ui->tableView,SLOT(setRootIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->chkIsDir->setChecked(model->isDir(index));
    ui->LabPath->setText(model->filePath(index));
    ui->LabType->setText(model->type(index));

    ui->LabFileName->setText(model->fileName(index));

    int sz=model->size(index)/1024;
    if (sz<1024)
        ui->LabFileSize->setText(QString("%1 KB").arg(sz));
    else
        ui->LabFileSize->setText(QString::asprintf("%.1f MB",sz/1024.0));
}
