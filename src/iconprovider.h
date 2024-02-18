#pragma once
#include <QtQuick>
#include <QQuickImageProvider>

class IconProvider : public QQuickImageProvider {
	Q_OBJECT
    public:
	explicit IconProvider(QQmlImageProviderBase::ImageType type,
			      QQmlImageProviderBase::Flags flags =
				      QQmlImageProviderBase::Flags());
	QPixmap requestPixmap(const QString &id, QSize *size,
			      const QSize &requestedSize);
};