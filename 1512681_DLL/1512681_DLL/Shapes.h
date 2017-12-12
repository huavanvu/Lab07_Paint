#include <iostream>
#include "stdafx.h"

using namespace std;

#define TY_LINE 0
#define TY_RECTANGLE 1
#define TY_ELLIPSE 2

class Shape
{
public:

	Shape();
	~Shape();
	virtual void Draw(Graphics* gp, Pen* pen) = 0;
	void setPoint(POINT _bt, POINT _kt);
protected:
	POINT bd;
	POINT kt;
};

class CLine :public Shape
{
public:

	CLine();
	~CLine();
	void Draw(Graphics* gp, Pen* pen);
};

class CRectangle :public Shape
{
public:
	CRectangle();
	~CRectangle();
	void Draw(Graphics* gp, Pen* pen);
};

class CEllipse :public Shape
{
public:

	CEllipse();
	~CEllipse();
	void Draw(Graphics* gp, Pen* pen);
};

class ShapeFactory
{
public:
	ShapeFactory();
	~ShapeFactory();

	//shapeType 0: Line, 1: Rectangle,2: Ellipse
	Shape* getShape(int shapeType);
};
