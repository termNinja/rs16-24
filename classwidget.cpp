#include "classwidget.hpp"

//todo: CompactView size problem
ClassWidget::ClassWidget(QWidget *parent ){

//    QString styleSheet = QString("font-size:10px;").arg(font().pointSize());
//    this->setStyleSheet(styleSheet);
    moving = false;
    //set color to widget so its easy to see dimensions
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::gray);
    setAutoFillBackground(true);
    setPalette(Pal);
    //todo: vratiti resize kada se zavrsi sa compactview-om
    this->setAttribute(Qt::WA_Hover, true);

    QWidget* firstPageWidget = makeFullSizeWidget();
    QWidget* secondPageWidget = new QWidget();

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(firstPageWidget);
    stackedLayout->addWidget(secondPageWidget);

    QHBoxLayout* qhblHeader = new QHBoxLayout();
    qhblHeader->setContentsMargins(QMargins(0,0,0,0));
    qhblHeader->setAlignment(Qt::AlignLeft);

    QPushButton* toggle = new QPushButton("-");
    toggle->setMaximumWidth(20);
    connect(toggle, SIGNAL(clicked()), this , SLOT(switchViews()));

    QPushButton* qpbDeleteWidget = new QPushButton("X");
    qpbDeleteWidget->setMaximumWidth(20);
    connect(qpbDeleteWidget, SIGNAL(clicked()), this , SLOT(deleteWidget()));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(QMargins(0,0,0,0));

    qhblHeader->addWidget(qpbDeleteWidget);
    qhblHeader->addWidget(toggle);

    mainLayout->addLayout(qhblHeader);
    mainLayout->addLayout(stackedLayout);
    setLayout(mainLayout);

    //because widget is visible we need to call show() method to see newly added objects
    this->setParent(parent);
    show();
}

QWidget* ClassWidget::makeFullSizeWidget(){

    QWidget* qwFullView = new QWidget();

    QVBoxLayout *qvblClassFull;

    qvblClassFull = new QVBoxLayout(qwFullView);
//    setLayout(qw);
    qwFullView->setLayout(qvblClassFull);
    qvblClassFull->setContentsMargins(QMargins(0,0,0,0));

    //add class name
    qleClassName = new QLineEdit();
    qleClassName->setPlaceholderText("My Class Name");
    qleClassName->setAlignment(Qt::AlignCenter);
    connect(qleClassName, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditRenameClass()));

    //variables
    qlwMembers = new QListWidget();
    qlwMembers->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwMembers->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwMembers->setSelectionMode(QAbstractItemView::ExtendedSelection);
    qlwMembers->setVisible(false);

    QHBoxLayout* qhblMemberButtons = new QHBoxLayout();

    //creating button for adding members
    QPushButton* qpbAddMember = new QPushButton("Add member");
    qhblMemberButtons->addWidget(qpbAddMember);
    connect(qpbAddMember, SIGNAL(clicked()), this , SLOT(addMemberClicked()));

    QPushButton* btnRemoveMember = new QPushButton("Remove \nmember(s)");
    qhblMemberButtons->addWidget(btnRemoveMember);
    connect(btnRemoveMember, SIGNAL(clicked()), this , SLOT(removeMemberClicked()));

    //constructors
    qlwConstructors = new QListWidget();
    qlwConstructors->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwConstructors->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwConstructors->setSelectionMode(QAbstractItemView::ExtendedSelection);
    qlwConstructors->setVisible(false);

    QHBoxLayout* qhblConstructorButtons = new QHBoxLayout();

    //creating button for adding members
    QPushButton* qpbAddConstructor = new QPushButton("Add constructor");
    qhblConstructorButtons->addWidget(qpbAddConstructor);
    connect(qpbAddConstructor, SIGNAL(clicked()), this , SLOT(addConstructorClicked()));

    QPushButton* btnRemoveConstructor = new QPushButton("Remove \nconstructor(s)");
    qhblConstructorButtons->addWidget(btnRemoveConstructor);
    connect(btnRemoveConstructor, SIGNAL(clicked()), this , SLOT(removeConstructorClicked()));

    //methods
    qlwMethods = new QListWidget();
    qlwMethods->setVisible(false);
    qlwMethods->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwMethods->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwMethods->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QHBoxLayout* qhblMethodButtons = new QHBoxLayout();

    QPushButton* qpbAddMethod = new QPushButton("Add method");
    qhblMethodButtons->addWidget(qpbAddMethod);
    connect(qpbAddMethod, SIGNAL(clicked()) , this , SLOT(addMethodClicked()));

    QPushButton* qpbRemoveMethod = new QPushButton("Remove \nmethod(s)");
    qhblMethodButtons->addWidget(qpbRemoveMethod);
    connect(qpbRemoveMethod, SIGNAL(clicked()), this , SLOT(removeMethodClicked()));


    qvblClassFull->addWidget(qleClassName);
    qvblClassFull->addLayout(qhblMemberButtons);
    qvblClassFull->addWidget(qlwMembers);
    qvblClassFull->addLayout(qhblConstructorButtons);
    qvblClassFull->addWidget(qlwConstructors);
    qvblClassFull->addLayout(qhblMethodButtons);
    qvblClassFull->addWidget(qlwMethods);

    return qwFullView;
}

