#include "StrokesRecognizer.h"
#include "Recognizer.h"

StrokesRecognizer::StrokesRecognizer(QWidget *parent):QWidget(parent)
	, mpLayout(NULL)
	, mpToolsLayout(NULL)
	, mpCanvas(NULL)
	, mpCharacterResult(NULL)
	, mpRecognizeBttn(NULL)
{
	resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

	mpLayout = new QHBoxLayout();
	setLayout(mpLayout);

	mpCanvas = new SmoothCanvas(this);
	mpCanvas->setObjectName(ON_CANVAS);
	mpCanvas->setStyleSheet("background-color:white;");
	mpLayout->addWidget(mpCanvas, 1);

	mpToolsLayout = new QVBoxLayout();
	mpLayout->addLayout(mpToolsLayout);

	mpCharacterResult = new QLabel(this);
	mpCharacterResult->setObjectName(ON_LABELBOX);
	mpCharacterResult->setStyleSheet("background-color: white;");
	mpCharacterResult->setAlignment(Qt::AlignCenter);
	QFont font;
	font.setBold(true);
	font.setPixelSize(100);
	mpCharacterResult->setFont(font);
	mpCharacterResult->setFixedSize(100, 100);
	mpToolsLayout->addWidget(mpCharacterResult);

	mpRecognizeBttn = new QPushButton(tr("Recognize"), this);
	mpRecognizeBttn->setObjectName(ON_BUTTON);
	mpToolsLayout->addWidget(mpRecognizeBttn);

	mpClearBttn = new QPushButton(tr("Clear"), this);
	mpRecognizeBttn->setObjectName(ON_BUTTON);
	mpToolsLayout->addWidget(mpClearBttn);

	mpToolsLayout->addStretch(1);

	connect(mpRecognizeBttn, SIGNAL(clicked()), this, SLOT(onRecognizeClicked()));
	connect(mpClearBttn, SIGNAL(clicked()), this, SLOT(onClearClicked()));
}

StrokesRecognizer::~StrokesRecognizer()
{
	DELETEPTR(mpClearBttn);
	DELETEPTR(mpRecognizeBttn);
	DELETEPTR(mpCharacterResult);
	DELETEPTR(mpCanvas);
	DELETEPTR(mpToolsLayout);
	DELETEPTR(mpLayout);
}

void StrokesRecognizer::onRecognizeClicked(){
	Recognizer rec;
	QString recognizedChar = rec.recognize(mpCanvas->strokes());

	mpCharacterResult->setText(recognizedChar);
}

void StrokesRecognizer::onClearClicked(){
	mpCanvas->clear();
}
