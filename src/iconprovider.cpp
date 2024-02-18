#include "iconprovider.h"

#include <QIcon>

IconProvider::IconProvider(QQmlImageProviderBase::ImageType type,
			   QQmlImageProviderBase::Flags flags)
	: QQuickImageProvider(type, flags)
{
}

QPixmap IconProvider::requestPixmap(const QString &id, QSize *size,
				    const QSize &requestedSize)
{
	if (!QIcon::hasThemeIcon(id) || id == "")
		return QPixmap();
	QIcon icon = QIcon::fromTheme(id);
	if (icon.isNull())
		return QPixmap();

	QSize pixmapSize = requestedSize.isValid() ? requestedSize :
						     QSize(512, 512);
	QPixmap pixmap = icon.pixmap(pixmapSize);
	*size = pixmap.size();
	return pixmap.scaled(pixmapSize);
}