QString ClassWidget::getName(){
    return name;
}

QWidget* ClassWidget::makeCompactWidget(){

    QWidget* qwCompactView = new QWidget();

    QVBoxLayout* qvblClassCompact = new QVBoxLayout();
    qwCompactView->setLayout(qvblClassCompact);
    qvblClassCompact->setContentsMargins(QMargins(0,0,0,0));

    QLabel* qlClassName = new QLabel();
    qlClassName->setText(name);
    qlClassName->setAlignment(Qt::AlignHCenter);
    qvblClassCompact->addWidget(qlClassName);

//    QLabel* qlMembers = new QLabel("Members:");
    //qvblClassCompact->addWidget(qlMembers);

    QListView* qlvMembers = new QListView();
    qlvMembers->setEditTriggers(QListView::NoEditTriggers);
    qlvMembers->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlvMembers->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QStandardItemModel* qaimMembers = new QStandardItemModel();;


    foreach( MemberVariable item, memberVariables )
    {
        std::string visibility;
        if(item.getVisibility() == PUBLIC){
            visibility = "+";
        }else if(item.getVisibility() == PRIVATE){
            visibility = "-";
        }else{
            visibility = "#";
        }

        QStandardItem* Items = new QStandardItem(QString::fromStdString(visibility + " " + item.getType().getName()+" "+item.getName()));
        qaimMembers->appendRow(Items);
    }

    qlvMembers->setModel(qaimMembers);

    qlvMembers->setFixedSize(qlvMembers->sizeHintForColumn(0) + 2 * qlvMembers->frameWidth(), qlvMembers->sizeHintForRow(0) * memberVariables.count() + 2 * qlvMembers->frameWidth());

    qvblClassCompact->addWidget(qlvMembers);

    //constructors
    QListView* qlvConstructors = new QListView();
    qlvConstructors->setEditTriggers(QListView::NoEditTriggers);
    qlvConstructors->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlvConstructors->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QStandardItemModel* qaimConstructor = new QStandardItemModel();;

    foreach( MemberConstructor item, memberConstructors)
    {
        std::string constructor;

        constructor+="public " + item.getName()+ "(";

        int n = item.getParameters().size();
        for(int i=0;i<n;i++){
            Variable parameter = item.getParameters()[i];
            constructor+=parameter.getType().getName() + " " + parameter.getName() + (i!=n-1 ? ", ":"");

        }
        constructor+=")";
        QStandardItem* Items = new QStandardItem(QString::fromStdString(constructor));
        qaimConstructor->appendRow(Items);
    }

    qlvConstructors->setModel(qaimConstructor);

    qlvConstructors->setFixedSize(qlvConstructors->sizeHintForColumn(0) + 2 * qlvConstructors->frameWidth(), qlvConstructors->sizeHintForRow(0) * memberConstructors.count() + 2 * qlvConstructors->frameWidth());

    qvblClassCompact->addWidget(qlvConstructors);

//    QLabel* qlMethods = new QLabel("Methods:");
    //qvblClassCompact->addWidget(qlMethods);

    QListView* qlvMethods = new QListView();
    qlvMethods->setEditTriggers(QListView::NoEditTriggers);
    qlvMethods->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlvMethods->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QStandardItemModel* qaimMethods = new QStandardItemModel();;

    foreach( MemberFunction item, memberFuncions)
    {
        std::string method;

        std::string visibility;
        if(item.getVisibility() == PUBLIC){
            method = "+ ";
        }else if(item.getVisibility() == PRIVATE){
            method = "- ";
        }else{
            method = "# ";
        }

        method+=item.getReturnType().getName()+" "+ item.getName()+"(";

        int n = item.getParameters().size();
        for(int i=0;i<n;i++){
            Variable parameter = item.getParameters()[i];
            method+=parameter.getType().getName() + " " + parameter.getName() + (i!=n-1 ? ", ":"");

        }
        method+=")";
        QStandardItem* Items = new QStandardItem(QString::fromStdString(method));
        qaimMethods->appendRow(Items);
    }

    qlvMethods->setModel(qaimMethods);

    qlvMethods->setFixedSize(qlvMethods->sizeHintForColumn(0) + 2 * qlvMethods->frameWidth(), qlvMethods->sizeHintForRow(0) * memberFuncions.count() + 2 * qlvMethods->frameWidth());

    qvblClassCompact->addWidget(qlvMethods);

    qwCompactView->setLayout(qvblClassCompact);
    qvblClassCompact->setSizeConstraint(QLayout::SetMaximumSize);


    int maxWidth = std::max(qlvConstructors->width(),std::max(qlvMethods->width(),qlvMembers->width()));
    qlvMembers->setFixedWidth(maxWidth);
    qlvMethods->setFixedWidth(maxWidth);
    qlvConstructors->setFixedWidth(maxWidth);
//    if(qlvMethods->width()>qlvMembers->width()){
//        qlvMembers->setFixedWidth(qlvMethods->widthh());
//    }else{
//        qlvMethods->setFixedWidth(qlvMembers->width());
//    }

    qlvMembers->setMinimumSize(80,0);
    qlvMethods->setMinimumSize(80,0);
    qlvConstructors->setMinimumSize(80,0);

    return qwCompactView;
}

