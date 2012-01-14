#include "ducttapewidget.hpp"
#include "State.hpp"

#include <stdio.h>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    /*QDeclarativeView main;
    main.connect(main.engine(), SIGNAL(quit()), SLOT(close()));
    main.setResizeMode(QDeclarativeView::SizeRootObjectToView);
    main.setSource(QUrl::fromLocalFile("../main.qml"));
    main.show();*/

    std::cout << "about to make widget" << std::endl;

    /*
     * this creates the QCoreApplication object in the main thread */
    dt::Game* game = (new dt::Game());

    DucttapeWidget dtwidget(game);

    dtwidget.show();

    /*
     * this tries to run the widget as a seperate thread,
     *  but it's not working right now; you don't have to call
     *  start, it will run on it's own */
    DucttapeThread dtthread(&dtwidget, argc, argv);
    dtthread.start();

    app.exec();
    /*
     * this doesn't work becaus qtgui has to be started in the main thread.
    DucttapeThread2 dtthread;

    dtthread.start();

    dtwidget.Run(new EditorState, argc, argv);*/

    return 0;
}
