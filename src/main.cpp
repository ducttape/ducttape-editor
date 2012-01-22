#include "ducttapewidget.hpp"
#include "State.hpp"

#include "ui_4editor.h"

#include <stdio.h>

int main(int argc, char** argv) {
    QString qargv(argv[1]);
    if(argc && qargv == "widget") {

        QApplication app(argc, argv);
        GameNonCont* game = new GameNonCont;
        game->Init(new EditorState, argc, argv);

        QWidget* mainwidget = new QWidget;
        QPushButton* quit = new QPushButton(mainwidget);
        quit->setText("quit");
        QObject::connect(quit, SIGNAL(clicked()), game, SLOT(RequestShutdown()));
        QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
        QVBoxLayout* layout = new QVBoxLayout;
        DucttapeWidget* widget = new DucttapeWidget(game, mainwidget);
        layout->addWidget(widget);
        layout->addWidget(quit);
        mainwidget->setLayout(layout);
        mainwidget->setMinimumSize(800, 600);
        mainwidget->show();

        app.exec();

        return 0;

    } else if(qargv == "noncont") {

        GameNonCont gamen;
        gamen.Init(new EditorState(), argc, argv);
        while(gamen.IsRunning()) {
            gamen.Run();
        }
        return 0;
    } else if(qargv == "ui") {
        QApplication app(argc, argv);
        QMainWindow* mainwidget = new QMainWindow;
        Ui::EditorWindow ui;
        ui.setupUi(mainwidget);
        QWidget* view3d = mainwidget->findChild<QWidget*>("viewport");
        GameNonCont* game = new GameNonCont;
        game->Init(new EditorState, argc, argv);
        DucttapeWidget* dtwidget = new DucttapeWidget(game, view3d);
        dtwidget->resize(view3d->size());
        mainwidget->show();
        app.exec();
        return 0;
    } else {
        dt::Game game;
        game.Run(new EditorState(), argc, argv);
        return 0;
    }
}
