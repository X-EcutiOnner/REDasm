#pragma once

#include <QColor>
#include <QIcon>
#include <redasm/redasm.h>

namespace theme_provider {

bool is_dark_theme();
QStringList themes();
QString theme(const QString& name);
QColor graph_bg();
QColor color(RDThemeKind kind);
QIcon icon(const QString& name);
void apply_theme();

} // namespace theme_provider
