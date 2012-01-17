#include "ducttapewidget.hpp"
#include "State.hpp"

DucttapeWidget::DucttapeWidget(GameNonCont* game, QWidget* parent) :
    QWidget(parent),
    mGame(game),
    mDisplay(nullptr) {

    //connect(mGame, SIGNAL(BeginFrame(double)), SLOT(updateQt(double)));
    connect(qApp, SIGNAL(aboutToQuit()), mGame, SLOT(RequestShutdown()), Qt::DirectConnection);

    mDisplay = dt::Root::GetInstance().GetDisplayManager();

    bool stealparent (parentWidget() != NULL);
    QWidget *nativewin ((stealparent)? parentWidget () : this);

    Ogre::NameValuePairList params;
    Ogre::String winhandle;

    #ifdef Q_WS_WIN
    // According to Ogre Docs
    // positive integer for W32 (HWND handle)
    winhandle = Ogre::StringConverter::toString((unsigned int)(nativewin-> winId()));

    //Add the external window handle parameters to the existing params set.
    params["externalWindowHandle"] = winhandle;
    #endif

    #ifdef Q_WS_X11
    // GLX - According to Ogre Docs:
    // poslong:posint:poslong:poslong (display*:screen:windowHandle:XVisualInfo*)
    QX11Info info = x11Info();

    winhandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
    winhandle += ":";
    winhandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
    winhandle += ":";
    winhandle += Ogre::StringConverter::toString((unsigned long)nativewin->winId());

    //Add the external window handle parameters to the existing params set.
    params["parentWindowHandle"] = winhandle;
    #endif

    mDisplay->SetRenderWindowParam(params);
    mDisplay->CreateOgreRoot();
    Ogre::RenderWindow* win_ = mDisplay->GetRenderWindow();

    // take over ogre window
    // needed with parent windows
    //if (stealparent) {
        std::cout << "steal parent" << std::endl;
        WId ogre_winid = 0x0;
    //#ifndef Q_WS_WIN
        win_-> getCustomAttribute ("WINDOW", &ogre_winid);
    //#else
        //win_-> getCustomAttribute ("HWND", &ogre_winid);
    //#endif
        assert(ogre_winid);
        create(ogre_winid);
    //}

    setAttribute( Qt::WA_PaintOnScreen, true );
    setAttribute( Qt::WA_NoBackground );
    mTimer.start(2, this);
}

DucttapeWidget::~DucttapeWidget() {
    delete mGame;
}

void DucttapeWidget::resizeEvent(QResizeEvent *e) {
    if(mGame) {
        dt::DisplayManager::Get()->SetWindowSize(width(), height());
    }
}

void DucttapeWidget::paintEvent(QPaintEvent *e) {
    if(mGame) {
        update();
    }
}

void DucttapeWidget::timerEvent(QTimerEvent *e) {
    if(e->timerId() == mTimer.timerId()) {
        mGame->Run();
        update();
    }
}