void ClassWidget::switchViews(){

    if(stackedLayout->currentIndex()==0){
        getMemberVariables();
        getMemberConstructors();
        getMemberFunctions();
        setContentsMargins(QMargins(5,5,5,5));

        if(name == ""){
                QMessageBox msgBox;
                msgBox.setText("Class must have a name");
                msgBox.exec();
            return;
        }
        stackedLayout->removeItem(stackedLayout->itemAt(1));
        stackedLayout->addWidget(makeCompactWidget());
        stackedLayout->setCurrentIndex(1);
//        stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
//        resize(stackedLayout->currentWidget()->sizeHint()+QSize(0,40));

        stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->width(), stackedLayout->currentWidget()->sizeHint().height()+10);

        resize(stackedLayout->currentWidget()->size()+QSize(10,50));
        this->setCursor(Qt::ArrowCursor);

    }else{
        this->setCursor(Qt::ArrowCursor);
        resizePosition=-1;
        setContentsMargins(QMargins(0,0,0,0));
        stackedLayout->setCurrentIndex(0);
        resize(sizeHint());
    }
    emit Moved();


//    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
//    resize(stackedLayout->currentWidget()->size());

//    QMessageBox msgBox;
//    msgBox.setText("test");
//    msgBox.exec();
}

void ClassWidget::deleteWidget(){
    layout()->removeWidget(this);
    delete this;
}

