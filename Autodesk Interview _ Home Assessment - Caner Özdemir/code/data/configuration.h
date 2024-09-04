#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>

class Configuration
{
public:
	static QString initialStyle;
	static QString initialStyleSheet;

	static QString initialImageBackground;
	static double initialImageZoom;

	static double initialToolSize;
	static QString initialToolColor;
	static int initialToolAlpha;
};

#endif // CONFIGURATION_H