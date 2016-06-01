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

    //because widget is visible we need to call show() method to see newly added objects
    this->setParent(parent);
    show();
//    parent->show();
}

void ClassWidget::mousePressEvent(QMouseEvent *e)
{
    offset = e->pos();
    moving = true;
    raise();
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

void ClassWidget::mouseMoveEvent(QMouseEvent *e)
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


void ClassWidget::mouseReleaseEvent(QMouseEvent *e){
    moving = false;
}