void ClassWidget::addMemberClicked()
{
    qlwMembers->setVisible(true);

    QComboBox* qcbAccessModifiers = new QComboBox();
    qcbAccessModifiers->addItem("private", qVariantFromValue(PRIVATE));
    qcbAccessModifiers->addItem("public", qVariantFromValue(PUBLIC));
    qcbAccessModifiers->addItem("protected", qVariantFromValue(PROTECTED));

    QLineEdit* qleType = new QLineEdit("type");
    QLineEdit* qleName = new QLineEdit("newMember");

    QListWidgetItem* itemN = new QListWidgetItem();
    QWidget* widget = new QWidget();

    QHBoxLayout* widgetLayout = new QHBoxLayout();
    widgetLayout->setContentsMargins(10,0,0,0);
    widgetLayout->addWidget(qcbAccessModifiers);
    widgetLayout->addWidget(qleType);
    widgetLayout->addWidget(qleName);

    QFont font = qleType->font();
    QFontMetrics fm(font);
    int pixelsWide = fm.width("type      ");
    qleType->setFixedWidth(pixelsWide);
    connect(qleType, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    pixelsWide = fm.width("newMember      ");
    qleName->setFixedWidth(pixelsWide);
    connect(qleName, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    widgetLayout->setSizeConstraint(QLayout::SetFixedSize);
    widget->setLayout(widgetLayout);
    itemN->setSizeHint(QSize(0,widget->sizeHint().height()));

    qlwMembers->addItem(itemN);
    qlwMembers->setItemWidget(itemN, widget);


    qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());

    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
    qlwConstructors->setFixedWidth(width());
}

void ClassWidget::removeMemberClicked(){
    qDeleteAll(qlwMembers->selectedItems());
    qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
    qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

    if(qlwMembers->count()==0)
        qlwMembers->setVisible(false);

    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
    qlwConstructors->setFixedWidth(width());
}

void ClassWidget::addConstructorClicked()
{
    qlwConstructors->setVisible(true);

    QLabel* qlName = new QLabel(name);

    QHBoxLayout* qhblParametersWrap = new QHBoxLayout();
    QPushButton* qpbAddParameter = new QPushButton("+");
    qpbAddParameter->setMaximumWidth(20);
    qpbAddParameter->setMaximumHeight(20);
    connect(qpbAddParameter, SIGNAL(clicked()), this , SLOT(addConstructorParameterClicked()));


    QListWidgetItem* itemN = new QListWidgetItem();
    QWidget* widget = new QWidget();

    QHBoxLayout* widgetLayout = new QHBoxLayout();
    widgetLayout->setContentsMargins(10,0,0,0);
    widgetLayout->addWidget(qlName);
    widgetLayout->addWidget(new QLabel("("));
    widgetLayout->addLayout(qhblParametersWrap);
    widgetLayout->addWidget(qpbAddParameter);
    widgetLayout->addWidget(new QLabel(")"));
    //lol, ovaj lineEdit sam dodao da bi se pravilno izracunala visina xD
    QLineEdit* qle= new QLineEdit("a");
    widgetLayout->addWidget(qle);


    widgetLayout->setSizeConstraint(QLayout::SetFixedSize);
    widget->setLayout(widgetLayout);
    itemN->setSizeHint(QSize(0,widget->sizeHint().height()));

    qlwConstructors->addItem(itemN);
    qlwConstructors->setItemWidget(itemN, widget);


    qlwConstructors->setFixedSize(qlwConstructors->sizeHintForColumn(0) + 2 * qlwConstructors->frameWidth(), qlwConstructors->sizeHintForRow(0) * qlwConstructors->count() + 2 * qlwConstructors->frameWidth());

    widgetLayout->removeWidget(qle);
    delete qle;

    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
    qlwConstructors->setFixedWidth(width());
}

void ClassWidget::removeConstructorClicked(){
    qDeleteAll(qlwConstructors->selectedItems());
    qlwConstructors->setFixedSize(qlwConstructors->sizeHintForColumn(0) + 2 * qlwConstructors->frameWidth(), qlwConstructors->sizeHintForRow(0) * qlwConstructors->count() + 2 * qlwConstructors->frameWidth());
    qlwConstructors->setFixedSize(qlwConstructors->sizeHintForColumn(0) + 2 * qlwConstructors->frameWidth()+25, qlwConstructors->sizeHintForRow(0) * qlwConstructors->count() + 2 * qlwConstructors->frameWidth());

    if(qlwConstructors->count()==0)
        qlwConstructors->setVisible(false);

    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
    qlwConstructors->setFixedWidth(width());
}

void ClassWidget::addMethodClicked()
{
    qlwMethods->setVisible(true);

    QComboBox* qcbAccessModifiers = new QComboBox();
    qcbAccessModifiers->addItem("private", qVariantFromValue(PRIVATE));
    qcbAccessModifiers->addItem("public", qVariantFromValue(PUBLIC));
    qcbAccessModifiers->addItem("protected", qVariantFromValue(PROTECTED));
    QLineEdit* qleType = new QLineEdit("type");
    QLineEdit* qleName = new QLineEdit("NewMethod");
    QHBoxLayout* qhblParametersWrap = new QHBoxLayout();
    QPushButton* qpbAddParameter = new QPushButton("+");
    qpbAddParameter->setMaximumWidth(20);
    qpbAddParameter->setMaximumHeight(20);
    connect(qpbAddParameter, SIGNAL(clicked()), this , SLOT(addMethodParameterClicked()));

    QListWidgetItem* itemN = new QListWidgetItem();
    QWidget* widget = new QWidget();

    QHBoxLayout* widgetLayout = new QHBoxLayout();
    widgetLayout->setContentsMargins(10,0,0,0);
    widgetLayout->addWidget(qcbAccessModifiers);
    widgetLayout->addWidget(qleType);
    widgetLayout->addWidget(qleName);
    widgetLayout->addWidget(new QLabel("("));
    widgetLayout->addLayout(qhblParametersWrap);
    widgetLayout->addWidget(qpbAddParameter);
    widgetLayout->addWidget(new QLabel(")"));

    QFont font = qleType->font();
    QFontMetrics fm(font);
    int pixelsWide = fm.width("type      ");
    qleType->setFixedWidth(pixelsWide);
    connect(qleType, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    pixelsWide = fm.width("NewMethod      ");
    qleName->setFixedWidth(pixelsWide);
    connect(qleName, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    widgetLayout->setSizeConstraint(QLayout::SetFixedSize);
    widget->setLayout(widgetLayout);
    itemN->setSizeHint(QSize(0,widget->sizeHint().height()));

    qlwMethods->addItem(itemN);
    qlwMethods->setItemWidget(itemN, widget);

    qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
    qlwConstructors->setFixedWidth(width());
}

void ClassWidget::removeMethodClicked(){

    qDeleteAll(qlwMethods->selectedItems());
    qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());
    qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());

    if(qlwMethods->count()==0)
        qlwMethods->setVisible(false);

    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
    qlwConstructors->setFixedWidth(width());
}

void ClassWidget::lineEditTextChanged(){
  QLineEdit* lineEdit = (QLineEdit*)sender();

  QFont font = lineEdit->font();
  QFontMetrics fm(font);
  int pixelsWide = fm.width(lineEdit->text().append("      "));

  lineEdit->setFixedWidth(pixelsWide);

  qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
  qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

  stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
  resize(sizeHint());
  qlwMembers->setFixedWidth(width());
  qlwMethods->setFixedWidth(width());
  qlwConstructors->setFixedWidth(width());
}

bool ClassWidget::insideRect(QPoint mousePos)
{
    int magicConst = 5;

    //leftTop coordinate
    QPoint a(magicConst , magicConst);
    //leftBottom coordinate
    QPoint b(magicConst , this->height() - magicConst);
    //rightTop coordinate
    QPoint d(this->width() - magicConst , magicConst);
    //rightBottom coordinate
    QPoint c(this->width()- magicConst , this->height() - magicConst);

    //mouse coordinate
    QPoint m(mousePos.x(), mousePos.y());
    std::cout<<"mouse: "<<m.x() << "a " << a.x()<<std::endl;
    // use orientation of triangles for evaluate
    // if cursor inside rectangle

    QPoint abVector(b.x() - a.x() , b.y() - a.y());
    QPoint amVector(m.x() - a.x() , m.y() - a.y());
    //determinant of vectors
    int dabm = (abVector.x() * amVector.y()) - (abVector.y() * amVector.x());

    QPoint bcVector(c.x() - b.x() , c.y() - b.y());
    QPoint bmVector(m.x() - b.x() , m.y() - b.y());
    int dbcm = (bcVector.x() * bmVector.y()) - (bcVector.y() * bmVector.x());

    QPoint cdVector(d.x() - c.x() , d.y() - c.y());
    QPoint cmVector(m.x() - c.x() , m.y() - c.y());
    int dcdm = (cdVector.x() * cmVector.y()) - (cdVector.y() * cmVector.x());

    QPoint daVector(a.x() - d.x() , a.y() - d.y());
    QPoint dmVector(m.x() - d.x() , m.y() - d.y());
    int ddam = (daVector.x() * dmVector.y()) - (daVector.y() * dmVector.x());

    // if orientation of all triangles if same then
    // poss of cursor is in rectangle
    std::cout<<"a "<< dabm <<"b "<<  dcdm<<"c " <<dcdm<< "d " <<ddam <<std::endl;
    if((dabm >= 0 && dbcm >= 0 && dcdm >= 0 && ddam >= 0)
           ||
      (dabm <= 0 && dbcm <= 0 && dcdm <= 0 && ddam <= 0))
        return true;
    else
        return false;
}

void ClassWidget::hoverMove(QHoverEvent * event)
{
    if(stackedLayout->currentIndex()==1){
    int magicConst = 5;
    QPoint mousePosition(event->pos().x() , event->pos().y());
    bool inside = insideRect(mousePosition);

    //left top edge
    if(resizePosition==0 ||!inside && mousePosition.x() < magicConst && mousePosition.y()<magicConst )
    {
        this->setCursor(Qt::SizeFDiagCursor);
        if(resizing)
        {
            resizePosition=0;
            int diffX = event->oldPos().x() - event->pos().x();
            int diffY = event->oldPos().y() - event->pos().y();
            if(diffX > 0 || diffY > 0){
                resize( this->width() + diffX, this->height() + diffY);
                moving = true;
                moveClass((QMouseEvent*)event);
                moving = false;
            }
            else if(diffX < 0 || diffY < 0) {
                resize( this->width() + diffX, this->height() + diffY);
                this->move(mapToParent( QPoint( -diffX, -diffY)));
            }
        }
    }
    //left bottom edge
    else if( resizePosition==1 || !inside && mousePosition.x() < magicConst &&
                        mousePosition.y() > this->height() - magicConst )
    {
        this->setCursor(Qt::SizeBDiagCursor);
        if(resizing)
        {
            resizePosition=1;
            int diffX = event->oldPos().x() - event->pos().x();
            int diffY = event->oldPos().y() - event->pos().y();
            if(diffX < 0 && diffY > 0)
            {
                resize( this->width() + diffX, this->height() - diffY);
                this->move(mapToParent( QPoint( -1*diffX ,0 )));
            }
            else if(diffX > 0 && diffY < 0){
                resize( this->width() - (-1)* diffX, this->height() - diffY);
                this->move(mapToParent( QPoint( -1*diffX, 0)));
            }
        }
    }
    //right top edge
    else if( resizePosition==2 ||!inside && mousePosition.y() < magicConst &&
                        mousePosition.x() > this->width() - magicConst )
    {
        this->setCursor(Qt::SizeBDiagCursor);
        if(resizing)
        {
            resizePosition=2;
            int diffX = event->oldPos().x() - event->pos().x();
            int diffY = event->oldPos().y() - event->pos().y();
            if(diffX > 0 || diffY < 0)
            {
                resize( this->width() - diffX, this->height() - -1*diffY);
                this->move(mapToParent( QPoint( 0 ,  -1*diffY  )));
            }
            else if(diffX < 0 && diffY > 0){
                resize( this->width() + (-1)* diffX, this->height() + diffY);
                this->move(mapToParent( QPoint( 0, -1*diffY )));
            }
        }
    }
    //left edge
    else if(resizePosition==3 ||!inside && mousePosition.x() < magicConst )
    {
        this->setCursor(Qt::SizeHorCursor);
        if(resizing)
        {
            resizePosition=3;
            int diffX = event->oldPos().x() - event->pos().x();
            if(diffX > 0){
                resize( this->width() + diffX, this->height() );
                this->move(mapToParent( QPoint(-diffX , 0)));

            }
            else if(diffX < 0) {
                resize( this->width() + diffX, this->height() + 0);
                this->move(mapToParent( QPoint( -diffX, 0)));
            }
        }
    }
    //right bottom
    else if(resizePosition==4 || !inside && mousePosition.x() > (this->width() - magicConst) &&
                       mousePosition.y() > (this->height() - magicConst) )
    {
        this->setCursor(Qt::SizeFDiagCursor);
        if(resizing)
        {
            resizePosition=4;
            int diffX = event->oldPos().x() - event->pos().x();
            int diffY = event->oldPos().y() - event->pos().y();

            if(diffX < 0 || diffY < 0){
                resize( this->width() + -1*diffX, this->height() + -1*diffY);
            }
            else if(diffX > 0 || diffY > 0){
                resize( this->width() - diffX, this->height() - diffY);
            }
        }
    }
    //right edge
    else if(resizePosition==5 || !inside && mousePosition.x() > this->width()- magicConst )
    {
        this->setCursor(Qt::SizeHorCursor);
        if(resizing)
        {
            resizePosition=5;
            int diffX = event->oldPos().x() - event->pos().x();
            if(diffX < 0){
                resize( this->width() + -1*diffX, this->height() + 0);
            }
            else if(diffX > 0){
                resize( this->width() - diffX, this->height()+ 0);
            }
        }
    }
    //top edge
    else if(resizePosition==6 || !inside &&  mousePosition.y() <  magicConst )
    {
        this->setCursor(Qt::SizeVerCursor);
        if(resizing)
        {
            resizePosition=6;
            int diffY = event->oldPos().y() - event->pos().y();

            if(diffY < 0){
                resize( this->width() + 0 , this->height() + diffY);
                this->move(mapToParent( QPoint( 0 , -diffY)));
            }
            else if(diffY > 0){
                resize( this->width() -  0 , this->height() - (-1)*diffY);
                this->move(mapToParent( QPoint( 0 , -diffY)));
            }
        }
    }
    //bottom edge
    else if(resizePosition==7 || !inside &&  mousePosition.y() > this->height()- magicConst )
    {
        this->setCursor(Qt::SizeVerCursor);
        if(resizing)
        {
            resizePosition=7;
            int diffY = event->oldPos().y() - event->pos().y();
            if(diffY > 0){
                resize( this->width() + 0 , this->height() - diffY);
            }
            else if(diffY < 0){
                resize( this->width() -  0 , this->height() + (-1)*diffY);
            }
        }
    }
    else{
        this->setCursor(Qt::ArrowCursor);
        resizePosition=-1;
    }
    }
}

bool ClassWidget::event(QEvent *e)
{
    if(e->type() == QEvent::HoverMove)
    {
        hoverMove(static_cast<QHoverEvent*>(e));
    }
    return QWidget::event(e);
}

void ClassWidget::mousePressEvent(QMouseEvent *e)
{
    offset = e->pos();
    if(stackedLayout->currentIndex()==0 || insideRect(QPoint(e->pos())))
    {
        moving = true;
    }else{
        resizing = true;
    }
    raise();
}

void ClassWidget::moveClass(QMouseEvent *e)
{

    if(e->buttons() && moving)
      {
          this->move(mapToParent(e->pos() - offset));
      }
    if(pos().x()<0){
        this->move(mapToParent(QPoint(pos().x()*-1,0)));
    }
    int rightMargin = parentWidget()->width()-width();
    if(pos().x()> rightMargin){
        this->move(mapToParent(QPoint(rightMargin - pos().x(),0)));
    }
    if(pos().y()<0){
        this->move(mapToParent(QPoint(0,pos().y()*-1)));
    }
    int bottomMargin = parentWidget()->height() - height();
    if(pos().y()> bottomMargin){
        this->move(mapToParent(QPoint(0,bottomMargin - pos().y())));
    }
}

void ClassWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPoint mousePosition(e->pos().x() , e->pos().x());
    moveClass(e);
}

