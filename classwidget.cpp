#include "classwidget.hpp"

ClassWidget::ClassWidget(QWidget *parent ){

    QString styleSheet = QString("font-size:10px;").arg(font().pointSize());
    this->setStyleSheet(styleSheet);

    moving = false;

    //set color to widget so its easy to see dimensions
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::gray);
    setAutoFillBackground(true);
    setPalette(Pal);

    qvblClass = new QVBoxLayout(this);
    setLayout(qvblClass);
    qvblClass->setContentsMargins(QMargins(0,20,0,0));

    //add class name
    qleClassName = new QLineEdit();
    qleClassName->setPlaceholderText("My Class Name");
    qleClassName->setAlignment(Qt::AlignCenter);


    //listview for member variables
    qlwMembers = new QListWidget();
    qlwMembers->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwMembers->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwMembers->setSelectionMode(QAbstractItemView::ExtendedSelection);
    qlwMembers->setVisible(false);

    QHBoxLayout* qhblMemberButtons = new QHBoxLayout(this);

    //creating button for adding members
    qpbAddMember = new QPushButton("Add member");
    qhblMemberButtons->addWidget(qpbAddMember);
    QObject::connect(qpbAddMember, SIGNAL(clicked()), this , SLOT(addMemberClicked()));

    QPushButton* btnRemoveMember = new QPushButton("Remove \nmember(s)");
    qhblMemberButtons->addWidget(btnRemoveMember);
    connect(btnRemoveMember, SIGNAL(clicked()), this , SLOT(removeMemberClicked()));


    //creating second half of a classObject(methods listview and button), same as the first half
    qlwMethods = new QListWidget();
    qlwMethods->setVisible(false);
    qlwMethods->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwMethods->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qlwMethods->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QHBoxLayout* qhblMethodButtons = new QHBoxLayout(this);

    qpbAddMethod = new QPushButton("Add method");
    qhblMethodButtons->addWidget(qpbAddMethod);
    QObject::connect(qpbAddMethod, SIGNAL(clicked()) , this , SLOT(addMethodClicked()));

    QPushButton* qpbRemoveMethod = new QPushButton("Remove \nmethod(s)");
    qhblMethodButtons->addWidget(qpbRemoveMethod);
    connect(qpbRemoveMethod, SIGNAL(clicked()), this , SLOT(removeMethodClicked()));


    qvblClass->addWidget(qleClassName);
    qvblClass->addLayout(qhblMemberButtons);
    qvblClass->addWidget(qlwMembers);
    qvblClass->addLayout(qhblMethodButtons);
    qvblClass->addWidget(qlwMethods);

     this->setAttribute(Qt::WA_Hover, true);

    //because widget is visible we need to call show() method to see newly added objects
    this->setParent(parent);
    show();
}

void ClassWidget::addMemberClicked()
{
    qlwMembers->setVisible(true);

    QComboBox* qcbAccessModifiers = new QComboBox();
    qcbAccessModifiers->addItems({"private", "public", "protected"});
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
    int pixelsWide = fm.width("type");
    qleType->setFixedWidth(pixelsWide);
    connect(qleType, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    pixelsWide = fm.width("newMember");
    qleName->setFixedWidth(pixelsWide);
    connect(qleName, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    widgetLayout->setSizeConstraint(QLayout::SetFixedSize);
    widget->setLayout(widgetLayout);
    itemN->setSizeHint(QSize(0,widget->sizeHint().height()));

    qlwMembers->addItem(itemN);
    qlwMembers->setItemWidget(itemN, widget);


    qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());

    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
}

void ClassWidget::removeMemberClicked(){
    qDeleteAll(qlwMembers->selectedItems());
    qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
    qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

    if(qlwMembers->count()==0)
        qlwMembers->setVisible(false);

    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
}

void ClassWidget::addMethodClicked()
{
    qlwMethods->setVisible(true);

    QComboBox* qcbAccessModifiers = new QComboBox();
    qcbAccessModifiers->addItems({"public","private","protected"});
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
    int pixelsWide = fm.width("type");
    qleType->setFixedWidth(pixelsWide);
    connect(qleType, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    pixelsWide = fm.width("NewMethod");
    qleName->setFixedWidth(pixelsWide);
    connect(qleName, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    widgetLayout->setSizeConstraint(QLayout::SetFixedSize);
    widget->setLayout(widgetLayout);
    itemN->setSizeHint(QSize(0,widget->sizeHint().height()));

    qlwMethods->addItem(itemN);
    qlwMethods->setItemWidget(itemN, widget);

    qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
}

void ClassWidget::removeMethodClicked(){

    qDeleteAll(qlwMethods->selectedItems());
    qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());
    qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());

    if(qlwMethods->count()==0)
        qlwMethods->setVisible(false);

    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
}

void ClassWidget::lineEditTextChanged(){
  QLineEdit* lineEdit = (QLineEdit*)sender();

  QFont font = lineEdit->font();
  QFontMetrics fm(font);
  int pixelsWide = fm.width(lineEdit->text().append("      "));

  lineEdit->setFixedWidth(pixelsWide);

  qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
  qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());
  resize(sizeHint());
  qlwMembers->setFixedWidth(width());
  qlwMethods->setFixedWidth(width());
}

