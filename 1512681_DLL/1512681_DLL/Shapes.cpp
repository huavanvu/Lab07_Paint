#include "stdafx.h"
#include "Shapes.h"


typedef void(*MYPROC)(Graphics*, Pen*, Point, Point);

void CLine::Draw(Graphics* gp, Pen* pen)
{
	///////gp->DrawLine(pen, bd.x, bd.y, kt.x, kt.y);
	Point batdau(bd.x, bd.y);
	Point ketthuc(kt.x, kt.y);
	HINSTANCE hinstLib = LoadLibrary(L"MyDLL.dll");
	// đã viết Ham_De_Ve_Duong_Thang trong file MyDLL.dll
	MYPROC Đia_chi_ham = (MYPROC)GetProcAddress(hinstLib, "Ham_De_Ve_Duong_Thang");
	if (Đia_chi_ham != NULL)
		Đia_chi_ham(gp, pen, batdau, ketthuc);
}


Shape::Shape() {}

Shape::~Shape() {}

void Shape::setPoint(POINT _bd, POINT _kt) {
	bd = _bd;
	kt = _kt;
}

CLine::CLine() {}

CLine::~CLine() {}


CRectangle::CRectangle() {}
CRectangle::~CRectangle() {}

void CRectangle::Draw(Graphics* gp, Pen* pen) {
	int width = kt.x - bd.x;
	int height = kt.y - bd.y;
	if (width < 0) {
		if (height < 0) {
			gp->DrawRectangle(pen, kt.x, kt.y, abs(width), abs(height));
		}
		else {
			gp->DrawRectangle(pen, kt.x, kt.y - height, abs(width), height);
		}

	}
	else {
		if (height > 0) {
			gp->DrawRectangle(pen, bd.x, bd.y, width, height);
		}
		else {
			gp->DrawRectangle(pen, kt.x - width, kt.y, width, abs(height));
		}
	}
}


CEllipse::CEllipse() {}
CEllipse::~CEllipse() {}

void CEllipse::Draw(Graphics* gp, Pen* pen) {
	int width = kt.x - bd.x;
	int height = kt.y - bd.y;
	if (width < 0) {
		if (height < 0) {
			gp->DrawEllipse(pen, kt.x, kt.y, abs(width), abs(height));
		}
		else {
			gp->DrawEllipse(pen, kt.x, kt.y - height, abs(width), height);
		}

	}
	else {
		if (height > 0) {
			gp->DrawEllipse(pen, bd.x, bd.y, width, height);
		}
		else {
			gp->DrawEllipse(pen, kt.x - width, kt.y, width, abs(height));
		}
	}
}

ShapeFactory::ShapeFactory() {}
ShapeFactory::~ShapeFactory() {}

Shape* ShapeFactory::getShape(int type) {
	switch (type) {
	case TY_LINE:
		return new CLine();
	case TY_RECTANGLE:
		return new CRectangle();
	case TY_ELLIPSE:
		return new CEllipse();
	}
}