void ClassWidget::mouseReleaseEvent(QMouseEvent *e){
    if(moving=true)
        emit Moved();
    moving = false;
    resizing = false;
    resizePosition = -1;
}

void ClassWidget::addMethodParameterClicked(){
    QHBoxLayout* qhblParametersWrap = (QHBoxLayout*)((QWidget*)(((QPushButton*)sender())->parent()))->layout()->itemAt(4)->layout();
    QLineEdit* qleParameter = new QLineEdit();

    qleParameter->setFixedWidth(15);
    connect(qleParameter, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));
    connect(qleParameter,SIGNAL(editingFinished()),this,SLOT(ParameterChanged()));

    qhblParametersWrap->addWidget(qleParameter);

//    QMessageBox msgBox;
//    msgBox.setText(->itemAt(0)->widget()->metaObject()->className());
//    msgBox.exec();

    qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
    qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
    qlwConstructors->setFixedWidth(width());
}

void ClassWidget::addConstructorParameterClicked(){
    QHBoxLayout* qhblParametersWrap = (QHBoxLayout*)((QWidget*)(((QPushButton*)sender())->parent()))->layout()->itemAt(2)->layout();
    QLineEdit* qleParameter = new QLineEdit();

    qleParameter->setFixedWidth(15);
    connect(qleParameter, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));
    connect(qleParameter,SIGNAL(editingFinished()),this,SLOT(ParameterChanged()));

    qhblParametersWrap->addWidget(qleParameter);