bool ClassWidget::insideRect(QPoint mousePos)
{
    int magicConst = 15;

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
    int magicConst = 15;
    QPoint mousePosition(event->pos().x() , event->pos().y());
    bool inside = insideRect(mousePosition);

    if(!inside && mousePosition.x() < magicConst && mousePosition.y()<magicConst )
    {
        this->setCursor(Qt::SizeFDiagCursor);
        if(m_resize)
        {
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
//    else if( !inside && mousePosition.x() < magicConst &&
//                        mousePosition.y() > this->height() - magicConst )
//    {
//        this->setCursor(Qt::SizeBDiagCursor);
//        if(moving)
//        {
//            int diffX = event->oldPos().x() - event->pos().x();
//            int diffY = event->oldPos().y() - event->pos().y();
//            if(diffX < 0 || diffY > 0)
//            {
//                resize( this->width() + (-1)*diffX, this->height() + diffY);
//            }
//            else if(diffX > 0 || diffY < 0){
//                resize( this->width() + (-1)* diffX, this->height() + diffY);
//            }
//        }
//    }

//    else if(!inside && mousePosition.x() > this->width() - magicConst &&
//                       mousePosition.y() < magicConst )
//    {
//        this->setCursor(Qt::SizeBDiagCursor);
//        if(moving)
//        {
//            int diffX = event->oldPos().x() - event->pos().x();
//            int diffY = event->oldPos().y() - event->pos().y();
//            if(diffX < 0 && diffY > 0)
//            {
//                resize( this->width() + diffX, this->height() + diffY);
//            }
//            else {
//                resize( this->width() - diffX, this->height() - diffY);
//            }
//        }
//    }

    else if(!inside && mousePosition.x() > (this->width() - magicConst) &&
                       mousePosition.y() > (this->height() - magicConst) )
    {
        this->setCursor(Qt::SizeFDiagCursor);
        if(m_resize)
        {
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
    else{
        this->setCursor(Qt::ArrowCursor);
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
    //if(insideRect(QPoint(e->pos())))
    //{
        moving = true;
    //}
    //m_resize = true;
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
    moving = false;
    m_resize = false;
}

void ClassWidget::addMethodParameterClicked(){
    QHBoxLayout* qhblParametersWrap = (QHBoxLayout*)((QWidget*)(((QPushButton*)sender())->parent()))->layout()->itemAt(4)->layout();
    QLineEdit* qleParameter = new QLineEdit();

    qleParameter->setFixedWidth(15);
    connect(qleParameter, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    qhblParametersWrap->addWidget(qleParameter);
//    QMessageBox msgBox;
//    msgBox.setText(->itemAt(0)->widget()->metaObject()->className());
//    msgBox.exec();

    qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
    qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());
    resize(sizeHint());
    qlwMembers->setFixedWidth(width());
    qlwMethods->setFixedWidth(width());
}

void ClassWidget::getMemberFunctions(){

    memberFuncions.clear();

    for(int i=0;i<qlwMethods->count();i++){
        QLayout* methodLayout = qlwMethods->itemWidget(qlwMethods->item(i))->layout();

        QComboBox* methodAccessModifier = (QComboBox*)methodLayout->itemAt(0)->widget();
        QLineEdit* methodType= (QLineEdit*)methodLayout->itemAt(1)->widget();
        QLineEdit* methodName= (QLineEdit*)methodLayout->itemAt(2)->widget();

        //todo: kreirati lepo metodu, sa svim podacima
        memberFuncions.append(new MemberFunction(methodName->text().toStdString(),false));
    }
}

void ClassWidget::getMembers(){

    memberVariables.clear();

    for(int i=0;i<qlwMembers->count();i++){
        QLayout* memberLayout = qlwMembers->itemWidget(qlwMembers->item(i))->layout();

        QComboBox* memberAccessModifier = (QComboBox*)memberLayout->itemAt(0)->widget();
        QLineEdit* memberType= (QLineEdit*)memberLayout->itemAt(1)->widget();
        QLineEdit* memberName= (QLineEdit*)memberLayout->itemAt(2)->widget();

        //todo: dogovoriti se oko toga kako treba da izgleda "interfejs" moduleCodgen-a
//        memberVariables.append(new MemberVariable());
    }
}
