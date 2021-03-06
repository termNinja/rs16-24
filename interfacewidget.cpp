#include "interfacewidget.hpp"

Q_DECLARE_METATYPE(MemberVisibility)

interfaceWidget::interfaceWidget(QWidget *parent) : QWidget(parent)
{
    //    QString styleSheet = QString("font-size:10px;").arg(font().pointSize());
    //    this->setStyleSheet(styleSheet);
        moving = false;
        //set color to widget so its easy to see dimensions
        QPalette Pal(palette());
    //    Pal.setColor(QPalette::Background, Qt::gray);
        Pal.setColor(QPalette::Background, Qt::gray);
        setAutoFillBackground(true);
        setPalette(Pal);

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

    QWidget* interfaceWidget::makeFullSizeWidget(){

        QWidget* qwFullView = new QWidget();

        QVBoxLayout *qvblInterfaceFull;

        qvblInterfaceFull = new QVBoxLayout(qwFullView);
    //    setLayout(qw);
        qwFullView->setLayout(qvblInterfaceFull);
        qvblInterfaceFull->setContentsMargins(QMargins(0,0,0,0));

        //add Interface name
        qleInterfaceName = new QLineEdit();
        qleInterfaceName->setPlaceholderText("My Interface Name");
        qleInterfaceName->setAlignment(Qt::AlignCenter);
        connect(qleInterfaceName, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditRenameInterface()));

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


        qvblInterfaceFull->addWidget(qleInterfaceName);
        qvblInterfaceFull->addLayout(qhblMemberButtons);
        qvblInterfaceFull->addWidget(qlwMembers);
        qvblInterfaceFull->addLayout(qhblMethodButtons);
        qvblInterfaceFull->addWidget(qlwMethods);

        return qwFullView;
    }

    QString interfaceWidget::getName(){
        return name;
    }

    QWidget* interfaceWidget::makeCompactWidget(){

        QWidget* qwCompactView = new QWidget();

        QVBoxLayout* qvblInterfaceCompact = new QVBoxLayout();
        qwCompactView->setLayout(qvblInterfaceCompact);
        qvblInterfaceCompact->setContentsMargins(QMargins(0,0,0,0));

        QLabel* qlInterfaceName = new QLabel();
        qlInterfaceName->setText(name);
        qlInterfaceName->setAlignment(Qt::AlignHCenter);
        qvblInterfaceCompact->addWidget(qlInterfaceName);

    //    QLabel* qlMembers = new QLabel("Members:");
        //qvblInterfaceCompact->addWidget(qlMembers);

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
            }else{
                visibility = "#";
            }

            QStandardItem* Items = new QStandardItem(QString::fromStdString(visibility + " " + item.getType().getName()+" "+item.getName()));
            qaimMembers->appendRow(Items);
        }

        qlvMembers->setModel(qaimMembers);

        qlvMembers->setFixedSize(qlvMembers->sizeHintForColumn(0) + 2 * qlvMembers->frameWidth(), qlvMembers->sizeHintForRow(0) * memberVariables.count() + 2 * qlvMembers->frameWidth());

        qvblInterfaceCompact->addWidget(qlvMembers);

    //    QLabel* qlMethods = new QLabel("Methods:");
        //qvblInterfaceCompact->addWidget(qlMethods);

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

        qvblInterfaceCompact->addWidget(qlvMethods);

        qwCompactView->setLayout(qvblInterfaceCompact);
        qvblInterfaceCompact->setSizeConstraint(QLayout::SetMaximumSize);


        if(qlvMethods->width()>qlvMembers->width()){
            qlvMembers->setFixedWidth(qlvMethods->width());
        }else{
            qlvMethods->setFixedWidth(qlvMembers->width());
        }

        qlvMembers->setMinimumSize(80,0);
        qlvMethods->setMinimumSize(80,0);

        return qwCompactView;
    }

    void interfaceWidget::switchViews(){

        if(stackedLayout->currentIndex()==0){
            getMemberVariables();
            getMemberFunctions();
            setContentsMargins(QMargins(5,5,5,5));

            if(name == ""){
                    QMessageBox msgBox;
                    msgBox.setText("Interface must have a name");
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

    void interfaceWidget::deleteWidget(){
        emit Deleted();
        layout()->removeWidget(this);
        delete this;
    }

    void interfaceWidget::addMemberClicked()
    {
        qlwMembers->setVisible(true);

        QComboBox* qcbAccessModifiers = new QComboBox();
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
    }

    void interfaceWidget::removeMemberClicked(){
        qDeleteAll(qlwMembers->selectedItems());
        qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
        qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

        if(qlwMembers->count()==0)
            qlwMembers->setVisible(false);

        stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
        resize(sizeHint());
        qlwMembers->setFixedWidth(width());
        qlwMethods->setFixedWidth(width());
    }

    void interfaceWidget::addMethodClicked()
    {
        qlwMethods->setVisible(true);

        QComboBox* qcbAccessModifiers = new QComboBox();
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
    }

    void interfaceWidget::removeMethodClicked(){

        qDeleteAll(qlwMethods->selectedItems());
        qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());
        qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());

        if(qlwMethods->count()==0)
            qlwMethods->setVisible(false);

        stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
        resize(sizeHint());
        qlwMembers->setFixedWidth(width());
        qlwMethods->setFixedWidth(width());
    }

    void interfaceWidget::lineEditTextChanged(){
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
    }

    bool interfaceWidget::insideRect(QPoint mousePos)
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

    void interfaceWidget::hoverMove(QHoverEvent * event)
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
                    moveInterface((QMouseEvent*)event);
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

    bool interfaceWidget::event(QEvent *e)
    {
        if(e->type() == QEvent::HoverMove)
        {
            hoverMove(static_cast<QHoverEvent*>(e));
        }
        return QWidget::event(e);
    }

    void interfaceWidget::mousePressEvent(QMouseEvent *e)
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

    void interfaceWidget::moveInterface(QMouseEvent *e)
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

    void interfaceWidget::mouseMoveEvent(QMouseEvent *e)
    {
        QPoint mousePosition(e->pos().x() , e->pos().x());
        moveInterface(e);
    }

    void interfaceWidget::mouseReleaseEvent(QMouseEvent *e){
        if(moving=true)
            emit Moved();
        moving = false;
        resizing = false;
        resizePosition = -1;
    }

    void interfaceWidget::addMethodParameterClicked(){
        QHBoxLayout* qhblParametersWrap = (QHBoxLayout*)((QWidget*)(((QPushButton*)sender())->parent()))->layout()->itemAt(4)->layout();
        QLineEdit* qleParameter = new QLineEdit();

        qleParameter->setFixedWidth(15);
        connect(qleParameter, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChanged()));
        connect(qleParameter,SIGNAL(editingFinished()),this,SLOT(ParameterChanged()));

        qhblParametersWrap->addWidget(qleParameter);

    //    QMessageBox msgBox;
    //    msgBox.setText(->itemAt(0)->widget()->metaObject()->InterfaceName());
    //    msgBox.exec();

        qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
        qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

        stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
        resize(sizeHint());
        qlwMembers->setFixedWidth(width());
        qlwMethods->setFixedWidth(width());
    }

    void interfaceWidget::getMemberVariables(){

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

    void interfaceWidget::getMemberFunctions(){

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


    void interfaceWidget::ParameterChanged(){

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

    }

    void interfaceWidget::lineEditRenameInterface(){
        name= ((QLineEdit*)sender())->text();

            qlwMembers->setFixedSize(qlwMembers->sizeHintForColumn(0) + 2 * qlwMembers->frameWidth(), qlwMembers->sizeHintForRow(0) * qlwMembers->count() + 2 * qlwMembers->frameWidth());
            qlwMethods->setFixedSize(qlwMethods->sizeHintForColumn(0) + 2 * qlwMethods->frameWidth()+25, qlwMethods->sizeHintForRow(0) * qlwMethods->count() + 2 * qlwMethods->frameWidth());

            stackedLayout->currentWidget()->resize(stackedLayout->currentWidget()->sizeHint());
            resize(sizeHint());
            qlwMembers->setFixedWidth(width());
            qlwMethods->setFixedWidth(width());
    }

//    Class ClassWidget::getClass(){
//        return Class(name.toStdString(),memberConstructors.toVector().toStdVector(),memberFuncions.toVector().toStdVector(),memberVariables.toVector().toStdVector());
//    }