//    QMessageBox msgBox;
//    msgBox.setText(->itemAt(0)->widget()->metaObject()->className());
//    msgBox.exec();

    qlwConstructors->setFixedSize(qlwConstructors->sizeHintForColumn(0) + 2 * qlwConstructors->frameWidth(), qlwConstructors->sizeHintForRow(0) * qlwConstructors->count() + 2 * qlwConstructors->frameWidth());
    qlwConstructors->setFixedSize(qlwConstructors->sizeHintForColumn(0) + 2 * qlwConstructors->frameWidth()+25, qlwConstructors->sizeHintForRow(0) * qlwConstructors->count() + 2 * qlwConstructors->frameWidth());

    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
    qlwConstructors->setFixedWidth(width());
}

void ClassWidget::getMemberVariables(){

    memberVariables.clear();

    for(int i=0;i<qlwMembers->count();i++){
        QLayout* memberLayout = qlwMembers->itemWidget(qlwMembers->item(i))->layout();

        QComboBox* memberAccessModifier = (QComboBox*)memberLayout->itemAt(0)->widget();
        QLineEdit* memberType= (QLineEdit*)memberLayout->itemAt(1)->widget();
        QLineEdit* memberName= (QLineEdit*)memberLayout->itemAt(2)->widget();

//        if(memberAccessModifier->currentIndex())
        memberVariables.append(
                    MemberVariable(Type(memberType->text().toStdString(),false),memberName->text().toStdString(),"",
                                                  memberAccessModifier->itemData(memberAccessModifier->currentIndex()).value<MemberVisibility>()));
    }
}

