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

    vblClass = new QVBoxLayout(this);
    setLayout(vblClass);
//    setContentsMargins(QMargins(0,20,0,0));
    vblClass->setContentsMargins(QMargins(0,20,0,0));

    //add class name
//    lclassName = new QLineEdit("My Class Name");
    lclassName = new QLineEdit();
    lclassName->setPlaceholderText("My Class Name");
//    lclassName->setMaximumWidth(200);
    lclassName->setAlignment(Qt::AlignCenter);


    //listview for member variables
    lvMembers = new QListWidget();
//    lvMembers->setMaximumWidth(200);
    lvMembers->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lvMembers->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lvMembers->setSelectionMode(QAbstractItemView::ExtendedSelection);
    lvMembers->setVisible(false);

    QHBoxLayout* qhblMemberButtons = new QHBoxLayout(this);

    //creating button for adding members
    btnAddMember = new QPushButton("Add member");
//    btnAddMember->setMaximumWidth(200);
    qhblMemberButtons->addWidget(btnAddMember);
    QObject::connect(btnAddMember, SIGNAL(clicked()), this , SLOT(addMemberClicked()));

    QPushButton* btnRemoveMember = new QPushButton("Remove \nmember(s)");
//    btnAddMember->setMaximumWidth(200);
    qhblMemberButtons->addWidget(btnRemoveMember);
    QObject::connect(btnRemoveMember, SIGNAL(clicked()), this , SLOT(removeMemberClicked()));


    //creating second half of a classObject(methods listview and button), same as the first half
    lvMethods = new QListWidget();
//    lvMethods->setMaximumWidth(200);
    lvMethods->setVisible(false);
    lvMethods->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lvMethods->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lvMethods->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QHBoxLayout* qhblMethodButtons = new QHBoxLayout(this);

    btnAddMethod = new QPushButton("Add method");
//    btnAddMethod->setMaximumWidth(200);
    qhblMethodButtons->addWidget(btnAddMethod);
    QObject::connect(btnAddMethod, SIGNAL(clicked()) , this , SLOT(addMethodClicked()));

    QPushButton* btnRemoveMethod = new QPushButton("Remove \nmethod(s)");
//    btnAddMethod->setMaximumWidth(200);
    qhblMethodButtons->addWidget(btnRemoveMethod);
    QObject::connect(btnRemoveMethod, SIGNAL(clicked()), this , SLOT(removeMethodClicked()));


    vblClass->addWidget(lclassName);
    vblClass->addLayout(qhblMemberButtons);
    vblClass->addWidget(lvMembers);
    vblClass->addLayout(qhblMethodButtons);
    vblClass->addWidget(lvMethods);
    this->setAttribute(Qt::WA_Hover, true);
    //because widget is visible we need to call show() method to see newly added objects
    this->setParent(parent);
    show();
//    parent->show();
}

void ClassWidget::addMemberClicked()
{
    lvMembers->setVisible(true);

    QComboBox* qcbAccessModifiers = new QComboBox();
    qcbAccessModifiers->addItems({"private", "public", "protected"});
//    qcbAccessModifiers->setMaximumWidth(50);
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

    lvMembers->addItem(itemN);
    lvMembers->setItemWidget(itemN, widget);


    lvMembers->setFixedSize(lvMembers->sizeHintForColumn(0) + 2 * lvMembers->frameWidth(), lvMembers->sizeHintForRow(0) * lvMembers->count() + 2 * lvMembers->frameWidth());

    resize(sizeHint());
    lvMembers->setFixedWidth(width());
    lvMethods->setFixedWidth(width());
}

void ClassWidget::removeMemberClicked(){
    qDeleteAll(lvMembers->selectedItems());
    lvMembers->setFixedSize(lvMembers->sizeHintForColumn(0) + 2 * lvMembers->frameWidth(), lvMembers->sizeHintForRow(0) * lvMembers->count() + 2 * lvMembers->frameWidth());
    lvMethods->setFixedSize(lvMethods->sizeHintForColumn(0) + 2 * lvMethods->frameWidth(), lvMethods->sizeHintForRow(0) * lvMethods->count() + 2 * lvMethods->frameWidth());

    if(lvMembers->count()==0)
        lvMembers->setVisible(false);

    resize(sizeHint());
    lvMembers->setFixedWidth(width());
    lvMethods->setFixedWidth(width());
}

