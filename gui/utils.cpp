#include "utils.h"

namespace utils
{
	QString loadStyleSheet(QString resource_path)
	{
		QFile file(resource_path);
		if (!file.open(QFile::ReadOnly | QFile::Text))
		{
			return QString();
		}

		return QLatin1String(file.readAll());
	}
}  // namespace utils