void ClassWidget::getMemberFunctions(){

    memberFuncions.clear();

    for(int i=0;i<qlwMethods->count();i++){
        QLayout* methodLayout = qlwMethods->itemWidget(qlwMethods->item(i))->layout();

        QComboBox* methodAccessModifier = (QComboBox*)methodLayout->itemAt(0)->widget();
        QLineEdit* methodType= (QLineEdit*)methodLayout->itemAt(1)->widget();
        QLineEdit* methodName= (QLineEdit*)methodLayout->itemAt(2)->widget();

        QHBoxLayout* qhblParametersWrap = (QHBoxLayout*)methodLayout->itemAt(4)->layout();
//        QMessageBox msgBox;
//            msgBox.setText("test "+ qhblParametersWrap->count());
//            msgBox.exec();


        MemberFunction memberFunction(Type(methodType->text().toStdString(),false), methodName->text().toStdString(),false,
                                                          methodAccessModifier->itemData(methodAccessModifier->currentIndex()).value<MemberVisibility>());

        for(int i=0;i<qhblParametersWrap->count();i++){


            QString qsParameter = ((QLineEdit*)qhblParametersWrap->itemAt(i)->widget())->text();
            QStringList qslParameters = qsParameter.split(" ");

            if(qslParameters.length()!=2){
                QMessageBox msgBox;
                msgBox.setText("Parametar "+ qsParameter + " u metodi " + QString::fromStdString(memberFunction.getName()) +" nije unesen u dobrom obliku!");
                msgBox.exec();
            }else{
                Variable* parameter= new Variable(Type(QString(qslParameters.at(0)).toStdString(),false),QString(qslParameters.at(1)).toStdString());

                memberFunction.addParameter(*parameter);
            }
        }

        memberFuncions.append(memberFunction);
    }
}