void ClassWidget::addMethodClicked()
{
    lvMethods->setVisible(true);

    QComboBox* qcbAccessModifiers = new QComboBox();
    qcbAccessModifiers->addItems({"public","private","protected"});
//    qcbAccessModifiers->setMaximumWidth(50);
    QLineEdit* qleType = new QLineEdit("type");
    QLineEdit* qleName = new QLineEdit("NewMethod");
    QLineEdit* qleParameters = new QLineEdit("");

    QListWidgetItem* itemN = new QListWidgetItem();
    QWidget* widget = new QWidget();

    QHBoxLayout* widgetLayout = new QHBoxLayout();
    widgetLayout->setContentsMargins(10,0,0,0);
    widgetLayout->addWidget(qcbAccessModifiers);
    widgetLayout->addWidget(qleType);
    widgetLayout->addWidget(qleName);
    widgetLayout->addWidget(new QLabel("("));
    widgetLayout->addWidget(qleParameters);
    widgetLayout->addWidget(new QLabel(")"));

    QFont font = qleType->font();
    QFontMetrics fm(font);
    int pixelsWide = fm.width("type");
    qleType->setFixedWidth(pixelsWide);
    connect(qleType, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    pixelsWide = fm.width("NewMethod");
    qleName->setFixedWidth(pixelsWide);
    connect(qleName, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    qleParameters->setFixedWidth(15);
    connect(qleParameters, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));

    widgetLayout->setSizeConstraint(QLayout::SetFixedSize);
    widget->setLayout(widgetLayout);
    itemN->setSizeHint(QSize(0,widget->sizeHint().height()));

    lvMethods->addItem(itemN);
    lvMethods->setItemWidget(itemN, widget);

    lvMethods->setFixedSize(lvMethods->sizeHintForColumn(0) + 2 * lvMethods->frameWidth(), lvMethods->sizeHintForRow(0) * lvMethods->count() + 2 * lvMethods->frameWidth());

    resize(sizeHint());
    lvMembers->setFixedWidth(width());
    lvMethods->setFixedWidth(width());
}

void ClassWidget::removeMethodClicked(){

    qDeleteAll(lvMethods->selectedItems());
    lvMethods->setFixedSize(lvMethods->sizeHintForColumn(0) + 2 * lvMethods->frameWidth(), lvMethods->sizeHintForRow(0) * lvMethods->count() + 2 * lvMethods->frameWidth());
    lvMembers->setFixedSize(lvMembers->sizeHintForColumn(0) + 2 * lvMembers->frameWidth(), lvMembers->sizeHintForRow(0) * lvMembers->count() + 2 * lvMembers->frameWidth());

    if(lvMethods->count()==0)
        lvMethods->setVisible(false);

    resize(sizeHint());
    lvMembers->setFixedWidth(width());
    lvMethods->setFixedWidth(width());
}

void ClassWidget::lineEditTextChanged(){
  QLineEdit* lineEdit = (QLineEdit*)sender();

  QFont font = lineEdit->font();
  QFontMetrics fm(font);
  int pixelsWide = fm.width(lineEdit->text().append("      "));

  lineEdit->setFixedWidth(pixelsWide);

  lvMembers->setFixedSize(lvMembers->sizeHintForColumn(0) + 2 * lvMembers->frameWidth(), lvMembers->sizeHintForRow(0) * lvMembers->count() + 2 * lvMembers->frameWidth());
  lvMethods->setFixedSize(lvMethods->sizeHintForColumn(0) + 2 * lvMethods->frameWidth(), lvMethods->sizeHintForRow(0) * lvMethods->count() + 2 * lvMethods->frameWidth());
  resize(sizeHint());
  lvMembers->setFixedWidth(width());
  lvMethods->setFixedWidth(width());
}

bool ClassWidget::insideRect(QPoint mousePos)
{
    int magicConst = 10;

    //leftTop coordinate
    QPoint a(magicConst , magicConst);
    //leftBottom coordinate
    QPoint b(this->height() - magicConst , magicConst);

    //rightTop coordinate
    QPoint c(this->width() - magicConst , magicConst);
    //rightTop coordinate
    QPoint d(this->height()- magicConst , this->width() - magicConst);

    //mouse coordinate
    QPoint m(mousePos.x(), mousePos.y());

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

    if(dabm > 0 && dbcm > 0 && dcdm > 0 && ddam > 0
           ||
      dabm < 0 && dbcm < 0 && dcdm < 0 && ddam < 0)
        return true;
    else
        return false;
}

void ClassWidget::hoverMove(QHoverEvent * event)
{
    int magicConst = 10;
    QPoint mousePosition(event->pos().x() , event->pos().y());
    bool inside = insideRect(mousePosition);

    if(!inside && mousePosition.x() < magicConst && mousePosition.y()<magicConst )
    {
        this->setCursor(Qt::SizeFDiagCursor);
        if(moving)
        {
            int diffX = event->oldPos().x() - event->pos().x();
            int diffY = event->oldPos().y() - event->pos().y();
            double translate = sqrt(pow(diffX,2) + pow(diffY,2));
            if(diffX > 0 || diffY > 0)
            {
                resize( this->width() + translate, this->height() + translate);
                moveClass((QMouseEvent*)event);
            }
            else if(diffX < 0 || diffY < 0) {
                resize( this->width() - translate, this->height() - translate);
                moveClass((QMouseEvent*)event);
            }
        }
    }
    else if( !inside && mousePosition.x() < magicConst &&
                        mousePosition.y() > this->height() - magicConst )
    {
        this->setCursor(Qt::SizeBDiagCursor);
        if(moving)
        {
            int diffX = event->oldPos().x() - event->pos().x();
            int diffY = event->oldPos().y() - event->pos().y();
            double translate = sqrt(pow(diffX,2) + pow(diffY,2));
            if(diffX > 0 || diffY < 0)
            {
                resize( this->width() + translate, this->height() + translate);
                moveClass((QMouseEvent*)event);
            }
            else {
                resize( this->width() - translate, this->height() - translate);
                moveClass((QMouseEvent*)event);
            }
        }
    }

    else if(!inside && mousePosition.x() > this->width() - magicConst &&
                       mousePosition.y() < magicConst )
    {
        this->setCursor(Qt::SizeBDiagCursor);
        if(moving)
        {
            int diffX = event->oldPos().x() - event->pos().x();
            int diffY = event->oldPos().y() - event->pos().y();
            double translate = sqrt(pow(diffX,2) + pow(diffY,2));
            if(diffX < 0 || diffY > 0)
            {
                resize( this->width() + translate, this->height() + translate);
                moveClass((QMouseEvent*)event);
            }
            else {
                resize( this->width() - translate, this->height() - translate);
                moveClass((QMouseEvent*)event);
            }
        }
    }

    else if(!inside && mousePosition.x() > this->width() - magicConst &&
                       mousePosition.y() > this->height() - magicConst )
    {
        this->setCursor(Qt::SizeFDiagCursor);
        if(moving)
        {
            int diffX = event->oldPos().x() - event->pos().x();
            int diffY = event->oldPos().y() - event->pos().y();
            double translate = sqrt(pow(diffX,2) + pow(diffY,2));
            if(diffX < 0 || diffY < 0)
            {
                resize( this->width() + translate, this->height() + translate);
            }
            else {
                resize( this->width() - translate, this->height() - translate);
            }
           }
    }
    else
        this->setCursor(Qt::ArrowCursor);
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
    moving = true;
    raise();
}
void ClassWidget::moveClass(QMouseEvent *e)
{
    if(e->buttons() & moving)
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
    bool inside = insideRect(mousePosition);

    if(inside)
    {
        moveClass(e);
    }
}


void ClassWidget::mouseReleaseEvent(QMouseEvent *e){
    moving = false;
}
