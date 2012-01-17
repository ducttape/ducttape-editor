#include "ducttapewidget.hpp"
#include "State.hpp"

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
        //QPushButton* widget = new QPushButton;
        DucttapeWidget* widget = new DucttapeWidget(game, mainwidget);
        layout->addWidget(widget);
        layout->addWidget(quit);
        mainwidget->setLayout(layout);
        mainwidget->setMinimumSize(800, 600);
        mainwidget->show();
        //widget->show();

        app.exec();

        return 0;

    } else if(qargv == "noncont") {

        GameNonCont gamen;
        gamen.Init(new EditorState(), argc, argv);
        while(gamen.IsRunning()) {
            gamen.Run();
        }
        return 0;
    } else {
        dt::Game game;
        game.Run(new EditorState(), argc, argv);
        return 0;
    }
}