void ClassWidget::getMemberConstructors(){

    memberConstructors.clear();

    for(int i=0;i<qlwConstructors->count();i++){
        QLayout* methodLayout = qlwConstructors->itemWidget(qlwConstructors->item(i))->layout();


        QHBoxLayout* qhblParametersWrap = (QHBoxLayout*)methodLayout->itemAt(2)->layout();
//        QMessageBox msgBox;
//            msgBox.setText("test "+ qhblParametersWrap->count());
//            msgBox.exec();


        MemberConstructor* memberConstructor= new MemberConstructor();

        for(int i=0;i<qhblParametersWrap->count();i++){


            QString qsParameter = ((QLineEdit*)qhblParametersWrap->itemAt(i)->widget())->text();
            QStringList qslParameters = qsParameter.split(" ");

            if(qslParameters.length()!=2){
                QMessageBox msgBox;
                msgBox.setText("Parametar "+ qsParameter + " u kostruktoru nije unesen u dobrom obliku!");
                msgBox.exec();
            }else{
                Variable* parameter= new Variable(Type(QString(qslParameters.at(0)).toStdString(),false),QString(qslParameters.at(1)).toStdString());

                memberConstructor->addParameter(*parameter);
            }
        }

        memberConstructor->setName(name.toStdString());
        memberConstructors.append(*memberConstructor);
    }
}

void ClassWidget::ParameterChanged(){

    QLineEdit* parameter = (QLineEdit*)sender();
    if(parameter->text().isEmpty()){
        parameter->deleteLater();
    }

    qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
    qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

    stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
    qlwConstructors->setFixedWidth(width());

}

void ClassWidget::lineEditRenameClass(){
    name= ((QLineEdit*)sender())->text();

        for(int i=0;i<qlwConstructors->count();i++){
            QLayout* methodLayout = qlwConstructors->itemWidget(qlwConstructors->item(i))->layout();

            QLabel* className = (QLabel*)methodLayout->itemAt(0)->widget();
    //        QMessageBox msgBox;
    //            msgBox.setText("test "+ qhblParametersWrap->count());
    //            msgBox.exec();


           className->setText(name);

    }
        qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
        qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());
        qlwConstructors->setFixedSize(qlwConstructors->sizeHintForColumn(0) + 2 * qlwConstructors->frameWidth()+25, qlwConstructors->sizeHintForRow(0) * qlwConstructors->count() + 2 * qlwConstructors->frameWidth());

        stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
        resize(sizeHint());
        qlwMembers->setFixedWidth(width());
        qlwMethods->setFixedWidth(width());
        qlwConstructors->setFixedWidth(width());
}

Class ClassWidget::getClass(){
    return Class(name.toStdString(),memberConstructors.toVector().toStdVector(),memberFuncions.toVector().toStdVector(),memberVariables.toVector().toStdVector());
}
